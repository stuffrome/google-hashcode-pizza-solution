#include "Pizza.hpp"

Pizza::Pizza(char** grid, int rows, int cols, int min_ingr, int max_cells) :
ROWS(rows),
COLUMNS(cols),
MIN_INGREDIENTS(min_ingr),
MAX_CELLS(max_cells)
{
    this->grid = grid;
    slices_found = 0;
}

void Pizza::find_slice_at(int row, int col)
{
    // Get all mulitples of max cells
    std::vector<int> slice_dim = get_multiples(MAX_CELLS);
    int slice_dim_size = slice_dim.size();

    for (int m = 0; m < (slice_dim_size + 1) / 2; ++m)
    {
        int dim_a = slice_dim[m];
        int dim_b = slice_dim[slice_dim_size - (m + 1)];

        // Square m x m
        if (dim_a == dim_b)
        {
            Slice slice(row, col, dim_a, dim_a);

            if (check(&slice))
            {
                ++slices_found;
                cut(&slice);
                print(&slice);
                //print_grid();
            }
        }
        else
        {
            Slice slice1(row, col, dim_a, dim_b);
            Slice slice2(row, col, dim_b, dim_a);

            if (check(&slice1))
            {
                ++slices_found;
                cut(&slice1);
                print(&slice1);
                //print_grid();
            }
            else if (check(&slice2))
            {
                ++slices_found;
                cut(&slice2);
                print(&slice2);
                //print_grid();
            }
        }  
    }
}

bool Pizza::check(Slice* slice)
{
    int m_cnt = 0;
    int t_cnt = 0;
    bool valid = false;

    if (slice->row_pos + slice->row_len <= ROWS && slice->col_pos + slice->col_len <= COLUMNS)
    {
        for (int r = slice->row_pos; r < slice->row_pos + slice->row_len; ++r)
        {
            for (int c = slice->col_pos; c < slice->col_pos + slice->col_len; ++c)
            {
                if (grid[r][c] == MUSHROOM)
                {
                    ++m_cnt;
                }
                else if (grid[r][c] == TOMATO)
                {
                    ++t_cnt;
                }
                else // Cut out
                {
                    return false;
                }
                
            }
        }
    }
    

    if (m_cnt >= MIN_INGREDIENTS && t_cnt >= MIN_INGREDIENTS)
    {
        valid = true;
    }

    return valid;
}

void Pizza::cut(Slice* slice)
{
    for (int r = slice->row_pos; r < slice->row_pos + slice->row_len; ++r)
    {
        for (int c = slice->col_pos; c < slice->col_pos + slice->col_len; ++c)
        {
            grid[r][c] = 'C';
        }
    }
}

int Pizza::get_slices_found()
{
    return slices_found;
}

/* --- DEBUGGING --- */

void Pizza::print(Slice* slice)
{
    printf("%d %d %d %d\n", slice->row_pos,
                            slice->col_pos,
                            slice->row_pos + (slice->row_len - 1),
                            slice->col_pos + (slice->col_len - 1));
}

void Pizza::print_grid()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}