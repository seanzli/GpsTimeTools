/*
 * @Descripttion:  Struct Test
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 21:07:15
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-13 20:52:53
 */

#include <iostream>
#include <gtest/gtest.h>

#include "struct.hpp"

using namespace GpsTimeTool;

TEST(GtimeStructTest, handleFunction) { 
    gtime_t a(0, 0.0);
    gtime_t b(1, 0.03);


    EXPECT_DOUBLE_EQ(b - a, 1.03);
    EXPECT_EQ(b - 1.03, a);
    EXPECT_EQ(b, a + 1.03);
}

TEST(GpstStructTest, handleFunction) {
    gps_t at(2020, -1.0);
    gps_t at_e(2019, 604800 - 1.0);
    gps_t bt(2021, 604800);
    gps_t bt_e(2022, 0.0);
    gps_t ct(2022, 604801);
    gps_t ct_e(2023, 1.0);

    EXPECT_EQ(at, at_e);
    EXPECT_EQ(bt, bt_e);
    EXPECT_EQ(ct, ct_e);
}

TEST(StructConvertTest, handleFunction) {
    //gps_t a_gpst(2020, SEC_A_WEEK - 1);
    gtime_t a_time(1538265599, 0.99999);
    gps_t a_gpst = gtime2gpst(a_time);
    std::vector<double> epoch;
    gtime2epoch(a_time, epoch);

    std::cout << "epoch2gtime\n";
    EXPECT_EQ(epoch2gtime(epoch),a_time);
    std::cout << "gpst2gtime\n";
    EXPECT_EQ(gpst2gtime(a_gpst),a_time);

    gtime_t utc_time = gpst2utc(a_time);
    gtime_t a_utc_time2gpst = utc2gpst(utc_time);
    EXPECT_EQ(a_time, a_utc_time2gpst);
}