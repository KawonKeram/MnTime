#ifndef __EVAL_TIMEMN_H
#define __EVAL_TIMEMNF_H

#define TIMEMN_TICK_PER_DAY              86400000
#define TIMEMN_DAYS_PER_4HOUNDRED_YEARS  146097
#define TIMEMN_DAYS_PER_HOUNDRED_YEARS   36524
#define TIMEMN_DAYS_PER_4YEARS           1461
#define TIMEMN_DAYS_PER_YEARS            365
#define TIMEMN_TICK_PER_HOUR             3600000
#define TIMEMN_TICK_PER_MIN              60000
#define TIMEMN_TICK_PER_SEC              1000

typedef struct _timeMn
{
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t ms;
    uint32_t IsFix;
}mntime_t;


uint64_t TimeMn_GetTicks(mntime_t);
mntime_t TimeMn_GetTimeMn(uint64_t ticks);

#endif // __EVAL_TIMEMN_H



