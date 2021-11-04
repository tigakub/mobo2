#ifndef __REFCTR_HPP__
#define __REFCTR_HPP__

#include <cstdint> // for uint64_t

using namespace std;

namespace mobo
{
    class RefCtr
    {
        public:
            RefCtr(uint64_t iRefCount = 0) : ref(iRefCount) { }
            virtual ~RefCtr() { }

            virtual void inc() { ref++; }
            virtual uint64_t dec() { return ref -= ((uint64_t) (ref != 0)); }

        protected:
            uint64_t ref;
    };
}

#endif
