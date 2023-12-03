#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

struct number {
  int value;   
  int length;
  int posx;
  int posy;
};

struct symbol {
  int posx;
  int posy;
};

number parseNumber(int x, int y, std::string num)
{
    number numb;
    numb.value = std::stoi(num);
    numb.length = num.length();
    numb.posx = x - numb.length;
    numb.posy = y;

    return numb;
}

int aoc_1(const char* file) {

    std::FILE* fp = fopen(file, "r");

    std::vector<number> numbers = {};
    std::vector<symbol> symbols = {};

    int c;
    int x = 0;
    int y = 0;

    int currentNumLength = 0;
    std::string currentNum = std::string();

    while ((c = std::fgetc(fp)) != EOF) 
    {
 
        if (isdigit(c))
        {
            currentNum += c;
            currentNumLength++;
            x++;
            continue;
        }

        if (c != '.' && c != '\n')
        {
            symbol sym;
            sym.posx = x;
            sym.posy = y;
            symbols.push_back(sym);
        }

        if (currentNum.length() != 0)
        {
            number parsed = parseNumber(x, y, currentNum); 
            numbers.push_back(parsed);
            currentNum = std::string();
            currentNumLength = 0;
        }

        if (c == '\n') 
        {
            y++;
            x = 0;
            continue;
        }
        
        x++;
    }

    int sum = 0;

    for (number n : numbers)
    {
        for (symbol s : symbols)
        {
            int diffy = std::abs(n.posy - s.posy);
            int diffx1 = std::abs(n.posx - s.posx);
            int diffx2 = std::abs(n.posx + n.length - 1 - s.posx);

            if ((diffx1 <= 1 || diffx2 <= 1) && diffy <= 1)
            {
                sum += n.value;
                break;
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}

int aoc_2(const char* file) {

    std::FILE* fp = fopen(file, "r");

    std::vector<number> numbers = {};
    std::vector<symbol> symbols = {};

    int c;
    int x = 0;
    int y = 0;

    int currentNumLength = 0;
    std::string currentNum = std::string();

    while ((c = std::fgetc(fp)) != EOF) 
    {
 
        if (isdigit(c))
        {
            currentNum += c;
            currentNumLength++;
            x++;
            continue;
        }

        if (c == '*')
        {
            symbol sym;
            sym.posx = x;
            sym.posy = y;
            symbols.push_back(sym);
        }

        if (currentNum.length() != 0)
        {
            number parsed = parseNumber(x, y, currentNum); 
            numbers.push_back(parsed);
            currentNum = std::string();
            currentNumLength = 0;
        }

        if (c == '\n') 
        {
            y++;
            x = 0;
            continue;
        }
        
        x++;
    }

    int sum = 0;

    for (symbol s : symbols)
    {
        int first = 0;
        for (number n : numbers)
        {
            int diffy = std::abs(n.posy - s.posy);
            int diffx1 = std::abs(n.posx - s.posx);
            int diffx2 = std::abs(n.posx + n.length - 1 - s.posx);

            if ((diffx1 <= 1 || diffx2 <= 1) && diffy <= 1)
            {
                if (first == 0)
                {
                    first = n.value;
                    continue;
                }

                sum += n.value * first;
                break;
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}




int main(int argc, char* argv[]) {
    aoc_1(argv[1]);
    aoc_2(argv[1]);
}

