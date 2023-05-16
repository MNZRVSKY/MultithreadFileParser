#pragma once

#include "ThreadSafeQueue.h"

class LoadTask {
public:
    LoadTask(std::ifstream& file, ThreadSafeQueue& queue) : 
        file_(file), 
        queue_(queue) {}

    void operator()();

private:
    std::ifstream& file_;
    ThreadSafeQueue& queue_;
};