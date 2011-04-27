/**
 * @file
 * @brief Definitions for Timer class.
 * @author   Steven Bloemer
 * @date     12/9/2010
 * @lastedit 12/9/2010
 */
#include "Timer.h"
#include "DebugDefs.h"

namespace flexi {
namespace util {

float Timer::period = 0.0f; // Initializes static class variable

void Timer::start()
{
    // Get the current time
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    // If the timer is currently running, stop it.
    if (startTime.QuadPart != -1) {
        lastDelta.QuadPart = now.QuadPart - startTime.QuadPart;
        totalTime.QuadPart += lastDelta.QuadPart;
        ++intervalCount;
    } // Timer is now definitely stopped

    startTime = now; // Set the start time; the timer is now "running"
} // Timer::start()

void Timer::stop()
{
    flexiAssert(startTime.QuadPart == -1);

    // Get the current time
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    // Record the last interval and stop the timer
    lastDelta.QuadPart = now.QuadPart - startTime.QuadPart;
    totalTime.QuadPart += lastDelta.QuadPart;
    ++intervalCount;
    startTime.QuadPart = -1; // Signals that the timer is stopped
} // Timer::stop()

void Timer::reset()
{
    // The last delta cannot be read from until assigned to, so requires no
    // initialization. This is enforced by the invariants of intervalCount
    
    // The start time is -1 when the timer is not running
    startTime.QuadPart = -1;

    totalTime.QuadPart = 0;
         intervalCount = 0;
} // Timer::reset()

float Timer::getLastSeconds() const
{
    // Return -1 if no intervals recorded
    if (intervalCount == 0) {
        return -1.0f;
    } else {
        // Compute the time in seconds of the last interval and return it
        return (lastDelta.QuadPart * Timer::period);
    }
} // Timer::getLastSeconds()

float Timer::getTotalSeconds() const
{
    // Return -1 if no intervals recorded
    if (intervalCount == 0) {
        return -1.0f;
    } else {
        // Compute the time in seconds of the total time and return it
        return (totalTime.QuadPart * Timer::period);
    }
} // Timer::getTotalSeconds()

float Timer::getAvgSeconds() const
{
    // Return -1 if no intervals recorded
    if (intervalCount == 0) {
        return -1.0f;
    } else {
        // Compute the average interval time
        const double avg = totalTime.QuadPart / double(intervalCount);
        // Convert to seconds and return
        return float(avg * Timer::period);
    }
} // Timer::getAvgSeconds()

unsigned Timer::getIntervalCount() const
{
    return intervalCount;
}

Timer::Timer()
{
    // Initialize cycle period if not already initialized
    if (Timer::period == 0.0f) {
        LARGE_INTEGER frequency;
        BOOL supportsCounter = QueryPerformanceFrequency(&frequency);
        flexiAssert(supportsCounter != 0); // bail if counter unsupported
        flexiAssert(frequency.QuadPart > 0);
        // From here on we can assume that high performance counters are supported
        Timer::period = 1.0f / frequency.QuadPart;
    }
    // Initialize fields
    reset();
} // Timer::Timer()

} // namespace util
} // namespace flexi