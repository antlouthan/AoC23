#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

struct Number {
    int row, col;
    int value;
    std::set<std::pair<int, int>> adjacentStars;

    Number(int r, int c, int val) : row(r), col(c), value(val) {}

    void addStar(int starRow, int starCol) {
        adjacentStars.insert({starRow, starCol});
    }
};

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int extractNumber(const std::vector<std::string>& grid, int row, int& col) {
    std::string numStr;
    int startCol = col;
    while (col < grid[0].size() && isDigit(grid[row][col])) {
        numStr += grid[row][col];
        col++;
    }
    return std::stoi(numStr);
}

void checkAdjacentStars(const std::vector<std::string>& grid, Number& number) {
    int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    // Calculate the length of the number
    int length = std::to_string(number.value).length();

    for (int digitIndex = 0; digitIndex < length; digitIndex++) {
        for (auto& d : dir) {
            int ni = number.row + d[0];
            int nj = number.col + digitIndex + d[1];
            if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[0].size() && grid[ni][nj] == '*') {
                number.addStar(ni, nj);
            }
        }
    }
}

int main() {
    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(inFile, line)) {
        grid.push_back(line);
    }
    inFile.close();

    std::vector<Number> numbers;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size();) {
            if (isDigit(grid[i][j])) {
                int startCol = j;
                int num = extractNumber(grid, i, j);
                Number number(i, startCol, num);
                checkAdjacentStars(grid, number);
                numbers.push_back(number);
            } else {
                j++;
            }
        }
    }

    long long totalGearRatio = 0;
    std::set<std::pair<int, int>> processedPairs;

    for (int i = 0; i < numbers.size(); i++) {
        for (int j = i + 1; j < numbers.size(); j++) {
            // Check if the pair (i, j) has already been processed
            if (processedPairs.find({i, j}) != processedPairs.end()) {
                continue;
            }

            // Check for shared star positions
            for (const auto& starPos : numbers[i].adjacentStars) {
                if (numbers[j].adjacentStars.find(starPos) != numbers[j].adjacentStars.end()) {
                    totalGearRatio += static_cast<long long>(numbers[i].value) * numbers[j].value;
                    processedPairs.insert({i, j});
                    break; // Break to avoid double counting for multiple shared stars
                }
            }
        }
    }

    std::cout << "Total sum of gear ratios: " << totalGearRatio << std::endl;

    return 0;
}




