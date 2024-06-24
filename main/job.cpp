#include "job.h"

// 構造函數，初始化間隔並將上次執行時間設為0
Job::Job(unsigned long interval)
{
    this->interval = interval;
    lastExecutionTime = 0;
}

// 檢查是否到達執行時間，如果是則執行任務
bool Job::checkAndExecute(void (*executed)())
{
    unsigned long currentTime = millis(); // 獲取當前時間

    // 如果當前時間減去上次執行時間大於或等於間隔，則執行任務
    if (currentTime - lastExecutionTime >= interval)
    {
        lastExecutionTime = currentTime; // 更新上次執行時間
        executed();                      // 執行任務
        return true;
    }
    return false;
}
