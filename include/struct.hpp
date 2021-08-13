/*
 * @Descripttion: Struct Define
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 20:54:55
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-13 20:51:25
 */

#ifndef _GPS_TIME_TOOL_STRUCT_H_
#define _GPS_TIME_TOOL_STRUCT_H_

// c++
#include <ctime>
#include <cmath>
#include <vector>

//#include <iostream> // for debug;

// other header
#include "ConstDefine.h"

namespace GpsTimeTool
{
    /* class gtime_t */
    class gtime_t
    {
    public:
        time_t time;    //time (s)  expressed by stardard time_t
        double sec;     //second under 1 s

        constexpr gtime_t() : time(0), sec(0.0) {}
        constexpr gtime_t(time_t _t) : time(_t), sec(0.0) {}
        gtime_t(time_t _t, double _sec) {
            time = _t + (int)_sec;
            sec = _sec - (int)_sec;
        }

        gtime_t operator+(const double _sec) const noexcept
        {
            double t, s = this->sec;
            s += _sec;
            t = floor(s);

            return gtime_t(this->time + (int)t, s - t);
        }

        gtime_t operator-(const double _sec) const noexcept
        {
            return this->operator+(-1.0 * _sec);
        }

        double operator-(gtime_t in) const
        {
            return difftime(this->time, in.time) + this->sec - in.sec;
        }

        bool operator==(gtime_t t) const {
            return (this->time == t.time) && (fabs(this->sec - t.sec) < DOUBLE_ZERO);
        }
    };

    /* class gps_t*/
    class gps_t {
    public:
        int week;   // week number in gps time
        double sec; // time of week in gps time (s)

        constexpr gps_t() : week(0), sec(0.0) {}
        gps_t(int _week, double _sec) {
            week = _week + floor(_sec / SEC_A_WEEK);
            sec = _sec - floor(_sec / SEC_A_WEEK) * SEC_A_WEEK;
        }

        gps_t(double _sec) {
            this->week = _sec / SEC_A_WEEK;
            this->sec = _sec - this->week * SEC_A_WEEK;
        }

        double operator-(const gps_t& in) const noexcept{
            return (this->week - in.week) * SEC_A_WEEK + this->sec - in.sec;
        }

        gps_t operator+(const double& in) const noexcept{
            return gps_t(this->week * SEC_A_WEEK + this->sec + in);
        }

        gps_t operator-(const double& in) const noexcept{
            return this->operator+(in * (-1.0));
        }

        bool operator==(const gps_t& in) const noexcept {
            return (this->week == in.week) && (fabs(this->sec - in.sec) < DOUBLE_ZERO);
        }
        
    };

    /**
     * @description: convert gtime_t to epoch time
     * @param  {const gtime_t}  in:                   input:      gtime_t
     * @param  {std::vector<double>} epoch:          output:     year, mon, day, hour, min, sec
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
     * @param  {const std::vector<double>} epoch:     input:     year, mon, day, hour, min, sec
     * @return {gtime_t}                             output:    gtime_t
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

    /**
     * @description: convert gtime_t time to gps time
     * @param  {const gtime_t}   in:                 input:     gtime_t
     * @return {gps_t}    :                         output:     gps_t
     */
    gps_t gtime2gpst(const gtime_t& in) {
        return gps_t(in - epoch2gtime(gpst0));
    }

    /**
     * @description: convert gps time to gtime
     * @param  {const gps_t}   in:                  input:     gps_t
     * @return {gtime_t}    :                      output:     gtime_t
     */
    gtime_t gpst2gtime(const gps_t& in) {
        gtime_t res = epoch2gtime(gpst0);
        res.time += in.week * SEC_A_WEEK + (int)in.sec;
        res.sec += (in.sec - (int)in.sec);
        return res;
    }

    /**
     * @description: convert gtime_t time to bdt time
     * @param  {const gtime_t}   in:                 input:     gtime_t
     * @return {gps_t}    :                         output:     gps_t
     */
    gps_t gtime2bdt(const gtime_t& in) {
        return gps_t(in - epoch2gtime(bdt0));
    }

    /**
     * @description: convert bdt time to gtime
     * @param  {const gps_t}   in:                  input:     gps_t
     * @return {gtime_t}    :                      output:     gtime_t
     */
    gtime_t bdt2gtime(const gps_t& in) {
        gtime_t res = epoch2gtime(bdt0);
        res.time += in.week * SEC_A_WEEK + (int)in.sec;
        res.sec += (in.sec - (int)in.sec);
        return res;
    }

    /**
     * @description: convert gps time to utc, considering leaps
     * @param  {const gtime_t}   in:                input:     gps time
     * @return {gtime_t}    :                      output:     utc time
     */
    gtime_t gpst2utc(const gtime_t& in) {
        gtime_t res;
        for (int i = 0; leaps[i][0] > 0; ++i) {
            res = in + leaps[i][6];
            if (res - epoch2gtime(leaps[i]) >= 0.0)
                return res;
        }
        return in;
    }

    /**
     * @description: convert utc time to gps time
     * @param  {const gtime_t}   in:                input:     utc time
     * @return {gtime_t}    :                      output:     gps time
     */
    gtime_t utc2gpst(const gtime_t& in) {
        for (int i = 0; leaps[i][0] > 0; ++i) {
            if (in - epoch2gtime(leaps[i]) >= 0.0)
                return in - leaps[i][6];
        }
        return in;
    }
};

#endif //_GPS_TIME_TOOL_STRUCT_H_