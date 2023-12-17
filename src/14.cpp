#include "14.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"
#include "char_grid.hpp"

struct coordinate {
   int x;
   int y;
   bool movable;
};

bool operator==(const coordinate a, const coordinate b)
{
   return (a.x == b.x && a.y == b.y);
}

bool operator!=(const coordinate a, const coordinate b)
{
   return (a.x != b.x || a.y != b.y);
}

string to_key(array<coordinate> *stones)
{
    string ret = ""_s;

    string tmp;
    for_array(s, stones)
    {
        init(&tmp);
        format(&tmp, "%|%|%", s->x, s->y, s->movable);
        append_string(&ret, &tmp);
    }
    
    free(&tmp);
    return ret;
}


void get_round_stones(char_grid *grid, array<coordinate> *stones, array<int> *cache)
{
    array<int> c;
    init(&c, grid->rows.size * grid->columns.size);

    for (int y = 0; y < grid->rows.size; y++)
        for (int x = 0; x < grid->columns.size; x++)
        {
            c[y*grid->col_num + x] = 0;
            char_grid g = *grid;
            if (g[y][x] == 'O')
            {
                coordinate temp = { .x = x, .y = y, .movable = true };
                add_at_end(stones, temp);
                c[y*grid->col_num + x] = 1;
            }

            if (g[y][x] == '#')
            {
                coordinate temp = { .x = x, .y = y, .movable = false };
                add_at_end(stones, temp);
                c[y*grid->col_num+ x] = 1;
            }
        }

    *cache = c;
}

bool stone_at_coordinate(array<coordinate> *stones, coordinate c)
{
    for_array(s, stones)
        if (*s == c)
            return true;

    return false;
}

int move(char_grid *grid, array<coordinate> *stones, int direction, array<int> *cache)
{
    char_grid g = *grid;

    array<int> c = *cache;

    for_array(s, stones)
    {
        if (!s->movable)
            continue;
        
        coordinate nc = { .x = s->x, .y = s->y };

        int mx = nc.x;
        int my = nc.y;

        c[my * grid->col_num + mx] = 0;

        while(true)
        {
            mx = nc.x;
            my = nc.y;

            if (direction == 0)
                nc.y = nc.y-1;
            if (direction == 1)
                nc.x = nc.x-1;
            if (direction == 2)
                nc.y = nc.y+1;
            if (direction == 3)
                nc.x = nc.x+1;

            if (nc.x < 0 || nc.y < 0 || nc.x >= grid->columns.size || nc.y >= grid->rows.size)
                break;

            int x = c[nc.y * grid->col_num + nc.x];

            if (x == 1)
                break;
        }

        s->y = my;
        s->x = mx;
        
        c[my * grid->col_num + mx] = 1;
    }

    *cache = c;
    return 0;
}

int sort_north(const coordinate *a, const coordinate *b)
{
    if (a->y > b->y) return 1;
    if (a->y < b->y) return -1;
    return 0;
}

int sort_south(const coordinate *a, const coordinate *b)
{
    if (a->y < b->y) return 1;
    if (a->y > b->y) return -1;
    return 0;
}

int sort_west(const coordinate *a, const coordinate *b)
{
    if (a->x > b->x) return 1;
    if (a->x < b->x) return -1;
    return 0;
}

int sort_east(const coordinate *a, const coordinate *b)
{
    if (a->x < b->x) return 1;
    if (a->x > b->x) return -1;
    return 0;
}

int sort_asc(const coordinate *a, const coordinate *b)
{
    if (a->x > b->x) return 1;
    if (a->x < b->x) return -1;
    if (a->y > b->y) return 1;
    if (a->y < b->y) return -1;
    return 0;
}

int aoc_14_1(const_string s_input) 
{
    char_grid grid;
    init(&grid);
    parse_grid(s_input, &grid);
   
    array<coordinate> stones = {};
    array<int> cache;
    get_round_stones(&grid, &stones, &cache);

    move(&grid, &stones, 0, &cache);

    int sum = 0;
    for_array(s, &stones)
    {
        if (!s->movable)
            continue;

        sum += 1 * grid.row_num - s->y;
    }

    tprint("%\n", sum);

    return 0;
}

int aoc_14_2(const_string s_input) 
{
    char_grid grid;
    init(&grid);
    parse_grid(s_input, &grid);
   
    array<coordinate> stones = {};
    array<int> cache;
    get_round_stones(&grid, &stones, &cache);

    hash_table<string, int> seen = {};
    array<int> result = {};

    for (long c = 0; c < 1000000000; c++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
                sort(stones.data, stones.size, sort_north);
            if (i == 1)
                sort(stones.data, stones.size, sort_west);
            if (i == 2)
                sort(stones.data, stones.size, sort_south);
            if (i == 3)
                sort(stones.data, stones.size, sort_east);

            int moved = move(&grid, &stones, i, &cache);
        }

       sort(stones.data, stones.size, sort_asc);

        int sum = 0;

        for_array(s, &stones)
        {
            if (!s->movable)
                continue;

            sum += 1 * grid.row_num - s->y;
        }

        add_at_end(&result, sum);

       string key = to_key(&stones);
       if (contains(&seen, &key))
       {
           int period = c - seen[key];
           int diff = (1000000000 - 1) - seen[key];
           int to_calculate = seen[key] + (diff % period);
           tprint("%\n", result[to_calculate]);
           break;
       }

       seen[key] = c;
       continue;
    }


    return 0;
}

