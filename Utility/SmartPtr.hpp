#ifndef __SMARTPTR_HPP__
#define __SMARTPTR_HPP__

#include "RefCtr.hpp"

#include <type_traits>

using namespace std;

namespace mobo
{

    class ForwardReference
    {
        public:
            ForwardReference(void* iPtr) : ptrRef(&iPtr) { }
            ForwardReference(const ForwardReference& iRef) : ptrRef(iRef.ptrRef) { }

            virtual void resolve(void* iPtr) { *ptrRef = iPtr; }

        protected:
            void** ptrRef;
    };

    template <class T, typename enable_if<is_base_of<RefCtr, T>::value, bool>::type E = true>
    class SmartPtr
    {
        public:
            SmartPtr(T* p = nullptr) : ptr(p) { if(ptr) ptr->inc(); }
            SmartPtr(const SmartPtr<T, E>& p) : ptr(p.ptr) { if(ptr) ptr->inc(); }
            SmartPtr(SmartPtr<T, E>&& p) : ptr(p.ptr) { p.ptr = nullptr; }
            virtual ~SmartPtr() { if(ptr && !ptr->dec()) delete ptr; }

            SmartPtr<T, E>& operator=(T* iPtr) {
                if(ptr && !ptr->dec()) delete ptr;
                ptr = iPtr;
                if(ptr) ptr->inc();
                return *this;
            }
            SmartPtr<T, E>& operator=(const SmartPtr<T, E>& iPtr) {
                if(ptr && !ptr->dec()) delete ptr;
                ptr = iPtr.ptr;
                if(ptr) ptr->inc();
                return *this;
            }
            SmartPtr<T, E>& operator=(SmartPtr<T, E>&& iPtr) {
                if(ptr && !ptr->dec()) delete ptr;
                ptr = iPtr.ptr;
                iPtr.ptr = nullptr;
                return *this;
            }

            ForwardReference forwardReference() { return ForwardReference(ptr); }

            T* deref() { return ptr; }
            const T* deref() const { return ptr; }

            T* operator->() { return ptr; }
            const T* operator->() const { return ptr; }

            operator T*() { return ptr; }
            operator T*() const { return ptr; }

            operator bool() const { return ptr != nullptr; }

        protected:
            T* ptr;
    };
}

#endif
