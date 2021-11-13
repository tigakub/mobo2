#ifndef __FILENODE_HPP__
#define __FILENODE_HPP__

#include "DataSourceNode.hpp"
#include "StringNode.hpp"

#include <vector>
#include <string>

using namespace std;

namespace mobo
{
    class FileNode : public DataSourceNode
    {
        DECLARE_TYPE

        public:
            FileNode() : DataSourceNode() { addInput(StringNode::_type); }
            virtual bool submit(Context& iCtx) { return true; }
            virtual bool retract(Context& iCtx) { return true; }
    };

    class BinaryFileInputNode : public FileNode, public DataSource
    {
        DECLARE_TYPE

        public:
            BinaryFileInputNode();

            virtual bool update(Context& iCtx);

            virtual uint32_t size() const { return buffer.size(); }
            virtual uint32_t byteStride() const { return 1; }
            virtual const void* rawMap() const { return static_cast<const void*>(&buffer[0]); }
            virtual void* rawMap() { return static_cast<void*>(&buffer[0]); }

        protected:
            virtual void setSize(uint32_t, bool) { }

        protected:
            vector<unsigned char> buffer;
    };

    class TextFileInputNode : public FileNode, public DataSource
    {
        DECLARE_TYPE

        public:
            TextFileInputNode();

            virtual bool update(Context& iCtx);

            virtual uint32_t size() const { return buffer.length(); }
            virtual uint32_t byteStride() const { return 1; }
            virtual const void* rawMap() const { return static_cast<const void*>(&buffer[0]); }
            virtual void* rawMap() { return static_cast<void*>(&buffer[0]); }

        protected:
            virtual void setSize(uint32_t, bool) { }

        protected:
            string buffer;
    };

    class BinaryFileOutputNode : public FileNode
    {
        DECLARE_TYPE
        
        public:
            BinaryFileOutputNode();

            virtual bool update(Context& iCtx);
    };

    class TextFileOutputNode : public FileNode
    {
        DECLARE_TYPE
        
        public:
            TextFileOutputNode();
            
            virtual bool update(Context& iCtx);
    };

}

#endif

