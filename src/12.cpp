#include "09.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/hash_table.hpp"
#include "numeric"
#include "math.h"

struct condition_record {
    const_string condition;
    array<int> damaged_groups;
};

void parse_inputs(const_string s_input, array<condition_record> *inp)
{
    array<const_string> lines {};
    split(s_input, '\n', &lines);

    array<array<int>> input_numbers;
    init(&input_numbers);

    array<condition_record> records = {};

    for_array(i, l, &lines)
    {
        if (l->size < 2)
            continue;

        array<const_string> line_split = {};
        array<const_string> cs_groups = {};
        array<int> groups = {};

        split(*l, ' ', &line_split);
        split(line_split[1], ',', &cs_groups);

        for_array(g, &cs_groups)
        {
            int group = to_int(*g);
            add_at_end(&groups, group);
        }

        condition_record cr = { .condition = line_split[0], .damaged_groups = groups };
        add_at_end(&records, cr);
    }
    
    *inp = records; 
    return;
}

int generate_all_poss_strings(int size, string poss_chars, array<string> *out)
{
    int num_chars = poss_chars.size; 

    int i = 0;
    
    string init_string;
    init(&init_string, size);
    add_at_end(out, init_string);
    free(&init_string);

    array<string> temp = {};
    while (i < size)
    {
        temp = {};
        for_array(s, out)
        {
            for (int j = 0; j < num_chars; j++)
            {
                string ss;
                init(&ss, s->data, size);
                ss.data[i] = poss_chars.data[j];
                add_at_end(&temp, ss); 
                free(&ss);
            }
        }

        *out = temp;
        i++;
    }
}

int count_unknowns(string *condition) 
{
    int c = 0;
    for (int i = 0; i < condition->size; i++)
    {
        if (condition->data[i] == '?')
            c++;
    }

    return c;
}

string replace(string condition, long bitmask)
{
    int c = 0;
    string n_cond;
    init(&n_cond, condition.data);

    for (int i = 0; i < condition.size; i++)
    {
        if (condition.data[i] != '?')
            continue;

        if (bitmask & (1 << c)) 
            n_cond.data[i] = '.';
        else
            n_cond.data[i] = '#';

        c++;
    }
   
    return n_cond;
}

bool check_if_possible(string *condition, array<int> *damaged_groups)
{
    bool in_group = false;
    int c = 0;
    int g = 0;

    array<int> dg = *damaged_groups;

    for (int i = 0; i < condition->size; i++)
    {
        if (condition->data[i] == '#')
        {
            in_group = true;
            c++;
            continue;
        }

        if (in_group)
        {
            if (g >= damaged_groups->size)
                return false;

            if (dg[g] != c)
                return false;

            in_group = false;
            c = 0;
            g++;
            continue;
        }
    }

    if (in_group)
    {
        if (g >= damaged_groups->size)
            return false;
        
        if (dg[g] != c)
            return false;
        
        g++;
    }

    if (g != damaged_groups -> size)
        return false;

    return true;
}

int count_possible_combinations(condition_record cr) 
{
    string cond;
    init(&cond, cr.condition);
    int num_unknowns = count_unknowns(&cond);

    array<string> all_poss = {};
    
    long num_pos = pow(2,num_unknowns);
    tprint("%\n", num_pos);

    int p = 0;
    for(long i = 0; i < num_pos; i++)
    {
        string replaced = replace(cond, i);

        if (check_if_possible(&replaced, &cr.damaged_groups))
            p++;
        
        free(&replaced);
    }
    
    free(&all_poss);
    return p;
}

string format_int_array(array<int> *arr)
{
    string temp = ""_s;

    for_array(k, arr)
    {
        string t = ""_s;
        format(&t, " %", *k);
        append_string(&temp, &t);
    }

    return temp;
}

int aoc_12_1(const_string s_input) 
{
    array<condition_record> crs;
    parse_inputs(s_input, &crs);

    int sum = 0;
    for_array(i, cr, &crs)
    {
        int c = count_possible_combinations(*cr);
        sum += c;
    }

    tprint("%\n", sum);
    return 0;
}

void unfold_input(array<condition_record> *crs)
{
    for_array(cr, crs)
    {
        string n_condition;
        init(&n_condition, cr->condition);

        for (int i = 0; i < 4; i++)
        {
            append_string(&n_condition, "?"_s);
            append_string(&n_condition, cr->condition);
        }

        cr->condition = n_condition;

        array<int> n_groups;
        init(&n_groups);

        for (int i = 0; i < 5; i++)
            add_range(&n_groups, &cr->damaged_groups);

        cr->damaged_groups = n_groups;
    }
}

int aoc_12_2(const_string s_input) 
{
    array<condition_record> crs;
    parse_inputs(s_input, &crs);
    unfold_input(&crs); 

    int sum = 0;
    for_array(i, cr, &crs)
    {
        int c = count_possible_combinations(*cr);
        tprint("% - % - %\n", c, cr->condition, format_int_array(&cr->damaged_groups).data);
        sum += c;
    }

    tprint("%\n", sum);
    return 0;
}

