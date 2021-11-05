#include "GLContext.hpp"
#include "GLGeometry.hpp"

using namespace std;

namespace mobo
{

    DERIVE_TYPE(GLGeometry, "", { &GLPipeline::_type });

    GLGeometry::GLGeometry()
    : GLPipeline()
    {
        addInput(GLV4BufferNode::_type);
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
            auto attribInfo = programNode->getAttribInfo();
            GLV4BufferNode* vtxNode = getInput<GLV4BufferNode>(1);
            GLV4BufferNode* clrNode = getInput<GLV4BufferNode>(2);
            GLV2BufferNode* uvNode = getInput<GLV2BufferNode>(3);
            vtxInfo.available = false;
            clrInfo.available = false;
            uvInfo.available = false;
            if(vtxNode) {
                if(attribInfo.find(vtxNode->attribName()) != attribInfo.end()) {
                    vtxInfo = attribInfo[vtxNode->attribName()]; vtxInfo.available = true;
                }
            }
            if(clrNode) {
                if(attribInfo.find(clrNode->attribName()) != attribInfo.end()) {
                    clrInfo = attribInfo[clrNode->attribName()]; clrInfo.available = true;
                }
            }
            if(uvNode) {
                if(attribInfo.find(uvNode->attribName()) != attribInfo.end()) {
                    uvInfo = attribInfo[uvNode->attribName()]; uvInfo.available = true;
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
        GLV4BufferNode* vtxNode = getInput<GLV4BufferNode>(1);
        GLV4BufferNode* clrNode = getInput<GLV4BufferNode>(2);
        GLV2BufferNode* uvNode = getInput<GLV2BufferNode>(3);

        if(vtxNode && vtxInfo.available) {
            vtxNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(vtxInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(vtxInfo.location);
        }

        if(clrNode && clrInfo.available) {
            clrNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(clrInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(clrInfo.location);
        }

        if(uvNode && uvInfo.available) {
            uvNode->bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(uvInfo.location, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(uvInfo.location);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }

    bool GLGeometry::deactivate()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(vtxInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(vtxInfo.location);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(clrInfo.location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(clrInfo.location);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(uvInfo.location, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(uvInfo.location);
        
        return true;
    }

}