#include "10.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"

struct wall {
    int x;
    int y;
    char c;
};

void parse_inputs(const_string s_input, array<const_string> *inp)
{
    array<const_string> lines {};
    split(s_input, '\n', &lines);
    
    array<const_string> filtered {};

    for_array(l, &lines)
    {
		if (l->size == 0)
			continue;

		add_at_end(&filtered, *l);
    }

    *inp = filtered; 
    return;
}

void find_s(array<const_string> *maze, int *x, int *y)
{
	for_array(j, m, maze)
	{
		for (int i = 0; i < m->size; i++)
		{
			const_string temp = *m;
			if (temp[i] == 'S')
			{
				*x = i;
				*y = j;
				return;
			}
		}
	}
}

int get_max_distance(array<const_string> *maze, int x, int y, array<wall> *loop)
{
    fixed_array<int, 2> s = { x, y };
    fixed_array<int, 2> south = { x, y + 1 };

	x = south[0];
	y = south[1];

	char start = maze->data[y][x];

    wall temp = {.x = x, .y = y, .c = start };
	add_at_end(loop, temp);

	int dir_x = -1;
	int dir_y = 1;
	bool last_horizontal = false;
	
	int i = 0;
	while ((start = maze->data[y][x]) != 'S')
	{
		i++;
        temp = {.x = x, .y = y, .c = start };
		add_at_end(loop, temp);

		if (start == '|')
		{
			y+= dir_y;
			last_horizontal = false;
			continue;
        }

		if (start == '-')
		{
			x+= dir_x;
			last_horizontal = true;
			continue;
		}

		if (!last_horizontal && (start == 'F' || start == 'L'))
		{
			dir_x = 1;
			x+= dir_x;
			last_horizontal = true;
			continue;
		}

		if (last_horizontal && start == 'F')
		{
			dir_y = 1;
			y+= dir_y;
			last_horizontal = false;
			continue;
		}

		if (last_horizontal && start == 'L')
		{
			dir_y = -1;
			y+= dir_y;
			last_horizontal = false;
			continue;
		}

		if (!last_horizontal && (start == 'J' || start == '7'))
		{
			dir_x = -1;
			x+= dir_x;
			last_horizontal = true;
			continue;
		}

		if (last_horizontal && start == 'J')
		{
			dir_y = -1;
			y += dir_y;
			last_horizontal = false;
			continue;
		}

		if (last_horizontal && start == '7')
		{
			dir_y = 1;
			y += dir_y;
			last_horizontal = false;
			continue;
		}
	}

	if (2 % i != 0)
		return i/2 + 1;

	return i/2;
}

bool check_if_wall(int x, int y, array<wall> *loop)
{
	for_array(v, loop)
	{
		auto vv = *v;
		if (vv.x == x && vv.y == y)
			return true;
	}

	return false;
}

void flood(wall w, hash_table<string, wall> *seen)
{

    array<wall> to_check = {};
    add_at_end(&to_check, w);
    hash_table<string, wall> t_seen = *seen;
   
    int i = 0;

    while (to_check.size != 0)
    {
        if (i++ == 20)
            break;

        wall temp = to_check.data[to_check.size - 1];

        string temp_s = ""_s;
        format(&temp_s, "%-|-%", temp.x, temp.y);
        t_seen[temp_s] = temp; 
       
        remove_from_end(&to_check);

        wall north = {.x = temp.x, .y = temp.y - 1, .c = temp.c};
        format(&temp_s, "%-|-%", north.x, north.y);

        if (!contains(seen, &temp_s))
        {
            add_at_end(&to_check, north);
            t_seen[temp_s] = north; 
        }

        wall south = {.x = temp.x, .y = temp.y + 1, .c = temp.c};
        format(&temp_s, "%-|-%", south.x, south.y);

        if (!contains(seen, &temp_s))
        {
            add_at_end(&to_check, south);
            t_seen[temp_s] = south; 
        }

        wall east = {.x = temp.x + 1, .y = temp.y, .c = temp.c};
        format(&temp_s, "%-|-%", east.x, east.y);

        if (!contains(seen, &temp_s))
        {
            add_at_end(&to_check, east);
            t_seen[temp_s] = east; 
        }

        wall west = {.x = temp.x - 1, .y = temp.y, .c = temp.c};
        format(&temp_s, "%-|-%", west.x, west.y);

        if (!contains(seen, &temp_s))
        {
            add_at_end(&to_check, west);
            t_seen[temp_s] = west; 
        }

        tprint("%\n", to_check.size);
    }
    
    tprint("\n");
}

int count_tiles_within(array<const_string> *maze, array<wall> *loop)
{
	int c = 0;
    
    array<wall> left = {};
    array<wall> right = {};

    int left_dir = -1;
    int right_dir = 1;
    bool last_horizontal = false;

    wall last = loop->data[loop->size -1];
	for_array(i, v, loop)
	{
        wall w = *v;

        int dirr_x = w.x - last.x;
        int dirr_y = w.y - last.y;
        last = w;
        wall next = loop->data[i & loop->size];

        char direction = ' ';
        if (dirr_x == -1)
            direction = 'W';
        if (dirr_x == 1)
            direction = 'O';
        if (dirr_y == -1)
            direction = 'N';
        if (dirr_y == 1)
            direction = 'S';

        if (direction == 'S' || direction == 'W')
        {
            left_dir = -1;
            right_dir = 1;
        }

        if (direction == 'O' || direction == 'N')
        {
            left_dir = 1;
            right_dir = -1;
        }

        if (direction == 'N' || direction == 'S')
        {
            wall l = { .x = w.x + left_dir, .y = w.y, .c = w.c };
            wall r = { .x = w.x + right_dir, .y = w.y, .c = w.c };

            if (next.x != l.x || next.y != l.y) 
                add_at_end(&left, l);

            if (next.x != r.x || next.y != r.y) 
                add_at_end(&right, r);

            continue;
        }

        if (direction == 'O' || direction == 'W')
        {
            wall l = { .x = w.x, .y = w.y + left_dir, .c = w.c };
            wall r = { .x = w.x, .y = w.y + right_dir, .c = w.c };

            if (next.x != l.x || next.y != l.y) 
                add_at_end(&left, l);

            if (next.x != r.x || next.y != r.y) 
                add_at_end(&right, r);

            continue;
        }
	}
 
    array<wall> inner = left;
    if (left.size < right.size)
        inner = right;

    array<wall> filtered = {};
    hash_table<string, wall> seen = {};

    for_array(w, &inner)
    {
        if (check_if_wall(w->x, w->y, loop))
            continue;

        bool already_in = false;
        for_array(af, &filtered)
        {
            if (af->x != w->x || af->y != w->y)
                continue;

            already_in = true;
            break;
        }
        
        if (already_in)
            continue;
        
        add_at_end(&filtered, *w);
    }

    for_array(l, loop)
    {
        string fmt = ""_s;
        format(&fmt, "%-|-%", l->x, l->y);
        seen[fmt] = *l;

    }

    tprint("% - % - %\n",right.size, left.size, loop->size);

    for_array(f, &filtered)
    {
        flood(*f, &seen); 
    }


    int i = 0;
    for_hash_table(key, value, &seen)
    {
        if (value->x < 0 || value->y < 0)
            continue;
        i++;
        //tprint("%\n", key->data);
    }

    tprint("Elems: %\n", i - loop->size);
     

	return seen.size;
}

int aoc_10_1(const_string s_input) 
{
    array<const_string> input;
    parse_inputs(s_input, &input);

	int x = 0;
	int y = 0;

	find_s(&input, &x, &y);
	array<wall> loop = {};
	int max_distance = get_max_distance(&input, x, y, &loop);
	tprint("%\n", max_distance);

    return 0;
}

int aoc_10_2(const_string s_input) 
{
    array<const_string> input;
    parse_inputs(s_input, &input);

	int x = 0;
	int y = 0;

	find_s(&input, &x, &y);
	array<wall> loop = {};
	int max_distance = get_max_distance(&input, x, y, &loop);
	int in = count_tiles_within(&input, &loop);
	tprint("%\n", in);

    return 0;
}

