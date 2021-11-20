#ifndef GENETIC_H
#define GENETIC_H


#include "loot.h"

#include <vector>


#define POPSIZE 2000
#define GENERATIONS 20
#define MUTATIONRATE 5.0f
#define ELITE 1 
#define DISPLAYSIZE 5


struct Organism
{
    int fitness;
    std::vector<int> genome; 
};

// comparator for sorting Organism 
bool cmp(const Organism &g1, const Organism &g2);


class DNA
{
    public:
        // population size, num generations, mutations rate in percentage, num organisms carried over 
        DNA(int pop, int gen, float mutate, int elite);

        // run genetic algoritm 
        Organism evolve(const std::vector<Loot> &items, int capacity);
    
        // display genome and fitness 
        void debugGenePool(const std::vector<Organism> &chromosomes);

        // display the first x genome and fitness 
        void displayGenePool(const std::vector<Organism> &chromosomes, int x);

    private:
        // population size of genepool
        int population;
        // number of generations genepool will evolve for
        int generations;
        // percent chance of mutation 
        float mutationrate;
        // top k organisms preserved for next generation
        int topk;
        // current genepool of organisms
        std::vector<Organism> genepool;
        // next generations genepool of organisms
        std::vector<Organism> nextgen;

        // generate population 
        void initPopulation(const std::vector<Loot> &items);

        // calculate the fitness of each organism 
        void fitnessFunction(const std::vector<Loot> &items, int capacity);

        // keep top k most fit organisms 
        void elitism(int k);

        // returns the genome of the most fit of the two organisms
        std::vector<int> battle(const Organism &c1, const Organism &c2); 

        // select 2 random organisms, have them battle, do that again 
        // the winners (the most fit) of each bracket will have up to 2 children 
        void tournamentSelection();

        // two point crossover 
        void crossover(std::vector<int> &parent1, std::vector<int> &parent2);

        // mutate genome
        void mutate();
};



#endif