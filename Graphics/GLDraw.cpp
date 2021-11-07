#include "GLDraw.hpp"
#include "GLContext.hpp"
#include "GLProgram.hpp"

namespace mobo
{

    GLDraw::GLDraw()
    : GLPipeline()
    { }

    bool GLDraw::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            const GLProgram::UniformInfo& projInfo = prog->getUniformInfo("project");
            const GLProgram::UniformInfo& cameraInfo = prog->getUniformInfo("camera");
            const GLProgram::UniformInfo& mvInfo = prog->getUniformInfo("modelview");
            glUniformMatrix4fv(projInfo.location, 1, true, (const GLfloat*) &ctx.projectionMatrix());
            glUniformMatrix4fv(cameraInfo.location, 1, true, (const GLfloat*) &ctx.cameraMatrix());
            glUniformMatrix4fv(mvInfo.location, 1, true, (const GLfloat*) &ctx.modelviewMatrix());

            draw();
        }
        return true;
    }

    bool GLDraw::retract(Context &iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        
        return true;
    }

    void GLDraw::draw()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}
