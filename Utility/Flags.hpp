#ifndef __FLAGS_HPP__
#define __FLAGS_HPP__

#include <cstdint> // for uint64_t

using namespace std;

namespace mobo
{
    class Flags
    {
        public:
            Flags() : bits(0) { }
            void set(uint64_t iFlags) { bits |= iFlags; }
            void clear(uint64_t iFlags) { bits &= ~iFlags; }
            uint64_t test(uint64_t iFlags) const { return bits & iFlags; }

        protected:
            uint64_t bits;
    };
}

#endif
