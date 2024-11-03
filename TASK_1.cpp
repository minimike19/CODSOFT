//Task 1
//NUMBER GUESSING GAME
//Create a program that generates a random number and asks the user to guess it. Provide feedback 
//on whether the guess is too
//high or too low until the user guesses the correct number.
#include <iostream>
#include <random>
using namespace std;

int main() {
    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "The rules of the game are simple:" << endl;
    cout << "1. The computer will generate a number from 1-100." << endl;
    cout << "2. The computer will give hints whether the number you are guessing" << endl;
    cout << "   is too high or too low." << endl;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 100);
    int randomNumber = distr(gen);

    int guessedNumber;
    cout << "Enter your guessed number: ";
    cin >> guessedNumber;

    while (guessedNumber != randomNumber) {
    	
        if (guessedNumber > randomNumber) {
            cout << "Too high! Try again: ";
        } else {
            cout << "Too low! Try again: ";
        }
        cin >> guessedNumber;
    }

    cout << "Congratulations! You guessed the correct number: " << randomNumber << endl;

    return 0;
}
