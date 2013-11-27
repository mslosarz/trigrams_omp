#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>

#ifndef TIMECALCULATOR_H
#define TIMECALCULATOR_H

using namespace::std;

class TimeCalculator
{
public:
    TimeCalculator() {}
    void start()
    {
        clock_gettime( CLOCK_REALTIME, &tstart);
    }

    void finish()
    {
        clock_gettime( CLOCK_REALTIME, &tstop);
    }

    void printDuration()
    {
        cout << setprecision(16) << durationInMiliseconds() << " ms" << endl;
    }

    double durationInMiliseconds()
    {
        return (
                   ( tstop.tv_sec - tstart.tv_sec )*1e9
                   + ( tstop.tv_nsec - tstart.tv_nsec )
               ) / 1e6;
    }

    ostream & operator<< (ostream &stream)
    {
        return stream << setprecision(16) << durationInMiliseconds() << " ms";
    }

private:
    struct timespec tstart;
    struct timespec tstop;
};

#endif // TIMECALCULATOR_H
