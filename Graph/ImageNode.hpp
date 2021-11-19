#ifndef __IMAGENODE_HPP__
#define __IMAGENODE_HPP__

#include "StringNode.hpp"
#include "DataSourceNode.hpp"
#include "Transblitter.hpp"
#include "Math.hpp"
#include "lodepng.h"
#include "Type.hpp"

#include <vector>

using namespace std;

namespace mobo
{

    class ImageNode : public FrameSourceNode, public DataSourceT<pnt4<uint8_t>>
    {
        DECLARE_TYPE

        public:
            ImageNode()
            : FrameSourceNode(), DataSourceT<pnt4<uint8_t>>() {
                addInput(StringNode::_type);
            }

            virtual size_t size() const { return imageBuffer.size() / byteStride(); }

            virtual bool update(Context& iCtx);

            virtual const void* rawMap() const;
            virtual void* rawMap();
            
        protected:
            virtual void setSize(size_t iSize, bool iPreserve = false) { }

        protected:
            vector<uint8_t> imageBuffer;
    };

}

#endif
