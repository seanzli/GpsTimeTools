/*
 * @Descripttion: Decode novatel message
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-16 21:00:53
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-22 10:55:35
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
        NO_MATCH_DECODER,
        LENGTH_ERROR
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
        return DECODE_ERROR::NO_MATCH_DECODER;
    }
    

    /**
     * @description: decode_rangeb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rangeb(const unsigned char* buf, const unsigned int len) {

        return DECODE_ERROR::NO_MATCH_DECODER;
    }

    /**
     * @description: decode_rangecmpb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rangecmpb(const unsigned char* buf, const unsigned int len) {

        int nobs = U4(buf + Oem4HeaderLen); // number of obs
        const int obs_length = 24;

        //length check
        if (len < Oem4HeaderLen + 4 + obs_length * nobs)
            return DECODE_ERROR::LENGTH_ERROR;
        
        const unsigned char* p = buf + Oem4HeaderLen + 4;
        
        double psr,adr,adr_rolls,lockt,tt,dop,snr,wavelen;
        int i,index,nobs,prn,sat,sys,code,freq,pos;
        int track,plock,clock,parity,halfc,lli;
        
        for (int i = 0; i < nobs; ++i) {
            if((freq = decode_trackstat(U4(p + i * obs_length), sys, code, track, plock, clock,
                                        parity, halfc)) < 0)
                continue;
            
        }


        return DECODE_ERROR::NO_ERROR;
    }

    /**
     * @description: decode_rawephemb
     * @param  {const unsigned char*}  buf:    input:       message buffer
     * @param  {const unsigned int} len:       input:       message length (buffer length = message length + 4byte)
     * @return {DECODE_ERROR}: output sign
     */
    DECODE_ERROR decode_rawephemb(const unsigned char* buf, const unsigned int len) {

        return DECODE_ERROR::NO_MATCH_DECODER;
    }

    /**
     * @description: decode_trackstat
     * @param  {unsigned int}  stat:           input:       stat code
     * @param  ...                             output:      stat options
     * @return {int}: freq code
     */
    int decode_trackstat(unsigned int stat, int& sys, int& code, int& track, int& plock, int& clock,
                         int& parity, int& halfc) {
        int satsys, sigtype, freq = 0;
        
        track  = stat&0x1F;
        plock  = (stat>>10)&1;
        parity = (stat>>11)&1;
        clock  = (stat>>12)&1;
        satsys = (stat>>16)&7;
        halfc  = (stat>>28)&1;
        sigtype= (stat>>21)&0x1F;

        switch (satsys) {
            case 0: sys = SYS_GPS; break;
            case 1: sys = SYS_GLO; break;
            case 2: sys = SYS_SBS; break;
            case 3: sys = SYS_GAL; break;
            case 4: sys = SYS_CMP; break;
            case 5: sys = SYS_QZS; break;
            default:
                return -1; // unknown system
        }

        if (sys ==SYS_GPS||sys ==SYS_QZS) {
            switch (sigtype) {
                case  0: freq=0; code =CODE_L1C; break; /* L1C/A */
                case  5: freq=0; code =CODE_L1P; break; /* L1P */
                case  9: freq=1; code =CODE_L2W; break; /* L2Pcodeless */
                case 14: freq=2; code =CODE_L5Q; break; /* L5Q (OEM6) */
                case 17: freq=1; code =CODE_L2X; break; /* L2C(M+L) */
                default: freq=-1; break;
            }
        }
        else if (sys ==SYS_GLO) {
            switch (sigtype) {
                case  0: freq=0; code =CODE_L1C; break; /* L1C/A */
                case  1: freq=1; code =CODE_L2C; break; /* L2C/A (OEM6) */
                case  5: freq=1; code =CODE_L2P; break; /* L2P */
                default: freq=-1; break;
            }
        }
        else if (sys ==SYS_GAL) {
            switch (sigtype) {
                case  1: freq=0; code =CODE_L1B; break; /* E1B  (OEM6) */
                case  2: freq=0; code =CODE_L1C; break; /* E1C  (OEM6) */
                case 12: freq=2; code =CODE_L5Q; break; /* E5aQ (OEM6) */
                case 17: freq=4; code =CODE_L7Q; break; /* E5bQ (OEM6) */
                case 20: freq=5; code =CODE_L8Q; break; /* AltBOCQ (OEM6) */
                default: freq=-1; break;
            }
        }
        else if (sys ==SYS_CMP) {
            switch (sigtype) {
                case  0: freq=0; code =CODE_L1I; break; /* B1 with D1 (OEM6) */
                case  1: freq=1; code =CODE_L7I; break; /* B2 with D1 (OEM6) */
                case  4: freq=0; code =CODE_L1I; break; /* B1 with D2 (OEM6) */
                case  5: freq=1; code =CODE_L7I; break; /* B2 with D2 (OEM6) */
                default: freq=-1; break;
            }
        }
        else if (sys ==SYS_SBS) {
            switch (sigtype) {
                case  0: freq=0; code =CODE_L1C; break; /* L1C/A */
                case  6: freq=2; code =CODE_L5I; break; /* L5I (OEM6) */
                default: freq=-1; break;
            }
        }
        if (freq < 0)
            return -2; // signal type decode error, sys = sys, sigtype = sigtype;
        
        return freq;
    }

    /* check code priority and return obs position -------------------------------*/
    int checkpri(const char *opt, int sys, int code, int freq)
    {
        int nex=NEXOBS; /* number of extended obs data */
        
        if (sys==SYS_GPS) {
            if (strstr(opt,"-GL1P")&&freq==0) return code==CODE_L1P?0:-1;
            if (strstr(opt,"-GL2X")&&freq==1) return code==CODE_L2X?1:-1;
            if (code==CODE_L1P) return nex<1?-1:NFREQ;
            if (code==CODE_L2X) return nex<2?-1:NFREQ+1;
        }
        else if (sys==SYS_GLO) {
            if (strstr(opt,"-RL2C")&&freq==1) return code==CODE_L2C?1:-1;
            if (code==CODE_L2C) return nex<1?-1:NFREQ;
        }
        else if (sys==SYS_GAL) {
            if (strstr(opt,"-EL1B")&&freq==0) return code==CODE_L1B?0:-1;
            if (code==CODE_L1B) return nex<1?-1:NFREQ;
            if (code==CODE_L7Q) return nex<2?-1:NFREQ+1;
            if (code==CODE_L8Q) return nex<3?-1:NFREQ+2;
        }
        return freq<NFREQ?freq:-1;
    }

}