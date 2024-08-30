#include <stdint.h>
#include <string.h>
#include "eval_timeMn.h"

uint64_t mntime_GetTicks(mntime_t time)
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
	
	uint32_t dayTicks = time.hour * MNTIME_TICK_PER_HOUR + time.min * MNTIME_TICK_PER_MIN + time.sec * MNTIME_TICK_PER_SEC + time.tickS;
    return ((uint64_t)(days) * MNTIME_TICK_PER_DAY) + dayTicks;
}

mntime_t mntime_GetMnTime(uint64_t ticks)
{
    mntime_t timeRet;

    timeRet.year = 0;
    timeRet.month = 0;
    timeRet.day = 0;
    timeRet.hour = 0;
    timeRet.min = 0;
    timeRet.sec = 0;
    timeRet.tickS = 0;

    uint32_t daysCount = (uint32_t)(ticks / MNTIME_TICK_PER_DAY);
    uint32_t msCount = (uint32_t)(ticks % MNTIME_TICK_PER_DAY);

    uint32_t fourHoundredYersCount = daysCount / MNTIME_DAYS_PER_4HOUNDRED_YEARS;
    daysCount -= fourHoundredYersCount * MNTIME_DAYS_PER_4HOUNDRED_YEARS;

    uint32_t houndredYersCount = daysCount / MNTIME_DAYS_PER_HOUNDRED_YEARS;
    if(houndredYersCount == 4)
    {
        houndredYersCount = 3;
    }
    daysCount -= houndredYersCount * MNTIME_DAYS_PER_HOUNDRED_YEARS;

    uint32_t fourYearsCount = daysCount / MNTIME_DAYS_PER_4YEARS;
    daysCount -= fourYearsCount * MNTIME_DAYS_PER_4YEARS;

    uint32_t yearsCount = daysCount / MNTIME_DAYS_PER_YEARS;
    if (yearsCount == 4)
    {
        yearsCount = 3;
    }
    daysCount -= yearsCount * MNTIME_DAYS_PER_YEARS;

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

    timeRet.hour = msCount / MNTIME_TICK_PER_HOUR;
    msCount -= timeRet.hour * MNTIME_TICK_PER_HOUR;

    timeRet.min = msCount / MNTIME_TICK_PER_MIN;
    msCount -= timeRet.min * MNTIME_TICK_PER_MIN;

    timeRet.sec = msCount / MNTIME_TICK_PER_SEC;
    msCount -= timeRet.sec * MNTIME_TICK_PER_SEC;

    timeRet.day = daysCount;
    timeRet.ms = msCount;

    return timeRet;
}
