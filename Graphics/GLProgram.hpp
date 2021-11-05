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
                    UniformInfo() : RefCtr() { }
                    UniformInfo(const UniformInfo& i)
                    : RefCtr(), size(i.size), type(i.type), location(i.location), name(i.name), typeName(i.typeName)
                    { }

                    UniformInfo& operator=(const UniformInfo& i) {
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

            UniformInfo& getUniformInfo(const string& iName);
            AttribInfo& getAttribInfo(const string& iName);
            
            const unordered_map<string, UniformInfo>& getUniformInfo() const;
            const unordered_map<string, AttribInfo>& getAttribInfo() const;

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
