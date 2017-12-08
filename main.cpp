#include <iostream>
#include "Factorization.h"
#include "FileFactorise.h"
#include <thread>

using namespace std;

/*void checkAnswer (string answ){

}

void func(string nameOfFile) {
    FileFactorise MyF(nameOfFile);
    string answer;
    cin >> answer;
    checkAnswer(answer);
} */



int main() {
    //uint64_t num;
    //string myString;
    int numberOfThreads;
  string fileName = "numbersToFactorise.txt";
    cin >> numberOfThreads;
   FileFactorise MyF(fileName, numberOfThreads);
   MyF.startDialog();




}