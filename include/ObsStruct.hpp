/*
 * @Descripttion: struct obs,eph
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-18 19:57:00
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-21 08:22:23
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