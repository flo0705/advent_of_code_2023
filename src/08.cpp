#include "08.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"
#include "numeric"

struct input {
	string commands;
	hash_table<string, fixed_array<string, 2>> maps;
};

void parse_inputs(const_string s_input, input *inp)
{
	array<const_string> lines {};
	split(s_input, '\n', &lines);

	hash_table<string, fixed_array<string, 2>> maps;
	init(&maps);

	for_array(i, l, &lines)
	{
		if (i < 2)
			continue;

		if (l->size == 0)
			continue;

		string key;
		init(&key);
		string left;
		init(&left);
		string right;
		init(&right);

		substring(*l,0,3, &key);
		substring(*l,7,3, &left);
		substring(*l,12,3, &right);
		
		fixed_array<string, 2> left_right;	
		left_right.data[0] = left;
		left_right.data[1] = right;

		maps[key] = left_right;
	}
	
	string commands;
	init(&commands, lines[0]);

	input res = { .commands = commands, .maps = maps };

	*inp = res; 
	return;
}

int aoc_08_1(const_string s_input) 
{
	input inp;
	parse_inputs(s_input, &inp);

	string start = "AAA"_s;
	int i = 0;
	int steps = 0;
	
	while (compare_strings(start, "ZZZ"_s))
	{
		i = i % inp.commands.size;
		char instr = inp.commands.data[i];
		
		fixed_array<string, 2> elem = inp.maps[start];
		
		if (instr == 'L')
			start = elem[0];
		else
			start = elem[1];

		i++;
		steps++;
	}

	tprint("%\n", steps);

    return 0;
}

int aoc_08_2(const_string s_input) 
{
	input inp;
	parse_inputs(s_input, &inp);

	array<string> starts;
	init(&starts);

	for_hash_table(k, v, &inp.maps)
	{
		if (k->data[2] != 'A')
			continue;

		add_at_end(&starts, *k);
	}

	array<int> num_start_finished;
	init(&num_start_finished, starts.size);

	for_array(i1, s1, &starts)
	{
		int steps = 0;
		string start;
		init(&start, s1->data);
		while (start.data[2] != 'Z')
		{
			int i = steps % inp.commands.size;
			char instr = inp.commands.data[i];
			
			fixed_array<string, 2> elem = inp.maps[start];
			
			if (instr == 'L')
				start = elem[0];
			else
				start = elem[1];

			steps++;
		}
		
		num_start_finished[i1] = steps;
	}

	long lcm = 0;

	for_array(ci, num_steps, &num_start_finished)
	{
		if (ci == 1)
			continue;

		if (lcm == 0)
			lcm = std::lcm(*num_steps, num_start_finished[ci+1]);
		else
			lcm = std::lcm(lcm, *num_steps);
		

	}
	
	tprint("%\n", lcm);

    return 0;
}

