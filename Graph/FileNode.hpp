#ifndef __FILENODE_HPP__
#define __FILENODE_HPP__

#include "DataSource.hpp"
#include "StringNode.hpp"

#include <vector>
#include <string>

using namespace std;

namespace mobo
{
    class FileNode : public Node
    {
        DECLARE_TYPE

        public:
            FileNode() : Node() { addInput(StringNode::_type); }
            virtual bool submit(Context& iCtx) { return true; }
            virtual bool retract(Context& iCtx) { return true; }
    };

    class BinaryFileInputNode : public FileNode, public DataSource
    {
        DECLARE_TYPE

        public:
            BinaryFileInputNode();

            virtual bool update(Context& iCtx);

            virtual uint32_t byteSize() const { return buffer.size(); }
            virtual const void* rawMap() const { return static_cast<const void*>(&buffer[0]); }
            virtual void* rawMap() { return static_cast<void*>(&buffer[0]); }

        protected:
            vector<unsigned char> buffer;
    };

    class TextFileInputNode : public FileNode, public DataSource
    {
        DECLARE_TYPE

        public:
            TextFileInputNode();

            virtual bool update(Context& iCtx);

            virtual uint32_t byteSize() const { return buffer.length(); }
            virtual const void* rawMap() const { return static_cast<const void*>(&buffer[0]); }
            virtual void* rawMap() { return static_cast<void*>(&buffer[0]); }

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

