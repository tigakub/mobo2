#ifndef __GLCAMERA_HPP__
#define __GLCAMERA_HPP__

#include "Node.hpp"
#include "GLTransform.hpp"

namespace mobo
{

    class GLCamera : public Node
    {
        DECLARE_TYPE

        public:
            GLCamera() : Node()
            { nodeFlags.set(Node::ISOLATE); addInput(GLTransform::_type); }
            
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

    };

}

#endif
