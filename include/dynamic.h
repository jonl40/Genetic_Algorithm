#ifndef DYNAMIC_H
#define DYNAMIC_H


#include "loot.h"

#include <iostream>
#include <vector>


class Knapsack
{
    public:
        // bottom up dynamic programming solution 
        int solveBotUp(std::vector<Loot> &items, int capacity);

        // memoization dynamic programming solution 
        int solveMemo(std::vector<Loot> &items, int capacity);

    private:

        // used in solveBotup
        void printGenome(std::vector<Loot> &items, int capacity, std::vector<std::vector<int>> &dp); 

        // used in solveMemo 
        int dfs(std::vector<Loot> &items, int capacity, int indx, std::vector<std::vector<int>> &dp);

};


#endif