#include "GLContext.hpp"
#include "GLProgram.hpp"

#include <iostream>

using namespace std;

namespace mobo
{

    DERIVE_TYPE(GLProgram, "d7ea0fc4-5596-4312-ba92-e781281d3c8a", { &GLPipeline::_type })

    string GLProgram::nameFromType(GLenum iType)
    {
        switch(iType) {
            case GL_FLOAT:                       return string("GL_FLOAT");
            case GL_FLOAT_VEC2:                  return string("GL_FLOAT_VEC2");
            case GL_FLOAT_VEC3:                  return string("GL_FLOAT_VEC3");
            case GL_FLOAT_VEC4:                  return string("GL_FLOAT_VEC4");
            case GL_DOUBLE:                      return string("GL_DOUBLE");
            case GL_DOUBLE_VEC2:                 return string("GL_DOUBLE_VEC2");
            case GL_DOUBLE_VEC3:                 return string("GL_DOUBLE_VEC3");
            case GL_DOUBLE_VEC4:                 return string("GL_DOUBLE_VEC4");
            case GL_INT:                         return string("GL_INT");
            case GL_INT_VEC2:                    return string("GL_INT_VEC2");
            case GL_INT_VEC3:                    return string("GL_INT_VEC3");
            case GL_INT_VEC4:                    return string("GL_INT_VEC4");
            case GL_UNSIGNED_INT:                return string("GL_UNSIGNED_INT");
            case GL_UNSIGNED_INT_VEC2:           return string("GL_UNSIGNED_INT_VEC2");
            case GL_UNSIGNED_INT_VEC3:           return string("GL_UNSIGNED_INT_VEC3");
            case GL_UNSIGNED_INT_VEC4:           return string("GL_UNSIGNED_INT_VEC4");
            case GL_BOOL:                        return string("GL_BOOL");
            case GL_BOOL_VEC2:                   return string("GL_BOOL_VEC2");
            case GL_BOOL_VEC3:                   return string("GL_BOOL_VEC3");
            case GL_BOOL_VEC4:                   return string("GL_BOOL_VEC4");
            case GL_FLOAT_MAT2:                  return string("GL_FLOAT_MAT2");
            case GL_FLOAT_MAT3:                  return string("GL_FLOAT_MAT3");
            case GL_FLOAT_MAT4:                  return string("GL_FLOAT_MAT4");
            case GL_FLOAT_MAT2x3:                return string("GL_FLOAT_MAT2x3");
            case GL_FLOAT_MAT2x4:                return string("GL_FLOAT_MAT2x4");
            case GL_FLOAT_MAT3x2:                return string("GL_FLOAT_MAT3x2");
            case GL_FLOAT_MAT3x4:                return string("GL_FLOAT_MAT3x4");
            case GL_FLOAT_MAT4x2:                return string("GL_FLOAT_MAT4x2");
            case GL_FLOAT_MAT4x3:                return string("GL_FLOAT_MAT4x3");
            case GL_DOUBLE_MAT2:                 return string("GL_DOUBLE_MAT2");
            case GL_DOUBLE_MAT3:                 return string("GL_DOUBLE_MAT3");
            case GL_DOUBLE_MAT4:                 return string("GL_DOUBLE_MAT4");
            case GL_DOUBLE_MAT2x3:               return string("GL_DOUBLE_MAT2x3");
            case GL_DOUBLE_MAT2x4:               return string("GL_DOUBLE_MAT2x4");
            case GL_DOUBLE_MAT3x2:               return string("GL_DOUBLE_MAT3x2");
            case GL_DOUBLE_MAT3x4:               return string("GL_DOUBLE_MAT3x4");
            case GL_DOUBLE_MAT4x2:               return string("GL_DOUBLE_MAT4x2");
            case GL_DOUBLE_MAT4x3:               return string("GL_DOUBLE_MAT4x3");
            case GL_SAMPLER_1D:                  return string("GL_SAMPLER_1D");
            case GL_SAMPLER_2D:                  return string("GL_SAMPLER_2D");
            case GL_SAMPLER_3D:                  return string("GL_SAMPLER_3D");
            case GL_SAMPLER_CUBE:                return string("GL_SAMPLER_CUBE");
            case GL_SAMPLER_1D_SHADOW:           return string("GL_SAMPLER_1D_SHADOW");
            case GL_SAMPLER_2D_SHADOW:           return string("GL_SAMPLER_2D_SHADOW");
            case GL_SAMPLER_1D_ARRAY:            return string("GL_SAMPLER_1D_ARRAY");
            case GL_SAMPLER_2D_ARRAY:            return string("GL_SAMPLER_2D_ARRAY");
            case GL_SAMPLER_1D_ARRAY_SHADOW:     return string("GL_SAMPLER_1D_ARRAY_SHADOW");
            case GL_SAMPLER_2D_ARRAY_SHADOW:     return string("GL_SAMPLER_2D_ARRAY_SHADOW");
            case GL_SAMPLER_CUBE_SHADOW:         return string("GL_SAMPLER_CUBE_SHADOW");
            case GL_SAMPLER_BUFFER:              return string("GL_SAMPLER_BUFFER");
            case GL_SAMPLER_2D_RECT:             return string("GL_SAMPLER_2D_RECT");
            case GL_SAMPLER_2D_RECT_SHADOW:      return string("GL_SAMPLER_2D_RECT_SHADOW");
            case GL_INT_SAMPLER_1D:              return string("GL_INT_SAMPLER_1D");
            case GL_INT_SAMPLER_2D:              return string("GL_INT_SAMPLER_2D");
            case GL_INT_SAMPLER_3D:              return string("GL_INT_SAMPLER_3D");
            case GL_INT_SAMPLER_CUBE:            return string("GL_INT_SAMPLER_CUBE");
            case GL_INT_SAMPLER_1D_ARRAY:        return string("GL_INT_SAMPLER_1D_ARRAY");
            case GL_INT_SAMPLER_2D_ARRAY:        return string("GL_INT_SAMPLER_2D_ARRAY");
            case GL_INT_SAMPLER_BUFFER:          return string("GL_INT_SAMPLER_BUFFER");
            case GL_INT_SAMPLER_2D_RECT:         return string("GL_INT_SAMPLER_2D_RECT");
            case GL_IMAGE_1D:                    return string("GL_IMAGE_1D");
            case GL_IMAGE_2D:                    return string("GL_IMAGE_2D");
            case GL_IMAGE_3D:                    return string("GL_IMAGE_3D");
            case GL_IMAGE_2D_RECT:               return string("GL_IMAGE_2D_RECT");
            case GL_IMAGE_CUBE:                  return string("GL_IMAGE_CUBE");
            case GL_IMAGE_BUFFER:                return string("GL_IMAGE_BUFFER");
            case GL_IMAGE_1D_ARRAY:              return string("GL_IMAGE_1D_ARRAY");
            case GL_IMAGE_2D_ARRAY:              return string("GL_IMAGE_2D_ARRAY");
            case GL_INT_IMAGE_1D:                return string("GL_INT_IMAGE_1D");
            case GL_INT_IMAGE_2D:                return string("GL_INT_IMAGE_2D");
            case GL_INT_IMAGE_3D:                return string("GL_INT_IMAGE_3D");
            case GL_INT_IMAGE_2D_RECT:           return string("GL_INT_IMAGE_2D_RECT");
            case GL_INT_IMAGE_CUBE:              return string("GL_INT_IMAGE_CUBE");
            case GL_INT_IMAGE_BUFFER:            return string("GL_INT_IMAGE_BUFFER");
            case GL_INT_IMAGE_1D_ARRAY:          return string("GL_INT_IMAGE_1D_ARRAY");
            case GL_INT_IMAGE_2D_ARRAY:          return string("GL_INT_IMAGE_2D_ARRAY");
            case GL_UNSIGNED_INT_IMAGE_1D:       return string("GL_UNSIGNED_INT_IMAGE_1D");
            case GL_UNSIGNED_INT_IMAGE_2D:       return string("GL_UNSIGNED_INT_IMAGE_2D");
            case GL_UNSIGNED_INT_IMAGE_3D:       return string("GL_UNSIGNED_INT_IMAGE_3D");
            case GL_UNSIGNED_INT_IMAGE_2D_RECT:  return string("GL_UNSIGNED_INT_IMAGE_2D_RECT");
            case GL_UNSIGNED_INT_IMAGE_CUBE:     return string("GL_UNSIGNED_INT_IMAGE_CUBE");
            case GL_UNSIGNED_INT_IMAGE_BUFFER:   return string("GL_UNSIGNED_INT_IMAGE_BUFFER");
            case GL_UNSIGNED_INT_IMAGE_1D_ARRAY: return string("GL_UNSIGNED_INT_IMAGE_1D_ARRAY");
            case GL_UNSIGNED_INT_IMAGE_2D_ARRAY: return string("GL_UNSIGNED_INT_IMAGE_2D_ARRAY");
            case GL_UNSIGNED_INT_ATOMIC_COUNTER: return string("GL_UNSIGNED_INT_ATOMIC_COUNTER");
        }
        return string("unknown");
    }

    GLProgram::GLProgram()
    : GLPipeline(), programHandle(glCreateProgram()), uniformInfo(), attribInfo()
    {
        addInput(GLVertexShader::_type);
        addInput(GLFragmentShader::_type);
    }

    GLProgram::~GLProgram()
    {
        if(programHandle) glDeleteProgram(programHandle);
    }

    const GLProgram::UniformInfo& GLProgram::getUniformInfo(const string& iName) const
    {
        auto i = uniformInfo.find(iName);
        if(i == uniformInfo.end()) throw;
        return i->second;
    }

    const GLProgram::AttribInfo& GLProgram::getAttribInfo(const string& iName) const
    {
        auto i = attribInfo.find(iName);
        if(i == attribInfo.end()) throw;
        return i->second;
    }
    /*
    const unordered_map<string, GLProgram::UniformInfo>& GLProgram::getUniformInfo() const
    {
        return uniformInfo;
    }

    const unordered_map<string, GLProgram::AttribInfo>& GLProgram::getAttribInfo() const 
    {
        return attribInfo;
    }
    */
    bool GLProgram::update(Context& iCtx)
    {
        GLint status;
        GLVertexShader* vtxShader = getInput<GLVertexShader>(1);
        GLFragmentShader* frgShader = getInput<GLFragmentShader>(2);
        if(vtxShader && frgShader) {
            #ifdef DEBUG_OPENGL
            cout << "Linking program ... ";
            #endif
            vtxShader->attach(programHandle);
            frgShader->attach(programHandle);
            glLinkProgram(programHandle);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glLinkProgram)
            #endif
            GLint status;
            glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glGetProgramiv)
            #endif
            if(status) {
                #ifdef DEBUG_OPENGL
                cout << "success" << endl;
                #endif
                GLchar nameBuf[256];
                uniformInfo.clear();
                attribInfo.clear();
                GLint n;
                glUseProgram(programHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glUseProgram)
                #endif
                glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &n);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glGetProgramiv)
                #endif
                if(!n) cout << "No active uniforms" << endl;
                else cout << n << " uniforms active" << endl;
                for(auto i = 0; i < n; i++) {
                    UniformInfo uInfo;
                    glGetActiveUniform(programHandle, i, 255, nullptr, &uInfo.size, &uInfo.type, nameBuf);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glGetActiveUniform)
                    #endif
                    uInfo.name = nameBuf;
                    uInfo.typeName = nameFromType(uInfo.type);
                    uInfo.location = glGetUniformLocation(programHandle, nameBuf);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glGetUniformLocation)
                    #endif
                    uniformInfo[uInfo.name] = uInfo;
                    cout << "Uniform:" << endl;
                    cout << "\tName:     " << uInfo.name << endl; 
                    cout << "\tIndex:    " << i << endl;
                    cout << "\tLocation: " << uInfo.location << endl;
                    cout << "\tSize:     " << uInfo.size << endl;
                    cout << "\tType:     " << uInfo.typeName << endl;
                    switch(uInfo.type) {
                        case GL_SAMPLER_2D:
                        case GL_SAMPLER_2D_RECT:
                            uInfo.generateSampler();
                            break;
                    }
                }

                glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &n);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glGetProgramiv)
                #endif
                if(!n) cout << "No active attributes" << endl;
                else cout << n << " attributes active" << endl;
                for(auto i = 0; i < n; i++) {
                    AttribInfo aInfo;
                    glGetActiveAttrib(programHandle, i, 255, nullptr, &aInfo.size, &aInfo.type, nameBuf);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glGetActiveAttrib)
                    #endif
                    aInfo.name = nameBuf;
                    aInfo.typeName = nameFromType(aInfo.type);
                    aInfo.location = glGetAttribLocation(programHandle, nameBuf);
                    #ifdef DEBUG_OPENGL
                    CHECK_OPENGL_ERROR(glGetAttribLocation)
                    #endif
                    attribInfo[aInfo.name] = aInfo;
                    cout << "Attribute:" << endl;
                    cout << "\tName:     " << aInfo.name << endl; 
                    cout << "\tIndex:    " << i << endl;
                    cout << "\tLocation: " << aInfo.location << endl;
                    cout << "\tSize:     " << aInfo.size << endl;
                    cout << "\tType:     " << aInfo.typeName << endl;
                }

                glUseProgram(0);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glUseProgram)
                #endif
                return status;
            #ifdef DEBUG_OPENGL
            } else {
                cout << "failure" << endl;
            #endif
            }
        }
        return false;
    }

    bool GLProgram::submit(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::submit" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushProgram(this);
        activate();
        return true;
    }

    bool GLProgram::retract(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::retract" << endl;
        #endif
        deactivate();
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::deactivated" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::context" << endl;
        #endif
        GLProgram* prev = ctx.popProgram();
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::popProgram" << endl;
        #endif
        if(prev) prev->activate();
        #ifdef DEBUG_OPENGL
        //cout << "GLProgram::retracted" << endl;
        #endif
        return true;
    }

    bool GLProgram::activate()
    {
        glUseProgram(programHandle);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glUseProgram)
        #endif
        GLint texLoc = glGetUniformLocation(programHandle, "tex");
        glUniform1i(texLoc, 0);

        return true;
    }

    bool GLProgram::deactivate()
    {
        glUseProgram(0);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glUseProgram)
        #endif
        return true;
    }

}
