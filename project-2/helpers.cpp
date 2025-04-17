#include <omp.h>
#include <fstream>
#include <iostream>
#include <vector>

#include "helpers.h"

omp_lock_t	    Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

void InitBarrier(int n) {
    NumInThreadTeam = n;
    NumAtBarrier = 0;
    omp_init_lock( &Lock );
}

void WaitBarrier() {
    omp_set_lock( &Lock );
    {
        NumAtBarrier++;
        if( NumAtBarrier == NumInThreadTeam )
        {
            NumGone = 0;
            NumAtBarrier = 0;
            // let all other threads get back to what they were doing
            // before this one unlocks, knowing that they might immediately
            // call WaitBarrier( ) again:
            while( NumGone != NumInThreadTeam-1 );
            omp_unset_lock( &Lock );
            return;
        }
    }
    omp_unset_lock( &Lock );

    while( NumAtBarrier != 0 );	// this waits for the nth thread to arrive

    #pragma omp atomic
    NumGone++;			// this flags how many threads have returned
}

void write_csv(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    // use auto type here so that I don't have to write a big vector type
    // for an iterator which would be my other option
    for (const auto& line : data) {
        file << line;
    }

    file.close();
}

float Ranf( float low, float high ) {
    float r = (float) rand();               // 0 - RAND_MAX
    float t = r  /  (float) RAND_MAX;       // 0. - 1.

    return   low  +  t * ( high - low );
}

int Ranf( int ilow, int ihigh ) {
    float low = (float)ilow;
    float high = ceil( (float)ihigh );

    return (int) Ranf(low,high);
}

float SQR( float x ) {
    return x*x;
}

float InchesToCM(float inches) {
    return inches * 2.54;
}

float FarenheitToCelcius(float farenheit) {
    return ((5./9.) * (farenheit - 32.));
}
