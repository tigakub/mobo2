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
        return true;
    }

    bool GLMaterial::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushMaterial(this);
        activate(iCtx);
    }

    bool GLMaterial::retract(Context& iCtx)
    {
        deactivate(iCtx);
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLMaterial* prev = ctx.popMaterial();
        if(prev) {
            prev->activate(iCtx);
        }
    }

    void GLMaterial::activate(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram *programNode = ctx.currentProgram();
        if(programNode) {
            for(auto link : dinputs) {
                GLTexture* node = static_cast<GLTexture*>(link.src.deref());
                if(node) {
                    const string& uniformName = node->unifName();
                    try {
                        const GLProgram::UniformInfo& info = programNode->getUniformInfo(uniformName);
                        glActiveTexture(GL_TEXTURE0 + info.location);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glActiveTexture)
                        #endif
                        glEnable(node->target());
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glEnable)
                        #endif
                        glBindTexture(node->target(), node->texHandle());
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindTexture)
                        #endif
                        if(info.sampler) {
                            glBindSampler(info.location, info.sampler);
                            #ifdef DEBUG_OPENGL
                            CHECK_OPENGL_ERROR(glBindSampler)
                            #endif
                        }
                    } catch(...) {
                    }
                }
            }
        }
        glActiveTexture(GL_TEXTURE0);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glActiveTexture)
        #endif
    }

    void GLMaterial::deactivate(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram *programNode = ctx.currentProgram();
        if(programNode) {
            for(auto link : dinputs) {
                GLTexture* node = static_cast<GLTexture*>(link.src.deref());
                if(node) {
                    const string& uniformName = node->unifName();
                    try {
                        const GLProgram::UniformInfo& info = programNode->getUniformInfo(uniformName);
                        glActiveTexture(GL_TEXTURE0 + info.location);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glActiveTexture)
                        #endif
                        if(info.sampler) {
                            glBindSampler(info.location, 0);
                            #ifdef DEBUG_OPENGL
                            CHECK_OPENGL_ERROR(glBindSampler)
                            #endif
                        }
                        glBindTexture(node->target(), 0);
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glBindTexture)
                        #endif
                        glDisable(node->target());
                        #ifdef DEBUG_OPENGL
                        CHECK_OPENGL_ERROR(glEnable)
                        #endif
                    } catch(...) {
                    }
                }
            }
        }
        glActiveTexture(GL_TEXTURE0);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glActiveTexture)
        #endif
    }

}