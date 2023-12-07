#include <cstdio>
#include <string>
#include <iostream>

int aoc_01_1(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int total = 0;
    char first = -1;
    char last = -1;
    int c;

    while ((c = std::fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            std::string num = std::string();
            num += first;
            num += last;
            total += std::stoi(num);
            first = -1;
            last = -1;
            continue;
        }

        if (!isdigit(c)) 
        {
            continue;
        }
        
        if (first == -1)
        {
            first = c;
            last = c;
            continue;
        }

        last = c;
    }


    std::cout << total << std::endl;

    return 0;
}
int aoc_01_2(const char* file) {

    std::FILE* fp = fopen(file, "r");

    int total = 0;
    char first = -1;
    char last = -1;
    int c;
    std::string word = "";

    while ((c = std::fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            std::string num = std::string();
            num += first;
            num += last;
            total += std::stoi(num);
            first = -1;
            last = -1;
            continue;
        }

        if (!isdigit(c)) 
        {
            word += c;
            
            if (word.find("one") != std::string::npos){
                c = '1';
            } else if (word.find("two") != std::string::npos){
                c = '2';
            } else if (word.find("three") != std::string::npos){
                c = '3';
            } else if (word.find("four") != std::string::npos){
                c = '4';
            } else if (word.find("five") != std::string::npos){
                c = '5';
            } else if (word.find("six") != std::string::npos){
                c = '6';
            } else if (word.find("seven") != std::string::npos){
                c = '7';
            } else if (word.find("eight") != std::string::npos){
                c = '8';
            } else if (word.find("nine") != std::string::npos){
                c = '9';
            } else {
                continue;
            }
            
            word = word.substr(word.length()-1,word.length());
        }

        if (first == -1)
        {
            first = c;
            last = c;
            continue;
        }

        last = c;
    }


    std::cout << total << std::endl;
    return 0;
}




int main(int argc, char* argv[]) {
    aoc_01_1(argv[1]);
    aoc_01_2(argv[1]);
}

