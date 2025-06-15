#include <chrono>
#include <cstdlib>
#include <vector>
#include <atomic>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "../include/CPUMetric.h"
#include "../include/HTTPMetric.h"
#include "../include/MetricManager.h"
#include "../include/AsyncFileWriter.h"

std::string fileName = "../results/metrics.txt";

struct ThreadData {
    HTTPMetric* http;
    uint64_t requests;
};

void* simulateHttpRequests(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    const uint64_t BATCH_SIZE = 100000;
    uint64_t remaining = data->requests;
    
    while (remaining > 0) {
        uint64_t batch = (remaining > BATCH_SIZE) ? BATCH_SIZE : remaining;
        data->http->AddRequestBatch(batch);
        remaining -= batch;
        usleep(1000);
    }
    
    delete data;
    return nullptr;
}

struct CpuUpdaterData {
    CPUMetric* cpu;
    std::atomic<bool>* running;
};

void* cpuUpdater(void* arg) {
    CpuUpdaterData* data = static_cast<CpuUpdaterData*>(arg);
    
    while (*(data->running)) {
        double value = static_cast<double>(rand() % 800) / 100.0;
        data->cpu->SetValue(value);
        sleep(1);
    }
    
    delete data;
    return nullptr;
}

struct CollectorData {
    MetricManager* manager;
    AsyncFileWriter* writer;
    std::atomic<bool>* running;
};

void* metricsCollector(void* arg) {
    CollectorData* data = static_cast<CollectorData*>(arg);
    
    while (*(data->running)) {
        sleep(1);
        std::string line = data->manager->CollectAndFormat();
        data->writer->WriteLine(line);
    }
    
    delete data;
    return nullptr;
}
int main() {
    srand(time(NULL));

    auto cpu = std::make_shared<CPUMetric>();
    auto http = std::make_shared<HTTPMetric>();
    
    MetricManager manager;
    manager.AddMetric(cpu);
    manager.AddMetric(http);

    AsyncFileWriter writer(fileName);
    
    std::vector<pthread_t> worker_threads;
    
    for (int i = 0; i < 100; ++i) {
        ThreadData* thread_data = new ThreadData{
            http.get(), 
            static_cast<uint64_t>(rand() % 100000) + 1000
        };
        
        pthread_t tid;
        pthread_create(&tid, nullptr, simulateHttpRequests, thread_data);
        worker_threads.push_back(tid);
        
        // Обновляем CPU и собираем метрики в основном потоке
        cpu->SetValue(static_cast<double>(rand() % 800) / 100.0);
        std::string line = manager.CollectAndFormat();
        writer.WriteLine(line);
        sleep(1);
    }

    for (pthread_t tid : worker_threads) {
        pthread_join(tid, nullptr);
    }

    std::string line = manager.CollectAndFormat();
    writer.WriteLine(line);

    return 0;
}