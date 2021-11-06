#include "GLContext.hpp"
#include "GLMaterial.hpp"

using namespace std;

namespace mobo
{
    DERIVE_TYPE(GLMaterial, "e5c483ff-b4c0-4130-a45f-d2743e86826a", { &GLPipeline::_type })

    GLMaterial::GLMaterial()
    : GLPipeline()
    {
    }

    bool GLMaterial::update(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram *programNode = ctx.currentProgram();
        if(programNode) {
            for(auto link : dinputs) {
                GLTexture* node = static_cast<GLTexture*>(link.src.ptr);
                if(node) {
                    const string& uniformName = node->unifName();
                    try {
                        GLProgram::UniformInfo info = programNode->getUniformInfo(uniformName);
                        info.tex = node->texHandle();
                        info.target = node->target();
                        switch(info.type) {
                            case GL_SAMPLER_2D:
                            case GL_SAMPLER_2D_RECT:
                                info.generateSampler();
                                glSamplerParameteri(info.sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
                                glSamplerParameteri(info.sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
                                glSamplerParameteri(info.sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                glSamplerParameteri(info.sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                                glSamplerParameterf(info.sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
                                break;
                        }
                        uniformInfo.push_back(move(info));
                    } catch(...) {
                    }
                }
            }
        }
        return true;
    }

    bool GLMaterial::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushMaterial(this);
        activate();
    }

    bool GLMaterial::retract(Context& iCtx)
    {
        deactivate();
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLMaterial* prev = ctx.popMaterial();
        if(prev) {
            prev->activate();
        }
    }

    void GLMaterial::activate()
    {
        for(auto info : uniformInfo) {
            glActiveTexture(GL_TEXTURE0 + info.location);
            //cout << "glActivateTexture(GL_TEXTURE0 + " << info.location << ")" << endl;
            glEnable(info.target);
            //cout << "glEnable(" << info.target << ")" << endl;
            glBindTexture(info.target, info.tex);
            //cout << "glBindTexture(" << info.target << ", " << info.tex << ")" << endl;
            if(info.sampler) {
                glBindSampler(info.location, info.sampler);
                //cout << "glBindSampler(" << info.location << ", " << info.sampler << ")" << endl;
            }
        }
        glActiveTexture(GL_TEXTURE0);
    }

    void GLMaterial::deactivate()
    {
        for(auto info : uniformInfo) {
            if(info.sampler)
                glActiveTexture(GL_TEXTURE0 + info.location);
                glBindSampler(info.location, 0);
                glBindTexture(info.target, 0);
                glDisable(info.target);
        }
        glActiveTexture(GL_TEXTURE0);
    }

}