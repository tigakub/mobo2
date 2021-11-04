#include "GLContext.hpp"
#include "GLShader.hpp"
#include "StringNode.hpp"
#include "Link.hpp"

#include <iostream>

using namespace std;

namespace mobo
{

    DEFINE_TYPE_SUB(GLShader, "c25e6c00-6725-402b-a7d2-25a587b34d3f", { &Node::_type })
    DEFINE_TYPE_SUB(GLVertexShader, "a7f4feeb-439e-4915-907e-b162eadb566c", { &GLShader::_type })
    DEFINE_TYPE_SUB(GLFragmentShader, "3b61940a-d5c9-42c9-986d-ac54d34651d8", { &GLShader::_type })

    GLShader::GLShader(GLenum iShaderType)
    : Node(), shaderHandle(glCreateShader(iShaderType))
    {
        addInput(StringNode::_type);
    }

    GLShader::~GLShader()
    {
        if(shaderHandle) glDeleteShader(shaderHandle);
    }

    GLuint GLShader::compileFromString(const string& iSource)
    {
        const GLchar* srcPtr = iSource.c_str();
        GLint srcSize = iSource.size();
        GLint status;
        glShaderSource(shaderHandle, 1, &srcPtr, &srcSize);
        glCompileShader(shaderHandle);
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

        return status;
    }

    bool GLShader::update(Context &iCtx)
    {
        auto input = inputs[0];
        StringNode* srcNode = getInput<StringNode>(0);
        if(srcNode) {
            #ifdef TRACE
            cout << "Compiling shader ... ";
            #endif
            if(compileFromString(srcNode->getValue())) {
                #ifdef TRACE
                cout << "success" << endl;
                #endif
                return true;
            #ifdef TRACE
            } else {
                cout << "failure" << endl;
            #endif
            }
        }
        return false;
    }

}