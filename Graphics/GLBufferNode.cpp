#include "GLBufferNode.hpp"

namespace mobo
{

    DERIVE_TYPE(GLBufferNode, "6daf4786-0e35-4fb2-8796-d170d5e0627e", { &DataSourceNode::_type });
    DERIVE_TYPE(GLV2BufferNode, "51c0e1c6-26bc-427c-b9bf-e8498fa5eab7", { &GLBufferNode::_type });
    DERIVE_TYPE(GLV3BufferNode, "46a867b9-e00a-4b73-8a1a-9a504b5c9238", { &GLBufferNode::_type });
    DERIVE_TYPE(GLV4BufferNode, "24941cad-ba78-4b81-a867-8011c1385ea0", { &GLBufferNode::_type });
    DERIVE_TYPE(GLP4BufferNode, "90428bbe-08ab-4589-9dfb-5379d17613aa", { &GLBufferNode::_type });
    DERIVE_TYPE(GLIndexBufferNode, "068f32a9-97f6-4908-9bed-07c6370efe8f", { &GLBufferNode::_type });
    DERIVE_TYPE(GLMeshUVBufferNode, "04cb8958-5355-4565-b35a-01ebae915902", { &GLV2BufferNode::_type });
    DERIVE_TYPE(GLMeshIndexBufferNode, "cb0357af-a847-43ef-923a-01097cc8f25e", { &GLIndexBufferNode::_type });

    bool GLMeshUVBufferNode::update(Context& iCtx)
    {
        auto frameSrc = getInput<FrameSourceNode>(0);
        if(frameSrc) {
            uint32_t width = frameSrc->getWidth();
            uint32_t height = frameSrc->getHeight();
            resizeIfNeeded(width * height);
            GLfloat widthRecip = 1.0 / GLfloat(width-1);
            GLfloat heightRecip = 1.0 / GLfloat(height-1);
            auto ptr = static_cast<vec2<GLfloat>*>(rawMap());
            for(uint32_t j = 0; j < height; j++) {
                uint32_t rowOffset = j * width;
                for(uint32_t i = 0; i < width; i++) {
                    ptr[i + rowOffset][0] = GLfloat(i) * widthRecip;
                    ptr[i + rowOffset][1] = GLfloat(j) * heightRecip;
                }
            }
            unmap();
        }
        return true;
    }

    bool GLMeshIndexBufferNode::update(Context& iCtx)
    {
        auto frameSrc = getInput<FrameSourceNode>(0);
        if(frameSrc) {
            uint32_t width = frameSrc->getWidth();
            stripCount = (frameSrc->getHeight() - 1);
            stripIndexCount = width << 1;
            resizeIfNeeded(stripCount * stripIndexCount);
            auto ptr = static_cast<GLuint*>(rawMap());
            uint32_t n = 0;
            for(uint32_t j = 0; j < stripCount; j++) {
                uint32_t o0 = j * stripIndexCount;
                uint32_t o1 = o0 + width;
                for(uint32_t i = 0; i < width; i++) {
                    ptr[n++] = o0 + i;
                    ptr[n++] = o1 + i;
                }
            }
            unmap();
        }
        return true;
    }
}
