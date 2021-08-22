/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-22 11:09:50
 */

#include <vector>
#include <memory.h>

#include "GpsTools.hpp"


namespace Raw{
    using namespace GpsTimeTool;

    struct sat{
        unsigned char               sys;    // sys code
        unsigned char               prn;    // prn
    };

    class obs {
    public:
        gtime_t                     time;   // time (gpst)
        unsigned char               satn;   // satellite number
        std::vector<unsigned char>  snr;    // signal strength (0.25 dBHz)
        std::vector<unsigned char>  lli;    // loss of lock indicator
        std::vector<unsigned char>  code;   // code indicator
        std::vector<double>         L;      // observation data -> carrier-phase(cycle)
        std::vector<double>         P;      // observation data -> pseudorange(m)
        std::vector<double>         D;      // observation data -> doppler frequency(Hz)
    }; // all vectors should be the same size;
};

namespace Raw {
    // GPS define

    // navigation system
    constexpr unsigned char SYS_NONE =   0x00;                /* navigation system: none */
    constexpr unsigned char SYS_GPS  =   0x01;                /* navigation system: GPS */
    constexpr unsigned char SYS_SBS  =   0x02;                /* navigation system: SBAS */
    constexpr unsigned char SYS_GLO  =   0x04;                /* navigation system: GLONASS */
    constexpr unsigned char SYS_GAL  =   0x08;                /* navigation system: Galileo */
    constexpr unsigned char SYS_QZS  =   0x10;                /* navigation system: QZSS */
    constexpr unsigned char SYS_CMP  =   0x20;                /* navigation system: BeiDou */
    constexpr unsigned char SYS_IRN  =   0x40;                /* navigation system: IRNSS */
    constexpr unsigned char SYS_LEO  =   0x80;                /* navigation system: LEO */
    constexpr unsigned char SYS_ALL  =   0xFF;                /* navigation system: all */

    // time system
    constexpr unsigned char TSYS_GPS  =  0;                   /* time system: GPS time */
    constexpr unsigned char TSYS_UTC  =  1;                   /* time system: UTC */
    constexpr unsigned char TSYS_GLO  =  2;                   /* time system: GLONASS time */
    constexpr unsigned char TSYS_GAL  =  3;                   /* time system: Galileo time */
    constexpr unsigned char TSYS_QZS  =  4;                   /* time system: QZSS time */
    constexpr unsigned char TSYS_CMP  =  5;                   /* time system: BeiDou time */

    // obs code
    constexpr unsigned char CODE_NONE =  0 ;                  /* obs code: none or unknown */
    constexpr unsigned char CODE_L1C  =  1 ;                  /* obs code: L1C/A,G1C/A,E1C (GPS,GLO,GAL,QZS,SBS) */
    constexpr unsigned char CODE_L1P  =  2 ;                  /* obs code: L1P,G1P    (GPS,GLO) */
    constexpr unsigned char CODE_L1W  =  3 ;                  /* obs code: L1 Z-track (GPS) */
    constexpr unsigned char CODE_L1Y  =  4 ;                  /* obs code: L1Y        (GPS) */
    constexpr unsigned char CODE_L1M  =  5 ;                  /* obs code: L1M        (GPS) */
    constexpr unsigned char CODE_L1N  =  6 ;                  /* obs code: L1codeless (GPS) */
    constexpr unsigned char CODE_L1S  =  7 ;                  /* obs code: L1C(D)     (GPS,QZS) */
    constexpr unsigned char CODE_L1L  =  8 ;                  /* obs code: L1C(P)     (GPS,QZS) */
    constexpr unsigned char CODE_L1E  =  9 ;                  /* obs code: L1-SAIF    (QZS) */
    constexpr unsigned char CODE_L1A  =  10;                  /* obs code: E1A        (GAL) */
    constexpr unsigned char CODE_L1B  =  11;                  /* obs code: E1B        (GAL) */
    constexpr unsigned char CODE_L1X  =  12;                  /* obs code: E1B+C,L1C(D+P) (GAL,QZS) */
    constexpr unsigned char CODE_L1Z  =  13;                  /* obs code: E1A+B+C,L1SAIF (GAL,QZS) */
    constexpr unsigned char CODE_L2C  =  14;                  /* obs code: L2C/A,G1C/A (GPS,GLO) */
    constexpr unsigned char CODE_L2D  =  15;                  /* obs code: L2 L1C/A-(P2-P1) (GPS) */
    constexpr unsigned char CODE_L2S  =  16;                  /* obs code: L2C(M)     (GPS,QZS) */
    constexpr unsigned char CODE_L2L  =  17;                  /* obs code: L2C(L)     (GPS,QZS) */
    constexpr unsigned char CODE_L2X  =  18;                  /* obs code: L2C(M+L),B1I+Q (GPS,QZS,CMP) */
    constexpr unsigned char CODE_L2P  =  19;                  /* obs code: L2P,G2P    (GPS,GLO) */
    constexpr unsigned char CODE_L2W  =  20;                  /* obs code: L2 Z-track (GPS) */
    constexpr unsigned char CODE_L2Y  =  21;                  /* obs code: L2Y        (GPS) */
    constexpr unsigned char CODE_L2M  =  22;                  /* obs code: L2M        (GPS) */
    constexpr unsigned char CODE_L2N  =  23;                  /* obs code: L2codeless (GPS) */
    constexpr unsigned char CODE_L5I  =  24;                  /* obs code: L5/E5aI    (GPS,GAL,QZS,SBS) */
    constexpr unsigned char CODE_L5Q  =  25;                  /* obs code: L5/E5aQ    (GPS,GAL,QZS,SBS) */
    constexpr unsigned char CODE_L5X  =  26;                  /* obs code: L5/E5aI+Q  (GPS,GAL,QZS,SBS) */
    constexpr unsigned char CODE_L7I  =  27;                  /* obs code: E5bI,B2I   (GAL,CMP) */
    constexpr unsigned char CODE_L7Q  =  28;                  /* obs code: E5bQ,B2Q   (GAL,CMP) */
    constexpr unsigned char CODE_L7X  =  29;                  /* obs code: E5bI+Q,B2I+Q (GAL,CMP) */
    constexpr unsigned char CODE_L6A  =  30;                  /* obs code: E6A        (GAL) */
    constexpr unsigned char CODE_L6B  =  31;                  /* obs code: E6B        (GAL) */
    constexpr unsigned char CODE_L6C  =  32;                  /* obs code: E6C        (GAL) */
    constexpr unsigned char CODE_L6X  =  33;                  /* obs code: E6B+C,LEXS+L,B3I+Q (GAL,QZS,CMP) */
    constexpr unsigned char CODE_L6Z  =  34;                  /* obs code: E6A+B+C    (GAL) */
    constexpr unsigned char CODE_L6S  =  35;                  /* obs code: LEXS       (QZS) */
    constexpr unsigned char CODE_L6L  =  36;                  /* obs code: LEXL       (QZS) */
    constexpr unsigned char CODE_L8I  =  37;                  /* obs code: E5(a+b)I   (GAL) */
    constexpr unsigned char CODE_L8Q  =  38;                  /* obs code: E5(a+b)Q   (GAL) */
    constexpr unsigned char CODE_L8X  =  39;                  /* obs code: E5(a+b)I+Q (GAL) */
    constexpr unsigned char CODE_L2I  =  40;                  /* obs code: B1I        (CMP) */
    constexpr unsigned char CODE_L2Q  =  41;                  /* obs code: B1Q        (CMP) */
    constexpr unsigned char CODE_L6I  =  42;                  /* obs code: B3I        (CMP) */
    constexpr unsigned char CODE_L6Q  =  43;                  /* obs code: B3Q        (CMP) */
    constexpr unsigned char CODE_L3I  =  44;                  /* obs code: G3I        (GLO) */
    constexpr unsigned char CODE_L3Q  =  45;                  /* obs code: G3Q        (GLO) */
    constexpr unsigned char CODE_L3X  =  46;                  /* obs code: G3I+Q      (GLO) */
    constexpr unsigned char CODE_L1I  =  47;                  /* obs code: B1I        (BDS) */
    constexpr unsigned char CODE_L1Q  =  48;                  /* obs code: B1Q        (BDS) */
    constexpr unsigned char MAXCODE   =  48;                  /* max number of obs code */

    constexpr double PI         = 3.1415926535897932;  /* pi */
    constexpr double D2R        = (PI/180.0);          /* deg to rad */
    constexpr double R2D        = (180.0/PI);          /* rad to deg */
    constexpr double CLIGHT     = 299792458.0;         /* speed of light (m/s)*/

    constexpr double FREQ1      = 1.57542E9 ;          /* L1/E1  frequency (Hz) */
    constexpr double FREQ2      = 1.22760E9 ;          /* L2     frequency (Hz) */
    constexpr double FREQ5      = 1.17645E9 ;          /* L5/E5a frequency (Hz) */
    constexpr double FREQ6      = 1.27875E9 ;          /* E6/LEX frequency (Hz) */
    constexpr double FREQ7      = 1.20714E9 ;          /* E5b    frequency (Hz) */
    constexpr double FREQ8      = 1.191795E9;          /* E5a+b  frequency (Hz) */
    constexpr double FREQ1_GLO  = 1.60200E9 ;          /* GLONASS G1 base frequency (Hz) */
    constexpr double DFRQ1_GLO  = 0.56250E6 ;          /* GLONASS G1 bias frequency (Hz/n) */
    constexpr double FREQ2_GLO  = 1.24600E9 ;          /* GLONASS G2 base frequency (Hz) */
    constexpr double DFRQ2_GLO  = 0.43750E6 ;          /* GLONASS G2 bias frequency (Hz/n) */
    constexpr double FREQ3_GLO  = 1.202025E9;          /* GLONASS G3 frequency (Hz) */
    constexpr double FREQ1_CMP  = 1.561098E9;          /* BeiDou B1 frequency (Hz) */
    constexpr double FREQ2_CMP  = 1.20714E9 ;          /* BeiDou B2 frequency (Hz) */
    constexpr double FREQ3_CMP  = 1.26852E9 ;          /* BeiDou B3 frequency (Hz) */


    constexpr unsigned char NEXOBS    =  0;
    constexpr unsigned char NFREQ     =  3;

    constexpr double satwavelen(int sys, int frq) {
        if (sys==SYS_CMP) {
            if      (frq==0) return CLIGHT/FREQ1_CMP; /* B1 */
            else if (frq==1) return CLIGHT/FREQ2_CMP; /* B3 */
            else if (frq==2) return CLIGHT/FREQ3_CMP; /* B2 */
        }
        else if (sys == SYS_GPS) {
            if      (frq==0) return CLIGHT/FREQ1; /* L1/E1 */
            else if (frq==1) return CLIGHT/FREQ2; /* L2 */
            else if (frq==2) return CLIGHT/FREQ5; /* L5/E5a */
            else if (frq==3) return CLIGHT/FREQ6; /* L6/LEX */
            else if (frq==4) return CLIGHT/FREQ7; /* E5b */
            else if (frq==5) return CLIGHT/FREQ8; /* E5a+b */
        }
        return 0.0;
    }

}

namespace Raw {
    class buffer {
    public:
        explicit buffer(unsigned int length) : 
        m_size(length), m_write_idx(0), m_read_idx(0),
        m_isEmpty(true), m_isFull(false) {
            m_buf = new unsigned char[m_size];
        }

        ~buffer() {
            if (m_buf)
                delete[] m_buf;
            m_buf = nullptr;

        }

        inline unsigned int capture() {return m_size;}
        inline bool isFull() {return m_isFull;}
        inline bool isEmpty() {return m_isEmpty;}
        

        /**
         * @description: buffer write
         * @param  {const unsigned char*}  buf:    input:     buffer pointer 
         * @param  {const unsigned int} size:      input:     buffer size
         * @return {int}: output buf size;  0=write success
         *                                  1=no more space to write
         */
        int write(const unsigned char* buf, const unsigned int size) {
            if (buf == nullptr || size > m_size || validLen() < size) // valid buffer length less than need
                return 1;
            if (m_write_idx >= m_read_idx) {  // tail -> read -> write -> head
                int valid_len_head = m_size - m_write_idx;
                if (valid_len_head >= size) {
                    memcpy(m_buf + m_write_idx, buf, size);
                    m_write_idx += size;
                } else {
                    memcpy(m_buf + m_write_idx, buf, valid_len_head);
                    memcpy(m_buf, buf + valid_len_head, size - valid_len_head);
                    m_write_idx = size - valid_len_head;
                }
            } else { // tail -> write -> read -> head
                memcpy(m_buf + m_write_idx, buf, size);
                m_write_idx += size;
            }
            m_isFull = m_write_idx == m_read_idx;
            return 0;
        }

        /**
         * @description: buffer resder
         * @param  {unsigned char*}  buf:          output:      
         * @param  {const unsigned int} size:      input:
         * @return {unsigned int}: output buf size;
         */
        unsigned int read(unsigned char* buf, const unsigned int size) {
            if (size == 0)
                return 0;
            int read_size = std::min(size, m_size - validLen());
            if (m_write_idx > m_read_idx) { // tail -> read -> write -> head
                memcpy(buf, m_buf + m_read_idx, read_size);
                m_read_idx += read_size;
            } else { // tail -> write -> read -> head
                unsigned head_len = m_size - m_read_idx;
                if (head_len > read_size) {
                    memcpy(buf, m_buf + m_read_idx, read_size);
                    m_read_idx += read_size;
                } else {
                    memcpy(buf, m_buf + m_read_idx, head_len);
                    memcpy(buf + head_len, m_buf, read_size - head_len);
                    m_read_idx = read_size - head_len;
                }
            }

            m_isEmpty = m_read_idx == m_write_idx;
            return read_size;
        }


    private:
        unsigned int    m_size;
        unsigned int    m_write_idx, m_read_idx;
        bool            m_isEmpty, m_isFull;
        unsigned char*  m_buf;

        unsigned int validLen() {
            if (m_write_idx > m_read_idx)
                return m_size - m_write_idx + m_read_idx;
            if (m_write_idx < m_read_idx)
                return m_read_idx - m_write_idx;
        }
    };
};