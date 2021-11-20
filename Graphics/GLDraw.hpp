#ifndef __GLDRAW_HPP__
#define __GLDRAW_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "GLProgram.hpp"
#include "GLPipeline.hpp"
#include "GLTransform.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace mobo
{

    class GLDraw : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLDraw();

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context &iCtx);

            void setDrawMode(GLenum iDrawMode) { drawMode  = iDrawMode; }
            GLenum getDrawMode() { return drawMode; }

        protected:
            GLenum drawMode;
            GLProgram::UniformInfo projInfo, cameraInfo, mvInfo, uvInfo;
   };

   class GLDrawMesh: public GLPipeline
   {
        DECLARE_TYPE

        public:
            GLDrawMesh();

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);
        
        protected:
            GLProgram::UniformInfo projInfo, cameraInfo, mvInfo, uvInfo;            
   };

}

#endif