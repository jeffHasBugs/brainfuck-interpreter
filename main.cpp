#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <stack>

//#define DEBUG

const int MEM_SIZE = 30001;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        std::cout << "Error: no file given" << std::endl;
        return 0;
    }
    std::ifstream infile(argv[1]);

    std::ostringstream sstr;
    sstr << infile.rdbuf();
    infile.close();
    std::string buf = sstr.str();

    // memory
    std::array<char, MEM_SIZE> mem;
    mem.fill(0);
    auto ptr = mem.begin();

    // stores positions for start-loop ('[') characters 
    std::stack<std::string::iterator> loop;
    // counter storing loops to skip 
    int skip = 0;

    auto bfPtr = buf.begin();
    for (; bfPtr != buf.end(); ++bfPtr) {
        // skip
        if (*bfPtr == '[' && *ptr == 0) ++skip;
        if (skip) {
            if (*bfPtr == ']') --skip;
            continue;
        }

        switch (*bfPtr)
        {
        case '+':
            ++*ptr;
            break;
        case '-':
            --*ptr;
            break;
        case '>':
            ++ptr;
            break;
        case '<':
            --ptr;
            break;
        case '[':
            loop.push(bfPtr);
            break;
        case ']':
            if (*ptr == 0)
                loop.pop();
            else
                bfPtr = loop.top();
            break;
        case ',':
            std::cin >> *ptr;
            break; 
        case '.':
            #ifdef DEBUG
            std::cout << int(*ptr);
            #endif
            std::cout << *ptr;
            break;
        }
    }

    return 0;
} 
