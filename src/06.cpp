#include "06.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/fixed_array.hpp"
#include "shl/file_stream.hpp"

array<fixed_array<int,2>> parse_input(const char* file)
{
    file_stream fs;
    init(&fs);
    open(&fs, file);
    s64 size = calculate_file_size(&fs);

    char contents[size];
    read_entire_file(&fs, contents);
    close(&fs);
    const_string s_content = to_const_string(contents);

    array<const_string> lines;
    init(&lines);
    split(s_content, "\n", &lines);

    array<const_string> s_times;
    init(&s_times);
    array<const_string> s_distances;
    init(&s_distances);

    split(lines[0], ' ', &s_times);
    split(lines[1], ' ', &s_distances);

    array<int> times;
    init(&times);
    array<int> distances;
    init(&distances);
    array<fixed_array<int, 2>> ret;
    init(&ret);

    for_array(i, e, &s_times)
    {
	const_string cs = *e;
	if (!is_digit(cs[0]))
	    continue;

	int t = to_int(cs);
	add_at_end(&times, t);
    }

    for_array(i, d, &s_distances)
    {
	const_string cs = *d;
	if (!is_digit(cs[0]))
	    continue;

	int t = to_int(cs);
	add_at_end(&distances, t);
    }
    
    for_array(i, x, &times)
    {
	fixed_array<int, 2> temp;
	temp.data[0] = *x;
	temp.data[1] = distances[i];
	add_at_end(&ret, temp);
    }

    free(&lines);
    free(&times);
    free(&distances);
    free(&s_times);
    free(&s_distances);

    return ret;
}

int aoc_06_1(const char* file) 
{
    array<fixed_array<int, 2>> input = parse_input(file);

    int total_win = 1;

    for_array(i, game, &input)
    {
	int win = 0;

	for (int i = 0; i < game->data[0]; i++)
	{
	    int diff = game->data[0] - i;

	    if (diff * i <= game->data[1])
		continue;

	    win++;
	}

	total_win *= win;	
    }

    tprint("%\n", total_win);

    return 0;
}

int aoc_06_2(const char* file) {

    array<fixed_array<int, 2>> input = parse_input(file);
    string times = ""_s;
    string distances = ""_s;

    for_array(i, game, &input)
    {
	string temp = ""_s;
	to_string(&temp, game->data[0]);
	append_string(&times, temp);

	temp = ""_s;
	to_string(&temp, game->data[1]);
	append_string(&distances, temp);
	free(&temp);
    }

    long total_time = to_int(times);
    long total_distance = to_long(distances);
    
    int win = 0;
    for (long i = 0; i < total_time; i++)
    {
	long diff = total_time - i;

	if (diff * i <= total_distance)
	    continue;

	win++;
    }

    tprint("%\n", win);

    return 0;
}

