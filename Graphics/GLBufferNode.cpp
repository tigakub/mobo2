#include "GLBufferNode.hpp"

namespace mobo
{

    DERIVE_TYPE(GLBufferNode, "6daf4786-0e35-4fb2-8796-d170d5e0627e", { &DataSourceNode::_type });
    DERIVE_TYPE(GLV2BufferNode, "51c0e1c6-26bc-427c-b9bf-e8498fa5eab7", { &GLBufferNode::_type });
    DERIVE_TYPE(GLV3BufferNode, "46a867b9-e00a-4b73-8a1a-9a504b5c9238", { &GLBufferNode::_type });
    DERIVE_TYPE(GLV4BufferNode, "24941cad-ba78-4b81-a867-8011c1385ea0", { &GLBufferNode::_type });
    DERIVE_TYPE(GLP4BufferNode, "90428bbe-08ab-4589-9dfb-5379d17613aa", { &GLBufferNode::_type });
    DERIVE_TYPE(GLIndexBufferNode, "068f32a9-97f6-4908-9bed-07c6370efe8f", { &GLBufferNode::_type });
    DERIVE_TYPE(GLMeshVtxBufferNode, "a66cf4d0-8130-4a80-9ee0-d13606ce6637", { &GLP4BufferNode::_type });
    DERIVE_TYPE(GLMeshUVBufferNode, "04cb8958-5355-4565-b35a-01ebae915902", { &GLV2BufferNode::_type });
    DERIVE_TYPE(GLMeshIndexBufferNode, "812f6f3c-5695-4cc6-b5a4-e9fb9c89f619", { &GLIndexBufferNode::_type });

    bool GLMeshVtxBufferNode::update(Context& iCtx)
    {
        auto frameNode = getInput<FrameSourceNode>(0);
        auto frameSource = dynamic_cast<DataSource*>(frameNode);
        if(frameNode && frameSource) {
            size_t width = frameNode->getWidth();
            size_t height = frameNode->getHeight();
            //cout << getClassName() << "::update, width: " << width << ", height: " << height << endl;
            if(width && height) {
                GLfloat widthRecip = 1.0 / GLfloat(width-1);
                GLfloat heightRecip = 1.0 / GLfloat(height-1);
                resizeIfNeeded(width * height);
                auto src = static_cast<vec4<GLfloat>*>(frameSource->rawMap());
                auto ptr = static_cast<pnt4<GLfloat>*>(rawMap());
                for(size_t j = 0; j < height; j++) {
                    size_t rowOffset = j * width;
                    for(size_t i = 0; i < width; i++) {
                        
                        vec4<GLfloat>& s = src[rowOffset + i];
                        pnt4<GLfloat>& v = ptr[rowOffset + i];
                        v = s;
                        v[3] = 1.0;
                        /*
                        pnt4<GLfloat>& v = ptr[rowOffset + i];
                        v[0] = GLfloat(i) * widthRecip * 2.0 - 1.0;
                        v[1] = GLfloat(j) * heightRecip * 2.0 - 1.0;
                        v[2] = 0.0;
                        v[3] = 1.0;
                        */
                    }
                }
                unmap();
                frameSource->unmap();
            }
        }
        return true;
    }

    bool GLMeshUVBufferNode::update(Context& iCtx)
    {
        auto frameNode = getInput<FrameSourceNode>(0);
        auto frameSource = dynamic_cast<DataSource*>(frameNode);
        if(frameNode && frameSource) {
            size_t width = frameNode->getWidth();
            size_t height = frameNode->getHeight();
            //cout << getClassName() << "::update, width: " << width << ", height: " << height << endl;
            if(width && height) {
                GLfloat widthRecip = 1.0 / GLfloat(width-1);
                GLfloat heightRecip = 1.0 / GLfloat(height-1);
                resizeIfNeeded(width * height);
                auto ptr = static_cast<vec2<GLfloat>*>(rawMap());
                for(size_t j = 0; j < height; j++) {
                    size_t rowOffset = j * width;
                    for(size_t i = 0; i < width; i++) {
                        vec2<GLfloat>& v = ptr[rowOffset + i];
                        v[0] = GLfloat(i) * widthRecip;
                        v[1] = GLfloat(j) * heightRecip;
                    }
                }
                unmap();
            }
        }
        return true;
    }

    bool GLMeshIndexBufferNode::update(Context& iCtx)
    {
        auto frameNode = getInput<FrameSourceNode>(0);
        auto frameSource = dynamic_cast<DataSource*>(frameNode);
        if(frameNode && frameSource) {
            GLuint width = frameNode->getWidth();
            GLuint height = frameNode->getHeight();
            //cout << getClassName() << "::update, width: " << width << ", height: " << height << endl;
            stripCount = 0;
            stripIndexCount = 0;
            if(width && height) {
                stripCount = height - 1;
                stripIndexCount = width << 1;
                resizeIfNeeded(stripCount * stripIndexCount);
                auto ptr = static_cast<GLuint*>(rawMap());
                size_t n = 0;
                for(GLuint j = 0; j < stripCount; j++) {
                    GLuint ro0 = j * width;
                    GLuint ro1 = ro0 + width;
                    //cout << "Strip " << j << " (";
                    for(GLuint i = 0; i < width; i++) {
                        //if(i) cout << ", ";
                        ptr[n++] = ro0 + i;
                        //cout << ptr[n-1];
                        ptr[n++] = ro1 + i;
                        //cout << ", " << ptr[n-1];
                    }
                    //cout << ")" << endl;
                }
                unmap();
            }
        }
        return true;
    }
    
}
