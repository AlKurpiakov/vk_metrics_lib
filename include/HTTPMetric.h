#pragma once
#include "IMetric.h"
#include <string>
#include <atomic>
#include <cstdint>

class HTTPMetric : public IMetric {
private:
    std::atomic<uint64_t> _requestCount;

public:
    HTTPMetric() ;

    void AddRequest();
    void AddRequestBatch(uint64_t count);
    
    std::string GetName() const override;

    std::string CollectAndReset() override;
};