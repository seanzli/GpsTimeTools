/*
 * @Author: Sean
 * @Date: 2021-08-10 20:43:09
 * @LastEditTime: 2021-08-10 20:54:05
 * @LastEditors: Sean
 * @Description: 
 * @FilePath: /GpsTimeTools/main.cpp
 */

// c++ stl
#include <iostream>

// google log
#include <glog/logging.h>

// test


int main(int argc, char* argv[]) {
    // google-logging-library initailization
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "../log/log_");

    LOG(INFO) << "------start-------\n";

    return 0;
}
