/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-18 20:33:51
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

namespace Raw {
    class buffer {
    public:
        explicit buffer(unsigned int length) : m_size(length), m_write_idx(0), m_read_idx(0) {
            m_buf = new char[m_size];
        }

        ~buffer() {
            if (m_buf)
                delete[] m_buf;
        }

        inline unsigned int size() {return m_size;}

        int write(const char* buf, const unsigned int size) {
            return 0;
        }

        int read(char* buf, const unsigned int size) {
            return 0;
        }


    private:
        unsigned int m_size;
        unsigned int m_write_idx, m_read_idx;
        char* m_buf;

        unsigned int left() {
            return m_size - m_write_idx + m_read_idx;
        }
    };
};