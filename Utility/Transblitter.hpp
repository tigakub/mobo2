#ifndef __TRANSBLITTER_HPP__
#define __TRANSBLITTER_HPP__

#include "Math.hpp"
using namespace std;

namespace mobo
{
    class Transblitter
    {
        public:
            virtual void operator()(void* iDst, const void* iSrc, uint32_t iCount) const = 0;
    };

    template <class T, class U>
    class TransblitterT : public Transblitter
    {
        virtual void operator()(void* iDst, const void* iSrc, uint32_t i) const {
            const U* src = static_cast<const U*>(iSrc);
            T* dst = static_cast<T*>(iDst);
            if(iDst > iSrc)
                while(i--) dst[i] = src[i];
            else
                for(uint32_t n = 0; n < i; n++)
                    dst[n] = src[n];
        }
    };

    using RGBAfromRGBTransblitter = TransblitterT<pnt4<uint8_t>, vec3<uint8_t>>;
    using Pnt4FfromVec3FTransblitter = TransblitterT<pnt4<float>, vec3<float>>;

    extern const RGBAfromRGBTransblitter rgbaFromRgbTransblitter;
    extern const Pnt4FfromVec3FTransblitter pnt4fFromVec3fTransblitter;
}

#endif