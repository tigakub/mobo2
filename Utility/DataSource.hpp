#ifndef __DATASOURCE_HPP__
#define __DATASOURCE_HPP__

#include "Node.hpp"

namespace mobo
{

    class DataSource
    {
        public:
            virtual uint32_t byteSize() const { return 0; }

            virtual const void* rawMap() const { return nullptr; }
            virtual void* rawMap() { return nullptr; }
            virtual void unmap() const { }
            virtual void unmap() { }
    };

}

#endif
