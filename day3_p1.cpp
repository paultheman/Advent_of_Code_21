#include <fstream>
#include <bitset>
#include <iostream>
#include <algorithm>

std::string gamma_str;
const int strLen {12};

int main()
{

    for (int i {0}; i<strLen; ++i)
    {
        std::ifstream inf {"day3_input.txt"};
        if (!inf)
        {
            std::cerr << "Can't find file!\n";
            return 1;
        }

        int counter {};
        std::string count_one;
        
        while (inf.peek()!=EOF)
        {
            std::string sBits;
            inf >> sBits;
            count_one += sBits.at(i);   
            ++counter;
        }

        if ((std::count(count_one.begin(), count_one.end(), '1')) > counter/2)
            gamma_str += '1';
        else
            gamma_str += '0';
    }

    std::bitset<strLen> gamma_rate {gamma_str};
    std::bitset<strLen> epsilon_rate { ~gamma_rate };

    std::cout << gamma_rate.to_ulong() * epsilon_rate.to_ulong();
    
    return 0;
}