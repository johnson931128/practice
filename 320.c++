#include <iostream>
#include <limits> // Add this line to include the <limits> header
using namespace std;

int main() {
    int target = 7; // Set the target number
    int guess = 0; // Store the user's guess

    cout << "Guess the number (between 1 and 10): ";

    while (guess != target) {
        cin >> guess;

        if (cin.fail()) {
            cin.clear(); // Clear the input error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the characters after the error input
            cout << "Please enter a number." << endl;
            continue;
        }

        if (guess < target) {
            cout << "Too low, try again: ";
        } else if (guess > target) {
            cout << "Too high, try again: ";
        } else {
            cout << "Congratulations, you guessed it right!" << endl;
        }
    }

    return 0;
}