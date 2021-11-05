#ifndef __GLBUFFER_HPP__
#define __GLBUFFER_HPP__

#include "Debug.hpp"

#include "Buffer.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <typeinfo>

#include <iostream>

using namespace std;

namespace mobo
{
    template <class T>
    class GLBufferT : public BufferT<T>
    {
        public:
            GLBufferT()
            : BufferT<T>(), bufferHandle(0), usage(GL_STATIC_DRAW), attributeName()
            {
                glGenBuffers(1, &bufferHandle);
            }

            virtual ~GLBufferT()
            {
                if(bufferHandle) glDeleteBuffers(1, &bufferHandle);
            }

            void setAttribName(const string &iName)
            {
                attributeName = iName;
            }

            const string& attribName() const
            {
                return attributeName;
            }

            void bind(GLenum iTarget)
            {
                glBindBuffer(iTarget, bufferHandle);
            }

            void setUsage(GLenum iUsage, bool iReallocate = true)
            {
                if(usage != iUsage) {
                    usage = iUsage;
                    if(iReallocate) {
                        GLBufferT<T>::resize(GLBufferT<T>::size(), true);
                    }
                }
            }

            virtual Buffer& operator=(const Buffer& iSrc)
            {
                GLBufferT<T>::resizeIfNeeded(iSrc.size());
                try {
                    const GLBufferT<T>& src = dynamic_cast<const GLBufferT<T>&>(iSrc);

                    glBindBuffer(GL_COPY_READ_BUFFER, src.bufferHandle);
                    glBindBuffer(GL_COPY_WRITE_BUFFER, bufferHandle);
                    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, GLBufferT<T>::byteSize());
                    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
                    glBindBuffer(GL_COPY_READ_BUFFER, 0);

                    return *this;
                } catch(const bad_cast& e) {
                }

                try {
                    const HostBufferT<T>& src = dynamic_cast<const HostBufferT<T>&>(iSrc);
                    const T* srcPtr = src.map();
                    T* dstPtr = GLBufferT<T>::map();
                    uint32_t n = GLBufferT<T>::size();
                    while(n--) {
                        dstPtr[n] = srcPtr[n];
                    }
                    GLBufferT<T>::unmap();
                    src.unmap();

                    return *this;
                } catch(const bad_cast& e) {
                }
                #ifdef DEBUG_OPENGL
                cerr << "Failed to copy buffer" << endl;
                #endif
                return *this;
            }

            virtual void unmap()
            {
                glUnmapBuffer(GL_ARRAY_BUFFER);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            virtual void unmap() const
            {
                glUnmapBuffer(GL_ARRAY_BUFFER);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

        protected:
            virtual void resize(uint32_t iSize, bool iPreserve = false)
            {
                GLuint newBuffer;
                glGenBuffers(1, &newBuffer);
                glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
                glBufferData(GL_ARRAY_BUFFER, iSize * GLBufferT<T>::elementSize(), nullptr, usage);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                if(bufferHandle) {
                    if(iPreserve) {
                        glBindBuffer(GL_COPY_READ_BUFFER, bufferHandle);
                        glBindBuffer(GL_COPY_WRITE_BUFFER, newBuffer);
                        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, GLBufferT<T>::byteSize());
                        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
                        glBindBuffer(GL_COPY_READ_BUFFER, 0);
                    }
                    glDeleteBuffers(1, &bufferHandle);
                }
                GLBufferT<T>::setSize(iSize);
                bufferHandle = newBuffer;
            }

            virtual const void* rawMap() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
                void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
                if(!ptr) cout << gluErrorString(glGetError()) << endl;
                return ptr;
            }

            virtual void* rawMap()
            {
                glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
                void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
                if(!ptr) cout << gluErrorString(glGetError()) << endl;
                return ptr;
            }

        protected:
            GLuint bufferHandle;
            GLenum usage;
            string attributeName;
    };

}

#endif
