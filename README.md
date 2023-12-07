# AoC23
AoC 2023 work

# Day 1
  ## Part 1: 
    1. Parsed each line of the input, each character in the string, and found first num. Stored these as strings to make later processing easier.  
    2. When found automatically set the second number to the same in case there is only 1 number on the line. 
    3. Then parse the rest of the characters and continue to update the number if we find another int in the line.
    4. Combine the strings for first and second numbers to create the 2 digit number represented as a string. 
    5. Convert the string to an integer and add this to a running total.
    6. When all lines processed, print the running total to get the answer.
  ## Part 2:
    1. Had to rework processing the numbers to include the words.
    2. Read each character and if a digit, set first/second.
    3. If character, add to a temp string to try to build a word.
    4. After adding the character, check if the temp string contains a number spelled out. Set the number we're investigating(one or two) to the string.
    5. Then Set the Temp String to the current string's last character and continue adding letters. This solves the overlapping word problem(TWONE is both Two and One, with One being the number further along in the string).
    6. When we have the "last" number in the line, if it's a word we convert the word to the actual number(still a string, but using the numerical character).
    7. Follow the same process as above starting at step 4.
# Day 2
  ## Part 1: 
  1. Parsed each line of input, removing the word Game and grabbing the current GameID. 
  2. Then looped through the rest of the line for the colors and their cube. 
  3. Every pass I checked to see if the round was valid and flipped a bool if not. 
  4. When reaching a semi-colon, reset the map. 
  5. If a game was valid, add it's ID to total. 
  ## Part 2: 
  1. Similar break down at the beginning. Removed the reset of the map until each line was done. 
  2. Simply checked if the current map's number of a color was the highest number. If not, replace with the higher number. 
  3. At the end of each loop just add r*b*g values. 


