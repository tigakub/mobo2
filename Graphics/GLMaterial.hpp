#ifndef __GLMATERIAL_HPP__
#define __GLMATERIAL_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "GLPipeline.hpp"
#include "GLTexture.hpp"
#include "GLProgram.hpp"

#include <unordered_map>

using namespace std;

namespace mobo
{
    class GLMaterial : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLMaterial();

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual void activate();
            virtual void deactivate();

        protected:
            vector<GLProgram::UniformInfo> uniformInfo;
    };
}

#endif