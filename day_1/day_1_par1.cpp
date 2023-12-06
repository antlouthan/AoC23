#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
    std::ifstream infile("input.txt");
    string num1 = "";
    string num2 = "";
    int total = 0;
    int lineCount = 0;
    string a = "";

    while(!infile.eof())
    {
        std::getline(infile, a);
        lineCount++;
        for (char c : a)
        {
            if(isdigit(c))
            {
                if(num1 == "")
                {
                    num1 = c;
                    num2 = c;
                }
                else
                {
                    num2 = c;
                }
            }
        }
        if(num1 != "")
        {
            total += (stoi((num1 + num2)));
        }

        
        num1 = "";
        num2 = "";
    }
    std::printf("%i", total);
}