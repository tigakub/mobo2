#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "DataSource.hpp"

#include <cstdint> // for uint32_t
#include <type_traits> // for enable_if
#include <vector>
#include <iostream>

using namespace std;

namespace mobo
{
    template <class T>
    class BufferT : public DataSourceT<T>
    {
        public:
            BufferT() : DataSourceT<T>(), elementCount(0) { }
            BufferT(const BufferT<T>& iSrc)
            : DataSourceT<T>(iSrc), elementCount(0) {
                DataSourceT<T>::blit(iSrc);
            }

            virtual uint32_t size() const {
                return elementCount;
            }

        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false) {
                elementCount = iSize;
            }

        protected:
            uint32_t elementCount;
    };

    template <class T>
    class HostBufferT : public BufferT<T>
    {
        public:
            HostBufferT()
            : BufferT<T>(), nativeBuffer() { }
            
            HostBufferT(const BufferT<T>& iBuffer)
            : nativeBuffer(), BufferT<T>(iBuffer) { }
            
            HostBufferT(HostBufferT<T>&& iBuffer)
            : BufferT<T>(), nativeBuffer(move(iBuffer.nativeBuffer))
            { }

            virtual ~HostBufferT() { }

            /*
            virtual Buffer& operator=(const Buffer& iSrc) {
                if(dynamic_cast<const BufferT<T>*>(&iSrc)) {
                    blit<T>(iSrc);
                }
                return *this;
            }
            */
            virtual DataSourceT<T>& operator=(HostBufferT<T>&& iSrc) {
                // if(nativeBuffer) delete [] nativeBuffer;
                nativeBuffer = move(iSrc.nativeBuffer);
                BufferT<T>::elementCount = iSrc.elementCount;
                // iSrc.nativeBuffer = nullptr;
                iSrc.elementCount = 0;
                return *this;
            }
            
        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false)
            {
                BufferT<T>::setSize(iSize, iPreserve);
                nativeBuffer.resize(iSize);
                /*
                T* newBuffer = new T[iSize];
                if(nativeBuffer) {
                    if(iPreserve) {
                        uint32_t i = BufferT<T>::size();
                        while(i--) newBuffer[i] = nativeBuffer[i];
                    }
                    delete [] nativeBuffer;
                }
                nativeBuffer = newBuffer;
                */
            }

        public:
            virtual const void* rawMap() const
            {
                return static_cast<const void*>(&(nativeBuffer[0]));
                // return (const void*) nativeBuffer;
            }

            virtual void* rawMap()
            {
                return static_cast<void*>(&(nativeBuffer[0]));
                // return (void*) nativeBuffer;
            }

        protected:
            //T* nativeBuffer;
            vector<T> nativeBuffer;
    };
}

#endif
