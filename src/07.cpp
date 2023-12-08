#include "07.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/array.hpp"
#include "shl/sort.hpp"
#include "shl/fixed_array.hpp"
#include "shl/file_stream.hpp"
#include "shl/hash_table.hpp"

struct game {
    string hand;
    int bid;
};

void parse_inputs(const char* file, array<game> *games)
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

    for_array(i, line, &lines)
    {
        if (line->size < 5)
            continue;

        array<const_string> s_game;
        split(*line, ' ', &s_game);

        string h;
        init(&h, s_game[0]);
        game g = { .hand = h, .bid = to_int(s_game[1]) };
        add_at_end(games, g);
    }
}

int get_type(game g)
{
    hash_table<int, int> dict = {};

    for (int i = 0; i < 5; i++)
    {
        int key = g.hand.data[i];
        bool contains_key = contains(&dict, &key);

        if (!contains_key) 
        {
            dict[key] = 1;
        }
        else
        {
            dict[key]++;
        }
    }
    
    if (dict.size == 1)
        return 6;
    
    if (dict.size == 2)
    {
        for_hash_table(v,&dict)
            if (*v == 4)
                return 5;
    }

    if (dict.size == 2)
    {
        for_hash_table(v,&dict)
            if (*v == 3)
                return 4;
    }

    if (dict.size == 3)
    {
        for_hash_table(v,&dict)
            if (*v == 3)
                return 3;
    }

    if (dict.size == 3)
    {
        for_hash_table(v,&dict)
            if (*v == 2)
                return 2;
    }

    if (dict.size == 4)
        return 1;

    if (dict.size == 5)
        return 0;

    return 0;
}

int get_type_with_joker(game g)
{
    hash_table<int, int> dict = {};

    for (int i = 0; i < 5; i++)
    {
        int key = g.hand.data[i];
        bool contains_key = contains(&dict, &key);

        if (!contains_key) 
        {
            dict[key] = 1;
        }
        else
        {
            dict[key]++;
        }
    }
   
    int type = 0;
    if (dict.size == 1)
        type = 6;
    
    if (type == 0 && dict.size == 2)
    {
        for_hash_table(v,&dict)
            if (*v == 4)
                type = 5;
    }

    if (type == 0 && dict.size == 2)
    {
        for_hash_table(v,&dict)
            if (*v == 3)
                type = 4;
    }

    if (type == 0 && dict.size == 3)
    {
        for_hash_table(v,&dict)
            if (*v == 3)
                type = 3;
    }

    if (type == 0 && dict.size == 3)
    {
        for_hash_table(v,&dict)
            if (*v == 2)
                type = 2;
    }

    if (type == 0 && dict.size == 4)
        type = 1;

    if (type == 0 && dict.size == 5)
        type = 0;

    int joker = 'J';

    if (!contains(&dict, &joker))
        return type;

    int num_j = dict[joker];

    if (type == 6)
        return type;

    if (type == 5)
        return 6;

    if (type == 4)
        return 6;

    if (type == 3)
        return 5;

    if (type == 2 and num_j == 1)
        return 4;

    if (type == 2 and num_j == 2)
        return 5;

    if (type == 1)
        return 3;

    if (type == 0 and num_j == 1)
        return 1;

    return 0;
}

int game_comparer(const game *a, const game *b)
{
    int type_a = get_type(*a);
    int type_b = get_type(*b);

    if (type_a < type_b) return 1;
    if (type_a > type_b) return -1;

    for (int i = 0; i < 5; i++)
    {
        char c_a = a->hand.data[i];
        char c_b = b->hand.data[i];

        if (c_a == c_b)
            continue;

        string order = "AKQJT98765432"_s;

        int i_a = index_of(order, c_a); 
        int i_b = index_of(order, c_b); 

        if (i_a > i_b) return 1;
        if (i_a < i_b) return -1;
    }


    return 0;
}

int game_comparer_2(const game *a, const game *b)
{
    int type_a = get_type_with_joker(*a);
    int type_b = get_type_with_joker(*b);

    if (type_a < type_b) return 1;
    if (type_a > type_b) return -1;

    for (int i = 0; i < 5; i++)
    {
        char c_a = a->hand.data[i];
        char c_b = b->hand.data[i];

        if (c_a == c_b)
            continue;

        string order = "AKQT98765432J"_s;

        int i_a = index_of(order, c_a); 
        int i_b = index_of(order, c_b); 

        if (i_a > i_b) return 1;
        if (i_a < i_b) return -1;
    }


    return 0;
}

int aoc_07_1(const char* file) 
{
    array<game> games;
    init(&games); 

    tprint("%\n", games.size);

    parse_inputs(file, &games);

    sort(games.data, games.size, game_comparer);
    
    int total = 0;

    for_array(i, g, &games)
    {
        //tprint("%\n", g->hand.data);
        total += (games.size - i) * g->bid;;
    }

    tprint("%\n", total);

    return 0;
}

int aoc_07_2(const char* file) {

    array<game> games;
    init(&games); 

    tprint("%\n", games.size);

    parse_inputs(file, &games);

    sort(games.data, games.size, game_comparer_2);
    
    int total = 0;

    for_array(i, g, &games)
    {
        int type = get_type_with_joker(*g);
        tprint("% - % - %\n", g->hand.data, g->bid, type);
        total += (games.size - i) * g->bid;;
    }

    tprint("%\n", total);

    return 0;

    return 0;
}

