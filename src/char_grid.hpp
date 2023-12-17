#include "shl/string.hpp"
#include "shl/array.hpp"

struct char_grid {
    int row_num;
    int col_num;
    array<const_string> rows;
    array<const_string> columns;
    
          const_string &operator[](u64 index)       { return rows[index]; }
    const const_string &operator[](u64 index) const { return rows[index]; }
};

void init(char_grid *grid);
void print_grid(char_grid *grid);
void parse_grid(const_string s_input, char_grid *grid);
