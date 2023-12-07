#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

/*
    For each character we need to check:
    UpLeft(-1,-1), Up(-1, 0), UpRight(-1, +1)
    Left(0, -1), Right(0, +1)
    DownLeft(+1, -1), Down(+1, 0), DownRight(+1, +1)

    If any of these is a symbol then the number needs to be added. 
    If left or right is a number, we need to use it to build the number. 

    If Row = 0, we don't need to check up. 
    If Col = 0, we don't have to check left. 
    If Row = MAXROWS, we don't need to check down. 
    If Col = MAXCOL, we don't have to check right.  
*/
bool checkSpecialChar(char cell)
{
    if((cell >= 'a' && cell <= 'z') || (cell >= 'A' && cell <= 'Z')) {

        return false;

    } else if(cell >= '0' && cell <= '9') {

        return false;

    } else {

        return true;

    }
}

bool checkIfNumUsed(vector<vector<char>> g, int r, int c, int MaxR, int MaxC)
{
    if(r != 0) //  R can be checked negative
    {
        if( r != MaxR -1) //R can be checked positive
        {
            if( c != 0) //C can be checked negative
            {
                if(c != MaxC-1) //C can be checked positive. 
                {
                    //can check all directions
                    if(checkSpecialChar(g[r-1][c-1]) || checkSpecialChar(g[r-1][c]) 
                        || checkSpecialChar(g[r-1][c+1]) || checkSpecialChar(g[r][c-1]) 
                        || checkSpecialChar(g[r][c+1]) || checkSpecialChar(g[r+1][c-1])
                        || checkSpecialChar(g[r+1][c]) || checkSpecialChar(g[r+1][c+1]))
                    {
                        return true;
                    }
                }
                else //C cannot be checked positive, r can be checked negative and positive
                {
                    if(checkSpecialChar(g[r-1][c-1]) || checkSpecialChar(g[r-1][c]) 
                        || checkSpecialChar(g[r][c-1]) || checkSpecialChar(g[r+1][c-1])
                        || checkSpecialChar(g[r+1][c]))
                    {
                        return true;
                    }
                }  
            }
            else //c cannot be checked negative(c = 0), r can be checked negative and positive
            {
                if(c != MaxC-1) // c can be checked positive
                    {
                        if(checkSpecialChar(g[r-1][c]) || checkSpecialChar(g[r-1][c+1]) 
                        || checkSpecialChar(g[r][c+1]) || checkSpecialChar(g[r+1][c]) 
                        || checkSpecialChar(g[r+1][c+1]))
                        {
                            return true;
                        }
                    }
                    else // c cannot be checked positive
                    {
                        if(checkSpecialChar(g[r-1][c]) || checkSpecialChar(g[r+1][c]))
                        {
                            return true;
                        }
                    }  
            }
        }
        else // R Cannot be checked positive
        {
            if( c != 0) //C can be checked negative
            {
                if(c != MaxC-1) //C can be checked positive. 
                {
                    //C can be positive and negative, R cannot be positive
                    if(checkSpecialChar(g[r-1][c-1]) || checkSpecialChar(g[r-1][c]) 
                        || checkSpecialChar(g[r-1][c+1]) || checkSpecialChar(g[r][c-1]) 
                        || checkSpecialChar(g[r][c+1]))
                    {
                        return true;
                    }
                }
                else //C cannot be checked positive, r cannot be positive
                {
                    if(checkSpecialChar(g[r-1][c-1]) || checkSpecialChar(g[r-1][c]) 
                        || checkSpecialChar(g[r][c-1]))
                    {
                        return true;
                    }
                }  
            }
            else //c cannot be checked negative(c = 0), r can be checked negative
            {
                if(c != MaxC-1) // c can be checked positive
                    {
                        if(checkSpecialChar(g[r-1][c]) || checkSpecialChar(g[r-1][c+1]) 
                        || checkSpecialChar(g[r][c+1]))
                        {
                            return true;
                        }
                    }
                    else // c cannot be checked positive
                    {
                        if(checkSpecialChar(g[r-1][c]))
                        {
                            return true;
                        }
                    }  
            }
        }
    }
}
/*
    Need to recheck the logic for checking for special characters. 
    Once that's confirmed we can start with the rest: 
    1. If we have a digit, we add it to the temp num. 
    2. if a number is touching special character, then the whole temp num should be added to the total. 

    something seems off here though....need to think about this .
*/
main()
{
    std::ifstream inFile("file");
    string line;
    string currNum;
    vector<vector<char>> grid;
    int MAXROWS, MAXCOL;
    int col = 0, rows = 0, int total = 0;
    if(inFile.is_open())
    {
        getline(inFile, line);
        MAXCOL = line.length();
        MAXROWS = std::count(std::istreambuf_iterator<char>(inFile), 
                std::istreambuf_iterator<char>(), '\n');
        inFile.close();
    }
    while(!inFile.eof())
    {
        getline(inFile, line);
        for(char c : line)
        {
            grid[rows][col] = c;
            col++;
        }
        rows++;
        col = 0;
    }
    for(int i = 0; i < MAXROWS; i++)
    {
        for(int j = 0; j < MAXROWS; j++)
        {
            if(isdigit(grid[i][j]))
            {
                currNum += grid[i][j];
            }
        }
    }


}