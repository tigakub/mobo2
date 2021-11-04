#include "Type.hpp"

namespace mobo
{
    const vector<const Type*> Type::nullVector;

    bool Type::isBaseOf(const Type& iType) const
    {
        if(isSame(iType)) return true;
        for(auto t : iType.baseTypes) {
            if(isBaseOf(*t.second)) return true;
        }
        return false;
    }
}
