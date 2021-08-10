/*
 * @Descripttion: Struct Define
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 20:54:55
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-10 21:19:01
 */


#ifndef _GPS_TIME_TOOL_STRUCT_H_
#define _GPS_TIME_TOOL_STRUCT_H_

// c++
#include <ctime>
#include <cmath>

namespace GpsTimeTool {
    struct gtime_t {
        time_t time;
        double sec;
        
        gtime_t() : time(0), sec(0.0) {}
        gtime_t(time_t _t, double _sec) : time(_t), sec(_sec) {}
        gtime_t(time_t _t) : time(_t), sec(0.0) {}

        gtime_t operator+(double _sec) {
            double t, s = this->sec;
            s += _sec;
            t = floor(s);

            return gtime_t(this->time + (int)t, s - t);
        }

        gtime_t operator-(double _sec) {
            return this->operator+(-1.0 * _sec);
        }

        bool operator==(gtime_t t) const {
            return (this->time == t.time) && (fabs(this->sec - t.sec) < 1e-9);
        }

        double operator-(gtime_t in) {
            return difftime(this->time, in.time) + this->sec - in.sec;
        }
    };


};


#endif //_GPS_TIME_TOOL_STRUCT_H_