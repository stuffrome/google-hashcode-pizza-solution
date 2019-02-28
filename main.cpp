#include <cstdio>
#include <iostream>

#include "include/Pizza.hpp"

int main()
{
    int rows = 0;
    int cols = 0;
    int min_ingr = 0;
    int max_cells = 0;
    
    std::scanf("%d %d %d %d", &rows, &cols, &min_ingr, &max_cells);

    // Create pizza grid
    char** pizza_grid = new char*[rows];
    for (int i = 0; i < rows; ++i)
    {
        pizza_grid[i] = new char[cols];
    }

    // Read in the pizza
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cin >> pizza_grid[i][j];        
        }
    }

    Pizza pizza(pizza_grid, rows, cols, min_ingr, max_cells);

    //std::tuple<int, std::string> results = pizza.iterative_find();
    //std::tuple<int, std::string> results = pizza.growing_iterative_find();
    //std::tuple<int, std::string> results = pizza.shrinking_iterative_find();

    std::tuple<int, std::string, int> tracker = std::make_tuple(0, "", 0);
    std::tuple<int, std::string, int> results = pizza.recursive_best_find(tracker, 0, 0, pizza_grid);

    std::cout << std::get<0>(results) << std::endl << std::get<1>(results);// << std::get<2>(results);


    //std::cout << pizza.get_area_covered() << std::endl;


    // Deallocation

    for (int i = 0; i < rows; ++i)
    {
        delete[] pizza_grid[i];
    }
    delete[] pizza_grid;

    return 0;
}