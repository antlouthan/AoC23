#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <future>
#include <mutex>





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
struct seedContents
{
    unsigned long long startNum, endNum;
};
struct mapContents
{
    unsigned long long destRangeStart, sourceRangeStart, rangeLength;
};

std::mutex consoleMutex; // Mutex for synchronizing console output

// Define a comparator for sorting
bool compareMapContents(const mapContents& a, const mapContents& b) {
    return a.sourceRangeStart < b.sourceRangeStart;
}

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

unsigned long long findnextID(const std::vector<mapContents>& map, unsigned long long curr) {
    auto it = std::lower_bound(map.begin(), map.end(), curr, 
        [](const mapContents& m, unsigned long long value) {
            return m.sourceRangeStart + m.rangeLength <= value;
        });

    if (it != map.end() && curr >= it->sourceRangeStart && curr < it->sourceRangeStart + it->rangeLength) {
        return it->destRangeStart + (curr - it->sourceRangeStart);
    }
    return curr;
}

unsigned long long processSeedRange(const std::vector<mapContents>& seedToSoil, 
                                    const std::vector<mapContents>& soilToFert, 
                                    const std::vector<mapContents>& fertToWater, 
                                    const std::vector<mapContents>& waterToLight,
                                    const std::vector<mapContents>& lightToTemp, 
                                    const std::vector<mapContents>& tempToHum, 
                                    const std::vector<mapContents>& humToLoc,
                                    unsigned long long start, unsigned long long end, 
                                    unsigned long long& processedCount) {
    unsigned long long localSmallestLoc = ULLONG_MAX;
    for (unsigned long long i = start; i <= end; ++i) {
        unsigned long long tmp = i;
            tmp = findnextID(seedToSoil, tmp);
            tmp = findnextID(soilToFert, tmp);
            tmp = findnextID(fertToWater, tmp);
            tmp = findnextID(waterToLight, tmp);
            tmp = findnextID(lightToTemp, tmp);
            tmp = findnextID(tempToHum, tmp);
            tmp = findnextID(humToLoc, tmp);
            if(tmp > 0)
            {
                localSmallestLoc = std::min(localSmallestLoc, tmp);
            }
        localSmallestLoc = std::min(localSmallestLoc, tmp);
         // Logging progress
        {
            std::lock_guard<std::mutex> lock(consoleMutex);
            if (++processedCount % 1000000 == 0) { // Adjust frequency as needed
                std::cout << "Processed " << processedCount << " seeds..." << std::endl;
            }
        }
    }
    return localSmallestLoc;
}

int main()
{
    std::vector<seedContents> seeds;
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
        if (line.find("seeds:") != std::string::npos) {
            std::istringstream iss(line.substr(line.find(":") + 1));
            unsigned long long start, length;
            while (iss >> start >> length) {
                seeds.push_back({start, start + length - 1});
            }
        }

        if (line.find("seed-to-soil map:") != std::string::npos) {
        readMap(infile, seedToSoil);
        continue;
        } 
        else if (line.find("soil-to-fertilizer map:") != std::string::npos) {
            readMap(infile, soilToFert);
            continue;
        } 
        else if (line.find("fertilizer-to-water map:") != std::string::npos) {
            readMap(infile, fertToWater);
            continue;
        }
        else if (line.find("water-to-light map:") != std::string::npos) {
            readMap(infile, waterToLight);
            continue;
        } 
        else if (line.find("light-to-temperature map:") != std::string::npos) {
            readMap(infile, lightToTemp);
            continue;
        }
        else if (line.find("temperature-to-humidity map:") != std::string::npos) {
            readMap(infile, tempToHum);
            continue;
        } 
        else if (line.find("humidity-to-location map:") != std::string::npos) {
            readMap(infile, humToLoc);
            continue;
        }
    }
    std::sort(seedToSoil.begin(), seedToSoil.end(), compareMapContents);
    std::sort(soilToFert.begin(), soilToFert.end(), compareMapContents);
    std::sort(fertToWater.begin(), fertToWater.end(), compareMapContents);
    std::sort(waterToLight.begin(), waterToLight.end(), compareMapContents);
    std::sort(lightToTemp.begin(), lightToTemp.end(), compareMapContents);
    std::sort(tempToHum.begin(), tempToHum.end(), compareMapContents);
    std::sort(humToLoc.begin(), humToLoc.end(), compareMapContents);

     unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::future<unsigned long long>> futures;
    unsigned long long totalProcessedCount = 0; // Total seeds processed

    // Process each seed range
    std::cout << "Starting to process seed ranges..." << std::endl;
    size_t totalSeedsProcessed = 0; // Total seeds processed across all ranges
    printf("%d number of seeds total!\n", seeds.size());
     // Launch concurrent tasks
    for (const auto& seed : seeds) {
        unsigned long long range = (seed.endNum - seed.startNum + 1) / numThreads;
        for (unsigned int i = 0; i < numThreads; ++i) {
            unsigned long long start = seed.startNum + i * range;
            unsigned long long end = (i == numThreads - 1) ? seed.endNum : start + range - 1;
            futures.push_back(std::async(std::launch::async, processSeedRange, 
                                         std::ref(seedToSoil), std::ref(soilToFert), 
                                         std::ref(fertToWater), std::ref(waterToLight),
                                         std::ref(lightToTemp), std::ref(tempToHum),
                                         std::ref(humToLoc),
                                         start, end, std::ref(totalProcessedCount)));
        }
    }
    // Retrieve results from futures and find the smallest location
    unsigned long long smallestLoc = ULLONG_MAX;
    for (auto& future : futures) {
        smallestLoc = std::min(smallestLoc, future.get());
    }

    std::cout << "Total seeds processed: " << totalProcessedCount << std::endl;
    std::cout << "The lowest location number is: " << smallestLoc << std::endl;
    return 0;
}
