#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using namespace std;


bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

string whichColor(string text)
{
    if(text == "red" || text == "red;" || text == "red,")
    {
        return "red";
    }
    else if(text == "green" || text == "green;" || text == "green,")
    {
        return "green";
    }
    else if(text == "blue" || text == "blue;" || text == "blue,")
    {
        return "blue";
    }
    else return "";
    
}

bool invalidGame(map<string, int> game)
{
    if(game["red"] > 12 || game["green"] > 13 || game["blue"] >14)
    {
        return true;
    }
    else return false;
}

int main()
{
    std::ifstream infile("input.txt");
    string a = "";
    map<string, int> gameResult;
    int total=0, gameID=0, tmpNum = 0;
    
    

     while(!infile.eof())
    {
        
        bool goodGame = true;
        std::getline(infile, a);
        int pos = a.find(":");
        string s = a.substr(0,pos);
        const std::string ext("Game");
        if ( s != ext &&
            s.size() > ext.size() &&
            s.substr(0, ext.size()) == "Game" )
        {
        // if so then strip them off
        s = s.substr(ext.size());
        }
        gameID = stoi(s);
        a = a.substr(pos+1);
        while(a != "")
        {
            gameResult["blue"]= 0;
            gameResult["red"]= 0;
            gameResult["green"]= 0;
            if(a.find(';') != string::npos)
            {
                pos = a.find(";");
                string tmpStr = a.substr(0, pos);
                string word;
                std::istringstream iss(tmpStr);
                while(iss >> word)
                {
                    if(is_number(word))
                    {
                        tmpNum = stoi(word);
                    }
                    else
                    {
                        string entry = whichColor(word);   
                        gameResult[entry] += tmpNum;
                        if(invalidGame(gameResult))
                        {
                            goodGame = false;
                            break;
                        } 
                    }
                }
               
                a = a.substr(pos+1);
                
            }
            else
            {
                string word;
                std::istringstream iss(a);
                while(iss >> word)
                {
                    if(is_number(word))
                    {
                        tmpNum = stoi(word);
                    }
                    else
                    {
                        string entry = whichColor(word);   
                        gameResult[entry] += tmpNum;
                        if(invalidGame(gameResult))
                        {
                            goodGame = false;
                            gameResult["blue"]= 0;
                            gameResult["red"]= 0;
                            gameResult["green"]= 0;
                            break;
                        }  
                    }
                }
                a = "";
                if(invalidGame(gameResult))
                {
                    goodGame = false;
                    gameResult["blue"]= 0;
                    gameResult["red"]= 0;
                    gameResult["green"]= 0;
                    break;
                }
            }
        }
        if(goodGame)
        {
            //Game 3 is listed as valid despite it having a 15 red. Start there tomorrow. 
            total += gameID;
        }
    }
    printf("%i\n", total);
}