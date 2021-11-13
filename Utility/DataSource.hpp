#ifndef __DATASOURCE_HPP__
#define __DATASOURCE_HPP__

#include "Debug.hpp"

#include "Transblitter.hpp"
#include "Node.hpp"

namespace mobo
{

    class DataSource
    {
        public:
            DataSource() { }
            virtual ~DataSource() { }

            virtual uint32_t byteSize() const { return size() * byteStride(); }
            virtual uint32_t size() const = 0;
            virtual uint32_t byteStride() const = 0;
            virtual void resizeIfNeeded(uint32_t iNewSize, bool iPreserve = false);
        
            virtual const void* rawMap() const = 0;
            virtual void* rawMap() = 0;
            virtual void unmap() const { }
            virtual void unmap() { }

            virtual void blit(const void* iData, uint32_t iSize, const Transblitter* iTransblitter = nullptr) { }

            virtual const Transblitter *getTransblitter() const { return nullptr; }
            virtual Transblitter *getTransblitter() { return nullptr; }

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
            
            virtual uint32_t byteStride() const { return sizeof(T); }

            virtual void blit(const void* iData, uint32_t i, const Transblitter* iTransblitter = nullptr) {
                resizeIfNeeded(i);
                void* rawDst = rawMap();
                if(rawDst) {
                    if(iTransblitter) {
                        (*iTransblitter)(rawDst, iData, i);
                    } else {
                        const T* src = static_cast<const T*>(iData);
                        T* dst = static_cast<T*>(rawDst);
                        if(rawDst > iData)
                            while(i--)
                                dst[i] = src[i];
                        else
                            for(uint32_t n = 0; n < i; n++)
                                dst[n] = src[n];
                    }
                }
                unmap();
            }

            virtual void blit(const DataSource& iSrc) {
                const Transblitter *transblitter = iSrc.getTransblitter();
                const void* src = iSrc.rawMap();
                if(src)
                    blit(src, iSrc.size(), transblitter);
                iSrc.unmap();
            }
    };

}

#endif
