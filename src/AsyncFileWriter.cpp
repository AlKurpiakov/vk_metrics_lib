#include "../include/AsyncFileWriter.h"

void* AsyncFileWriter::ThreadProc(void* arg) {
    static_cast<AsyncFileWriter*>(arg)->Run();
    return nullptr;
}

void AsyncFileWriter::Run() {
    while (true) {
        pthread_mutex_lock(&_mtx);

        while (_queue.empty() && !_stop) {
            pthread_cond_wait(&_cv, &_mtx);
        }

        if (_stop && _queue.empty()) {
            pthread_mutex_unlock(&_mtx);
            break;
        }

        std::queue<std::string> localQueue;
        std::swap(_queue, localQueue);
        pthread_mutex_unlock(&_mtx);

        while (!localQueue.empty()) {
            _file << localQueue.front() << "\n";
            localQueue.pop();
        }

        _file.flush();
    }
}


AsyncFileWriter::AsyncFileWriter(const std::string& filename) {
    _file.open(filename, std::ios::out | std::ios::app);
    
    if (!_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    if (pthread_create(&_writerThread, nullptr, &AsyncFileWriter::ThreadProc, this) != 0) {
        throw std::runtime_error("Failed to create writer thread");
    }
}

void AsyncFileWriter::WriteLine(const std::string& line) {
    pthread_mutex_lock(&_mtx);
    if (_stop) {
        pthread_mutex_unlock(&_mtx);
        return;
    }
    _queue.push(line);
    pthread_cond_signal(&_cv);
    pthread_mutex_unlock(&_mtx);
}

AsyncFileWriter::~AsyncFileWriter() {
    _stop = true;
    pthread_mutex_lock(&_mtx);
    pthread_cond_broadcast(&_cv);
    pthread_mutex_unlock(&_mtx);
    
    pthread_join(_writerThread, nullptr);
    
    pthread_mutex_destroy(&_mtx);
    pthread_cond_destroy(&_cv);

    _file.close();
}
