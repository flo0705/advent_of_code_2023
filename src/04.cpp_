#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <map>
#include <math.h>

int aoc_1(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int c;

    std::vector<int> winningNums = {};
    std::vector<int> nums = {};
    
    int totalSum = 0;
    bool isWinningNums = true;
    bool start = false;
    std::string currentNum = std::string();
    

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == ':')
        {
            start = true;
            continue;
        }

        if (!start)
            continue;

        if ((c == ' ' || c == '\n') && currentNum.length() > 0)
        {
            if (isWinningNums)
                winningNums.push_back(std::stoi(currentNum));
            else
                nums.push_back(std::stoi(currentNum));

            currentNum = std::string();
        }

        if (c == '\n')
        {
            int cardSum = 1;


            std::sort( winningNums.begin(), winningNums.end() );
            winningNums.erase( std::unique( winningNums.begin(), winningNums.end() ), winningNums.end() );

            for (int n : winningNums)
            {
                if ( std::find(nums.begin(), nums.end(), n) != nums.end() )
                {
                    cardSum *= 2;            
                }
            }
            
            if (cardSum != 1)
            {
                cardSum /= 2;
                totalSum += cardSum;
            }

            winningNums = {};
            nums = {};
            isWinningNums = true;
            start = false;
            continue;
        }
        
        if (c == '|')
        {
            isWinningNums = false;
            continue;
        }


        if (isdigit(c))
        {
            currentNum += c;
        }

    }


    std::cout << totalSum << std::endl;

    return 0;
}

int find_sub_amount(std::map<int,int> &cache, std::tuple<int,int,int> card, std::vector<std::tuple<int,int,int>> cards)
{
    int card_num = std::get<0>(card);
    int matches = std::get<2>(card);

    if (auto ci = cache.find(card_num); ci != cache.end())
        return ci->second;

    int sum = 1;
    
    for (int i = card_num + 1; i < card_num + 1 + matches; ++i) 
    {
        auto found = std::find_if(begin(cards), end(cards), 
                [i](std::tuple<int,int,int> c)
                {
                    return std::get<0>(c) == i;
                });
        
        if (found == cards.end())
            continue;
        
        int sub = find_sub_amount(cache, *found, cards);
        sum += sub;
    }

    if (auto ci = cache.find(card_num); ci != cache.end())
        return sum;

    cache[card_num] = sum;

    return sum;
}


int aoc_2(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int c;
    
    std::vector<std::tuple<int, int, int>> cards = {};
    std::vector<int> winningNums = {};
    std::vector<int> nums = {};
    
    int cardNum = 1;
    bool isWinningNums = true;
    bool start = false;
    std::string currentNum = std::string();

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == ':')
        {
            start = true;
            continue;
        }

        if (!start)
            continue;

        if ((c == ' ' || c == '\n') && currentNum.length() > 0)
        {
            if (isWinningNums)
                winningNums.push_back(std::stoi(currentNum));
            else
                nums.push_back(std::stoi(currentNum));

            currentNum = std::string();
        }

        if (c == '\n')
        {
            std::sort( winningNums.begin(), winningNums.end() );
            winningNums.erase( std::unique( winningNums.begin(), winningNums.end() ), winningNums.end() );

            int matches = 0;
            for (int n : winningNums)
                if ( std::find(nums.begin(), nums.end(), n) != nums.end() )
                    matches++;
            
            if (matches > 0)
            {
                int cardSum = pow(2, (matches - 1));
                cards.push_back(std::make_tuple(cardNum, cardSum, matches));
            } else
                cards.push_back(std::make_tuple(cardNum, 0, matches));

            winningNums = {};
            nums = {};
            isWinningNums = true;
            start = false;
            cardNum++;
            continue;
        }
        
        if (c == '|')
        {
            isWinningNums = false;
            continue;
        }


        if (isdigit(c))
        {
            currentNum += c;
        }
    }

    int totalSum = 0;

    std::vector<std::tuple<int,int,int>> orig;
    orig.assign(cards.begin(), cards.end()); 

    std::map<int, int> cache;

    int amount = 0;
    for (auto card : cards)
    {
        amount += find_sub_amount(cache, card, cards);
    }
    
    std::cout << amount << std::endl;
    return 0;
}



int main(int argc, char* argv[]) {
    aoc_1(argv[1]);
    aoc_2(argv[1]);
}

