#ifndef __GLGEOMETRY_HPP__
#define __GLGEOMETRY_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "GLPipeline.hpp"
#include "GLBufferNode.hpp"
#include "GLProgram.hpp"

namespace mobo
{
    class GLContext;

    class GLGeometry : public GLPipeline
    {
        DECLARE_TYPE
        public:
            GLGeometry();
            virtual ~GLGeometry();

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual bool activate();
            virtual bool deactivate();

        protected:
            GLProgram::AttribInfo vtxInfo;
            GLProgram::AttribInfo clrInfo;
            GLProgram::AttribInfo uvInfo;
    };
}

#endif
