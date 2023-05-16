#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

class ThreadSafeQueue {
public:
    ThreadSafeQueue(size_t max_size) : max_size_(max_size) {}

    void push(const std::string& word);
    bool pop(std::string& word);
    void done();

private:
    std::queue<std::string> queue_;
    const size_t max_size_;
    std::mutex mutex_;
    std::condition_variable empty_cond_;
    std::condition_variable full_cond_;
    bool is_done_ = false;
};