#include "09.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"
#include "numeric"

void parse_inputs(const_string s_input, array<array<int>> *inp)
{
    array<const_string> lines {};
    split(s_input, '\n', &lines);

    array<array<int>> input_numbers;
    init(&input_numbers);

    for_array(i, l, &lines)
    {
        if (l->size == 0)
            continue;

        array<const_string> cs_numbers;
        init(&cs_numbers);
        
        array<int> numbers;
        init(&numbers);

        split(*l, ' ', &cs_numbers);

        for_array(i2, cs_num, &cs_numbers)
            add_at_end(&numbers, to_int(*cs_num));

        add_at_end(&input_numbers, numbers);
    }
    
    *inp = input_numbers; 
    return;
}

long find_next(array<int> *numbers)
{
    array<int> next_numbers;
    init(&next_numbers);

    int sum = 0;
    for_array(i, n, numbers)
    {
        if (i == numbers->size -1)
            break;

        int diff = numbers->data[i + 1] - numbers->data[i];
        add_at_end(&next_numbers, diff);
        
        if (diff < 0)
            diff = diff * -1;
        sum += diff;
    }

    int *last = numbers->data + numbers->size - 1;

    if (sum == 0)
	    return *last;

    int next_i = find_next(&next_numbers);
    return *last + next_i;
}

long find_next_2(array<int> *numbers)
{
    array<int> next_numbers;
    init(&next_numbers);

    int sum = 0;
    for_array(i, n, numbers)
    {
        if (i == numbers->size -1)
            break;

        int diff = numbers->data[i + 1] - numbers->data[i];
        add_at_end(&next_numbers, diff);
        
        if (diff < 0)
            diff = diff * -1;
        sum += diff;
    }

    int first = numbers->data[0];

    if (sum == 0)
	    return first;

    int next_i = find_next_2(&next_numbers);
    return first - next_i;
}

int aoc_09_1(const_string s_input) 
{
    array<array<int>> input_numbers;
    parse_inputs(s_input, &input_numbers);

    long sum = 0;
    for_array(v, &input_numbers)
    {
        int x = find_next(v);
        sum += x;
    }

    tprint("%\n", sum);

    return 0;
}

int aoc_09_2(const_string s_input) 
{
    array<array<int>> input_numbers;
    parse_inputs(s_input, &input_numbers);

    long sum = 0;
    for_array(v, &input_numbers)
    {
        int x = find_next_2(v);
        sum += x;
    }

    tprint("%\n", sum);

    return 0;
}

