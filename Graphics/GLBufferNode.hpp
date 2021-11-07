#ifndef __GLBUFFERNODE_HPP__
#define __GLBUFFERNODE_HPP__

#include "Debug.hpp"

#include "Math.hpp"
#include "GLBuffer.hpp"
#include "Node.hpp"

using namespace std;

namespace mobo
{

    extern const Type GLBUFFERTYPE;
    
    template <class T>
    class GLBufferNodeT : public Node, public GLBufferT<T>
    {
        public:
            GLBufferNodeT()
            : Node(), GLBufferT<T>() { }
    };

    template <class V>
    class GLVertexBufferNodeT : public GLBufferNodeT<V>
    {
        public:
            GLVertexBufferNodeT()
            : GLBufferNodeT<V>() { }
    };

    class GLV2BufferNode : public GLVertexBufferNodeT<vec2<GLfloat>>
    {
        DECLARE_TYPE
        public:
            GLV2BufferNode()
            : GLVertexBufferNodeT<vec2<GLfloat>>() { }
    };

    class GLV3BufferNode : public GLVertexBufferNodeT<vec3<GLfloat>>
    {
        DECLARE_TYPE
        public:
            GLV3BufferNode()
            : GLVertexBufferNodeT<vec3<GLfloat>>() { }
    };

    class GLV4BufferNode : public GLVertexBufferNodeT<vec4<GLfloat>>
    {
        DECLARE_TYPE
        public:
            GLV4BufferNode()
            : GLVertexBufferNodeT<vec4<GLfloat>>() { }
    };

    class GLIndexBufferNode : public GLBufferNodeT<GLint>
    {
        DECLARE_TYPE
        public:
            GLIndexBufferNode()
            : GLBufferNodeT<GLint>() { }
    };

}

#endif
