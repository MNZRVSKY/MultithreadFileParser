#include "LoadTask.h"

#include <fstream>
#include <thread>

void LoadTask::operator()() {
    const int BUFFER_SIZE = 256;
    char* buffer = new char[BUFFER_SIZE];
    int pos = 0;

    while (!file_.eof()) 
    {
        file_.seekg(pos);
        file_.read(buffer, BUFFER_SIZE);
        std::string file_part = buffer;

        std::size_t lastWordEnds = file_part.find_last_of(' ');

        queue_.push(file_part.substr(0, lastWordEnds));

        pos += lastWordEnds;
    }

    queue_.done();

    delete[] buffer;

    file_.close();
}