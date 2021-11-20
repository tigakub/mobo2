#ifndef __GLCONTEXT_HPP__
#define __GLCONTEXT_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "GLShader.hpp"
#include "GLProgram.hpp"
#include "GLGeometry.hpp"
#include "GLMaterial.hpp"

#include "Math.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

using namespace std;

namespace mobo
{

    class GLContext : public Context
    {
        public:
            GLContext();
            virtual ~GLContext() { }

            const rect<GLint, GLsizei>& getViewport() { return viewport; }
            void setViewport(const rect<GLint, GLsizei>& iViewport) { viewport = iViewport; }

            virtual void initialize();
            virtual void finalize();

            void pushProgram(GLProgram* iProgram) { programStack.push_back(iProgram); }
            GLProgram* currentProgram() { if(programStack.size()) return static_cast<GLProgram*>(programStack.back()); return nullptr; }
            GLProgram* popProgram() { programStack.pop_back(); return currentProgram(); }

            void pushGeometry(GLGeometry* iGeometry) { geometryStack.push_back(iGeometry); }
            GLGeometry* currentGeometry() { if(geometryStack.size()) return static_cast<GLGeometry*>(geometryStack.back()); return nullptr; }
            GLGeometry* popGeometry() { geometryStack.pop_back(); return currentGeometry(); }

            void pushMaterial(GLMaterial* iMaterial) { materialStack.push_back(iMaterial); }
            GLMaterial* currentMaterial() { if(materialStack.size()) return static_cast<GLMaterial*>(materialStack.back()); return nullptr; }
            GLMaterial* popMaterial() { materialStack.pop_back(); return currentMaterial(); }

            void pushProjectionMatrix(const mat4<GLfloat>& iMat) { projectionMatrixStack.push_back(iMat); }
            const mat4<GLfloat>& projectionMatrix() const { return projectionMatrixStack.back(); }
            const mat4<GLfloat>& popProjectionMatrix() { projectionMatrixStack.pop_back(); return projectionMatrix(); }

            void pushCameraMatrix(const mat4<GLfloat>& iMat) { cameraMatrixStack.push_back(iMat); }
            const mat4<GLfloat>& cameraMatrix() const { return cameraMatrixStack.back(); }
            const mat4<GLfloat>& popCameraMatrix() { cameraMatrixStack.pop_back(); return cameraMatrix(); }

            void pushModelviewMatrix(const mat4<GLfloat>& iMat) { modelviewMatrixStack.push_back(iMat); }
            const mat4<GLfloat>& modelviewMatrix() const { return modelviewMatrixStack.back(); }
            const mat4<GLfloat>& popModelviewMatrix() { modelviewMatrixStack.pop_back(); return modelviewMatrix(); }

            void pushUVMatrix(const mat3<GLfloat>& iMat) { uvMatrixStack.push_back(iMat); }
            const mat3<GLfloat>& uvMatrix() const { return uvMatrixStack.back(); }
            const mat3<GLfloat>& popUVMatrix() { uvMatrixStack.pop_back(); return uvMatrix(); }

        protected:
            vector<SmartPtr<GLProgram>> programStack;
            vector<SmartPtr<GLGeometry>> geometryStack;
            vector<SmartPtr<GLMaterial>> materialStack;
            rect<GLint, GLsizei> viewport;
            vector<mat4<GLfloat>> projectionMatrixStack;
            vector<mat4<GLfloat>> cameraMatrixStack;
            vector<mat4<GLfloat>> modelviewMatrixStack;
            vector<mat3<GLfloat>> uvMatrixStack;
    };

}

#endif