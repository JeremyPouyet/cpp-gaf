#ifndef GETTERS_HPP
#define GETTERS_HPP

#include <string>
#include <climits>

namespace getters {
    // get an int from the strand: int8_t, int16_t, int32_t, int64_t and unsigned type)
    template<class T>
    T getValue(const std::string &strand, unsigned int &off) {
        T value = 0;
        unsigned int reverseOff = strand.size() - off - 1;
        unsigned int bitSize = sizeof(T) * CHAR_BIT;
        for (unsigned int i = 0; i < bitSize; i++)
            if (strand[reverseOff - i] == '1')
                value |= 1 << i;
        off += bitSize;
        return value;
    }
    
    // get a boolean from the strand
    template<>
    bool getValue(const std::string &strand, unsigned int &off) {
        bool value = strand[off] == '1';
        ++off;
        return value;
    }
    
    // get a 32 bits float from the strand
    template<>
    float getValue(const std::string &strand, unsigned int &off) {
        int16_t a = getValue<int16_t>(strand, off);
        int16_t b = getValue<int16_t>(strand, off);
        bool isNeg = false;
        if (b < 0)
            b = -b;
        if (a < 0) {
            isNeg = true;
            a = -a;
        }
        float value = a + ( b / 100000.0);
        return isNeg ? -value : value;
    }
};

#endif /* GETTERS_HPP */

