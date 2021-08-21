/*
 * @Descripttion: Decode novatel message
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-16 21:00:53
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-21 08:37:18
 */

#include <string>
#include <memory.h>

#include "GpsTools.hpp"
#include "ObsStruct.hpp"

namespace NovatelDecode {

    using namespace GpsTimeTool;
    using namespace Raw;

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

    constexpr unsigned char U1(const unsigned char* p) { return (unsigned char)(*p);}
    constexpr signed char   I1(const signed char *p)   { return (signed char)(*p);  }
    unsigned short          U2(const unsigned char *p) { unsigned short u; memcpy(&u, p, 2);  return u;}
    unsigned int            U4(const unsigned char *p) { unsigned int   u; memcpy(&u, p, 4);  return u;}
    int                     I4(const unsigned char *p) { int            i; memcpy(&i, p, 4);  return i;}
    float                   R4(const unsigned char *p) { float          r; memcpy(&r, p, 4);  return r;}
    double                  R8(const unsigned char *p) { double         r; memcpy(&r, p, 8);  return r;}

    enum class DECODE_ERROR{
        NO_ERROR,             
        CRC32_CHECK_FALSE,
        MESSAGE_TYPE_ASSCII,
    };

    /**
     * @description: novatle crc32 parity
     * @param  {const unsigned char*}  buff:   input:       input buffer
     * @param  {const unsigned int} len:       input:       buffer length
     * @return {unsigned int}:                              crc32 parity
     */
    constexpr unsigned long POLYCRC32 =  0xEDB88320u;           /* CRC32 polynomial */
    unsigned int rtk_crc32(const unsigned char *buff, const unsigned int len)
    {
        unsigned int crc=0;
        int i,j;
        for (i=0;i<len;i++) {
            crc^=buff[i];
            for (j=0;j<8;j++) {
                if (crc&1) crc=(crc>>1)^POLYCRC32; else crc>>=1;
            }
        }
        return crc;
    }

    /**
     * @description: decode_oem4
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_oem4(const unsigned char* buf, const unsigned int len) {
        if (rtk_crc32(buf, len) != U4(buf + len))
            return DECODE_ERROR::CRC32_CHECK_FALSE;  // check crc32 false;
        if ((U1(buf+6)>>4)&0x3 == 1)
            return DECODE_ERROR::MESSAGE_TYPE_ASSCII;  // message type is ascii
        unsigned short type = U2(buf+4);
        
        // int week = U2(buf+14);              //week num;
        // double tow = U4(buf + 16) * 0.001;  //week sec; //gps time

        switch (type) {
            case ID_RANGE       : return decode_rangeb(buf, len);
            case ID_RANGECMP    : return decode_rangecmpb(buf, len);
            case ID_RAWEPHEM    : return decode_rawephemb(buf, len);
        }
        return DECODE_ERROR::NO_ERROR;
    }
    

    /**
     * @description: decode_rangeb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rangeb(const unsigned char* buf, const unsigned int len) {

        return DECODE_ERROR::NO_ERROR;
    }

    /**
     * @description: decode_rangecmpb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rangecmpb(const unsigned char* buf, const unsigned int len) {

        return DECODE_ERROR::NO_ERROR;
    }

    /**
     * @description: decode_rawephemb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rawephemb(const unsigned char* buf, const unsigned int len) {

        return DECODE_ERROR::NO_ERROR;
    }
}