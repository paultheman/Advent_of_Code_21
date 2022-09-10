#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>

template <typename T>
inline bool FromString(const std::string& sString, T& output)
{
    std::istringstream iStream(sString);
    return !(iStream >> output).fail();
}

struct Position
{
    int horizontal {};
    int depth {};
    int aim {};
} position;

int main()
{
    std::ifstream inf {"day2_input.txt"};
    if (!inf)
    {
        std::cerr << "Can't find file!\n";
        return 1;
    }

    while(inf)
    {
        std::string strInput;
        std::getline (inf, strInput);
        
        size_t separator_pos {strInput.find(" ")};
        std::string_view direction {strInput.substr(0, separator_pos)};
        std::string_view amount {strInput.substr(separator_pos+1, strInput.find('\n'))};

        int iAmount;
        FromString(static_cast<std::string>(amount), iAmount);

        if (direction == "forward")
        {
            position.horizontal += iAmount;
            if (position.aim ==0)
                continue;
            position.depth += iAmount * position.aim;
        }
        else if (direction == "down")
            position.aim += iAmount;
        else if (direction == "up")
            position.aim -= iAmount;

    }
    std::cout << position.depth * position.horizontal;

    return 0;
}