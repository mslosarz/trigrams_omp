#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>

#ifndef TIMECALCULATOR_H
#define TIMECALCULATOR_H

using namespace::std;

class Timer
{
public:
    Timer() {}
    void start()
    {
        clock_gettime( CLOCK_REALTIME, &tstart);
    }

    void finish()
    {
        clock_gettime( CLOCK_REALTIME, &tstop);
    }

    void finish_and_print_duration(){
    	finish();
    	print_duration();
    }

    void print_duration()
    {
        cout << setprecision(16) << duration_in_millis() << " ms" << endl;
    }

    double duration_in_millis()
    {
        return (
                   ( tstop.tv_sec - tstart.tv_sec )*1e9
                   + ( tstop.tv_nsec - tstart.tv_nsec )
               ) / 1e6;
    }

private:
    struct timespec tstart;
    struct timespec tstop;
};

#endif // TIMECALCULATOR_H
