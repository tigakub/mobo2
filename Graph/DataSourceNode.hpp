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

    class FrameSourceNode : public DataSourceNode
    {
        DECLARE_TYPE

        public:
            FrameSourceNode()
            : DataSourceNode(), imgWidth(0), imgHeight(0)
            { }

            size_t getWidth() const { return imgWidth; }
            size_t getHeight() const { return imgHeight; }
        
        protected:
            size_t imgWidth, imgHeight;
    };

}

#endif