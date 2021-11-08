#include "FileNode.hpp"
#include "HostBufferNode.hpp"

#include <iostream>
#include <fstream>

using namespace std;

namespace mobo
{
    DERIVE_TYPE(FileNode, "82de52c8-67eb-4712-b89a-db6b50d4024c", {&Node::_type})
    DERIVE_TYPE(BinaryFileInputNode, "9acfc04f-b1f9-421c-95b4-16f52e46c88d", {&FileNode::_type})
    DERIVE_TYPE(TextFileInputNode, "84d485f6-469a-4f1b-968e-6a6bb37f350b", {&FileNode::_type})
    DERIVE_TYPE(BinaryFileOutputNode, "fb7eac00-7a75-4f48-a983-82e5f3384255", {&FileNode::_type})
    DERIVE_TYPE(TextFileOutputNode, "cad92ad1-10d1-475f-959e-a3a62a6cc236", {&FileNode::_type})
    
    BinaryFileInputNode::BinaryFileInputNode()
    : FileNode(), DataSource()
    { }

    bool BinaryFileInputNode::update(Context& iCtx)
    {
        StringNode* stringNode = getInput<StringNode>(0);
        if(stringNode) {
            const string& filepath = stringNode->getValue();
            ifstream fileStream(filepath, ios::binary);
            vector<unsigned char> data(istreambuf_iterator<char>(fileStream), {});
            buffer = data;
        }
        return true;
    }

    TextFileInputNode::TextFileInputNode()
    : FileNode(), DataSource()
    { }

    bool TextFileInputNode::update(Context& iCtx)
    {
        StringNode* stringNode = getInput<StringNode>(0);
        if(stringNode) {
            const string& filepath = stringNode->getValue();
            ifstream fileStream(filepath);
            string data(istreambuf_iterator<char>(fileStream), {});
            buffer = data;
        }
        return true;
    }

    BinaryFileOutputNode::BinaryFileOutputNode()
    : FileNode()
    {
        addInput(HOSTBUFFERTYPE);
    }

    bool BinaryFileOutputNode::update(Context& iCtx)
    {
        StringNode* stringNode = getInput<StringNode>(0);
        if(stringNode) {
            cout << "fuck1" << endl;
            const string& filepath = stringNode->getValue();
            Buffer* dataNode = dynamic_cast<Buffer*>(getInput<Node>(1));
            if(dataNode) {
                cout << "fuck2" << endl;
                ofstream fileStream(filepath, ios::binary);
                uint32_t byteSize = dataNode->byteSize();
                void* bufferPtr = dataNode->rawMap();
                fileStream.write(static_cast<char*>(bufferPtr), byteSize);
                dataNode->unmap();
            }
        }
        return true;
    }

    TextFileOutputNode::TextFileOutputNode()
    : FileNode()
    {
        addInput(StringNode::_type);
    }

    bool TextFileOutputNode::update(Context& iCtx)
    {
        StringNode* stringNode = getInput<StringNode>(0);
        if(stringNode) {
            const string& filepath = stringNode->getValue();
            StringNode* dataNode = dynamic_cast<StringNode*>(getInput<StringNode>(1));
            if(dataNode) {
                ofstream fileStream(filepath);
                fileStream << dataNode->getValue();
            }
        }
        return true;
    }

}