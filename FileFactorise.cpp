//
// Created by Маргарита on 30.10.2017.
//

#include "FileFactorise.h"
#include "Factorization.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <thread>

using namespace std;

FileFactorise::FileFactorise(string &f, int n) : fileName(f), numberOfThreads(n) {
    start();
}

void FileFactorise::startDialog() {
    string userAnswer;
    while (!isFileReaded || !numbersByProducer.empty()) {
        cin >> userAnswer;
        if (userAnswer == "exit") {
            stop();
            break;
        }
        if (userAnswer == "pause") {
            isPause = true;
        }
        if (userAnswer == "resume") {
            isPause = false;
            condition.notify_all();
        }
    }
}

void FileFactorise::stop() {
    isFileReaded = true;
    queue<uint64_t> emptyQueue;
    swap(emptyQueue, numbersByProducer);
}

void FileFactorise::joinThreads() noexcept {
    if (producer.joinable()) {
        producer.join();
    }
    for (auto& i : consumer) {
        if (i.joinable()) {
            i.join();
        }
    }
}

void FileFactorise::start() {
    producer = thread(&FileFactorise::producerFunc, this);
    for (int i=0; i<numberOfThreads; i++) {
        consumer.emplace_back(&FileFactorise::consumerMakeFile, this);
    }
}


void FileFactorise::producerFunc() {
    ifstream file(fileName);
    uint64_t numberFromFile = 0;
    while (file >> numberFromFile) {

        unique_lock<mutex> prodLock(locks);
        condition.wait(prodLock, [this]() -> bool { return !isPause; });

        numbersByProducer.push(numberFromFile);
        condition.notify_one();


    }
    isFileReaded = true;
    condition.notify_one();
}

void FileFactorise::consumerMakeFile() {

   static ofstream fillFile("output.txt");
    while (true) {
        unique_lock<mutex> consLock(locks);
        if (!(!isFileReaded || !numbersByProducer.empty())) {
            return;
        }
        condition.wait(consLock, [this]() {
            return (isFileReaded || !numbersByProducer.empty());
        });
        while (!numbersByProducer.empty()) {
            condition.wait(consLock, [this]() -> bool { return !isPause; });
            uint64_t numToFactorise = numbersByProducer.front();
            numbersByProducer.pop();
            consLock.unlock();
            Factorization FactorizationNum(numToFactorise);
            string numberFactor = FactorizationNum.getFactors();
            lock_guard<mutex> fileLock(lockFile);
            fillFile << numberFactor << endl;
            consLock.lock();
        }


    }

}

FileFactorise::~FileFactorise() {

    joinThreads();
}



