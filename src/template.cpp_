#include <cstdio>
#include <string>

int main(int argc, char* argv[]) {
    std::FILE* fp = fopen(argv[1], "r");
    std::string content;

    int c;
    while ((c = std::fgetc(fp)) != EOF)
    {
        content += c;
    }


    std::printf("%s", content.c_str());
    return 0;
}
