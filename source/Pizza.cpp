#include "Pizza.hpp"

Pizza::Pizza(char** grid, int rows, int cols, int min_ingr, int max_cells) :
ROWS(rows),
COLUMNS(cols),
MIN_INGREDIENTS(min_ingr),
MAX_CELLS(max_cells)
{
    this->grid = grid;
    area_covered = 0;
}

std::tuple<int, std::string> Pizza::iterative_find()
{
    int slice_count = 0;
    std::string slice_list = "";

    // Get all mulitples of max cells
    std::vector<int> slice_dim = get_multiples(MAX_CELLS);
    int slice_dim_size = slice_dim.size();

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLUMNS; ++c)
        {
            for (int m = 0; m < (slice_dim_size + 1) / 2; ++m)
            {
                int dim_a = slice_dim[m];
                int dim_b = slice_dim[slice_dim_size - (m + 1)];

                // Square m x m
                if (dim_a == dim_b)
                {
                    Slice slice(r, c, dim_a, dim_a);

                    if (check(&slice))
                    {
                        cut(&slice);
                        
                        ++slice_count;
                        append_slice(&slice_list, &slice);
                    }
                }
                else
                {
                    Slice slice1(r, c, dim_a, dim_b);
                    Slice slice2(r, c, dim_b, dim_a);

                    if (check(&slice1))
                    {
                        cut(&slice1);

                        ++slice_count;
                        append_slice(&slice_list, &slice1);
                    }
                    else if (check(&slice2))
                    {
                        cut(&slice2);

                        ++slice_count;
                        append_slice(&slice_list, &slice2);
                    }
                }  
            }
        }
    }

    return std::make_tuple(slice_count, slice_list);
}

std::tuple<int, std::string> Pizza::growing_iterative_find()
{
    int slice_count = 0;
    std::string slice_list = "";

    // Get all possible slice rectangles
    std::vector<std::tuple<int, int>> slice_rect_list = get_rectangles_within(MAX_CELLS);
    int slice_rect_list_size = slice_rect_list.size();

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLUMNS; ++c)
        {
            for (int rect = 0; rect < slice_rect_list_size; ++rect)
            {
                int dim_a = std::get<0>(slice_rect_list[rect]);
                int dim_b = std::get<1>(slice_rect_list[rect]);

                Slice slice(r, c, dim_a, dim_a);

                if (check(&slice))
                {
                    cut(&slice);
                    
                    ++slice_count;
                    append_slice(&slice_list, &slice);
                }
            }
        }
    }

    return std::make_tuple(slice_count, slice_list);
}

std::tuple<int, std::string> Pizza::shrinking_iterative_find()
{
    int slice_count = 0;
    std::string slice_list = "";

    // Get all possible slice rectangles
    std::vector<std::tuple<int, int>> slice_rect_list = get_rectangles_within(MAX_CELLS);
    int slice_rect_list_size = slice_rect_list.size();

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLUMNS; ++c)
        {
            for (int rect = slice_rect_list_size - 1; rect >= 0; --rect)
            {
                int dim_a = std::get<0>(slice_rect_list[rect]);
                int dim_b = std::get<1>(slice_rect_list[rect]);

                Slice slice(r, c, dim_a, dim_a);

                if (check(&slice))
                {
                    cut(&slice);
                    
                    ++slice_count;
                    append_slice(&slice_list, &slice);
                }
            }
        }
    }

    return std::make_tuple(slice_count, slice_list);
}

// std::tuple<int, std::string, int> Pizza::recursive_best_find(std::tuple<int, std::string, int> tracker, int row, int col, )
// {
//     if (row >= ROWS || col >= COLUMNS)
//     {
//         return tracker;
//     }
//     else if (grid[row][col] == CUT_OUT)
//     {
//         if (col < COLUMNS - 1)
//         {
//             return recursive_best_find(tracker, row, ++col);
//         }
        
//         return recursive_best_find(tracker, ++row, 0);
//     }

//     std::vector<std::tuple<int, std::string, int>> possible_slices;

//     // Get all possible slice rectangles
//     std::vector<std::tuple<int, int>> slice_rect_list = get_rectangles_within(MAX_CELLS);
//     int slice_rect_list_size = slice_rect_list.size();

//     for (int rect = 0; rect < slice_rect_list_size; ++rect)
//     {
//         int dim_a = std::get<0>(slice_rect_list[rect]);
//         int dim_b = std::get<1>(slice_rect_list[rect]);

//         Slice slice(row, col, dim_a, dim_a);

//         if (check(&slice))
//         {
//             std::stringstream ss;

//             ss << slice.row_pos << ' '
//             << slice.col_pos << ' '
//             << slice.row_pos + (slice.row_len - 1) << ' '
//             << slice.col_pos + (slice.col_len - 1) << ' '
//             << '\n';

//             std::string slice_str = ss.str();

//             if (col < COLUMNS - 1)
//             {
//                 std::tuple<int, std::string, int> next_slice = recursive_best_find(tracker, row, ++col);
//                 possible_slices.push_back(std::make_tuple(std::get<0>(next_slice) + 1,
//                                                           slice_str + std::get<1>(next_slice),
//                                                           slice.row_len * slice.col_len + std::get<2>(next_slice)));
//             }
            
//             std::tuple<int, std::string, int> next_slice = recursive_best_find(tracker, ++row, 0);
//                 possible_slices.push_back(std::make_tuple(std::get<0>(next_slice) + 1,
//                                                           slice_str + std::get<1>(next_slice),
//                                                           slice.row_len * slice.col_len + std::get<2>(next_slice)));
//         }
//     }

//     std::tuple<int, std::string, int> best_slice = possible_slices[0];

//     for (int i = 1; i < possible_slices.size(); ++i)
//     {
//         if (std::get<2>(possible_slices[i]) > std::get<2>(best_slice))
//         {
//             best_slice = possible_slices[i];
//         }
//     }

//     return best_slice;
// }

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
            ++area_covered;

            grid[r][c] = 'C';
        }
    }
}

int Pizza::get_area_covered()
{
    return area_covered;
}

void Pizza::append_slice(std::string* slice_list, Slice* slice)
{
    std::stringstream ss;

    ss << slice->row_pos << ' '
       << slice->col_pos << ' '
       << slice->row_pos + (slice->row_len - 1) << ' '
       << slice->col_pos + (slice->col_len - 1) << ' '
       << '\n';

    slice_list->append(ss.str());
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