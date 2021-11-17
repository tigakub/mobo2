#include "HostBufferNode.hpp"

namespace mobo
{

    DERIVE_TYPE(HostBufferNode, "11174dd5-2234-4b69-9af7-4f099b16ad28", { &DataSourceNode::_type });

    DERIVE_TYPE(HostV2BufferNode, "9c95978c-beed-48dd-8fe0-ce1d0abf65fa", { &HostBufferNode::_type });
    DERIVE_TYPE(HostV3BufferNode, "daf63155-3800-434c-8157-94dda0c62082", { &HostBufferNode::_type });
    DERIVE_TYPE(HostV4BufferNode, "cd1995a0-35b1-49c0-95a5-3bfe2aa1fc31", { &HostBufferNode::_type });
    DERIVE_TYPE(HostIndexBufferNode, "859ff41a-3008-4c8a-8b33-d95770808dd3", { &HostBufferNode::_type });
    DERIVE_TYPE(MeshUVBufferNode, "d4ca243b-a979-4070-820c-c4732cf6bbd7", { &HostV2BufferNode::_type });
    DERIVE_TYPE(MeshIndexBufferNode, "db999180-f191-496d-8e7a-9c55cb925d7c", { &HostIndexBufferNode::_type });

    HostV4BufferNode& HostV4BufferNode::operator=(const DataSourceT<vec3<float>>& iV3DataSource)
    {
        resizeIfNeeded(iV3DataSource.size());
        const vec3<float>* src = static_cast<const vec3<float>*>(iV3DataSource.rawMap());
        pnt4<float>* dst = static_cast<pnt4<float>*>(rawMap());
        size_t i = size();
        while(i--) {
            dst[i] = src[i];
        }
        iV3DataSource.unmap();
        unmap();
        return *this;
    }

    bool MeshUVBufferNode::update(Context& iCtx)
    {
        auto frameSrc = getInput<FrameSourceNode>(0);
        if(frameSrc) {
            uint32_t width = frameSrc->getWidth();
            uint32_t height = frameSrc->getHeight();
            resizeIfNeeded(width * height);
            float widthRecip = 1.0 / float(width-1);
            float heightRecip = 1.0 / float(height-1);
            auto ptr = static_cast<vec2<float>*>(rawMap());
            for(uint32_t j = 0; j < height; j++) {
                uint32_t rowOffset = j * width;
                for(uint32_t i = 0; i < width; i++) {
                    ptr[i + rowOffset][0] = float(i) * widthRecip;
                    ptr[i + rowOffset][1] = float(j) * heightRecip;
                }
            }
            unmap();
        }
        return true;
    }

    bool MeshIndexBufferNode::update(Context& iCtx)
    {
        auto frameNode = getInput<FrameSourceNode>(0);
        if(frameNode) {
            uint32_t width = frameNode->getWidth();
            stripCount = frameNode->getHeight() - 1;
            stripIndexCount = width << 1;
            resizeIfNeeded(stripCount * stripIndexCount);
            auto ptr = static_cast<int*>(rawMap());
            int n = 0;
            for(int j = 0; j < stripCount; j++) {
                int o0 = j * stripIndexCount;
                int o1 = o0 + width;
                for(int i = 0; i < width; i++) {
                    ptr[n++] = o0 + i;
                    ptr[n++] = o1 + i;
                }
            }
            unmap();
        }

        return true;
    }
}
