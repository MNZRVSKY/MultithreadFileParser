#include "ThreadSafeQueue.h"

void ThreadSafeQueue::push(const std::string& word) {
    std::unique_lock<std::mutex> lock(mutex_);
    while (queue_.size() >= max_size_) {
        full_cond_.wait(lock);
    }
    queue_.push(word);
    empty_cond_.notify_one();
}

bool ThreadSafeQueue::pop(std::string& word) {
    std::unique_lock<std::mutex> lock(mutex_);
    while (queue_.empty()) {
        if (is_done_) {
            return false;
        }
        empty_cond_.wait(lock);
    }
    word = queue_.front();
    queue_.pop();
    full_cond_.notify_one();
    return true;
}

void ThreadSafeQueue::done() {
    is_done_ = true;
    empty_cond_.notify_all();
    full_cond_.notify_all();
}
