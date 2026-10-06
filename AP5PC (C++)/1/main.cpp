#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void calculateFactorial();
void enterKeyToContinue();
void guessTheNumber();
void bubbleSortInit();
int* bubbleSort(int n[]);

#define MAX_ATTEMPTS 5

int main(){
    int option = 0;
    do {
        cout << "\nChose an option: " << endl;
        cout << "1. Factorial\n2. Guess the number\n3. Bubble sort\n";
        cout << "9. Exit\n\n" << endl;
        cin >> option;
        switch(option){
            case 1:
                calculateFactorial();
                break;
            case 2:
                guessTheNumber();
                break;
            case 3:
                bubbleSortInit();
                break;
            default:
                break;
        }
    } while(option != 9);

    
    return 0;
}

void calculateFactorial(){
    int n = 1;
    cout << "\n\n\nEnter a number: ";
    cin >> n;
    int result = 1;
    for(int i = 1; i <= n; i++){
        result *= i;
    }
    cout << "Factorial of " << n << " is " << result << endl;
    ofstream file("last_factorial.txt");
    if(file.is_open()){
        file << "Factorial of " << n << " is " << result << endl;
        file.close();
    }

    enterKeyToContinue();
}
void guessTheNumber(){
    srand(time(nullptr));
    int numberToGuess = rand() % 80;
    int userGuess = -1;
    int leftAttempts = MAX_ATTEMPTS;
    while(leftAttempts > 0){
        cout << "\n\n\nGuess the number (0-79): ";
        cin >> userGuess;
        if(userGuess == numberToGuess){
            cout << "\nCongratulations! You guessed the number correctly!" << endl;
            break;
        }else{
            cout << "\nIncorrect guess. You have " << --leftAttempts << " attempts left." << endl;
        }
        cout << "\n\n";
    }
    if(userGuess != numberToGuess){
        cout << "\nSorry! The correct number was " << numberToGuess << "." << endl;
    }else{
        cout << "\nYou guessed the number correctly!" << endl;
    }
    enterKeyToContinue();
}
void bubbleSortInit(){
    int n[100] = {};
    int i = 0;
    int userInput = 1;
    while(userInput != 0){
        cout << "\nEnter a number to add to the array (0 to stop): ";
        cin >> userInput;
        if(userInput != 0){
            n[i++] = userInput;
        }
    }
    int* sorted = bubbleSort(n);
    cout << "\nSorted array: ";
    int currentSize = 0;
    while(sorted[currentSize] != 0){
        cout << sorted[currentSize] << " ";
        currentSize++;
    }
    cout << endl;
    enterKeyToContinue();
}
int* bubbleSort(int n[]){
    int currentSize = 0;
    while(n[currentSize] != 0){
        currentSize++;
    }
    cout << currentSize << endl;
    for(int j = 0; j < currentSize-1; j++){
        for(int k = 0; k < currentSize-j-1; k++){
            if(n[k] > n[k+1]){
                int temp = n[k];
                n[k] = n[k+1];
                n[k+1] = temp;
            }
        }
    }
    return n;
}
void enterKeyToContinue(){
    cout << "\n\nPress Enter to continue..." << endl;
    cin.ignore();
    cin.get(); 
}