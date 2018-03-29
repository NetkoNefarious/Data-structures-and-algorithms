#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <ctime>

/* C++98
const string wordsArray[] = {"word", "hangman", "language", "mathematics"};
const vector<string> words(wordsArray, wordsArray+(sizeof(wordsArray) / sizeof(wordsArray[0])));*/

using namespace std;

// I separated this so that the Ascii is a little easier to improve upon
vector<string> VectorHangman(const int maxMistakes)
{
    vector<string> hangmanAscii(maxMistakes + 1);
    
    hangmanAscii[0] = string (" ___\n  | \n"); // Empty gallows
    hangmanAscii[1] = string (" ___\n  | \n  O \n"); // Head
    hangmanAscii[2] = string (" ___\n  | \n  O \n  | \n"); // +torso
    hangmanAscii[3] = string (" ___\n  | \n  O \n /| \n"); // +left arm
    hangmanAscii[4] = string (" ___\n  | \n  O \n /|\\\n"); // +right arm
    hangmanAscii[5] = string (" ___\n  | \n  O \n /|\\\n /\n"); // +left leg
    hangmanAscii[6] = string(" ___\n  | \n  O \n /|\\\n / \\\n"); // +right leg

    return hangmanAscii;
}

void DrawBoard(vector<string>& hangmanAscii, string word, vector<char> wrongLetters, string correctString, int mistakes)
{
    cout << hangmanAscii[mistakes] << endl;

    cout << "Mistakes: " << mistakes << endl;
    cout << "Wrong letters:";
    copy(wrongLetters.begin(), wrongLetters.end(), ostream_iterator<char>(cout, " ")); // Prints all this out neatly to cout
    cout << endl;

    cout << "Correct:";
    copy(correctString.begin(), correctString.end(), ostream_iterator<char>(cout, " ")); // Prints all this out neatly to cout
    cout << endl << endl;
}

void CheckLetter(char letter, string word, vector<char>& wrongLetters, string& correctString, int& mistakes)
{
    // Letter that's already been guessed
    if (find(wrongLetters.begin(), wrongLetters.end(), letter) != wrongLetters.end() ||
        find(correctString.begin(), correctString.end(), letter) != correctString.end())
    {
        cout << "You already put in that letter. Try another letter." << endl;
        return;
    }

    unsigned pos;

    // Wrong letter
    if ( (pos = word.find(letter, 0) ) == word.npos)
    {
        wrongLetters.push_back(letter);
        mistakes++;
    }

    // Correct letter
    else
    {
        do
        {
            correctString[pos] = letter;
        } while ( (pos = word.find(letter, pos+1) ) != word.npos);
    }
}

bool CheckWinLossState(string word, string correctString, const int mistakes, const int maxMistakes)
{
    if (word == correctString)
    {
        cout << "Pobjeda!" << endl;
        return true;
    }

    else if (mistakes >= maxMistakes)
    {
        cout << "Poraz!" << endl;
        return true;
    }

    return false;
}

int main()
{
    srand(time(NULL));
    const int maxMistakes = 6;
    vector<string> hangmanAscii = VectorHangman(maxMistakes);
    const vector<string> words {"word", "hangman", "language", "mathematics"};     // C++11

    while (true)
    {
        int randomNum = rand() % words.size(); // Parametrizes the random index number
        string correctString(words[randomNum].length(), '_'); // We will save correct letters guessed here
        int mistakes = 0;
        vector<char> wrongLetters(1);
        char letter; // This is where we put in the guess that the user inputs

        bool isOver = false; // A flag that checks if the game is over
        do
        {
            DrawBoard(hangmanAscii, words[randomNum], wrongLetters, correctString, mistakes);

            cout << "Guess a letter: ";
            cin >> letter;
            cout << "---" << endl;

            CheckLetter(letter, words[randomNum], wrongLetters, correctString, mistakes);
            isOver = CheckWinLossState(words[randomNum], correctString, mistakes, maxMistakes);
        } while (!isOver );

        cout << "Rijec: " << words[randomNum] << endl;
        cout << "Do you want to play again? (y/n)" << endl;
        cin >> letter;
        if (letter == 'n')
            break;
    }

    return 0;
}
