#ifndef SLICE_HPP
#define SLICE_HPP

#include <iostream>

class Slice {
public:

    Slice(int row_pos, int col_pos, int row_len, int col_len);

    void print();

    int row_pos;
    int col_pos;
    int row_len;
    int col_len;
};

#endif // SLICE_H