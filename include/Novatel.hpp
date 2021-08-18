/*
 * @Descripttion: Decode novatel message
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-16 21:00:53
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-18 20:19:18
 */

#include <string>
#include <memory.h>

#include "GpsTools.hpp"

namespace NovatelDecode {

    using namespace GpsTimeTool;

    constexpr char OME4SYNC1 = 0xAA;
    constexpr char OME4SYNC2 = 0x44;
    constexpr char OME4SYNC3 = 0x12;

    constexpr char OME3SYNC1 = 0xAA;
    constexpr char OME3SYNC2 = 0x44;
    constexpr char OME3SYNC3 = 0x11;

    constexpr  int Oem4HeaderLen = 28;  // bytes
    constexpr  int Oem3HeaderLen = 12;  // bytes

    constexpr  int ID_RANGE     = 43;
    constexpr  int ID_RANGECMP  = 140;
    constexpr  int ID_RAWEPHEM  = 41;

    constexpr unsigned char U1(unsigned char* p) { return (unsigned char)(*p);}
    constexpr signed char   I1(signed char *p)   { return (signed char)(*p);  }
    unsigned short          U2(unsigned char *p) { unsigned short u; memcpy(&u, p, 2);  return u;}
    unsigned int            U4(unsigned char *p) { unsigned int   u; memcpy(&u, p, 4);  return u;}
    int                     I4(unsigned char *p) { int            i; memcpy(&i, p, 4);  return i;}
    float                   R4(unsigned char *p) { float          r; memcpy(&r, p, 4);  return r;}
    double                  R8(unsigned char *p) { double         r; memcpy(&r, p, 8);  return r;}

    
}