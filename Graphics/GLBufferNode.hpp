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
            /*
            GLBufferNodeT(const BufferT<T>& iBuffer)
            : Node(), GLBufferT<T>(iBuffer) { }
            GLBufferNodeT(GLBufferT<T>&& iBuffer)
            : Node(), GLBufferT<T>(move(iBuffer)) { }
            GLBufferNodeT(const GLBufferNodeT<T>& iBuffer)
            : Node(), GLBufferT<T>(iBuffer) { }
            GLBufferNodeT(GLBufferNodeT<T>&& iBuffer)
            : Node(), GLBufferT<T>(move(iBuffer)) { }
            */
    };

    template <int S>
    class GLVertexBufferNodeT : public GLBufferNodeT<vec<GLfloat, S>>
    {
        public:
            GLVertexBufferNodeT()
            : GLBufferNodeT<vec<GLfloat, S>>() { }
            /*
            GLVertexBufferNodeT(const BufferT<vec<GLfloat, S>>& iBuffer)
            : GLBufferNodeT<vec<GLfloat, S>>(iBuffer) { }
            GLVertexBufferNodeT(GLBufferT<vec<GLfloat, S>>&& iBuffer)
            : GLBufferNodeT<vec<GLfloat, S>>(move(iBuffer)) { }
            GLVertexBufferNodeT(const GLVertexBufferNodeT<S>& iBuffer)
            : GLBufferNodeT<vec<GLfloat, S>>(iBuffer) { }
            GLVertexBufferNodeT(GLVertexBufferNodeT<S>&& iBuffer)
            : GLBufferNodeT<vec<GLfloat, S>>(move(iBuffer)) { }
            */
    };

    class GLV2BufferNode : public GLVertexBufferNodeT<2>
    {
        DECLARE_TYPE
        public:
            GLV2BufferNode()
            : GLVertexBufferNodeT<2>() { }
            /*
            GLV2BufferNode(const BufferT<vec<GLfloat, 2>>& iBuffer)
            : GLVertexBufferNodeT<2>(iBuffer) { }
            GLV2BufferNode(GLBufferT<vec<GLfloat, 2>>&& iBuffer)
            : GLVertexBufferNodeT<2>(iBuffer) { }
            GLV2BufferNode(const GLV2BufferNode& iBuffer)
            : GLVertexBufferNodeT<2>(iBuffer) { }
            GLV2BufferNode(GLV2BufferNode&& iBuffer)
            : GLVertexBufferNodeT<2>(move(iBuffer)) { }
            */
    };

    class GLV3BufferNode : public GLVertexBufferNodeT<3>
    {
        DECLARE_TYPE
        public:
            GLV3BufferNode()
            : GLVertexBufferNodeT<3>() { }
            /*
            GLV3BufferNode(const BufferT<vec<GLfloat, 3>>& iBuffer)
            : GLVertexBufferNodeT<3>(iBuffer) { }
            GLV3BufferNode(GLBufferT<vec<GLfloat, 3>>&& iBuffer)
            : GLVertexBufferNodeT<3>(move(iBuffer)) { }
            GLV3BufferNode(const GLV3BufferNode& iBuffer)
            : GLVertexBufferNodeT<3>(iBuffer) { }
            GLV3BufferNode(GLV3BufferNode&& iBuffer)
            : GLVertexBufferNodeT<3>(move(iBuffer)) { }
            */
    };

    class GLV4BufferNode : public GLVertexBufferNodeT<4>
    {
        DECLARE_TYPE
        public:
            GLV4BufferNode()
            : GLVertexBufferNodeT<4>() { }
            /*
            GLV4BufferNode(const BufferT<vec<GLfloat, 4>>& iBuffer)
            : GLVertexBufferNodeT<4>(iBuffer) { }
            GLV4BufferNode(GLBufferT<vec<GLfloat, 4>>&& iBuffer)
            : GLVertexBufferNodeT<4>(move(iBuffer)) { }
            GLV4BufferNode(const GLV4BufferNode& iBuffer)
            : GLVertexBufferNodeT<4>(iBuffer) { }
            GLV4BufferNode(GLV4BufferNode&& iBuffer)
            : GLVertexBufferNodeT<4>(move(iBuffer)) { }
            */
    };

    class GLIndexBufferNode : public GLBufferNodeT<GLint>
    {
        DECLARE_TYPE
        public:
            GLIndexBufferNode()
            : GLBufferNodeT<GLint>() { }
            /*
            GLIndexBufferNode(const BufferT<GLint>& iBuffer)
            : GLBufferNodeT<GLint>(iBuffer) { }
            GLIndexBufferNode(GLBufferT<GLint>&& iBuffer)
            : GLBufferNodeT<GLint>(move(iBuffer)) { }
            GLIndexBufferNode(const GLIndexBufferNode& iBuffer)
            : GLBufferNodeT<GLint>(iBuffer) { }
            GLIndexBufferNode(GLIndexBufferNode&& iBuffer)
            : GLBufferNodeT<GLint>(move(iBuffer)) { }
            */
    };

}

#endif
