#ifndef __GLPROGRAM_HPP__
#define __GLPROGRAM_HPP__

#include "Debug.hpp"

#include "RefCtr.hpp"
#include "Context.hpp"
#include "GLPipeline.hpp"
#include "GLShader.hpp"

#include <cstddef>
#include <functional>
#include <string_view>
#include <vector>
#include <unordered_map>

using namespace std;

namespace mobo
{
    class GLContext;

    class GLProgram : public GLPipeline
    {
        DECLARE_TYPE

        public:
            static string nameFromType(GLenum iType);

        public:
            class UniformInfo : public RefCtr {
                public:
                    UniformInfo()
                    : RefCtr(), size(0), type(0), location(0), name(),
                      typeName(), tex(0), target(0), sampler(0) { }

                    UniformInfo(const UniformInfo& i)
                    : RefCtr(), size(i.size), type(i.type), location(i.location), 
                      name(i.name), typeName(i.typeName), tex(i.tex), target(i.target),
                      sampler(i.sampler)
                    { }

                    UniformInfo(UniformInfo&& i)
                    : RefCtr(), size(i.size), type(i.type), location(i.location),
                      name(move(i.name)), typeName(move(i.typeName)), tex(i.tex), target(i.target),
                      sampler(i.sampler)
                    {
                        i.sampler = 0;
                    }

                    virtual ~UniformInfo() {
                        if(sampler) glDeleteSamplers(1, &sampler);
                    }

                    virtual void generateSampler() {
                        if(!sampler) glGenSamplers(1, &sampler);
                    }

                    UniformInfo& operator=(const UniformInfo& i) {
                        size = i.size;
                        type = i.type;
                        location = i.location;
                        name = i.name;
                        typeName = i.typeName;
                        tex = i.tex;
                        target = i.target;
                        sampler = i.sampler;
                        return *this;
                    }
                    
                    GLsizei size;
                    GLenum type;
                    GLint location;
                    string name;
                    string typeName;
                    GLuint tex;
                    GLenum target;
                    GLuint sampler;
            };

            class AttribInfo : public RefCtr {
                public:
                    AttribInfo() : RefCtr() { }
                    AttribInfo(const AttribInfo& i)
                    :  RefCtr(), size(i.size), type(i.type), location(i.location), name(i.name), typeName(i.typeName)
                    { }

                    AttribInfo& operator=(const AttribInfo& i) {
                        size = i.size;
                        type = i.type;
                        location = i.location;
                        name = i.name;
                        typeName = i.typeName;
                        return *this;
                    }

                    bool available;
                    GLsizei size;
                    GLenum type;
                    GLint location;
                    string name;
                    string typeName;
            };

        public:
            GLProgram();
            virtual ~GLProgram();

            const UniformInfo& getUniformInfo(const string&) const;
            const AttribInfo& getAttribInfo(const string&) const;
            /*
            const unordered_map<string, UniformInfo>& getUniformInfo() const;
            const unordered_map<string, AttribInfo>& getAttribInfo() const;
            */

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual bool activate();
            virtual bool deactivate();

        protected:
            GLint programHandle;
            unordered_map<string, UniformInfo, hash<string>> uniformInfo;
            unordered_map<string, AttribInfo, hash<string>> attribInfo;
    };
}

#endif
