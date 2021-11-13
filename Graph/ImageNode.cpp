#include "ImageNode.hpp"

namespace mobo
{
    DERIVE_TYPE(ImageNode, "0ef83d70-53b7-464d-b32e-10dbfb31afa2", {&DataSourceNode::_type});
    
    bool ImageNode::update(Context& iCtx)
    {
        imageBuffer.clear();
        auto stringNode = getInput<StringNode>(0);
        if(stringNode) {
            auto filename = stringNode->getValue();
            vector<unsigned char> fileBuffer;
            unsigned error = lodepng::load_file(fileBuffer, filename.c_str());
            if(error) {
                cerr << "Failed to load png file " << filename << endl; return false;
            } else cout << "Loaded png file " << filename << endl;
            lodepng::State state;
            imageBuffer.clear();
            error = lodepng::decode(imageBuffer, imgWidth, imgHeight, state, fileBuffer);
            if(error) {
                cerr << "Failed to decode png file " << filename << endl; return false;
            }
            cout << "Decoded png file, width: " << imgWidth << ", height: " << imgHeight << endl;
        }
        return true;
    }

    const void* ImageNode::rawMap() const
    {
        return static_cast<const void*>(&imageBuffer[0]);
    }

}
