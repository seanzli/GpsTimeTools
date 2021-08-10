/*
 * @Descripttion: test main function
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-10 21:04:39
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-10 21:07:47
 */

#include <iostream>
#include <gtest/gtest.h>

#include "TestStruct.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}