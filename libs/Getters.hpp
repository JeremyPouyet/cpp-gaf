#pragma once

#include <climits>
#include <cstring>

namespace getters {
    // get an int from the strand: int8_t, int16_t, int32_t, int64_t and unsigned type
    template<class T>
    T getValue(const Strand &strand, unsigned int &off) {
        T value = 0;
        unsigned int reverseOff = strand.size() - off - 1;
        unsigned int bitSize = sizeof(T) * CHAR_BIT;
        for (unsigned int i = 0; i < bitSize; ++i)
            if (strand[reverseOff - i] == true)
                value |= 1 << i;
        off += bitSize;
        return value;
    }
    
    // get a boolean from the strand
    template<>
    bool getValue(const Strand &strand, unsigned int &off) {
        bool value = strand[off];
        ++off;
        return value;
    }

    // get a 64 bits float from the strand
    template<>
    double getValue(const Strand &strand, unsigned int &off) {
        int64_t i = getValue<int64_t>(strand, off);
        double d;
        std::memcpy(&d, &i, 8);
        return d;
    }

    template<>
    float getValue(const Strand &strand, unsigned int &off) {
        int32_t i = getValue<int32_t>(strand, off);
        float f;
        std::memcpy(&f, &i, 4);
        return f;
    }
};