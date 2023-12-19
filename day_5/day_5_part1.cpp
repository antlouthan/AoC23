#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <queue>
#include <string>



/*
    Thoughts:
        We need a vector<string> for seeds. 
        We need to capture the data for each map. Let's use a struct to represent the numbers and a vector of those to compose the full map. 
            The first number is the start of the range for the ID we will use. 
            The second number is the start of the range for the numbers we'll look up the seed within. 
            The third number is how long the range of the second number is. 
        Take in the ID for the seed then do the following: 
            Look at the second number for each element of the map as a starting point. 
            Add the last number for each element of the map to determine the full range. 
            If the Seed ID falls within this range, take the Seed ID and subtract the Second Number. 
            Add this new number to the First number of the element of the map you are on. 
*/ 

struct mapContents
{
    unsigned long long destRangeStart, sourceRangeStart, rangeLength;
};

void readMap(std::istream& in, std::vector<mapContents>& map) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) break; // Empty line or end of section

        std::istringstream iss(line);
        mapContents mc;
        iss >> mc.destRangeStart >> mc.sourceRangeStart >> mc.rangeLength;
        map.push_back(mc);
    }
}

unsigned long long findnextID(std::vector<mapContents>& map, unsigned long long curr)
{
    for(mapContents m : map)
    {
        if(m.sourceRangeStart + m.rangeLength > curr && curr >=m.sourceRangeStart)
        {
            return m.destRangeStart + (curr - m.sourceRangeStart); 
        }
    }
    return curr; 
}


int main()
{
    std::vector<unsigned long long> seeds;
    std::vector<mapContents> seedToSoil;
    std::vector<mapContents> soilToFert;
    std::vector<mapContents> fertToWater;
    std::vector<mapContents> waterToLight;
    std::vector<mapContents> lightToTemp;
    std::vector<mapContents> tempToHum;
    std::vector<mapContents> humToLoc;
    std::string line;
    std::ifstream infile("input.txt");
    while(!infile.eof())
    {
        std::getline(infile, line);
        if(seeds.empty())
        {
            int pos = line.find(":");
            line = line.substr(pos + 1);
            std::istringstream iss1(line);
            std::string word;
            while(iss1 >> word)
            {
                seeds.push_back(stoull(word));
            }
        }
        else
        {
            if (line == "seed-to-soil map:") {
            readMap(infile, seedToSoil);
            } 
            else if (line == "soil-to-fertilizer map:") {
                readMap(infile, soilToFert);
            } 
            else if (line == "fertilizer-to-water map:") {
                readMap(infile, fertToWater);
            }
            else if (line == "water-to-light map:") {
                readMap(infile, waterToLight);
            } 
            else if (line == "light-to-temperature map:") {
                readMap(infile, lightToTemp);
            }
            else if (line == "temperature-to-humidity map:") {
                readMap(infile, tempToHum);
            } 
            else if (line == "humidity-to-location map:") {
                readMap(infile, humToLoc);
            }
        }
    }
    unsigned long long smallestLoc = 0;
    for(unsigned long long seed : seeds)
    {
        seed = findnextID(seedToSoil, seed);
        seed = findnextID(soilToFert, seed);
        seed = findnextID(fertToWater, seed);
        seed = findnextID(waterToLight, seed);
        seed = findnextID(lightToTemp, seed);
        seed = findnextID(tempToHum, seed);
        seed = findnextID(humToLoc, seed);
        if(smallestLoc == 0)
        {
            smallestLoc = seed;
        }
        else if(seed < smallestLoc)
        {
            smallestLoc = seed;
        }
    }

    printf("The lowest location number is: %d", smallestLoc);


}
