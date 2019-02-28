#include "extra.hpp"

std::vector<int> get_multiples(int n)
{
    std::vector<int> multiples;

    for (int i = 1; i <= n; ++i)
    {
        if (n % i == 0)
        {
            multiples.push_back(i);
        }
    }

    return multiples;
}

std::vector<std::tuple<int, int>> get_rectangles_within(int area)
{
    std::vector<std::tuple<int, int>> list;

    for (int i = 2; i <= area; ++i)
    {
        std::vector<int> dim = get_multiples(i);

        for (int m = 0; m < (dim.size() + 1) / 2; ++m)
        {
            int dim_a = dim[m];
            int dim_b = dim[dim.size() - (m + 1)];

            if (dim_a == dim_b)
            {
                list.push_back(std::make_tuple(dim_a, dim_b));
            }
            else
            {
                list.push_back(std::make_tuple(dim_a, dim_b));
                list.push_back(std::make_tuple(dim_b, dim_a));
            }    
        }
    }

    return list;
}