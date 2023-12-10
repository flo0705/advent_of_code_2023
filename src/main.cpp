#include "05.hpp"
#include "06.hpp"
#include "07.hpp"
#include "08.hpp"
#include "09.hpp"
#include "shl/print.hpp";
#include "shl/file_stream.hpp"
#include "shl/print.hpp";

string read_file(const char *filepath)
{
    file_stream fs;
    init(&fs);
    open(&fs, filepath);
    s64 size = calculate_file_size(&fs);

    char contents[size];
    read_entire_file(&fs, contents);
    close(&fs);
	
	string str;
	init(&str, contents);
	return str;
}

int main(int argc, char* argv[]) {
    //aoc_05_1("inputs/05.txt");
    //aoc_05_2("inputs/05.txt");

    //aoc_06_1("inputs/06.txt");
    //aoc_06_2("inputs/06.txt");

   // tprint("AOC 07\n");
   // aoc_07_1("inputs/07.txt");
   // aoc_07_2("inputs/07.txt");

    tprint("AOC 08\n");
    string file_08 = read_file("inputs/08.txt");
    aoc_08_1(file_08);
    aoc_08_2(file_08);

    tprint("AOC 09\n");
    string file_09 = read_file("inputs/09.txt");
    aoc_09_1(file_09);
    aoc_09_2(file_09);
}

