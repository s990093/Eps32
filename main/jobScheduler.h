#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H

#include <Arduino.h>
#include <functional>
#include "config.h"

class Job
{
public:
    Job(void (*task)(), unsigned long interval, bool repeat = true);

    void run();
    bool shouldRun();
    bool isRepeat();

private:
    void (*task)();
    unsigned long interval;
    bool repeat;
    unsigned long lastRun;
};

class Scheduler
{
public:
    Scheduler();
    void addJob(std::function<void()> job, unsigned long interval);
    void run();

private:
    struct Job
    {
        std::function<void()> task;
        unsigned long interval;
        unsigned long lastExecutionTime;
    };

    Job jobs[MAX_JOBS];
    int jobCount;

    void executeJob(Job &job);
};

#endif
