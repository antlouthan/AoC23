#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int calculateScore(int score)
{
    if(score == 1)
    {
        return 1;
    }
    else
    {
        return (pow(2, score-1));
    }
}

int howManyWins(vector<int> goals, vector<int> nums)
{
    int countWins = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        if(std::find(goals.begin(), goals.end(), nums[i]) != goals.end())
        {
            countWins++;
        }
    }
    return countWins;
}

int main()
{
     std::ifstream infile("input.txt");
     vector<int> winningNums;
     vector<int> gameNums;
     int numWins;
     int total = 0;
     string line;

     while(!infile.eof())
    {
        numWins = 0; 
        winningNums.clear();
        gameNums.clear();
        std::getline(infile, line);
        int pos = line.find(":");
        line = line.substr(pos + 1);
        int pos2 = line.find("|");
        string gameNumStr = line.substr(0, pos2);
        string winNumStr = line.substr(pos2+1);
        std::istringstream iss1(gameNumStr);
        string word;
        while(iss1 >> word)
        {
            gameNums.push_back(stoi(word));
        }
        std::istringstream iss2(winNumStr);
        while(iss2 >> word)
        {
            winningNums.push_back(stoi(word));
        }
        int wins = howManyWins(gameNums, winningNums);
        if( wins > 0)
        {
            total += calculateScore(wins);
        }
    }
    printf("%i", total);
}