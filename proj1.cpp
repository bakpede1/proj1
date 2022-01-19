/*****************************************

 ** File:    Proj1.cpp

 ** Author:  Blossom Akpedeye

 ** Date:    9/30/21


 ** This file contains the main driver program for Project 1.

 ** This program reads the file specified by the user,

 ** displays the file's word search and stores words

 ** to look for, before commencing the word search game.

 ***********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int ROWS = 15;
const int COLUMNS = 15;
const int NUM_OF_WORDS = 10;
const string EMPTY_SPACE = "";


// Name: getFileName
// PreCondition: None
// PostCondition: returns the fileName
string getFileName();


// Name: loadFile
// PreCondition: gets the file, word search
//               array and words to search for array
// PostCondition: populates the word search
//                and the words to search for arrays
void loadFile(string file, char wordSearch[][COLUMNS], string searchWords[]);


// Name: displayPuzzle
// PreCondition: gets word search grid
//               and array of words to search
// PostCondition: displays word search puzzle
void displayPuzzle(char searchGrid[][COLUMNS], string remWords[]);

// Name: buildWord
// PrecCondition: gets the grid
// PostCondition: builds word using starting
//                and ending (x,y) values,
//                and returns the built word
string buildWord(char searchGrid[][COLUMNS]);


// Name: checkWord
// PreCondition: gets built word
// PostCondition: compares the built word
//                with the list of rem words
void checkWord(string builtWord, string remWords[]);


// Name: gameOver
// PreCondition: gets the list of rem words
// PostCondition: returns boolean value
//                showing if game is over
bool gameOver(string remWords[]);


int main() {
  char wordSearch[ROWS][COLUMNS];
  string wordsToFind[NUM_OF_WORDS];

  cout << "Welcome to UMBC Word Search" << endl;

  bool isGameOver = false;

  // loads user's game file
  loadFile(getFileName(), wordSearch, wordsToFind);

  // plays game functions until game is over
  while (!isGameOver) {
    displayPuzzle(wordSearch, wordsToFind);
    string userBuiltWord = buildWord(wordSearch);
    checkWord(userBuiltWord, wordsToFind);
    isGameOver = gameOver(wordsToFind);
  }

  cout << "Thank you for playing UMBC Word Search!" << endl;

  return 0;
}

// Name: getFileName
// PreCondition: None
// PostCondition: returns the fileName
string getFileName() {
  string fileName;
  cout << "What is the name of file you would like to load?" << endl;
  cin >> fileName;

  return fileName;
}

// Name: loadFile
// PreCondition: gets the file, word search
//               array and words to search for array
// PostCondition: populates the word search
//                and the words to search for arrays
void loadFile(string file, char wordSearch[][COLUMNS], string searchWords[]) {

  string word;
  char letter;
  string newFile;
  int numOfLetters = 0;
  int numOfWords = 0;
   
  ifstream inputStream(file);

  // validates if file exists
  while (!inputStream.is_open()) {
    cout << "That file does not exist" << endl;
    cout << "Please re-enter file name:" << endl;
    cin >> newFile;
    inputStream.open(newFile);
  }
  
  // populates the grid
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      inputStream >> letter;
      wordSearch[i][j] = letter;
      numOfLetters++; // counts each letter in the file
    }
  }

  // populates the words list
  for (int i = 0; i < NUM_OF_WORDS; i++) {
    inputStream >> word;
    searchWords[i] = word;
    numOfWords++; // counts each word in the file
  }

  inputStream.close();
  
  cout << numOfLetters << " letters imported." << endl;
  cout << numOfWords << " words imported." << endl;

}

// Name: displayPuzzle
// PreCondition: gets word search grid
//               and array of words to search
// PostCondition: displays word search puzzle
void displayPuzzle(char searchGrid[][COLUMNS], string remWords[]) {

  // prints header
  cout << "     0   1   2   3   "
                "4   5   6   7   8   "
    "9  10  11  12  13  14" << endl;

  // displays full word search grid
  for (int i = 0; i < ROWS; i++) {
    cout << setw(3) << i << "  ";
    for (int j = 0; j < COLUMNS; j++) {
      cout << searchGrid[i][j] << "   ";
    }
    cout << "\n";
  }

  cout << "\n" << "*********REMAINING WORDS*********" << endl;

  // displays list of words to find
  for (int i = 0; i < NUM_OF_WORDS; i++) {
    if (remWords[i] != EMPTY_SPACE) {
      cout << remWords[i] << endl;
    }
  }

}

// Name: buildWord
// PrecCondition: gets the grid
// PostCondition: builds word using starting
//                and ending (x,y) values,
//                and returns the built word
string buildWord(char searchGrid[][COLUMNS]) {

  int startX;
  int startY;
  int endX;
  int endY;
  string fullWord = EMPTY_SPACE;

  cout << "What is the starting X Y (separated by a space)?" << endl;
  cin >> startX >> startY;

  cout << "What is the ending X Y (separated by a space)?" << endl;
  cin >> endX >> endY;

  // validates input for valid grid point
  while (((0 > startX || startX > 14) || (0 > startY || startY > 14))
         || ((0 > endX || endX > 14) || (0 > endY || endY > 14))) {

    cout << "That point is not in the grid" << endl;

    cout << "What is the starting X Y (separated by a space)?" << endl;
    cin >> startX >> startY;

    cout << "What is the ending X Y (separated by a space)?" << endl;
    cin >> endX >> endY;

  }

  // checks the direction of user's search
  if ((startX > endX) && (startY > endY)) {
    // diagonal up from R to L
    int x = startX;
    int y = startY;

    while ((x > endX - 1) && (y > endY - 1)) {
      fullWord += searchGrid[x][y];
      x--;
      y--;
    }

  } else if ((startX > endX) && (startY < endY)) {
    // diagonal up from L to R
    int x = startX;
    int y = startY;

    while ((x > endX - 1) && (y < endY + 1)) {
      fullWord += searchGrid[x][y];
      x--;
      y++;
    }

  } else if ((startX < endX) && (startY < endY)) {
    // diagonal down from L to R
    int x = startX;
    int y = startY;

    while ((x < endX + 1) && (y < endY + 1)) {
      fullWord += searchGrid[x][y];
      x++;
      y++;
    }

  } else if ((startX < endX) && (startY > endY)) {
    // diagonal down from R to L
    int x = startX;
    int y = startY;

    while ((x < endX + 1) && (y > endY - 1)) {
      fullWord += searchGrid[x][y];
      x++;
      y--;
    }

  } else if (startX > endX) {
    // up
    for (int x = startX; x > endX - 1; x--) {
      fullWord += searchGrid[x][endY];
    }

  } else if (startX < endX) {
    // down
    for (int x = startX; x < endX + 1; x++) {
      fullWord += searchGrid[x][endY];
    }

  } else if (startY < endY) {
    // right
    for (int y = startY; y < endY + 1; y++) {
      fullWord += searchGrid[endX][y];
    }

  } else if (startY > endY) {
    // left
    for (int y = startY; y > endY - 1; y--) {
      fullWord += searchGrid[endX][y];
    }

  }

  return fullWord;
}


// Name: checkWord
// PreCondition: gets built word
// PostCondition: compares the built word
//                with the list of rem words
void checkWord(string builtWord, string remWords[]) {
  
  int count = 0;
  int len = builtWord.length();
  bool found = false;
  
  // loops until a match is found
  do {

    if ((builtWord == remWords[count])) {

      cout << "You found the word " << remWords[count] << "!" << endl;
      found = true;
      remWords[count] = "";

    } else {
      count++;
    }
    
  } while ((count < NUM_OF_WORDS) && (!found));

  // if user doesn't get the word
  if (count == NUM_OF_WORDS) {
    cout << "You didn't find a word on the list" << endl;
  }

}

// Name: gameOver
// PreCondition: gets the list of rem words
// PostCondition: returns boolean value
//                showing if game is over
bool gameOver(string remWords[]) {

  int count = 0;
  bool over = false;

  // checks how many words are found
  for (int i = 0; i < NUM_OF_WORDS; i++) {
    if (remWords[i] == EMPTY_SPACE) {
      count++;
    }
  }

  over = (count == 10);

  return over;
}
