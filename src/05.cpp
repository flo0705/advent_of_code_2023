#include "05.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/fixed_array.hpp"
#include "shl/file_stream.hpp"
#include "limits.h"

struct map {
    int src_low;
    int src_high;
    int dst_low;
    int dst_high;
};

using maps = array<map>;

maps seed_to_soil;
maps soil_to_fert;
maps fert_to_water;
maps water_to_light;
maps light_to_temp;
maps temp_to_humid;
maps humid_to_loc;

array<long> parse_seeds(const_string seeds_string)
{
    array<const_string> seeds;
    init(&seeds);

    array<long> l_seeds;
    init(&l_seeds);

    split(seeds_string, ' ', &seeds);

    for_array(i, v, &seeds)
    {
	if (i == 0)
	    continue;

	long i_seed = to_long(*v);
	add_at_end(&l_seeds, i_seed);
    }

    return l_seeds;
}

array<fixed_array<long, 3>> parse_map(const_string seeds_string)
{
    array<const_string> lines;
    init(&lines);

    array<fixed_array<long, 3>> ret;
    init(&ret);

    split(seeds_string, '\n', &lines);

    for_array(i, v, &lines)
    {
	if (i == 0)
	    continue;

	fixed_array<long, 3> arr;
	
	array<const_string> s_arr;
	init(&s_arr);
	
	split(*v, ' ', &s_arr);
	arr[0] = to_long(s_arr[0]);
	arr[1] = to_long(s_arr[1]);
	arr[2] = to_long(s_arr[2]);

	add_at_end(&ret, arr);	
    }

    return ret;
}

long map_number(long num, array<fixed_array<long,3>> *map)
{
    for_array(v, map)
    {
	if (num < v->data[1])
	    continue;

	if (v->data[1] + v->data[2] < num)
	    continue;

	long diff = num - v->data[1];
	return v->data[0] + diff;
    }
    
    return num;
}

long map_number(long num, array<fixed_array<long,3>> *map, long *skip)
{
    for_array(v, map)
    {
	long diff = num - v->data[1];

	if (num < v->data[1])
	    continue;

	if (v->data[1] + v->data[2] < num)
	    continue;

	long upper_diff = v->data[1] + v->data[2] - num;

	if (*skip == -1 || *skip > upper_diff)
	    *skip = upper_diff;

	return v->data[0] + diff;
    }

    return num;
}

int aoc_05_1(const char* file) 
{
    file_stream fs;
    init(&fs);
    open(&fs, file);
    s64 size = calculate_file_size(&fs);

    char contents[size];
    read_entire_file(&fs, contents);
    close(&fs);
    const_string s_content = to_const_string(contents);

    array<const_string> sections;
    init(&sections);
    split(s_content, "\n\n", &sections);


    array<long> seeds = parse_seeds(sections[0]);
    array<fixed_array<long, 3>> seed_to_soil = parse_map(sections[1]);
    array<fixed_array<long, 3>> soil_to_fert = parse_map(sections[2]);
    array<fixed_array<long, 3>> fert_to_water = parse_map(sections[3]);
    array<fixed_array<long, 3>> water_to_light = parse_map(sections[4]);
    array<fixed_array<long, 3>> light_to_temp = parse_map(sections[5]);
    array<fixed_array<long, 3>> temp_to_humid = parse_map(sections[6]);
    array<fixed_array<long, 3>> humid_to_loc = parse_map(sections[7]);
    

    long lowest = LONG_MAX;
    for_array(s, &seeds) 
    {
	long seed = *s;
	seed = map_number(seed, &seed_to_soil);
	seed = map_number(seed, &soil_to_fert);
	seed = map_number(seed, &fert_to_water);
	seed = map_number(seed, &water_to_light);
	seed = map_number(seed, &light_to_temp);
	seed = map_number(seed, &temp_to_humid);
	seed = map_number(seed, &humid_to_loc);

	if (seed < lowest)
	    lowest = seed;
    }
    
    tprint("%\n", lowest);

    return 0;
}

int aoc_05_2(const char* file) {

    file_stream fs;
    init(&fs);
    open(&fs, file);
    s64 size = calculate_file_size(&fs);

    char contents[size];
    read_entire_file(&fs, contents);
    close(&fs);
    const_string s_content = to_const_string(contents);

    array<const_string> sections;
    init(&sections);
    split(s_content, "\n\n", &sections);

    array<long> seeds = parse_seeds(sections[0]);
    array<fixed_array<long, 3>> seed_to_soil = parse_map(sections[1]);
    array<fixed_array<long, 3>> soil_to_fert = parse_map(sections[2]);
    array<fixed_array<long, 3>> fert_to_water = parse_map(sections[3]);
    array<fixed_array<long, 3>> water_to_light = parse_map(sections[4]);
    array<fixed_array<long, 3>> light_to_temp = parse_map(sections[5]);
    array<fixed_array<long, 3>> temp_to_humid = parse_map(sections[6]);
    array<fixed_array<long, 3>> humid_to_loc = parse_map(sections[7]);
    
    long lowest = LONG_MAX;
    long l_seed = 0;

    for_array(i, s, &seeds) 
    {
	if (i % 2 != 0)
	    continue;

	tprint("Handling % \n", *s);
	for (long j = seeds[i]; j < seeds[i] + seeds[i + 1]; j++)
	{
	    long seed = j;

	    long skip = -1;

	    seed = map_number(seed, &seed_to_soil, &skip);
	    seed = map_number(seed, &soil_to_fert, &skip);
	    seed = map_number(seed, &fert_to_water, &skip);
	    seed = map_number(seed, &water_to_light, &skip);
	    seed = map_number(seed, &light_to_temp, &skip);
	    seed = map_number(seed, &temp_to_humid, &skip);
	    seed = map_number(seed, &humid_to_loc, &skip);

	    if (seed < lowest)
	    {
		lowest = seed;
		l_seed = j;
	    }

	   // skip -= 4000000;
	   // if (skip > 0)
	   // {
	   //     j+=skip;
	   //     j--;
	   // }	
	}
    }
  
    tprint("%\n", lowest);

    return 0;
}

