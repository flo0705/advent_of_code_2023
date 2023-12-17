#include "13.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"
#include "char_grid.hpp"

void parse_inputs(const_string s_input, array<char_grid> *array_grid)
{
    array<const_string> grids = {};
    split(s_input, "\n\n", &grids);

    for_array(i, l, &grids)
    {
        if (l->size < 2)
            break;
       
        char_grid grid;
        parse_grid(*l, &grid);
        add_at_end(array_grid, grid);
    }
   
    return;
}

int get_char_diff(const_string a, const_string b)
{
    int diff = 0;

    if (a.size != b.size)
    {
        tprint("% - %\n", a.size, b.size);
        return 10;
    }

    for (int i = 0; i < a.size; i++)
    {
        if (a[i] != b[i])
            diff++;
    }

    return diff;
}

int find_num_mirrored(char_grid *grid)
{
    char_grid g = *grid;
   
    bool smudge_found = false;
    int num_hor = 0;

    for (int i = 0; i < g.row_num - 1; i++)
    {
        int diff = get_char_diff(g.rows[i], g.rows[i+1]);

        if (diff > 1)
            continue;


        if (diff == 1)
            smudge_found = true;
        
        if (i == 0 || i + 1 == g.row_num - 1)
        {
            if (!smudge_found)
                continue;

            num_hor = i + 1;
            break;
        }

        for (int j = 1; j <= i; j++)
        {
            diff = get_char_diff(g.rows[i-j], g.rows[i+j+1]);
            if (diff > 1)
                break;

            if (diff == 1 && smudge_found)
                break;

            if (diff == 1)
                smudge_found = true;

            if (i - j > 0 && i + j + 1 < g.row_num - 1 )
                continue; 

            if (smudge_found && num_hor < i + 1)
                num_hor = i + 1;

            break;
        }

        smudge_found = false;
    }

    smudge_found = false;
    int num_ver = 0;
    for (int i = 0; i < g.col_num - 1; i++)
    {
        int diff = get_char_diff(g.columns[i], g.columns[i+1]);
        if (diff > 1)
            continue;

        if (diff == 1)
            smudge_found = true;

        if (i == 0 || i + 1 == g.col_num - 1)
        {
            if (!smudge_found)
                continue;

            num_ver = i + 1;
            break;
        }

        for (int j = 1; j <= i; j++)
        {
            diff = get_char_diff(g.columns[i-j], g.columns[i+j+1]);
            if (diff > 1)
                break;

            if (diff == 1 && smudge_found)
                break;

            if (diff == 1)
                smudge_found = true;

            if (i - j > 0 && i + j + 1< g.col_num - 1 )
                continue; 
            
            if (smudge_found && num_ver < i + 1)
                num_ver = i + 1;

            break;
        }

        smudge_found = false;
    }

    return num_ver + 100 * num_hor;
}

int aoc_13_1(const_string s_input) 
{
    array<char_grid> arr_g = {};
    parse_inputs(s_input, &arr_g);

    int sum = 0;
    for_array(i, g, &arr_g)
    {
        char_grid gg = *g;
        int c = find_num_mirrored(g);

        if (c == 0)
        {
            print_grid(g);
            tprint("%\n\n", c);
        }

        sum += c;
    }

    tprint("%\n", sum);
    return 0;
}

int aoc_13_2(const_string s_input) 
{
    return 0;
}

