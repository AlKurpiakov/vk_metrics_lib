#include "../include/CPUMetric.h"

CPUMetric::CPUMetric() : _cpuValue(0.0) {}

void CPUMetric::SetValue(double value) {
    _cpuValue.store(value, std::memory_order_relaxed);
}

std::string CPUMetric::GetName() const {
    return "CPU";
}

std::string CPUMetric::CollectAndReset() {
    double val = _cpuValue.exchange(0.0, std::memory_order_relaxed);
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << val;
    return out.str();
}