#include "ParseTask.h"

#include <iostream>
#include <sstream>


void ParseTask::operator()() {
    std::string filePart;
    while (queue_.pop(filePart)) 
    {
        std::stringstream ss(filePart);
        std::string word;
        while (std::getline(ss, word, ' ')) 
        {
             std::unique_lock<std::mutex> lock(mutex_);
             unique_words_.insert(std::move(word));
        }
    }
}