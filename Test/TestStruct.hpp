/*
 * @Descripttion:  Struct Test
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 21:07:15
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-10 21:22:01
 */

#include <iostream>
#include <gtest/gtest.h>

#include "struct.h"

using namespace GpsTimeTool;

TEST(StructTest, handleFunction) { 
    gtime_t a(0, 0.0);
    gtime_t b(1, 0.03);


    EXPECT_DOUBLE_EQ(b - a, 1.03);
    EXPECT_EQ(b - 1.03, a);
    EXPECT_EQ(b, a + 1.03);
}