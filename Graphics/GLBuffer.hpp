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
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glGenBuffers)
                #endif
            }
            GLBufferT(const GLBufferT<T>& iSrc)
            : BufferT<T>(), bufferHandle(0), usage(iSrc.usage), attributeName(iSrc.attributeName)
            {
                DataSourceT<T>::operator=(iSrc);
            }
            GLBufferT(GLBufferT<T>&& iSrc)
            : BufferT<T>(), bufferHandle(iSrc.bufferHandle), usage(iSrc.usage), attributeName(move(iSrc.attributeName)) 
            {
                BufferT<T>::elementCount = iSrc.size();
                iSrc.bufferHandle = 0;
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

            /*
            virtual DataSourceT<T>& operator=(const HostBufferT<T>& iSrc)
            {
                return DataSourceT<T>::operator=(dynamic_cast<const DataSource&>(iSrc));
            }
            */

            virtual DataSourceT<T>& operator=(const GLBufferT<T>& iSrc)
            {
                GLBufferT<T>::resizeIfNeeded(iSrc.size());
                glBindBuffer(GL_COPY_READ_BUFFER, iSrc.bufferHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                glBindBuffer(GL_COPY_WRITE_BUFFER, bufferHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, GLBufferT<T>::byteSize());
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glCopyBufferSubData)
                #endif
                glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                glBindBuffer(GL_COPY_READ_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                return *this;
            }

            virtual void unmap()
            {
                glUnmapBuffer(GL_ARRAY_BUFFER);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glUnmapBuffer)
                #endif
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
            }

            virtual void unmap() const
            {
                glUnmapBuffer(GL_ARRAY_BUFFER);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glUnmapBuffer)
                #endif
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
            }

        protected:
            virtual void setSize(uint32_t iSize, bool iPreserve = false)
            {
                GLuint newBuffer;
                glGenBuffers(1, &newBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glGenBuffers)
                #endif
                glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                glBufferData(GL_ARRAY_BUFFER, iSize * GLBufferT<T>::byteStride(), nullptr, usage);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBufferData)
                #endif
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                if(bufferHandle) {
                    if(iPreserve) {
                        glBindBuffer(GL_COPY_READ_BUFFER, bufferHandle);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindBuffer)
                        #endif
                        glBindBuffer(GL_COPY_WRITE_BUFFER, newBuffer);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindBuffer)
                        #endif
                        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, GLBufferT<T>::byteSize());
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glCopyBufferSubData)
                        #endif
                        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindBuffer)
                        #endif
                        glBindBuffer(GL_COPY_READ_BUFFER, 0);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindBuffer)
                        #endif
                    }
                    glDeleteBuffers(1, &bufferHandle);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glDeleteBuffers)
                    #endif
                }
                BufferT<T>::setSize(iSize);
                bufferHandle = newBuffer;
            }
        
        public:
            virtual const void* rawMap() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glMapBuffer)
                #endif
                return ptr;
            }

            virtual void* rawMap()
            {
                glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
                void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glMapBuffer)
                #endif
                return ptr;
            }

        protected:
            GLuint bufferHandle;
            GLenum usage;
            string attributeName;
    };

}

#endif
