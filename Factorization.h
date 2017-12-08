//
// Created by Маргарита on 28.10.2017.
//

#pragma once

#include <vector>
#include <cstdint>
#include <string>

class Factorization {
public:
    Factorization(uint64_t inputNum);

    void factorize();

    std::string getFactors();

private:
    std::vector<uint64_t> primeMultiplier;

    void fillPrimeMultiplier();

    const uint64_t number;

    bool isPrime();
};


