/*
 * @Descripttion: Struct Define
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 20:54:55
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-11 20:58:13
 */

#ifndef _GPS_TIME_TOOL_STRUCT_H_
#define _GPS_TIME_TOOL_STRUCT_H_

// c++
#include <ctime>
#include <cmath>
#include <vector>

// other header
#include "ConstDefine.h"

namespace GpsTimeTool
{
    /* sturct gtime_t */
    struct gtime_t
    {
        time_t time;    //time (s)  expressed by stardard time_t
        double sec;     //second under 1 s

        constexpr gtime_t() : time(0), sec(0.0) {}
        constexpr gtime_t(time_t _t, double _sec) : time(_t), sec(_sec) {}
        constexpr gtime_t(time_t _t) : time(_t), sec(0.0) {}

        gtime_t operator+(double _sec) noexcept
        {
            double t, s = this->sec;
            s += _sec;
            t = floor(s);

            return gtime_t(this->time + (int)t, s - t);
        }

        gtime_t operator-(double _sec) noexcept
        {
            return this->operator+(-1.0 * _sec);
        }

        double operator-(gtime_t in) const
        {
            return difftime(this->time, in.time) + this->sec - in.sec;
        }

        bool operator==(gtime_t t) const
        {
            return (this->time == t.time) && (fabs(this->sec - t.sec) < 1e-9);
        }
    };

    /**
     * @description: convert gtime_t to epoch time
     * @param  {const gtime_t}  in:             input:      gtime_t
     * @param  {std::vector<double>} epoch:     output:     year, mon, day, hour, min, sec
     * @return {*}
     */
    void gtime2epoch(const gtime_t in, std::vector<double> &epoch)
    {
        int days, sec, mon, day;
        epoch.resize(6);

        // leap year if year % 4 == 0
        days = (int)(in.time / 86400);
        sec = (int)(in.time - (time_t)days * 86400);
        for (day = days % 1461, mon = 0; mon < 48; mon++)
        {
            if (day >= mday[mon])
                day -= mday[mon];
            else
                break;
        }
        epoch[0] = 1970 + days / 1461 * 4 + mon / 12;
        epoch[1] = mon % 12 + 1;
        epoch[2] = day + 1;
        epoch[3] = sec / 3600;
        epoch[4] = sec % 3600 / 60;
        epoch[5] = sec % 60 + in.sec;
    }

    /**
     * @description: convert epoch time to gtime_t
     * @param  {std::vector<double>} epoch:     input:     year, mon, day, hour, min, sec
     * @return {const gtime_t}    :             output:    gtime_t
     */

    gtime_t epoch2gtime(const std::vector<double>& ep) {
        gtime_t time={0};
        int days,sec,year=(int)ep[0],mon=(int)ep[1],day=(int)ep[2];
        
        if (year<1970||2099<year||mon<1||12<mon) return time;
        
        /* leap year if year%4==0 in 1901-2099 */
        days=(year-1970)*365+(year-1969)/4+doy[mon-1]+day-2+(year%4==0&&mon>=3?1:0);
        sec=(int)floor(ep[5]);
        time.time=(time_t)days*86400+(int)ep[3]*3600+(int)ep[4]*60+sec;
        time.sec=ep[5]-sec;
        return time;
    }


};

#endif //_GPS_TIME_TOOL_STRUCT_H_