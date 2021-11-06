#ifndef __LINK_HPP__
#define __LINK_HPP__

#include "RefCtr.hpp"
#include "SmartPtr.hpp"
#include "Type.hpp"
#include "Typed.hpp"

namespace mobo
{
    template <class T>
    class Link : public Typed
    {
        public:
            Link(T* iNode) : srcType(iNode->type()), src(iNode) { }
            Link(const Type& iType) : srcType(iType), src() { }
            Link(Link<T>&& iLink) : srcType(iLink.srcType), src(move(iLink.src)) { }
            Link(const Link<T>& iLink) : srcType(iLink.srcType), src(iLink.src) { }

            virtual const Type& type() const { return srcType; }

            Type srcType;
            SmartPtr<T> src;
    };
}

#endif
