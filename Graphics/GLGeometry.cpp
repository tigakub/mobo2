#include "GLContext.hpp"
#include "GLGeometry.hpp"

using namespace std;

namespace mobo
{

    DERIVE_TYPE(GLGeometry, "", { &GLPipeline::_type });

    GLGeometry::GLGeometry()
    : GLPipeline()
    {
        addInput(GLP4BufferNode::_type);
        addInput(GLV4BufferNode::_type);
        addInput(GLV2BufferNode::_type);
    }

    GLGeometry::~GLGeometry()
    {
    }

    bool GLGeometry::update(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram *programNode = ctx.currentProgram();
        if(programNode) {
            // auto attribInfo = programNode->getAttribInfo();
            GLP4BufferNode* vtxNode = getInput<GLP4BufferNode>(1);
            GLV4BufferNode* clrNode = getInput<GLV4BufferNode>(2);
            GLV2BufferNode* uvNode = getInput<GLV2BufferNode>(3);
            vtxInfo.available = false;
            clrInfo.available = false;
            uvInfo.available = false;
            if(vtxNode) {
                try { 
                    vtxInfo = programNode->getAttribInfo(vtxNode->attribName());
                    vtxInfo.available = true;
                } catch(...) {
                }
            }
            if(clrNode) {
                try { 
                    clrInfo = programNode->getAttribInfo(clrNode->attribName());
                    clrInfo.available = true;
                } catch(...) {
                }
            }
            if(uvNode) {
                try { 
                    uvInfo = programNode->getAttribInfo(uvNode->attribName());
                    uvInfo.available = true;
                } catch(...) {
                }
           }
        }
        return true;
    }

    bool GLGeometry::submit(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLGeometry::submit" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushGeometry(this);
        activate();
        return true;
    }

    bool GLGeometry::retract(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLGeometry::retact" << endl;
        #endif
        deactivate();
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLGeometry* prev = ctx.popGeometry();
        if(prev) prev->activate();
        return true;
    }

    bool GLGeometry::activate()
    {
        GLP4BufferNode* vtxNode = getInput<GLP4BufferNode>(1);
        GLV4BufferNode* clrNode = getInput<GLV4BufferNode>(2);
        GLV2BufferNode* uvNode = getInput<GLV2BufferNode>(3);

        if(vtxNode && vtxInfo.available) {
            vtxNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(vtxInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glVertexAttribPointer)
            #endif
            glEnableVertexAttribArray(vtxInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glEnableVertexAttribArray)
            #endif
        }

        if(clrNode && clrInfo.available) {
            clrNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(clrInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glVertexAttribPointer)
            #endif
            glEnableVertexAttribArray(clrInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glEnableVertexAttribArray)
            #endif
        }

        if(uvNode && uvInfo.available) {
            uvNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(uvInfo.location, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glVertexAttribPointer)
            #endif
            glEnableVertexAttribArray(uvInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glEnableVertexAttribArray)
            #endif
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }

    bool GLGeometry::deactivate()
    {
        GLP4BufferNode* vtxNode = getInput<GLP4BufferNode>(1);
        GLV4BufferNode* clrNode = getInput<GLV4BufferNode>(2);
        GLV2BufferNode* uvNode = getInput<GLV2BufferNode>(3);

        if(vtxNode && vtxInfo.available) {
            vtxNode->bind(GL_ARRAY_BUFFER);
            glDisableVertexAttribArray(vtxInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glDisableVertexAttribArray)
            #endif
        }

        if(clrNode && clrInfo.available) {
            clrNode->bind(GL_ARRAY_BUFFER);
            glDisableVertexAttribArray(clrInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glDisableVertexAttribArray)
            #endif
        }

        if(uvNode && uvInfo.available) {
            uvNode->bind(GL_ARRAY_BUFFER);
            glDisableVertexAttribArray(uvInfo.location);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glDisableVertexAttribArray)
            #endif
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glBindBuffer)
        #endif

        return true;
    }

}