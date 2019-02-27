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