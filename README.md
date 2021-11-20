# Genetic_Algorithm  
C++ Genetic Algorithm implementation to predict a solution for the 0/1 Knapsack problem 

Compares accuracy of Genetic Algorithm's prediction to the dynamic programming solution

## Approach:
1. Genome represented as vector of 0 or 1 values, 1 for include item, 0 for exclude item
2. Initialize random population 
3. Compute fitness of population
4. Preserve the top k organisms in the population (elitism)
5. Use tournament selection and 2 point crossover to produce next generation 
6. Mutate population at the given mutation rate 
7. Repeat steps 3 to 6 for the given number of Generations 

## References:  
https://www.youtube.com/watch?v=nhT56blfRpE  
https://www.youtube.com/watch?v=9zfeTw-uFCw&list=PLRqwX-V7Uu6bJM3VgzjNV5YxVxUwzALHV  
https://www.youtube.com/watch?v=MacVqujSXWE  
