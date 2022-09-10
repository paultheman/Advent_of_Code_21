#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> bVect;

char find_predominant_bit(const std::vector<std::string>& vec, const int column, const char bit)
{
    int count_one {};
    int count_zero {};

    for (size_t i {0}; i < vec.size(); ++i)
    {
        vec[i].at(column) == '1' ? ++count_one : ++count_zero;
    }

    if (count_one == count_zero)
        return bit;
    if (bit == '1')
    {
        return (count_one > count_zero) ? '1' : '0';
    }
    else if (bit == '0')
    {
        return (count_one > count_zero) ? '0' : '1';
    }
    else 
        return '0';
}

std::vector<std::string> findRating (const std::vector<std::string>& input, const char o2, int column = 0)
{
    if (input.size() == 1)
        return input;

    std::vector<std::string> output;
    
    char bit {find_predominant_bit(input, column, o2)};

    for (size_t row {0}; row < input.size(); ++row)
    {
        if (input.at(row).at(column) == bit)
        {
            output.push_back(input.at(row));   
        }
    }
    ++column;
    return findRating(output, o2, column);
}

int main()
{
    std::ifstream inf {"day3_input.txt"};
    if (!inf)
    {
        std::cerr << "Can't find file!\n";
        return 1;
    }
    
    while (inf.peek()!=EOF)
    {
        std::string sBits;
        std::getline(inf, sBits);
        bVect.push_back(sBits);
    }  
    
    std::vector<std::string>oxygen_rating = findRating(bVect, '1');
    std::vector<std::string>co2_rating = findRating(bVect, '0');
    
    int decO2Rating { std::stoi(oxygen_rating[0], nullptr, 2) };
    int decCO2Rating { std::stoi (co2_rating[0], nullptr, 2) };

    std::cout << decO2Rating * decCO2Rating;
    
    return 0;
}