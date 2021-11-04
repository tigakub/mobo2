#ifndef __GLPROGRAM_HPP__
#define __GLPROGRAM_HPP__

#include "Context.hpp"
#include "GLPipeline.hpp"
#include "GLShader.hpp"

namespace mobo
{
    class GLContext;

    class GLProgram : public GLPipeline
    {
        DECLARE_TYPE
        public:
            GLProgram();
            virtual ~GLProgram();

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual bool activate();
            virtual bool deactivate();

        protected:
            GLint programHandle;
    };
}

#endif
