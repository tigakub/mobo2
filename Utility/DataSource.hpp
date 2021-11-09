#ifndef __DATASOURCE_HPP__
#define __DATASOURCE_HPP__

#include "Debug.hpp"

#include "Node.hpp"

namespace mobo
{

    class DataSource
    {
        public:
            DataSource() { }
            virtual ~DataSource() { }

            virtual uint32_t byteSize() const { return size() * elementSize(); }
            virtual uint32_t size() const = 0;
            virtual uint32_t elementSize() const = 0;
            virtual void resizeIfNeeded(uint32_t iNewSize, bool iPreserve = false);
        
            virtual const void* rawMap() const = 0;
            virtual void* rawMap() = 0;
            virtual void unmap() const { }
            virtual void unmap() { }

        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false) = 0;
    };

    template <class T>
    class DataSourceT : public DataSource
    {
        public:
            DataSourceT() : DataSource() { }
            DataSourceT(const DataSourceT& iSrc)
            : DataSource() {
                blit(iSrc);
            }

            virtual DataSourceT<T>& operator=(const DataSource& iSrc) {
                blit(iSrc);
                return *this;
            }

            virtual uint32_t elementSize() const { return sizeof(T); }

            virtual void blit(const T* iData, uint32_t iSize) {
                resizeIfNeeded(iSize);
                T* dst = (T*) rawMap();
                if(dst) {
                    while(iSize--) {
                        dst[iSize] = iData[iSize];
                    }
                }
                unmap();
            }

            virtual void blit(const DataSource& iSrc) {
                const T* src = (const T*) iSrc.rawMap();
                blit(src, iSrc.byteSize() / elementSize());
                iSrc.unmap();
            }

    };

}

#endif
