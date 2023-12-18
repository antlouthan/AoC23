#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <queue>

using namespace std;

struct scratchCard
{
    int cardID;
    std::vector<int> winNums;
    std::vector<int> cardNums;
    int numWins;

    void checkWinningNums(std::vector<int> wins, std::vector<int> nums)
    {
        int howMany = 0;
        for(int i = 0; i < wins.size(); i++)
        {
            for(int j=0; j<nums.size(); j++)
            {
                if (wins[i] == nums[j])
                {
                    howMany++;
                }
            }
        }
        numWins = howMany;
    }

};

int processCards(std::vector<scratchCard>& cards) {
    int totalCards = 0; // Initialize the total count of scratchcards
    std::queue<scratchCard> queue; // Queue to hold cards for processing

    // Initially add all original cards to the queue
    for (const auto& card : cards) {
        queue.push(card);
    }

    while (!queue.empty()) {
        scratchCard currentCard = queue.front();
        queue.pop();

        totalCards++; // Count the current card

        // Process wins and add copies of subsequent cards
        for (int w = 0; w < currentCard.numWins; ++w) {
            int nextID = currentCard.cardID + w;
            if (nextID < cards.size()) { // Ensure we're within bounds
                queue.push(cards[nextID]);
            }
        }
    }

    return totalCards;
}



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



int main()
{
    std::ifstream infile("input.txt");
    int totalCards = 0;
    string line;
    std::vector<scratchCard> cards;
    while(!infile.eof())
    {
        scratchCard tmpCard;
        std::getline(infile, line);
        int pos = line.find(":");
        string cardNum = line.substr(0, pos);
        std::istringstream iss0(cardNum);
        string word;
        while (iss0 >> word)
        {
            if(word == "Card")
            {
                continue;
            }
            tmpCard.cardID = stoi(word);
        }
        line = line.substr(pos + 1);
        int pos2 = line.find("|");
        string gameNumStr = line.substr(0, pos2);
        string winNumStr = line.substr(pos2+1);
        std::istringstream iss1(gameNumStr);
        while(iss1 >> word)
        {
            tmpCard.cardNums.push_back(stoi(word));
        }
        std::istringstream iss2(winNumStr);
        while(iss2 >> word)
        {
            tmpCard.winNums.push_back(stoi(word));
        }
        tmpCard.checkWinningNums(tmpCard.cardNums, tmpCard.winNums);
        if( tmpCard.numWins > 0)
        {
            totalCards += calculateScore(tmpCard.numWins);
        }
        cards.push_back(tmpCard);
    }
    printf("%i\n", totalCards);
    printf("%i", processCards(cards));
}