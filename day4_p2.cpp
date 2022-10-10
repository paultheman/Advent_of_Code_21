#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

std::string fileName {"day4_input.txt"};

std::vector<int> getBingoNumbers()
{
    std::vector<int> output;
    std::ifstream inf {fileName};
    if (!inf)
    {
        std::cerr << "Missing input file!\n";
    }

    while (!inf.eof())
    {
        std::string number;
        std::getline(inf, number, ',');
        output.emplace_back(stoi(number, nullptr, 10));        
    }    
    return output;
}

std::vector<std::vector<int>> createBoards()
{
    std::vector<int> board;
    std::vector<std::vector<int>> boards;

    std::ifstream inf {fileName};
    
    int line_counter { 0 };
    while (!inf.eof())
    {
        ++line_counter;
        std::string line;
        std::getline(inf, line);
      
        if (line_counter > 1 && line != "")
        {
            static int bLineCounter {};
            size_t off {};
            do {
                size_t sz;
                board.push_back(std::stoi(line.substr(off), &sz));
                off += sz;
                ++bLineCounter;
            } while (off < line.length());

            if (bLineCounter % 25 == 0)
            {
                boards.push_back(board);
                board.clear();
            } 
        }          
    }
    return boards;
}

std::vector<std::vector<bool>> createMirror (const std::vector<std::vector<int>>& boards)
{
    std::vector<std::vector<bool>> mirror_vect;
    mirror_vect.resize(boards.size());

    for (size_t i {0}; i < mirror_vect.size(); ++i)
    {
        mirror_vect[i].resize(boards[i].size());
        std::fill(mirror_vect[i].begin(), mirror_vect[i].end(), 0);
    }
    return mirror_vect;
}

int checkRow (const std::vector<std::vector<bool>>& mirror)
{
    for (auto boards_it {mirror.begin()};  boards_it < mirror.end(); ++boards_it)
    {
        for (size_t i {0}; i < boards_it->size(); i+=5)
        {
            int occurances {};
            for (auto it {boards_it->begin()+i}; it < boards_it->begin()+i+5; ++it)
                if (*it == 1) ++occurances;
            if (occurances == 5)
            {
                std::cout << "Winning row in board no " << boards_it - mirror.begin() << " row " << i/5 << '\n';
                return boards_it - mirror.begin();
            }
        }
    }
    return -1; 
}

int checkColumn (const std::vector<std::vector<bool>>& mirror)
{
    for (auto boards_it {mirror.begin()}; boards_it < mirror.end(); ++boards_it)
    {
        for (size_t i {}; i < 5; ++i)
        {
            int occurances {};
            for (auto it {boards_it->begin()+i}; it < boards_it->end(); it+=5)
                if (*it == 1) ++occurances;
            if (occurances == 5)
            {
                std::cout << "Winning column in board no " << boards_it-mirror.begin() << " column " << i << '\n';
                return boards_it-mirror.begin();
            }
        }
    }
    return -1;
}

int64_t calculateBoard (const std::vector<std::vector<int>>& boards, const std::vector<std::vector<bool>>& mirror, const int number, const int index)
{
    int64_t sum {};

    for (size_t i {0}; i < mirror[index].size(); ++i)
    {
        if (mirror[index].at(i) == 0)
        {
            sum += boards[index].at(i);
        }
    }
    std::cout << "Score " << sum * number << '\n';
    return sum * number;
}

void findIndex(std::vector<std::vector<int>>& boards, const int val, std::vector<std::vector<bool>>& mirror)
{
    
    std::vector<std::vector<int>>::iterator b_it;
    std::vector<std::vector<bool>>::iterator m_it;

    for (b_it = boards.begin(), m_it = mirror.begin(); b_it != boards.end() && m_it != mirror.end(); )
    {
        auto it { std::find (b_it->begin(), b_it->end(), val)};

        if (it != b_it->end())
        {
            const int index { it - b_it->begin()};
            const int boards_no {b_it - boards.begin()};
            std::cout << "Value " << val << " Board no. " << boards_no << " Pos "<< index << '\n';
            mirror.at(boards_no).at(index) = 1;
            if (boards.size() == 1) break;
        }
        else if (boards.size() ==1)
        {
            ++b_it;
            ++m_it;  
        }
        if (boards.size() > 1)
        {
            if (checkRow(mirror) != -1 || checkColumn(mirror) != -1)
            {
                b_it = boards.erase(b_it);
                m_it = mirror.erase(m_it);                
            }
            else
            {
                ++b_it;
                ++m_it;                
            }
        }
    }
}

const std::vector<int> input_numbers { getBingoNumbers()};
std::vector<std::vector<int>> boards { createBoards() };
std::vector<std::vector<bool>> mirror {createMirror(boards)};

int main()
{     
    for (const auto& each : input_numbers)
    {
        findIndex(boards, each, mirror);

        if (boards.size() == 1)
        {
            int row { checkRow(mirror) };
            int column { checkColumn(mirror) };

            if (row != -1)
            {
                std::cout << "Winning number " << each << '\n';
                calculateBoard(boards, mirror, each, row);
                break;
            }
            if (column != -1)
            {
                std::cout << "Winning number " << each << '\n';
                calculateBoard(boards, mirror, each, column);
                break;
            }
        }
    }
    return 0;
}