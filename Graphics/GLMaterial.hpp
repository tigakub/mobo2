#ifndef __GLMATERIAL_HPP__
#define __GLMATERIAL_HPP__

#include "Debug.hpp"

#include "GLPipeline.hpp"
#include "GLTexture.hpp"

namespace mobo
{
    class GLMaterial : public GLPipeline
    {
        DECLARE_TYPE

        protected:
            typedef struct Binding {
                string uniformName;
                GLint unit;
            } Binding;

        public:
            GLMaterial();

        protected:
            vector<Binding> bindings;
    };
}

#endif