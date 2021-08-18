/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-18 20:10:00
 */

#include <vector>

#include "GpsTools.hpp"


namespace Raw{
    using namespace GpsTimeTool;
    class obs {
    public:
        gtime_t                     time;   // time (gpst)
        unsigned char               sat;    // satellite number
        std::vector<unsigned char>  snr;    // signal strength (0.25 dBHz)
        std::vector<unsigned char>  lli;    // loss of lock indicator
        std::vector<unsigned char>  code;   // code indicator
        std::vector<double>         L;      // observation data -> carrier-phase(cycle)
        std::vector<double>         P;      // observation data -> pseudorange(m)
        std::vector<double>         D;      // observation data -> doppler frequency(Hz)
    }; // all vectors should be the same size;
};