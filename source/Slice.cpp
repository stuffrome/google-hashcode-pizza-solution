#include "Slice.hpp"

Slice::Slice(int row_pos, int col_pos, int row_len, int col_len)
{
    this->row_pos = row_pos;
    this->col_pos = col_pos;
    this->row_len = row_len;
    this->col_len = col_len;
}

void Slice::print()
{
    printf("%d %d %d %d\n", row_pos, col_pos, row_pos + (row_len - 1), col_pos + (col_len - 1));
}