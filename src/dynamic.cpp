#include "dynamic.h"


int Knapsack::solveBotUp(std::vector<Loot> &items, int capacity)
{
    if (items.size() == 0 || capacity <= 0)
        throw "'Knapsack::solveBotUp' invalid input!";

    int row = items.size();
    // rows represent items, cols represent capacity 
    // init all values in vector to zero
    std::vector<std::vector<int>> dp(row, std::vector<int>(capacity+1,0));

    // init first row, place first item in cell if it does not exceed capacity
    for (int k=0; k<capacity; k++)
    {
        if (k >= items[0].weight)
            dp[0][k] = items[0].value;
    }

    // first row and first col already zero
    for (int i=1; i<row; i++)
    {
        for (int c=1; c<capacity+1; c++)
        {
            int p1 = 0;
            int p2 = 0; 

            // include item, profit = items value + max value without item
            if (c >= items[i].weight)
                p1 = items[i].value + dp[i-1][c-items[i].weight];
            
            // exclude item, one row up, profit = max value without cur item 
            p2 = dp[i-1][c];

            // take max profit
            dp[i][c] = std::max(p1, p2);
        }
    }

    Knapsack::printGenome(items, capacity, dp);
    return dp[row-1][capacity];
}


void Knapsack::printGenome(std::vector<Loot> &items, int capacity, std::vector<std::vector<int>> &dp)
{
    std::vector<int> gene(items.size()-1, 0); 
    std::vector<int> selected;
    int totvalue = dp[items.size()-1][capacity];

    for (int i=items.size()-1; i>0; i--)
    {
        // if cell is not equal to cell the row above then item was selected 
        if (totvalue != dp[i-1][capacity])
        {
            totvalue -= items[i].value;
            capacity -= items[i].weight;
            selected.push_back(i);
        }
    }

    if (totvalue != 0)
        selected.push_back(0);

    for (int j=0; j<selected.size(); j++)
        gene[selected[j]] = 1; 

    for (int k=0; k<items.size(); k++)
        std::cout << gene[k] << " ";

    std::cout << "  fitness: ";
}



int Knapsack::solveMemo(std::vector<Loot> &items, int capacity)
{
    if (items.size() == 0 || capacity <= 0)
        throw "'Knapsack::solveMemo' invalid input!";

    int row = items.size();
    // rows represent items, cols represent capacity 
    // init all values in vector to -1
    std::vector<std::vector<int>> memo(row, std::vector<int>(capacity+1, -1));

    return Knapsack::dfs(items, capacity, 0, memo);
}


int Knapsack::dfs(std::vector<Loot> &items, int capacity, int indx, std::vector<std::vector<int>> &dp)
{
    // base case 
    if (indx >= items.size() || capacity <= 0)
      return 0;

    // return cached val
    if (dp[indx][capacity] != -1)
      return dp[indx][capacity];

    int p1 = 0;
    int p2 = 0; 
    if (capacity >= items[indx].weight)
    {
      // include item 
      p1 = items[indx].value + Knapsack::dfs(items, capacity-items[indx].weight, indx+1, dp);
    }

    // exclude item (too heavy or save capacity for another item)
    p2 = Knapsack::dfs(items, capacity, indx+1, dp);
    dp[indx][capacity] = std::max(p1, p2);
    return dp[indx][capacity];
}