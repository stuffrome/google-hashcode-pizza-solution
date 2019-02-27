#include <cstdio>
#include <iostream>

#include "include/Pizza.hpp"

using std::cin;
using std::cout;

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
            cin >> pizza_grid[i][j];
        }
    }

    Pizza pizza(pizza_grid, rows, cols, min_ingr, max_cells);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            pizza.find_slice_at(i, j);
        }
    }

    std::cout << pizza.get_slices_found() << std::endl;

    return 0;
}