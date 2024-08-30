#ifndef __MNTIME_H
#define __MNTIME_H

#define MNTIME_DAYS_PER_4HOUNDRED_YEARS  146097
#define MNTIME_DAYS_PER_HOUNDRED_YEARS   36524
#define MNTIME_DAYS_PER_4YEARS           1461
#define MNTIME_DAYS_PER_YEARS            365

#define MNTIME_TICK_PER_SEC              32768
//#define MNTIME_TICK_PER_SEC            1000

#define MNTIME_TICK_PER_MIN              (MNTIME_TICK_PER_SEC * 60)
#define MNTIME_TICK_PER_HOUR             (MNTIME_TICK_PER_MIN * 60)
#define MNTIME_TICK_PER_DAY              (MNTIME_TICK_PER_HOUR *24)		
				 
typedef struct _mntime
{
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t tickS;
    uint32_t IsFix;
}mntime_t;


uint64_t mntime_GetTicks(mntime_t);
mntime_t mntime_GetMnTime(uint64_t ticks);

#endif // __MNTIME_H



