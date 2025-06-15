#pragma once
#include "IMetric.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <atomic>

class CPUMetric : public IMetric {
private:
    std::atomic<double> _cpuValue;

public:
    CPUMetric();

    void SetValue(double value);

    std::string GetName() const override;

    std::string CollectAndReset() override;
};