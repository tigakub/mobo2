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
    }

    bool GLGeometry::submit(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        cout << "GLGeometry::submit" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushGeometry(this);
        activate();
        return true;
    }

    bool GLGeometry::retract(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        cout << "GLGeometry::retact" << endl;
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

        vtxNode->bind(GL_ARRAY_BUFFER);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        clrNode->bind(GL_ARRAY_BUFFER);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);

        uvNode->bind(GL_ARRAY_BUFFER);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }

    bool GLGeometry::deactivate()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glDisableVertexAttribArray(2);
        
        return true;
    }

}