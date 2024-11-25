#include "Zeitmessung.h"


t_timevalue  get_clock_time ()
{
#ifdef __unix__

    struct timespec ts;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
    {
        return (t_timevalue) ((t_timevalue)ts.tv_sec * 1000000000ULL + ts.tv_nsec );
    }
    else
    {
        return 0;
    }
#endif // __unix__
#ifdef _WIN32
    LARGE_INTEGER TickFrequecny;
    LARGE_INTEGER TimerValue;
    QueryPerformanceCounter(&TimerValue);
    QueryPerformanceFrequency(&TickFrequecny);
    t_timevalue result=TimerValue.QuadPart*1000000000ULL/TickFrequecny.QuadPart;
    return result;
#endif // _WIN32
}

void startStopwatch(t_stopwatch* theWatch)
{
    theWatch->TimestampStart=get_clock_time();
    theWatch->ResultingTime=0;
    theWatch->isRunning=1;
}

t_timevalue restartStopwatch(t_stopwatch* theWatch)
{
    t_timevalue newstart=get_clock_time();
    if (theWatch->isRunning)
    {
        theWatch->ResultingTime+=newstart-theWatch->TimestampStart;
    }
    theWatch->TimestampStart=newstart;
    return theWatch->ResultingTime;
}

t_timevalue stopStopwatch(t_stopwatch* theWatch)
{
    theWatch->ResultingTime += get_clock_time()-theWatch->TimestampStart;
    theWatch->isRunning=0;
    return theWatch->ResultingTime;
}

t_timevalue evaluateStopwatch(t_stopwatch* theWatch)
{
    return theWatch->ResultingTime + get_clock_time()-theWatch->TimestampStart;
}

t_timevalue readStopwatch(t_stopwatch* theWatch)
{
    return theWatch->ResultingTime;
}
