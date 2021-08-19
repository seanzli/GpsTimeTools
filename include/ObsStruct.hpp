/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-19 21:14:28
 */

#include <vector>
#include <memory.h>

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
            m_buf = nullptr;

        }

        inline unsigned int size() {return m_size;}

        int write(const char* buf, const unsigned int size) {
            if (buf == nullptr || size > m_size || validLen() < size) // valid buffer length less than need
                return 0;
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
            return 0;
        }

        int read(char* buf, const unsigned int size) {
            return 0;
        }


    private:
        unsigned int m_size;
        unsigned int m_write_idx, m_read_idx;
        char* m_buf;

        unsigned int validLen() {
            if (m_write_idx > m_read_idx)
                return m_size - m_write_idx + m_read_idx;
            if (m_write_idx < m_read_idx)
                return m_read_idx - m_write_idx;
        }
    };
};