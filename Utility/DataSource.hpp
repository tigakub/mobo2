#ifndef __DATASOURCE_HPP__
#define __DATASOURCE_HPP__

#include "Debug.hpp"

#include "Node.hpp"

namespace mobo
{
    class Translator
    {
        public:
            virtual void operator()(void* iDst, const void* iSrc, size_t iCount) = 0;
    };

    template <class T, class U>
    class TranslatorT : public Translator
    {
        public:
            virtual void operator()(void* iDst, const void* iSrc, size_t iCount) {
                const U* src = static_cast<const U*>(iSrc);
                T* dst = static_cast<T*>(iDst);
                while(iCount--) dst[iCount] = src[iCount];
            }
    };

    class DataSource
    {
        public:
            DataSource() : translator(nullptr) { }
            virtual ~DataSource() { }

            virtual uint32_t byteSize() const { return size() * elementSize(); }
            virtual uint32_t size() const = 0;
            virtual uint32_t elementSize() const = 0;
            virtual void resizeIfNeeded(uint32_t iNewSize, bool iPreserve = false);
        
            virtual const void* rawMap() const = 0;
            virtual void* rawMap() = 0;
            virtual void unmap() const { }
            virtual void unmap() { }

            void setTranslator(Translator *iTranslator) { translator = iTranslator; }
            Translator* getTranslator() { return translator; }

            virtual void blit(const void* iData, uint32_t iSize) { }

        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false) = 0;

        protected:
            Translator* translator;
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

            virtual void blit(const void* iData, uint32_t iSize) {
                resizeIfNeeded(iSize);
                void* rawDst = rawMap();
                if(rawDst) {
                    if(translator) {
                        (*translator)(rawDst, iData, iSize);
                    } else {
                        const T* src = static_cast<const T*>(iData);
                        T* dst = static_cast<T*>(rawDst);
                        while(iSize--) {
                            dst[iSize] = src[iSize];
                        }
                    }
                }
                unmap();
            }

            virtual void blit(const DataSource& iSrc) {
                blit(iSrc.rawMap(), iSrc.size());
                iSrc.unmap();
            }
    };

}

#endif
