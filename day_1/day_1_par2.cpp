#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

string checkIfNum(string word)
{
    if (word.find("one") != std::string::npos)
    {
        return "one";
    }
    else if (word.find("two") != std::string::npos)
    {
        return "two";
    }
    else if (word.find("three") != std::string::npos)
    {
        return "three";
    }
    else if (word.find("four") != std::string::npos)
    {
        return "four";
    }
    else if (word.find("five") != std::string::npos)
    {
        return "five";
    }
    else if (word.find("six") != std::string::npos)
    {
        return "six";
    }
    else if (word.find("seven") != std::string::npos)
    {
        return "seven";
    }
    else if (word.find("eight") != std::string::npos)
    {
        return "eight";
    }
    else if (word.find("nine") != std::string::npos)
    {
        return "nine";
    }
    else if (word.find("zero") != std::string::npos)
    {
        return "zero";
    }
    else
    {
        return word;
    }
}

string convertNum(string word)
{
    if (word.find("one") != std::string::npos)
    {
        return "1";
    }
    else if (word.find("two") != std::string::npos)
    {
        return "2";
    }
    else if (word.find("three") != std::string::npos)
    {
        return "3";
    }
    else if (word.find("four") != std::string::npos)
    {
        return "4";
    }
    else if (word.find("five") != std::string::npos)
    {
        return "5";
    }
    else if (word.find("six") != std::string::npos)
    {
        return "6";
    }
    else if (word.find("seven") != std::string::npos)
    {
        return "7";
    }
    else if (word.find("eight") != std::string::npos)
    {
        return "8";
    }
    else if (word.find("nine") != std::string::npos)
    {
        return "9";
    }
    else if (word.find("zero") != std::string::npos)
    {
        return "0";
    }
    else
    {
        return word;
    }
}

int main()
{
    std::ifstream infile("input.txt");
    string num1 = "";
    string num2 = "";
    string tmpNum = "";
    int total = 0;
    int lineCount = 0;
    string a = "";

    while(!infile.eof())
    {
        std::getline(infile, a);
        lineCount++;
        for (char c : a)
        {

            if(!is_number(num1))
            {
                if(isdigit(c))
                {
                    num1 = c;
                    num2 = c;
                }
                else
                {
                    num1 += c;
                    num1 = convertNum(num1);
                    if(is_number(num1))
                    {
                        num2 = num1;
                    }
                }
            }
            else
            {
                if(isdigit(c))
                {
                    num2 = c;
                }
                else
                {
                    tmpNum += c;
                    tmpNum = checkIfNum(tmpNum);
                    if(is_number(convertNum(tmpNum)))
                    {
                        num2 = convertNum(tmpNum);
                        tmpNum = tmpNum.back();
                    }
                }
                
            }
        }

        total += (stoi((num1 + num2)));
        num1 = "";
        num2 = "";
        tmpNum = "";
    }
    
    std::printf("%i", total);
}