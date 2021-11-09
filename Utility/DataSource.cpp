#include "DataSource.hpp"

namespace mobo
{
    void DataSource::resizeIfNeeded(uint32_t iNewSize, bool iPreserve)
    {
        if(iNewSize > size()) {
            setSize(iNewSize, iPreserve);
        }
    }
}
