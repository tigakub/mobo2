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
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glEnable)
        #endif
        glBindTexture(target(), textureHandle);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glBindTexture)
        #endif
        glTexParameterf(target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glTexParameterf)
        #endif
        glTexParameterf(target(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glTexParameterf)
        #endif
        loadFromBuffer(&(imageBuffer[0]));
    }

    bool GLTexture::update(Context& iCtx)
    {
        auto imgNode = getInput<FrameSourceNode>(0);
        const DataSource* ds = dynamic_cast<const DataSource*>(imgNode);
        if(imgNode && ds) {
            imgWidth = imgNode->getWidth();
            imgHeight = imgNode->getHeight();
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
            GLint err;
            glEnable(target());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glEnable)
            #endif
            glBindTexture(target(), textureHandle);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glBindTexture)
            #endif
            glTexParameterf(target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glTexParameterf)
            #endif
            glTexParameterf(target(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glTexParameterf)
            #endif
            const uint8_t* ptr = static_cast<const uint8_t*>(ds->rawMap());
            if(!ptr) cout << "Null texture buffer" << endl;
            loadFromBuffer(ptr);
            ds->unmap();
        }
    }

    void GL2DTexture::loadFromBuffer(const unsigned char* iBuffer)
    {
        if(imgWidth && imgHeight) {
            if(!textureCreated) {
                //cout << "Allocating texture memory" << endl;
                //cout << "target: " << target() << ", internalFormat: " << internalFormat << ", imgWidth: " << std::dec << imgWidth << ", imgHeight: " << imgHeight << ", format: " << format << ", buffer: 0x" << hex << (uint64_t) iBuffer << std::dec << endl;
                // glPixelStorei(
                glTexImage2D(target(), 0, internalFormat, imgWidth, imgHeight, 0, format, GL_UNSIGNED_INT_8_8_8_8_REV, (void*) iBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glTexImage2D)
                #endif
                textureCreated = true;
            } else {
                //cout << "Updating texture" << endl;
                //cout << "target: " << target() << ", internalFormat: " << internalFormat << ", imgWidth: " << std::dec << imgWidth << ", imgHeight: " << imgHeight << ", format: " << format << ", buffer: 0x" << hex << (uint64_t) iBuffer << std::dec << endl;
                glTexSubImage2D(target(), 0, 0, 0, imgWidth, imgHeight, format, GL_UNSIGNED_INT_8_8_8_8_REV, (void *) iBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glTexSubImage2D)
                #endif
            }
        }
    }

    void GLRectTexture::loadFromBuffer(const unsigned char* iBuffer)
    {
        if(imgWidth && imgHeight) {
            if(!textureCreated) {
                //cout << "Allocating texture memory" << endl;
                //cout << "target: " << target() << ", internalFormat: " << internalFormat << ", imgWidth: " << std::dec << imgWidth << ", imgHeight: " << imgHeight << ", format: " << format << ", buffer: 0x" << hex << (uint64_t) iBuffer << std::dec << endl;
                glTexImage2D(target(), 0, internalFormat, imgWidth, imgHeight, 0, format, GL_UNSIGNED_INT_8_8_8_8, (void*) iBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glTexImage2D)
                #endif
                textureCreated = true;
            } else {
                //cout << "Updating texture" << endl;
                //cout << "target: " << target() << ", internalFormat: " << internalFormat << ", imgWidth: " << std::dec << imgWidth << ", imgHeight: " << imgHeight << ", format: " << format << ", buffer: 0x" << hex << (uint64_t) iBuffer << std::dec << endl;
                glTexSubImage2D(target(), 0, 0, 0, imgWidth, imgHeight, format, GL_UNSIGNED_INT_8_8_8_8, (void *) iBuffer);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glTexSubImage2D)
                #endif
            }
        }
    }
}
