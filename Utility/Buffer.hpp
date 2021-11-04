#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <cstdint> // for uint32_t
#include <type_traits> // for enable_if

using namespace std;

namespace mobo
{
    class Buffer
    {
        protected:
            Buffer() { }
            Buffer(const Buffer& iSrc) { }
            virtual ~Buffer() { }

        public:
            virtual uint32_t elementSize() const = 0;
            virtual uint32_t size() const = 0;
            virtual uint32_t byteSize() const { return size() * elementSize(); }

            virtual Buffer& operator=(const Buffer& iSrc) = 0;
            virtual void unmap() = 0;
            virtual void unmap() const = 0;

        protected:
            virtual void resizeIfNeeded(uint32_t iSize, bool iPreserve = false) = 0;
            virtual void resize(uint32_t iSize, bool iPreserve = false) = 0;
            virtual void setSize(uint32_t iSize) = 0;
            virtual const void* rawMap() const = 0;
            virtual void* rawMap() = 0;
    };

    template <class T>
    class BufferT : public Buffer
    {
        public:
            BufferT() : Buffer(), elementCount(0) { }
            BufferT(const BufferT& iSrc)
            : Buffer(iSrc), elementCount(0) {
                blit(iSrc);
            }

            virtual const T* map() const {
                return (const T*) rawMap();
            }

            virtual T* map() {
                return (T*) rawMap();
            }

            virtual uint32_t elementSize() const {
                return sizeof(T);
            }

            virtual uint32_t size() const {
                return elementCount;
            }

            virtual void resizeIfNeeded(uint32_t iSize, bool iPreserve = false)
            {
                if(iSize > elementCount) {
                    resize(iSize, iPreserve);
                }
            }

        protected:
            virtual void blit(const T* iSrc, uint32_t iSize) {
                resizeIfNeeded(iSize);
                T* dst = map();
                uint32_t n = iSize;
                while(n--) {
                    dst[n] = iSrc[n];
                }
                unmap();
            }

            virtual void blit(const BufferT<T>& iSrc) {
                resizeIfNeeded(iSrc.elementCount);
                const T* src = iSrc.map();
                blit(src, iSrc.elementCount);
                iSrc.unmap();
            }

            virtual void setSize(uint32_t iSize) {
                Buffer::setSize(iSize);
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
            : BufferT<T>(), nativeBuffer(nullptr) { }
            
            HostBufferT(const BufferT<T>& iBuffer)
            : nativeBuffer(nullptr), BufferT<T>(iBuffer) { }
            
            HostBufferT(HostBufferT<T>&& iBuffer)
            : BufferT<T>(), nativeBuffer(nullptr) {
                nativeBuffer = iBuffer.nativeBuffer; iBuffer.nativeBuffer = nullptr;
             }
            
            virtual ~HostBufferT() {
                if(nativeBuffer) delete [] nativeBuffer;
            }
            
            virtual Buffer& operator=(const Buffer& iSrc) {
                if(dynamic_cast<const BufferT<T>*>(&iSrc)) {
                    blit(dynamic_cast<const BufferT<T>&>(iSrc));
                }
                return *this;
            }
            
            virtual void unmap()
            { }
            
            virtual void unmap() const
            { }

        protected:
            virtual void resize(uint32_t iSize, bool iPreserve = false)
            {
                T* newBuffer = new T[iSize];
                if(nativeBuffer) {
                    if(iPreserve) {
                        uint32_t i = BufferT<T>::size();
                        while(i--) newBuffer[i] = nativeBuffer[i];
                    }
                    delete [] nativeBuffer;
                }
                BufferT<T>::setSize(iSize);
                nativeBuffer = newBuffer;
            }

            virtual const void* rawMap() const
            {
                return (const void*) nativeBuffer;
            }

            virtual void* rawMap()
            {
                return (void*) nativeBuffer;
            }

        protected:
            T* nativeBuffer;
    };
}

#endif
