#include "Renderer.hpp"

#include "lodepng.h"
#include <string>
#include <iostream>

using namespace std;

namespace mobo
{
    GLfloat vtxData[] = { -1.0, -1.0, 0.0, 1.0,    1.0, -1.0, 0.0, 1.0,    0.0, 1.0, 0.0, 1.0 };
    GLint vtxDataSize = 12;
    GLfloat clrData[] = { 1.0, 0.0, 0.0, 1.0,    0.0, 1.0, 0.0, 1.0,    0.0, 0.0, 1.0, 1.0 };
    GLint clrDataSize = 12;
    GLfloat uvData[] = { 0.0, 1.0,    1.0, 1.0,    0.5, 0.0 };
    GLint uvDataSize = 6;

    void Renderer::init()
    {
        #ifdef TRACE
        cout << "Generating VBOs" << endl;
        #endif

        glGenBuffers(3, vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vtxDataSize * sizeof(GLfloat), vtxData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, clrDataSize * sizeof(GLfloat), clrData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, uvDataSize * sizeof(GLfloat), uvData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        #ifdef TRACE
        cout << "Loading textures" << endl;
        #endif

        string imageFilename("../Burst.png");
        unsigned imgWidth, imgHeight;
        vector<unsigned char> buffer;
        lodepng::load_file(buffer, imageFilename.c_str());
        lodepng::State state;
        vector<unsigned char> imageBytes;
        lodepng::decode(imageBytes, imgWidth, imgHeight, state, buffer);

        glGenTextures(1, &tex);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);

        // glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imgWidth, imgHeight); // NOT Available until OpenGL V4.2
        // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imgWidth, imgHeight, GL_RGBA, GL_UNSIGNED_BYTE, (void*) &(imageBytes[0]));
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) &(imageBytes[0]));

        glGenSamplers(1, &samp);
        glSamplerParameteri(samp, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(samp, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glSamplerParameteri(samp, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(samp, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameterf(samp, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

        /*
        auto info = state.info_png;
        auto color = info.color;
        cout << "Image width: " << imgWidth << endl;
        cout << "Image height: " << imgHeight << endl;
        cout << "Bit depth: " << color.bitdepth << endl;
        cout << "Bits per pixel: " << lodepng_get_bpp(&color) << endl;
        cout << "Channels per pixel: " << lodepng_get_channels(&color) << endl;
        cout << "Can have alpha: " << lodepng_can_have_alpha(&color) << endl;
        */

        #ifdef TRACE
        cout << "Binding buffers" << endl;
        #endif

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Renderer::~Renderer()
    {
        if(prog) glDeleteProgram(prog);
    }

    void Renderer::didReshape(int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    void Renderer::render()
    {
        #ifdef TRACE
        cout << "Rendering" << endl;
        #endif

        GLint texLoc = glGetUniformLocation(prog, "tex");
        glUniform1i(texLoc, 0);

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glBindSampler(0, samp);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindSampler(0, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        #ifdef TRACE
        cout << "Render Complete" << endl;
        #endif
    }
}
