#include <stdint.h>
#include <string.h>
#include "eval_timeMn.h"

uint64_t TimeMn_GetTicks(mntime_t time)
{
    uint32_t years = time.year;
    uint32_t leapYearsLast = years / 4  + years / 400 - years/100 ;
    uint32_t days = (years-1) * 365 + leapYearsLast + time.day - 1;

    switch (time.month)
    {
        case 1 : if(years % 4 == 0) {days -= 1;} break;
        case 2 : days += 31 ;  if(years % 4 == 0) {days -= 1;} break;
        case 3 : days += 31 + 28; break;
        case 4 : days += 31 + 28 + 31; break;
        case 5 : days += 31 + 28 + 31 + 30; break;
        case 6 : days += 31 + 28 + 31 + 30 + 31; break;
        case 7 : days += 31 + 28 + 31 + 30 + 31 + 30; break;
        case 8 : days += 31 + 28 + 31 + 30 + 31 + 30 + 31; break;
        case 9 : days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31; break;
        case 10 : days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30; break;
        case 11 : days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31; break;
        case 12 : days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30; break;
        default: break;
    }

    uint32_t mSec = time.hour * 3600000 + time.min * 60000 + time.sec * 1000 + time.ms;

    return ((uint64_t)(days) * 86400000) + mSec;
}

mntime_t TimeMn_GetTimeMn(uint64_t ticks)
{
    mntime_t timeRet;

    timeRet.year = 0;
    timeRet.month = 0;
    timeRet.day = 0;
    timeRet.hour = 0;
    timeRet.min = 0;
    timeRet.sec = 0;
    timeRet.ms = 0;

    uint32_t daysCount = (uint32_t)(ticks / TIMEMN_TICK_PER_DAY);
    uint32_t msCount = (uint32_t)(ticks % TIMEMN_TICK_PER_DAY);

    uint32_t fourHoundredYersCount = daysCount / TIMEMN_DAYS_PER_4HOUNDRED_YEARS;
    daysCount -= fourHoundredYersCount * TIMEMN_DAYS_PER_4HOUNDRED_YEARS;

    uint32_t houndredYersCount = daysCount / TIMEMN_DAYS_PER_HOUNDRED_YEARS;
    if(houndredYersCount == 4)
    {
        houndredYersCount = 3;
    }
    daysCount -= houndredYersCount * TIMEMN_DAYS_PER_HOUNDRED_YEARS;

    uint32_t fourYearsCount = daysCount / TIMEMN_DAYS_PER_4YEARS;
    daysCount -= fourYearsCount * TIMEMN_DAYS_PER_4YEARS;

    uint32_t yearsCount = daysCount / TIMEMN_DAYS_PER_YEARS;
    if (yearsCount == 4)
    {
        yearsCount = 3;
    }
    daysCount -= yearsCount * TIMEMN_DAYS_PER_YEARS;

    timeRet.year = fourHoundredYersCount * 400 + houndredYersCount * 100 + fourYearsCount * 4 + yearsCount + 1;
    timeRet.month = 0;
    uint32_t leapYearDay = 0;

    if (timeRet.year % 4 == 0 && timeRet.year % 100 != 0 || timeRet.year % 400 == 0)
    {
         leapYearDay = 1;
    }

    daysCount++;

    if (daysCount <= 31)
    {
        timeRet.month = 1;
    }
    else if(daysCount <= 31 + 28 + leapYearDay)
    {
        timeRet.month = 2;
        daysCount -= 31;
    }
    else if (daysCount <= 31 + 28 + 31 + leapYearDay)
    {
        timeRet.month = 3;
        daysCount -= 31 + 28 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + leapYearDay)
    {
        timeRet.month = 4;
        daysCount -= 31 + 28 + 31 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + leapYearDay)
    {
        timeRet.month = 5;
        daysCount -= 31 + 28 + 31 + 30 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + leapYearDay)
    {
        timeRet.month = 6;
        daysCount -= 31 + 28 + 31 + 30 + 31 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + leapYearDay)
    {
        timeRet.month = 7;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 +  leapYearDay)
    {
        timeRet.month = 8;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + 31 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + leapYearDay)
    {
        timeRet.month = 9;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + leapYearDay)
    {
        timeRet.month = 10;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + leapYearDay)
    {
        timeRet.month = 11;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + leapYearDay;
    }
    else if (daysCount <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + leapYearDay)
    {
        timeRet.month = 12;
        daysCount -= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + leapYearDay;
    }

    timeRet.hour = msCount / TIMEMN_TICK_PER_HOUR;
    msCount -= timeRet.hour * TIMEMN_TICK_PER_HOUR;

    timeRet.min = msCount / TIMEMN_TICK_PER_MIN;
    msCount -= timeRet.min * TIMEMN_TICK_PER_MIN;

    timeRet.sec = msCount / TIMEMN_TICK_PER_SEC;
    msCount -= timeRet.sec * TIMEMN_TICK_PER_SEC;

    timeRet.day = daysCount;
    timeRet.ms = msCount;

    return timeRet;
}
