#include "Node.hpp"
#include "GLContext.hpp"
#include "GLTexture.hpp"

namespace mobo
{
    DERIVE_TYPE(GLTexture, "4fc9c202-8b5c-41db-a801-f367cbfc3f06", { &Node::_type } )
    DERIVE_TYPE(GL2DTexture, "04700b9b-050d-433b-b1b3-117363c9adc2", { &GLTexture::_type } )
    DERIVE_TYPE(GLRectTexture, "022e5a99-b097-488e-811e-c475aa94ab87", { &GLTexture::_type } )

    void GLTexture::loadFromPNG(const string& iFilename)
    {
        vector<unsigned char> fileBuffer;
        vector<unsigned char> imageBuffer;
        unsigned error = lodepng::load_file(fileBuffer, iFilename.c_str());
        if(error) { cerr << "Failed to load png file" << endl; return; }
        else cout << "Loaded png file" << endl;
        lodepng::State state;
        error = lodepng::decode(imageBuffer, imgWidth, imgHeight, state, fileBuffer);
        if(error) { cerr << "Failed to decode png file" << endl; return; }
        else cout << "Decoded png file" << endl;
        cout << "imgWidth " << imgWidth << endl;
        cout << "imgHeight " << imgHeight << endl;
        glEnable(target());
        glBindTexture(target(), textureHandle);
        glTexParameterf(target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(target(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        loadFromBuffer(imageBuffer);
    }

    bool GLTexture::update(Context& iContext)
    {
        auto imgNode = getInput<ImageNode>(0);
        if(imgNode) {
            imgWidth = imgNode->getWidth();
            imgHeight = imgNode->getHeight();
            glEnable(target());
            glBindTexture(target(), textureHandle);
            glTexParameterf(target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(target(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            loadFromBuffer(imgNode->getImageBuffer());
        }
    }

    void GL2DTexture::loadFromBuffer(const vector<unsigned char>& iBuffer)
    {
        glTexImage2D(target(), 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) &(iBuffer[0]));
        if(glGetError()) cout << "Failed glTexImage2D " << gluErrorString(glGetError()) << endl;
    }

    void GLRectTexture::loadFromBuffer(const vector<unsigned char>& iBuffer)
    {
        glTexImage2D(target(), 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) &(iBuffer[0]));
        if(glGetError()) cout << "Failed glTexImage2D " << gluErrorString(glGetError()) << endl;
    }
}
