/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-18 20:05:02
 */

#include <vector>

#include "GpsTools.hpp"


namespace Raw{
    using namespace GpsTimeTool;
    class obs {
    public:
        gtime_t                     time;
        unsigned char               sat;
        std::vector<unsigned char>  snr;
        std::vector<unsigned char>  lli;
        std::vector<unsigned char>  code;
        std::vector<double>         L;
        std::vector<double>         P;
        std::vector<double>         D;
    };
};