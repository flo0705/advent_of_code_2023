#include "shl/array.hpp";
#include "shl/string.hpp";
#include "shl/print.hpp";
#include "char_grid.hpp";

void init(char_grid *grid)
{
    assert(grid != nullptr);

    grid->rows = {};
    grid->columns = {};
    grid->row_num= 0;
    grid->col_num= 0;
}	

void print_grid(char_grid *grid)
{
    for_array(s, &grid->rows)
        tprint("%\n", *s);
}

void parse_grid(const_string s_input, char_grid *grid)
{
    array<const_string> lines = {};
    split(s_input, '\n', &lines);

    array<const_string> cols = {};
   	
    int ls = 0;
    for(int j = 0; j < lines[0].size; j++)
    {
        string temp = ""_s;
        for_array(i, l, &lines)
        {
            if (l->size < 2)
                break;

            string sub = ""_s;
            substring(*l, j, 1, &sub);
            append_string(&temp, sub);
            free(&sub);
        }
        
        add_at_end(&cols, to_const_string(&temp));
    }

    grid->rows = lines;
    grid->columns = cols;
    grid->row_num = lines.size;
    grid->col_num = cols.size;
    return;
}
