#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <sstream>
#include <string>
#include <tuple>
#include "Slice.hpp"
#include "extra.hpp"

class Pizza {
public:

    Pizza(char** grid, int rows, int cols, int min_ingr, int max_cells);

    // Searches for a possible slice at the given position
    std::tuple<int, std::string> iterative_find();
    std::tuple<int, std::string> growing_iterative_find();
    std::tuple<int, std::string> shrinking_iterative_find();
    //std::tuple<int, std::string, int> recursive_best_find(std::tuple<int, std::string, int> tracker, int row, int col);

    // Check if slice is valid
    bool check(Slice* slice);
    // Remove the slice from grid
    void cut(Slice* slice);

    int get_area_covered();

    void append_slice(std::string* slice_list, Slice* slice);

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

    int area_covered;
    
};

#endif // PIZZA_H