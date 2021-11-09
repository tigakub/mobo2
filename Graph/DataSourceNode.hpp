#ifndef __DATASOURCENODE_HPP__
#define __DATASOURCENODE_HPP__

#include "Node.hpp"
#include "DataSource.hpp"

namespace mobo
{

    class DataSourceNode : public Node
    {
        DECLARE_TYPE
        
        public:
            DataSourceNode()
            : Node()
            { }
    };

}

#endif