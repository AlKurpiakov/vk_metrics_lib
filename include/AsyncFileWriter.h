// AsyncFileWriter.h
#pragma once
#include <fstream>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <pthread.h>
#include <stdexcept>

class AsyncFileWriter {
private:
    std::ofstream _file;
    std::queue<std::string> _queue;
    pthread_mutex_t _mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t _cv = PTHREAD_COND_INITIALIZER;
    pthread_t _writerThread;
    std::atomic<bool> _stop{false};

    static void* ThreadProc(void* arg);

    void Run();

public:
    AsyncFileWriter(const std::string& filename);

    void WriteLine(const std::string& line);

    ~AsyncFileWriter();
};