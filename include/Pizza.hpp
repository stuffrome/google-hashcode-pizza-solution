#ifndef PIZZA_HPP
#define PIZZA_HPP

#include "Slice.hpp"
#include "extra.hpp"

class Pizza {
public:

    Pizza(char** grid, int rows, int cols, int min_ingr, int max_cells);

    // Searches for a possible slice at the given position
    void find_slice_at(int row, int col);
    // Check if slice is valid
    bool check(Slice* slice);
    // Remove the slice from grid
    void cut(Slice* slice);

    int get_slices_found();

    /* --- DEBUGGING --- */
    
    // Output slice
    void print(Slice* slice);
    // Output grid
    void print_grid();


private:

    const char TOMATO = 'T';
    const char MUSHROOM = 'M';
    const char CUT_OUT = 'C';

    const int ROWS;
    const int COLUMNS;
    const int MIN_INGREDIENTS;
    const int MAX_CELLS;

    char** grid;

    int slices_found;
    
};

#endif // PIZZA_H