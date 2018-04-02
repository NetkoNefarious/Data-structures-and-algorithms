#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <ctime>

using namespace std;

vector<string> VectorHangman(const int maxMistakes)
{
    vector<string> hangmanAscii(maxMistakes + 1);

    hangmanAscii[0] = string (" ___\n  | \n");
    hangmanAscii[1] = string (" ___\n  | \n  O \n");
    hangmanAscii[2] = string (" ___\n  | \n  O \n  | \n");
    hangmanAscii[3] = string (" ___\n  | \n  O \n /| \n");
    hangmanAscii[4] = string (" ___\n  | \n  O \n /|\\\n");
    hangmanAscii[5] = string (" ___\n  | \n  O \n /|\\\n /\n");
    hangmanAscii[6] = string(" ___\n  | \n  O \n /|\\\n / \\\n");

    return hangmanAscii;
}

void DrawBoard(vector<string>& hangmanAscii, vector<char> wrongLetters, string correctString, int mistakes)
{
    cout << hangmanAscii[mistakes] << endl;

    cout << "Mistakes: " << mistakes << endl;
    cout << "Wrong letters:";
    copy(wrongLetters.begin(), wrongLetters.end(), ostream_iterator<char>(cout, " "));
    cout << endl;

    cout << "Correct:";
    copy(correctString.begin(), correctString.end(), ostream_iterator<char>(cout, " "));
    cout << endl << endl;
}

void CheckLetter(char letter, string word, vector<char>& wrongLetters, string& correctString, int& mistakes)
{
    if (find(wrongLetters.begin(), wrongLetters.end(), letter) != wrongLetters.end() ||
        find(correctString.begin(), correctString.end(), letter) != correctString.end())
    {
        cout << "You already put in that letter. Try another letter." << endl;
        return;
    }

    unsigned pos;

    if ( (pos = word.find(letter, 0) ) == word.npos)
    {
        wrongLetters.push_back(letter);
        mistakes++;
    }

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
    // 1. Set constants
    srand(time(NULL));
    const int maxMistakes = 6;
    vector<string> hangmanAscii = VectorHangman(maxMistakes);
    const string wordsArray[] = {"word", "hangman", "language", "mathematics"};
    const vector<string> words(wordsArray, wordsArray+(sizeof(wordsArray) / sizeof(wordsArray[0])));

    while (true)
    {
        // 2. Set variables that can be changed if the user wants to play again
        int randomIndex = rand() % words.size(); // Chooses a word randomly
        string correctString(words[randomIndex].length(), '_'); // Stores correct letters here
        int mistakes = 0;
        vector<char> wrongLetters(1);
        char letter;

        // 3. Main game variable
        bool isOver = false;
        do
        {
            DrawBoard(hangmanAscii, wrongLetters, correctString, mistakes);

            cout << "Guess a letter: ";
            cin >> letter;
            cout << "---" << endl;

            CheckLetter(letter, words[randomIndex], wrongLetters, correctString, mistakes);
            isOver = CheckWinLossState(words[randomIndex], correctString, mistakes, maxMistakes);
        } while (!isOver );

        // 4. Ask if the player wants to play again
        cout << "Rijec: " << words[randomIndex] << endl;
        cout << "Do you want to play again? (y/n)" << endl;
        cin >> letter;

        if (letter == 'n')
            break;
    }
}
