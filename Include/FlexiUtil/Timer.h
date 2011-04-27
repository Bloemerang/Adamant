#ifndef Timer_H__
#define Timer_H__
/**
 * @file
 * @brief Header for Timer class.
 * @author   Steven Bloemer
 * @date     12/9/2010
 * @lastedit 12/9/2010
 */
#include "windows.h"

namespace flexi {
namespace util {

/**
 * @brief A high-precision timer for performance tests.
 * 
 * Provides an interface for timing single intervals and for getting the average
 * time over multiple intervals. An interval is a sequence of computer
 * ructions with known beginning and end points. The start of an interval is
 * marked by a call to start(), and the end of an interval may be marked by a
 * a subsequent call either to stop() or to start(). Data recorded for previous
 * intervals may be erased by a call to reset().
 * 
 * Timer data may be accessed as follows (units are always in seconds):
 * - @b getLastSeconds(): Gets the length of the last interval.
 * - @b getTotalSeconds(): Gets the aggregate length of all recorded intervals.
 * - @b getAvgSeconds(): Gets the average length over all recorded intervals.
 * - @b getIntervalCount(): Gets the number of recorded intervals.
 */
class Timer
{
public:  /************************** Public Interface *************************/
    /**
     * @brief Starts the timer.
     * 
     * Stops the timer if it was already running, and then sets the starting
     * time of this Timer to the current time.
     */
    void start();

    /**
     * @brief Stops the timer.
     * 
     * Saves the last start-stop delta and adds to the total time and number of
     * stops. Asserts that the timer had already been started (and not stopped).
     */
    void stop();

    /**
     * @brief Stops the timer (if running) and resets the total time to zero.
     */
    void reset();

    /**
     * @brief Gets the length of the last recorded interval in seconds.
     * 
     * If called during the recording of an interval - that is, after a call to
     * start() and before the corresponding call to stop(), returns the length
     * of the interval recorded before the current. If there is no such interval
     * (either because the timer has never been started, has just been reset, or
     * is currently within its first interval), this method returns -1.
     */
    float getLastSeconds() const;

    /**
     * @brief Gets the aggregate length of all recorded intervals.
     * 
     * Does not include the interval currently being recorded (if any).
     * @returns The sum of the lengths of all recorded intervals, or -1 if none
     *  have yet been recorded.
     */
    float getTotalSeconds() const;

    /**
     * @brief Gets the average length over all recorded intervals.
     *
     * Does not include the interval currently being recorded (if any).
     * @returns The sum of the lengths of all recorded intervals divided by the
     *  number of intervals, or -1 if none have been recorded.
     */
    float getAvgSeconds() const;

    /**
     * @brief Gets the number of intervals recorded.
     *
     * Does not include the interval currently being recorded (if any).
     */
    unsigned getIntervalCount() const;

    Timer();

private: /******************************* Fields ******************************/
    LARGE_INTEGER lastDelta;
    LARGE_INTEGER startTime;
    LARGE_INTEGER totalTime;
    unsigned intervalCount;

    static float period; // Initialized in Timer ctor
};

} // namespace util
} // namespace flexi

#endif // Timer_H__