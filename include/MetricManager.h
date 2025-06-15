#pragma once
#include "IMetric.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

class MetricManager {
private:
    std::vector<std::shared_ptr<IMetric>> _metrics;
    mutable std::mutex _metricsMutex;

    std::string GetTimestamp() const;

public:
    void AddMetric(std::shared_ptr<IMetric> metric);

    std::string CollectAndFormat();
};