#include "genetic.h"

#include <iostream>
#include <random>
#include <algorithm>

// constructor 
DNA::DNA(int pop, int gen, float mutate, int elite)
{
    population = pop;
    generations = gen;
    mutationrate = mutate;
    topk = elite;
}


void DNA::debugGenePool(const std::vector<Organism> &chromosomes)
{
    std::cout << std::endl;

    // display genome and fitness 
    for (int a=0; a<chromosomes.size(); a++)
    {
        for (int b=0; b<chromosomes[a].genome.size(); b++)
        {
            std::cout << chromosomes[a].genome[b] << " ";
        }
        std::cout << "  fitness: " << chromosomes[a].fitness;
        std::cout << std::endl;
    }
}


void DNA::displayGenePool(const std::vector<Organism> &chromosomes, int x)
{
    if (x > chromosomes.size())
        throw "'DNA::displayGenePool' 'x' is larger than the chromosomes size";

    std::cout << std::endl;

    // display genome and fitness 
    for (int a=0; a<x; a++)
    {
        for (int b=0; b<chromosomes[a].genome.size(); b++)
        {
            std::cout << chromosomes[a].genome[b] << " ";
        }
        std::cout << "  fitness: " << chromosomes[a].fitness;
        std::cout << std::endl;
    }

}


void DNA::initPopulation(const std::vector<Loot> &items)
{
    std::random_device rd; // random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<> distr(0, 1); // range

    genepool.clear();

    for (int i=0; i<population; i++)
    {
        std::vector<int> creature;
        for (int j=0; j<items.size(); j++)
        {
            // pseudo random 0 or 1 number 
            creature.push_back(distr(gen));
        }
        // initial fitness of zero for creature 
        genepool.push_back({0, creature});
    }
}


bool cmp(const Organism &g1, const Organism &g2)
{
    // largest comes first 
    return g1.fitness > g2.fitness;
}


void DNA::fitnessFunction(const std::vector<Loot> &items, int capacity)
{
    if (genepool.size() == 0)
        throw "''DNA::fitnessFunction' genepool of size 0!";

    // zero out fitness from prev run 
    for (int k=0; k<genepool.size(); k++)
        genepool[k].fitness = 0;

    for (int i=0; i<genepool.size(); i++)
    {
        int weight = 0;
        for (int j=0; j<genepool[i].genome.size(); j++)
        {
            // try to insert item
            if (genepool[i].genome[j] == 1)
            {
                weight += items[j].weight;
                if (capacity >= weight)
                {
                    genepool[i].fitness += items[j].value;
                }
                else
                {
                    genepool[i].fitness = 0;
                    break; 
                }
            }
        }
    }

    std::sort(genepool.begin(), genepool.end(), cmp);
}


void DNA::elitism(int k)
{
    if (k > genepool.size())
        throw "'k' value in 'void DNA::elitism(int k)' exceeds genepool size!";

    if (genepool.size() == 0)
        throw "''void DNA::elitism(int k)' genepool of size 0!";

    for (int i=0; i<k; i++)
        nextgen.push_back(genepool[i]);
}



std::vector<int> DNA::battle(const Organism &c1, const Organism &c2)
{
    if (c1.fitness > c2.fitness)
        return c1.genome;
    else
        return c2.genome;
}


void DNA::tournamentSelection()
{
    if (genepool.size() == 0)
        throw "''void DNA::tournamentSelection()' genepool of size 0!";

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> contestant(0, genepool.size()-1); 

    std::vector<int> winner1 = DNA::battle(genepool[contestant(gen)], genepool[contestant(gen)]);
    std::vector<int> winner2 = DNA::battle(genepool[contestant(gen)], genepool[contestant(gen)]);

    DNA::crossover(winner1, winner2);
}


void DNA::crossover(std::vector<int> &parent1, std::vector<int> &parent2)
{
    std::random_device rd; // random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<> slice1(0, parent1.size()-1); 

    int p1 = slice1(gen);
    std::uniform_int_distribution<> slice2(p1, parent1.size()-1);
    int p2 = slice2(gen);
    std::vector<int> child1 = parent1;
    std::vector<int> child2 = parent2; 

    for (int i=p1; i<=p2; i++)
    {
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }

    if (nextgen.size() < population)
        nextgen.push_back({0, child1});
    if (nextgen.size() < population)
        nextgen.push_back({0, child2});
}


void DNA::mutate()
{
    if (genepool.size() == 0)
        throw "''void DNA::mutate()' genepool of size 0!";

    std::random_device rd; // random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_real_distribution<float> distr(0.0f, 100.0f); // range

    // what gene will be mutated 
    std::uniform_int_distribution<> genemutate(0, genepool[0].genome.size()-1);


    for (int i=0; i<genepool.size(); i++)
    {
        if (distr(gen) <= mutationrate)
        {
            // xor gene to toggle bit 
            genepool[i].genome[genemutate(gen)] ^= 1;
        }
    }
}


Organism DNA::evolve(const std::vector<Loot> &items, int capacity)
{

    // generate initial population 
    DNA::initPopulation(items);

    // calculate fitness of initial population 
    DNA::fitnessFunction(items, capacity);

    // save 0th generation to display later 
    std::vector<Organism> gen0 = genepool;

    // apply genetic algo for specified 'generations'
    for (int i=0; i<generations; i++)
    {
        DNA::elitism(topk);
        while (nextgen.size() < population)
        {
            DNA::tournamentSelection();
        }

        // move the next generation created from DNA::tournamentSelection() into the genepool 
        // clear 'nextgen' for the coming iteration
        genepool = nextgen;
        nextgen.clear();

        // don't mutate last generation  
        if (i < generations-1)
        {
            // mutate population 
            DNA::mutate();
        }
        DNA::fitnessFunction(items, capacity);
    }

    std::cout << "Knapsack capacity: " << capacity; 
    std::cout << std::endl << "Population: " << population << ", Mutation Rate: " << mutationrate << "%"; 
    std::cout << ", Top " << DISPLAYSIZE << " most fit";
    std::cout  << std::endl << "Generation 0: ";
    DNA::displayGenePool(gen0, DISPLAYSIZE);

    std::cout << std::endl << "Generation " << generations << ": ";
    DNA::displayGenePool(genepool, DISPLAYSIZE);
    std::cout  << std::endl;

    return genepool[0];
}