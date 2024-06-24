#ifndef JOB_H
#define JOB_H

#include <Arduino.h>

class Job
{
private:
    unsigned long lastExecutionTime; // 上次執行時間
    unsigned long interval;          // 執行間隔

public:
    Job(unsigned long interval);              // 構造函數
    bool checkAndExecute(void (*executed)()); // 檢查並執行任務
};

#endif // JOB_H
