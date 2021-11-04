#ifndef __GLPIPELINESTART_HPP__
#define __GLPIPELINESTART_HPP__

#include "Debug.hpp"

#include "GLPipeline.hpp"

namespace mobo
{
    class GLPipelineStart : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLPipelineStart();
            virtual ~GLPipelineStart() { }

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context &iCtx);

    };
}

#endif
