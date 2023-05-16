#include "UniqueWordCounter.h"

#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include "ThreadSafeQueue.h"
#include "LoadTask.h"
#include "ParseTask.h"

const size_t MAX_THREADS = std::thread::hardware_concurrency();

int UniqueWordCounter::countWordInFile(const std::string& path)
{
    // Open the file and check if it was successfully opened
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error opening file " << path << std::endl;
        return -1;
    }

    // Create the thread pool
    std::vector<std::thread> pool;
    pool.reserve(MAX_THREADS - 1);
    ThreadSafeQueue queue(MAX_THREADS);
    std::unordered_set<std::string> unique_words;
    std::mutex mutex;

    // Create the load task and add it to the pool
    LoadTask load_task(file, queue);
    std::thread load_thread(std::ref(load_task));
    pool.emplace_back(std::move(load_thread));


    // Create the worker tasks and add them to the pool
    for (size_t i = 0; i < MAX_THREADS - 1; ++i)
    {
        ParseTask task(queue, unique_words, mutex);
        std::thread worker_thread(std::ref(task));
        pool.emplace_back(std::move(worker_thread));
    }

    // Wait for all tasks to finish
    for (auto& thread : pool)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    return static_cast<int>(unique_words.size());
}
