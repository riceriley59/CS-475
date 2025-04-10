#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "helpers.h"

int	    NowYear;		// 2025- 2030
int	    NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches

float   NowFireDamage;

int	    NowNumDeer;		// number of deer in the current population

unsigned int seed = 0;

std::vector<std::string>   Data;

const float GRAIN_GROWS_PER_MONTH =	       12.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;

const float AVG_PRECIP_PER_MONTH =		7.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				60.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;

void Deer();
void Grain();
void Watcher();
void WildFires();

int main() {
    omp_set_num_threads( 4 );	// or 4
    InitBarrier( 4 );		// or 4

    // starting date and time:
    NowMonth =    0;
    NowYear  = 2025;

    // starting state (feel free to change this if you want):
    NowNumDeer = 2;
    NowHeight =  5.;
    NowFireDamage = 0.;

    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );	// angle of earth around the sun

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0. )
        NowPrecip = 0.;


    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Month, Year, Months, Deer, Grain (cm), Fire Damage (cm), Temperature (celsius), Precipitation (cm)\n");
    Data.push_back(std::string(buffer));

    omp_set_num_threads(4);	// same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            Deer( );
        }

        #pragma omp section
        {
            Grain( );
        }

        #pragma omp section
        {
            Watcher( );
        }

        #pragma omp section
        {
            WildFires();
        }
    }
    // implied barrier -- all functions must return in order
    // to allow any of them to get past here

    write_csv("data.csv", Data);

    return 0;
}

void Deer() {
    while( NowYear < 2031 ) {
        int nextNumDeer = NowNumDeer;
        int carryingCapacity = (int)( NowHeight );
        if( nextNumDeer < carryingCapacity )
            nextNumDeer++;
        else
            if( nextNumDeer > carryingCapacity )
            nextNumDeer--;

        if( nextNumDeer < 0 )
            nextNumDeer = 0;

        // DoneComputing barrier:
        WaitBarrier();

        NowNumDeer = nextNumDeer;

        // DoneAssigning barrier:
        WaitBarrier();

        // DonePrinting barrier:
        WaitBarrier();
    }

    return;
}

void Grain() {
    while( NowYear < 2031 ) {
        float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));
        float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));

        float nextHeight = NowHeight;
        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

        if( nextHeight < 0. ) nextHeight = 0.;

        // DoneComputing barrier:
        WaitBarrier();

        NowHeight = nextHeight;

        // DoneAssigning barrier:
        WaitBarrier();

        // DonePrinting barrier:
        WaitBarrier();
    }

    return;
};

void WildFires() {
    while( NowYear < 2031 ) {
        float nextFireDamage = NowFireDamage;
        if (NowTemp > 70. && NowPrecip < 4.0 && NowHeight > 2.) {
            nextFireDamage = Ranf(0.f, (NowHeight - 0.5f));
        } else {
            nextFireDamage = 0.;
        }

        // DoneComputing barrier:
        WaitBarrier();

        NowFireDamage = nextFireDamage;

        // DoneAssigning barrier:
        WaitBarrier();

        // DonePrinting barrier:
        WaitBarrier();
    }

    return;
};

void Watcher() {
    while( NowYear < 2031 ) {
        // DoneComputing barrier:
        WaitBarrier();

        // DoneAssigning barrier:
        WaitBarrier();

        NowHeight -= NowFireDamage;
        if( NowHeight < 0. ) NowHeight = 0.;

        int monthNumber = ((NowYear - 2025) * 12) + NowMonth;
        printf("Month: %d, Year: %d, Deer: %d, Grain: %f, Fire Damage: %f, Temp: %f, Precipitation: %f\n",
                 NowMonth, NowYear, NowNumDeer, NowHeight, NowFireDamage, NowTemp, NowPrecip);

        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%d, %d, %d, %d, %f, %f, %f, %f\n",
                 NowMonth, NowYear, monthNumber, NowNumDeer, InchesToCM(NowHeight), InchesToCM(NowFireDamage), FarenheitToCelcius(NowTemp), InchesToCM(NowPrecip));

        Data.push_back(std::string(buffer));

        NowMonth++;
        if (NowMonth == 12) {
            NowYear++;
            NowMonth = 0;
        }

        float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);	// angle of earth around the sun

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;

        // DonePrinting barrier:
        WaitBarrier();
    }

    return;
};
