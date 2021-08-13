/*
 * @Descripttion: const define
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-11 20:34:22
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-13 20:47:46
 */

#include <vector>

namespace GpsTimeTool {

    static const std::vector<double> gpst0 = {1980,1,6,0,0,0};    // gps time reference
    static const std::vector<double> bdt0  = {2006,1,1,0,0,0};    // beidou time reference

    constexpr unsigned int MAXLEAPS = 18;
    static const std::vector<std::vector<double>> leaps = {
        {2017,1,1,0,0,0,-18},
        {2015,7,1,0,0,0,-17},
        {2012,7,1,0,0,0,-16},
        {2009,1,1,0,0,0,-15},
        {2006,1,1,0,0,0,-14},
        {1999,1,1,0,0,0,-13},
        {1997,7,1,0,0,0,-12},
        {1996,1,1,0,0,0,-11},
        {1994,7,1,0,0,0,-10},
        {1993,7,1,0,0,0, -9},
        {1992,7,1,0,0,0, -8},
        {1991,1,1,0,0,0, -7},
        {1990,1,1,0,0,0, -6},
        {1988,1,1,0,0,0, -5},
        {1985,7,1,0,0,0, -4},
        {1983,7,1,0,0,0, -3},
        {1982,7,1,0,0,0, -2},
        {1981,7,1,0,0,0, -1},
        {0}
    };

    constexpr unsigned char mday[] = {              // days in a month  // four year
        31,28,31,30,31,30,31,31,30,31,30,31,31,28,31,30,31,30,31,31,30,31,30,31,
        31,29,31,30,31,30,31,31,30,31,30,31,31,28,31,30,31,30,31,31,30,31,30,31
    };

    constexpr unsigned int doy[]  = {1,32,60,91,121,152,182,213,244,274,305,335}; //month day

    constexpr unsigned int SEC_A_DAY = 86400;
    constexpr unsigned int SEC_A_WEEK = 604800;

    constexpr double DOUBLE_ZERO = 1e-7;
};