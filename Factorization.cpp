//
// Created by Маргарита on 28.10.2017.
//

#include "Factorization.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

Factorization::Factorization(uint64_t inputNum) : number(inputNum) {
    fillPrimeMultiplier();
}

void Factorization::fillPrimeMultiplier() {
    primeMultiplier.push_back(1);
    if (isPrime()) {
        primeMultiplier.push_back(number);
    } else {
        factorize();
    }
}


bool Factorization::isPrime() {
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void Factorization::factorize() {
    uint64_t curNumber = number;
    for (uint64_t i = 2; i <= sqrt(curNumber) + 1; i++) {
        while (curNumber % i == 0) {
            primeMultiplier.push_back(i);
            curNumber = curNumber / i;
        }
    }

    if (curNumber != 1) {
        primeMultiplier.push_back(curNumber);
    }

}

string Factorization::getFactors() {
    string s;
    s = "Factorization of " + to_string(number) + " is : ";
    for (uint64_t i : primeMultiplier) {
        s += to_string(i) + " ";
    }
    return s;
}