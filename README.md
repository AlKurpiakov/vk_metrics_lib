# VK Metrics Library

**Solution for VK Internship Task**  
**PROJECT IMPLEMENTED USING POSIX THREADS**

## Overview

This C++ library provides a solution for collecting and saving metrics to a file in text format. Metrics represent named events that can occur at arbitrary times with corresponding values of specific data types. The implementation uses POSIX threads for efficient multi-threading.

## Project Structure

| File | Description |
|------|-------------|
| `IMetric.h` | Base metric interface |
| `CpuMetric.h` | CPU metric implementation |
| `HttpMetric.h` | HTTP requests metric implementation |
| `MetricManager.h` | Metric registration and collection |
| `AsyncFileWriter.h` | Thread-safe asynchronous file writer |
| `main.cpp` | Usage example |
| `CMakeLists.txt` | Build configuration |


## Output Format

Each metric record is a separate line with the following format:  
`TIMESTAMP "METRIC_NAME" VALUE "METRIC_NAME" VALUE...`

Example:
```
2025-06-15 15:44:28.695 "CPU" 3.75 "HTTP requests RPS" 94218
```

## Build Instructions

```bash
# Clone repository
git clone https://github.com/AlKurpiakov/vk_metrics_lib.git
cd vk_metrics_lib

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the application
./VK_Metrics_Lib
```

Metrics output will be saved in `results/metrics.txt`.

## Custom Metric Implementation

To add a new metric type:

1. Create a new class inheriting from `IMetric`
2. Implement the required methods:
```cpp
#include "IMetric.h"
#include <atomic>

class NewMetric : public IMetric {
private:
    std::atomic<data_type> value;

public:
    std::string getName() const override;
    std::string collectAndReset() override;
};
```
