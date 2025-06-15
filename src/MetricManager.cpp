#include "../include/MetricManager.h"

std::string MetricManager::GetTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

void MetricManager::AddMetric(std::shared_ptr<IMetric> metric) {
    std::lock_guard<std::mutex> lock(_metricsMutex);
    _metrics.push_back(metric);
}

std::string MetricManager::CollectAndFormat() {
    std::lock_guard<std::mutex> lock(_metricsMutex);
    std::stringstream line;
    line << GetTimestamp();

    for (auto& metric : _metrics) {
        line << " \"" << metric->GetName() << "\" " << metric->CollectAndReset();
    }

    return line.str();
}