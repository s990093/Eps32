#include "jobScheduler.h"

// Job class implementation
Job::Job(void (*task)(), unsigned long interval, bool repeat)
    : task(task), interval(interval), repeat(repeat), lastRun(0) {}

void Job::run()
{
    if (task)
    {
        task();
    }
    lastRun = millis();
}

bool Job::shouldRun()
{
    return (millis() - lastRun) >= interval;
}

bool Job::isRepeat()
{
    return repeat;
}

#include <Arduino.h>

Scheduler::Scheduler()
{
    jobCount = 0;
}

void Scheduler::addJob(std::function<void()> job, unsigned long interval)
{
    if (jobCount < MAX_JOBS)
    {
        jobs[jobCount++] = {job, interval, 0};
    }
}

void Scheduler::run()
{
    unsigned long currentMillis = millis();

    for (int i = 0; i < jobCount; ++i)
    {
        if (currentMillis - jobs[i].lastExecutionTime >= jobs[i].interval)
        {
            executeJob(jobs[i]);
            jobs[i].lastExecutionTime = currentMillis;
        }
    }
}

void Scheduler::executeJob(Job &job)
{
    job.task();
}