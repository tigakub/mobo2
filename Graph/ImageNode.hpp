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

    class ImageNode : public DataSourceNode, public DataSourceT<pnt4<uint8_t>>
    {
        DECLARE_TYPE

        public:
            ImageNode()
            : DataSourceNode(), DataSourceT<pnt4<uint8_t>>(), imgWidth(0), imgHeight(0) {
                addInput(StringNode::_type);
            }

            virtual uint32_t size() const { return imageBuffer.size() / byteStride(); }

            virtual bool update(Context& iCtx);

            virtual const void* rawMap() const;
            virtual void* rawMap() { return nullptr; }

            const vector<unsigned char> getImageBuffer() const { return imageBuffer; }

            uint32_t getWidth() { return imgWidth; }
            uint32_t getHeight() { return imgHeight; }
            
        protected:

        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false) { }

        protected:
            vector<unsigned char> imageBuffer;
            uint32_t imgWidth, imgHeight;
    };

}

#endif
