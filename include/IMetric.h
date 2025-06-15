#pragma once
#include <string>

class IMetric {
public:
    virtual std::string GetName() const = 0;
    virtual std::string CollectAndReset() = 0;  // Атомарный сбор и сброс
    virtual ~IMetric() = default;
};