#include "dynamic.h"
#include "genetic.h"

#include <iostream>
#include <thread>


void testGeneticAlgo(int p, int g, float m, int e, std::vector<Loot> goods, int capacity);


using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main()
{
    typedef std::chrono::high_resolution_clock clock;
    auto start = clock::now();

    std::vector<Loot> items1 = {{1,1},{6,2},{10,3},{16,5},
                                {89,34},{10,2},{62,21},{27,9},
                                {69,10},{100,35},{12,1},{47,20},
                                {9,1},{8,2},{7,3},{10,3},{15,5},
                                {18,3},{67,30},{18,5},{12,5},
                                {17,2},{26,6},{21,8},{23,4}}; 

    std::vector<Loot> items2 = {{1,1},{6,2},{10,3},{16,5},
                                {89,34},{10,2},{62,21},{27,9},
                                {69,10},{100,35},{12,1},{47,20},
                                {9,1},{8,2},{7,3},{10,3},{15,5},
                                {18,3},{67,30},{18,5},{12,5},
                                {17,2},{26,6},{21,8},{23,4},
                                {54,6},{587,42},{17,3},{19,4},
                                {893,343},{102,22},{6,2},{26,7},
                                {6,1},{10,1},{80,24},{723,91},
                                {1,9},{8,6},{8,2},{6,1},{34,2},
                                {12,6},{67,34},{14,2},{19,4},
                                {60,8},{154,46},{123,67},{24,5}}; 


    std::thread t1 (testGeneticAlgo, POPSIZE, GENERATIONS, MUTATIONRATE, ELITE, items1, 167);
    std::thread t2 (testGeneticAlgo, POPSIZE, GENERATIONS, MUTATIONRATE, ELITE, items2, 234);
    std::thread t3 (testGeneticAlgo, POPSIZE, GENERATIONS, MUTATIONRATE, ELITE, items2, 299);
    t1.join();
    t2.join();
    t3.join();

    auto end = clock::now();
    std::cout << std::endl << "Run time: " << duration_cast<milliseconds>(end-start).count()/1000.0f << "s" << std::endl;

    return 0;
}


void testGeneticAlgo(int p, int g, float m, int e, std::vector<Loot> goods, int capacity)
{

    try
    {
        // genetic algo 
        DNA geneticmaterial(p, g, m, e);
        Organism mostfit = geneticmaterial.evolve(goods, capacity);
        int predictedvalue = mostfit.fitness;

        // dynamic programming 
        Knapsack bag; 
        std::cout << "Dynamic Programming solution and genome representation:" << std::endl;
        int actualvalue = bag.solveBotUp(goods, capacity);
        std::cout << actualvalue << std::endl;

        // genetic algo 
        std::cout << std::endl << "Genetic Algorithm prediction and genome representation:" << std::endl;
        for (int i=0; i<mostfit.genome.size(); i++)
            std::cout << mostfit.genome[i] << " ";
        std::cout << "  fitness: " << mostfit.fitness << std::endl << std::endl;

        float percenterror = static_cast<float>((actualvalue - predictedvalue))/static_cast<float>(actualvalue) * 100.0f;
        std::cout <<  "Dynamic programming's max Value: " << bag.solveMemo(goods, capacity) << std::endl;
        std::cout <<  "Genetic algorithm's predicted Value: " << predictedvalue << std::endl;
        std::cout <<  "Percent Error: " << percenterror << "%" << std::endl;
        std::cout << "-----------------------------------------" << std::endl << std::endl;
    }

    catch(const char* error)
    {
        std::cout << std::endl << "ERROR: " << error << std::endl;
    }

}