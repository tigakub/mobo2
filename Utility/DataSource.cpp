#include "DataSource.hpp"

namespace mobo
{
    void DataSource::resizeIfNeeded(size_t iNewSize, bool iPreserve)
    {
        if(iNewSize != size()) {
            setSize(iNewSize, iPreserve);
        }
    }
}
