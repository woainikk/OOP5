//
// Created by Маргарита on 30.10.2017.
//

#pragma once

#include <condition_variable>
#include "Factorization.h"
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class FileFactorise {

public:
    FileFactorise(std::string &f, int n);
    ~FileFactorise();

    void startDialog();

private:
    void start();

    const std::string fileName;

    void producerFunc();

    std::queue<uint64_t> numbersByProducer;

    void consumerMakeFile();

    bool isFileReaded = false;

    std::mutex locks;

    std::mutex lockFile;

    std::condition_variable condition;

    void stop();

    std::thread producer;
    std::vector<std::thread> consumer;

    void joinThreads() noexcept;

    bool isPause = false;

    int numberOfThreads;

};



