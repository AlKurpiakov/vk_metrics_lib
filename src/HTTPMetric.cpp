#include "../include/HTTPMetric.h"

HTTPMetric::HTTPMetric() : _requestCount(0) {}

void HTTPMetric::AddRequest() {
    _requestCount.fetch_add(1, std::memory_order_relaxed);
}

std::string HTTPMetric::GetName() const {
    return "HTTP requests RPS";
}

void HTTPMetric::AddRequestBatch(uint64_t count) {
    _requestCount.fetch_add(count, std::memory_order_relaxed);
}

std::string HTTPMetric::CollectAndReset() {
    int count = _requestCount.exchange(0, std::memory_order_relaxed);
    return std::to_string(count);
}