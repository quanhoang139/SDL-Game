#include<iostream>
#include<SDL.h>
#include<time.h>
#include<random>

using namespace std;

const string wordlist[] = {"dog", "cat", "book"};
const int word_count = sizeof(wordlist)/sizeof(string);
string chooseWord()
{
    int randomIndex = rand() % word_count;
    return wordlist[randomIndex];
}

const string figue[]= {"fig0", "fig1", "fig2", "fig3", "fig4", "fig5", "fig6", "fig7"};
void renderGame(string guessedWord, int badGuessCount)
{
    cout<<figue[badGuessCount]<<endl;
    cout<<guessedWord<<endl;
    cout<<"Number of wrong guesses: "<<badGuessCount<<endl;
}

string update(string guessedWord, string secretWord, char guess)
{
    for(int i = secretWord.length() - 1; i >= 0; i--)
        if(secretWord[i] == guess) guessedWord[i] = guess;
    return guessedWord;
}

char readAGuess()
{
    char word;
    cin >> word;
    return word;
}

bool contains(string secretWord, char guess)
{
    for(int i = 0; i < secretWord.length(); ++i)
        if(secretWord[i] == guess) return true;
    return false;
}

int main(int argc, char* args[])
{
    srand(time(NULL));
    string secretWord = chooseWord();
    string guessedWord = string(secretWord.length(), '-');
    int badGuessCount = 0;
    do{
        renderGame(guessedWord, badGuessCount);
        char guess = readAGuess();
        if(contains(secretWord, guess))
            guessedWord = update(guessedWord, secretWord, guess);
        else badGuessCount++;
    } while(badGuessCount < 7 && secretWord != guessedWord);

    renderGame(guessedWord, badGuessCount);
    if(badGuessCount < 7) cout<<"Congratulations! You win!";
    else cout<<"You lost. The word is "<< secretWord;
}
