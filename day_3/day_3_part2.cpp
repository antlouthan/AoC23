#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Function to check if a character is a digit
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Function to extract a number starting from a given position in the grid
int extractNumber(const std::vector<std::string>& grid, int row, int col, int rowDir, int colDir) {
    std::string numStr;
    while (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() && isDigit(grid[row][col])) {
        numStr += grid[row][col];
        row += rowDir;
        col += colDir;
    }
    return numStr.empty() ? -1 : std::stoi(numStr);
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

    long long totalGearRatio = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '*') {
                std::vector<int> adjacentNumbers;

                // Directions to check all 8 surrounding cells
                int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

                for (auto& d : dir) {
                    int num = extractNumber(grid, i + d[0], j + d[1], d[0], d[1]);
                    if (num != -1) {
                        adjacentNumbers.push_back(num);
                        if (adjacentNumbers.size() > 2) break; // Stop if more than two numbers found
                    }
                }

                if (adjacentNumbers.size() == 2) {
                    totalGearRatio += static_cast<long long>(adjacentNumbers[0]) * adjacentNumbers[1];
                }
            }
        }
    }

    std::cout << "Total sum of gear ratios: " << totalGearRatio << std::endl;

    return 0;
}
