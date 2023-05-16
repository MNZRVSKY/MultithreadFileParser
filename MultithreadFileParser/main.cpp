#include <iostream>
#include <thread>

#include "UniqueWordCounter.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    // Begin time point
    auto start_time = std::chrono::high_resolution_clock::now();

    UniqueWordCounter counter;
    int count = counter.countWordInFile(argv[1]);

    // End time point
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Print time spand
    std::cout << "Elapsed time: " << elapsed_time.count() << std::endl;

    // Print the number of unique words
    std::cout << "Unique words: " << count << std::endl;
    
    return 0;
}
