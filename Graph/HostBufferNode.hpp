#ifndef __HOSTBUFFERNODE_HPP__
#define __HOSTBUFFERNODE_HPP__

#include "Math.hpp"
#include "Buffer.hpp"
#include "Node.hpp"

namespace mobo
{
    extern const Type HOSTBUFFERTYPE;
    
    template <class T>
    class HostBufferNodeT : public Node, public HostBufferT<T>
    {
        public:
            HostBufferNodeT()
            : Node(), HostBufferT<T>() { }
            HostBufferNodeT(const BufferT<T>& iBuffer)
            : Node(), HostBufferT<T>(iBuffer) { }
            HostBufferNodeT(const HostBufferNodeT<T>& iBuffer)
            : Node(), HostBufferT<T>(iBuffer) { }
            HostBufferNodeT(HostBufferT<T>&& iBuffer)
            : Node(), HostBufferT<T>(move(iBuffer)) { }
            HostBufferNodeT(HostBufferNodeT<T>&& iBuffer)
            : Node(), HostBufferT<T>(move(iBuffer)) { }
    };

    template <int S>
    class HostVertexBufferNodeT : public HostBufferNodeT<vec<float, S>>
    {
        public:
            HostVertexBufferNodeT()
            : HostBufferNodeT<vec<float, S>>() { }
            HostVertexBufferNodeT(const BufferT<vec<float, S>>& iBuffer)
            : HostBufferNodeT<vec<float, S>>(iBuffer) { }
            HostVertexBufferNodeT(HostBufferT<vec<float, S>>&& iBuffer)
            : HostBufferNodeT<vec<float, S>>(move(iBuffer)) { }
            HostVertexBufferNodeT(const HostVertexBufferNodeT<S>& iBuffer)
            : HostBufferNodeT<vec<float, S>>(iBuffer) { }
            HostVertexBufferNodeT(HostVertexBufferNodeT<S>&& iBuffer)
            : HostBufferNodeT<vec<float, S>>(move(iBuffer)) { }
    };

    class HostV2BufferNode : public HostVertexBufferNodeT<2>
    {
        DECLARE_TYPE
        public:
            HostV2BufferNode()
            : HostVertexBufferNodeT<2>() { }
            HostV2BufferNode(const BufferT<vec<float, 2>>& iBuffer)
            : HostVertexBufferNodeT<2>(iBuffer) { }
            HostV2BufferNode(HostBufferT<vec<float, 2>>&& iBuffer)
            : HostVertexBufferNodeT<2>(iBuffer) { }
            HostV2BufferNode(const HostV2BufferNode& iBuffer)
            : HostVertexBufferNodeT<2>(iBuffer) { }
            HostV2BufferNode(HostV2BufferNode&& iBuffer)
            : HostVertexBufferNodeT<2>(move(iBuffer)) { }
    };

    class HostV3BufferNode : public HostVertexBufferNodeT<3>
    {
        DECLARE_TYPE
        public:
            HostV3BufferNode()
            : HostVertexBufferNodeT<3>() { }
            HostV3BufferNode(const BufferT<vec<float, 3>>& iBuffer)
            : HostVertexBufferNodeT<3>(iBuffer) { }
            HostV3BufferNode(HostBufferT<vec<float, 3>>&& iBuffer)
            : HostVertexBufferNodeT<3>(move(iBuffer)) { }
            HostV3BufferNode(const HostV3BufferNode& iBuffer)
            : HostVertexBufferNodeT<3>(iBuffer) { }
            HostV3BufferNode(HostV3BufferNode&& iBuffer)
            : HostVertexBufferNodeT<3>(move(iBuffer)) { }
    };

    class HostV4BufferNode : public HostVertexBufferNodeT<4>
    {
        DECLARE_TYPE
        public:
            HostV4BufferNode()
            : HostVertexBufferNodeT<4>() { }
            HostV4BufferNode(const BufferT<vec<float, 4>>& iBuffer)
            : HostVertexBufferNodeT<4>(iBuffer) { }
            HostV4BufferNode(HostBufferT<vec<float, 4>>&& iBuffer)
            : HostVertexBufferNodeT<4>(move(iBuffer)) { }
            HostV4BufferNode(const HostV4BufferNode& iBuffer)
            : HostVertexBufferNodeT<4>(iBuffer) { }
            HostV4BufferNode(HostV4BufferNode&& iBuffer)
            : HostVertexBufferNodeT<4>(move(iBuffer)) { }
    };

    class HostIndexBufferNode : public HostBufferNodeT<int>
    {
        DECLARE_TYPE
        public:
            HostIndexBufferNode()
            : HostBufferNodeT<int>() { }
            HostIndexBufferNode(const BufferT<int>& iBuffer)
            : HostBufferNodeT<int>(iBuffer) { }
            HostIndexBufferNode(HostBufferT<int>&& iBuffer)
            : HostBufferNodeT<int>(move(iBuffer)) { }
            HostIndexBufferNode(const HostIndexBufferNode& iBuffer)
            : HostBufferNodeT<int>(iBuffer) { }
            HostIndexBufferNode(HostIndexBufferNode&& iBuffer)
            : HostBufferNodeT<int>(move(iBuffer)) { }
    };

}

#endif
