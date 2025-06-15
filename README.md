# vk_metrics_lib
solution for vk internship task
ПРОЕКТ СДЕЛАН С ИСПОЛЬЗОВАНИЕМ POSIX!!!

## Структура

- `IMetric.h` — базовый интерфейс метрик
- `CpuMetric.h`, `HttpMetric.h` — примеры реализаций
- `MetricManager.h` — регистрация и сбор метрик
- `AsyncFileWriter.h` — потоковая запись строк
- `main.cpp` — пример использования

## Сборка

```bash
git clone https://github.com/AlKurpiakov/vk_metrics_lib.git
git checkout v1.0
mkdir build
cd build
cmake ..
make
```
Результат записывается в директорию results в файл metrics.txt.
