#include <cstdio>
#include <string>
#include <iostream>

int aoc_1(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int totalRed = 12;
    int totalGreen = 13;
    int totalBlue = 14;

    int idsImp = 0;
    int idsTotal = 0;

    int game = 1;
    bool colonRead = false;
    int currentNum = 0;
    int isAlreadyImp = false;
    
    int c;

    while ((c = std::fgetc(fp)) != EOF)
    {

        if (c == ':')
        {
            colonRead = true;
            continue;
        }

        if (colonRead == false)
        {
            continue;
        }

        if (isdigit(c))
        {
            std::string num = std::string();
            num += c;
            int c2 = std::fgetc(fp);
            if (isdigit(c2))
            {
                num += c2;
                c = std::fgetc(fp);
            }

            currentNum = std::stoi(num);
            
            c = std::fgetc(fp);

            if (!isAlreadyImp  && c == 'r' && currentNum > totalRed)
            {
                idsImp += game;
                isAlreadyImp = true;
            }
         
            if (!isAlreadyImp  && c == 'g' && currentNum > totalGreen)
            {
                idsImp += game;
                isAlreadyImp = true;
            }
            
            if (!isAlreadyImp  && c == 'b' && currentNum > totalBlue)
            {
                idsImp += game;
                isAlreadyImp = true;
            }

            while (c != ';' && c != ',' && c != '\n')
            {
                c = fgetc(fp);
                continue;
            }
        }

        if (c == '\n')
        {
            idsTotal += game++;
            colonRead = false;
            isAlreadyImp = false;
            continue;
        }
    }

    std::cout << idsTotal - idsImp << std::endl;

    return 0;
}
int aoc_2(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int gameMaxRed = 0;
    int gameMaxGreen = 0;
    int gameMaxBlue = 0;

    int powTotal = 0;

    int game = 1;
    bool colonRead = false;
    int currentNum = 0;
    
    int c;

    while ((c = std::fgetc(fp)) != EOF)
    {

        if (c == ':')
        {
            colonRead = true;
            continue;
        }

        if (colonRead == false)
        {
            continue;
        }

        if (isdigit(c))
        {
            std::string num = std::string();
            num += c;
            int c2 = std::fgetc(fp);
            if (isdigit(c2))
            {
                num += c2;
                c = std::fgetc(fp);
            }

            currentNum = std::stoi(num);
            
            c = std::fgetc(fp);

            if (c == 'r' && gameMaxRed < currentNum)
            { 
                gameMaxRed = currentNum;
            }
         
            if (c == 'g' && gameMaxGreen < currentNum)
            { 
                gameMaxGreen = currentNum;
            }

            if (c == 'b' && gameMaxBlue < currentNum)
            { 
                gameMaxBlue = currentNum;
            }

            while (c != ';' && c != ',' && c != '\n')
            {
                c = fgetc(fp);
                continue;
            }
        }

        if (c == '\n')
        {
            powTotal += (gameMaxBlue * gameMaxGreen * gameMaxRed);
            gameMaxRed = 0;
            gameMaxGreen = 0;
            gameMaxBlue= 0;
            colonRead = false;
            continue;
        }
    }

    std::cout << powTotal << std::endl;

    return 0;
}


int main(int argc, char* argv[]) {
    aoc_1(argv[1]);
    aoc_2(argv[1]);
}

