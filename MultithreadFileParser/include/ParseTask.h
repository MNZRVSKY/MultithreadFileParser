#pragma once

#include <unordered_set>

#include "ThreadSafeQueue.h"

class ParseTask {
public:
    ParseTask(ThreadSafeQueue& queue, std::unordered_set<std::string>& unique_words, std::mutex& mutex) : 
        queue_(queue), 
        unique_words_(unique_words), 
        mutex_(mutex) {}

    void operator()();

private:
    ThreadSafeQueue& queue_;
    std::unordered_set<std::string>& unique_words_;
    std::mutex& mutex_;
};