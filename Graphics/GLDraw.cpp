#include "GLDraw.hpp"
#include "GLContext.hpp"
#include "GLProgram.hpp"
#include "DataSourceNode.hpp"
#include "RealSense.hpp"

namespace mobo
{
    DERIVE_TYPE(GLDraw, "6ba4bafa-5cfd-4b51-9987-c5763cd68411", {&GLPipeline::_type});
    DERIVE_TYPE(GLDrawMesh, "db14a600-ca2c-4ec0-b4e5-4c055abaf8b3", {&GLPipeline::_type});

    GLDraw::GLDraw()
    : GLPipeline()
    { 
        addInput(GLIndexBufferNode::_type);
    }

    bool GLDraw::update(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            projInfo = prog->getUniformInfo("project");
            cameraInfo = prog->getUniformInfo("camera");
            mvInfo = prog->getUniformInfo("modelview");
            uvInfo = prog->getUniformInfo("uvMatrix");
        }
        return true;
    }

    bool GLDraw::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            glUniformMatrix4fv(projInfo.location, 1, true, (const GLfloat*) &ctx.projectionMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif
            
            glUniformMatrix4fv(cameraInfo.location, 1, true, (const GLfloat*) &ctx.cameraMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif

            glUniformMatrix4fv(mvInfo.location, 1, true, (const GLfloat*) &ctx.modelviewMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif

            glUniformMatrix3fv(uvInfo.location, 1, true, (const GLfloat*) &ctx.uvMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix3fv)
            #endif

            GLIndexBufferNode* ndxNode = getInput<GLIndexBufferNode>(1);
            if(ndxNode) {
                ndxNode->bind(GL_ELEMENT_ARRAY_BUFFER);
                glDrawElements(getDrawMode(), ndxNode->size(), GL_UNSIGNED_INT, NULL);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glDrawElements)
                #endif
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glBindBuffer)
                #endif
            }
        }
        return true;
    }

    bool GLDraw::retract(Context &iCtx)
    {
        return true;
    }

    GLDrawMesh::GLDrawMesh()
    : GLPipeline()
    {
        addInput(GLMeshIndexBufferNode::_type);
        addInput(Node::_type);
        addInput(GLUVMatrix::_type);
    }

    bool GLDrawMesh::update(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            projInfo = prog->getUniformInfo("project");
            cameraInfo = prog->getUniformInfo("camera");
            mvInfo = prog->getUniformInfo("modelview");
            uvInfo = prog->getUniformInfo("uvMatrix");
        }
        return true;
    }

    bool GLDrawMesh::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            glUniformMatrix4fv(projInfo.location, 1, true, (const GLfloat*) &ctx.projectionMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif
            
            glUniformMatrix4fv(cameraInfo.location, 1, true, (const GLfloat*) &ctx.cameraMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif

            glUniformMatrix4fv(mvInfo.location, 1, true, (const GLfloat*) &ctx.modelviewMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif

            glUniformMatrix3fv(uvInfo.location, 1, true, (const GLfloat*) &ctx.uvMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix3fv)
            #endif

            auto ndxNode = getInput<GLMeshIndexBufferNode>(1);
            auto segmentationSource = getInput<RealSense>(2);
            if(ndxNode && segmentationSource) {
                ndxNode->bind(GL_ELEMENT_ARRAY_BUFFER);
                const vector<MeshSegmentation::Segment>& segs = segmentationSource->getMeshSegmentation();
                /*
                if(segs.size()) {
                    auto segment = segs.front();
                */
                for(auto segment : segs) {
                    size_t offset = segment.offset * sizeof(GLuint);
                    glDrawElements(GL_TRIANGLE_STRIP, segment.count, GL_UNSIGNED_INT, (const GLvoid*) offset);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glDrawElements)
                    #endif
                }
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }
        return true;
    }

    bool GLDrawMesh::retract(Context &iCtx)
    {
        return true;
    }


}
