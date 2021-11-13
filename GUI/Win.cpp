#include "Win.hpp"

#include "GLPipeline.hpp"
#include "GLPipelineStart.hpp"
#include "GLShader.hpp"
#include "StringNode.hpp"
#include "HostBufferNode.hpp"
#include "ImageNode.hpp"
#include "GLBufferNode.hpp"
#include "GLGeometry.hpp"
#include "GLTexture.hpp"
#include "GLMaterial.hpp"
#include "GLDraw.hpp"
#include "GLTransform.hpp"
#include "GLCamera.hpp"
#include "FileNode.hpp"

#include <jsoncpp/json/json.h>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace mobo
{

    const string vtxShaderText(
    R"(
        #version 330 core

        layout(location = 0) in vec4 iVtxPos;
        layout(location = 1) in vec4 iVtxClr;
        layout(location = 2) in vec2 iVtxUV;

        uniform mat4 project;
        uniform mat4 camera;
        uniform mat4 modelview;

        out vec4 fVtxClr;
        out vec2 fVtxUV;

        void main() {
            gl_Position = project * camera * modelview * iVtxPos;
            fVtxClr = iVtxClr;
            fVtxUV = iVtxUV;
        }
    )");

    const string frgShaderText(
    R"(
        #version 330 core

        uniform sampler2D tex;

        in vec4 fVtxClr;
        in vec2 fVtxUV;

        out vec4 oColor;

        void main() {
            oColor = texture(tex, fVtxUV) * fVtxClr;
        }
    )");

    const GLfloat vtxData[] = { -1.0, -1.0, 0.0, 1.0,    1.0, -1.0, 0.0, 1.0,    0.0, 1.0, 0.0, 1.0 };
    const GLfloat clrData[] = { 1.0, 0.0, 0.0, 1.0,    0.0, 1.0, 0.0, 1.0,    0.0, 0.0, 1.0, 1.0 };
    const GLfloat uvData[] = { 0.0, 1.0,    1.0, 1.0,    0.5, 0.0 };

    void _didMove(int x, int y);
    void _didReshape(int w, int h);
    void _willClose();
    void _keyDown(unsigned char k, int x, int y);
    void _keyUp(unsigned char k, int x, int y);
    void _specialDown(int k, int x, int y);
    void _specialUp(int k, int x, int y);
    void _mouseMove(int x, int y);
    void _mouse(int b, int d, int x, int y);
    void _mouseDrag(int x, int y);
    void _mouseSense(int d);
    void _render();
    void _renderOverlay();

    Win::Win(App& iApp)
    : app(iApp), winId(glutCreateWindow("")),
      mouseButtonState(0), needsDisplay(false),
      timestamp(time_point<steady_clock>(seconds(0))), emaWindow(0.0), fpsWMA(0.0), fpsEMA(0.0), fpsAVG(30),
      ctx()
    {
        /*
        ifstream fs("../test.json", ifstream::in);
        fs >> root;
        Json::Value node = root.get("node", "");
        Json::Value id = node.get("id", "");
        cout << id.asString() << endl;
        */

        auto startNode = ctx.createNodeT(GLPipelineStart);
        cout << "startNode " << startNode->nodeId.toString() << endl;

        auto vtxShaderSrc = ctx.createNodeT(StringNode);
        vtxShaderSrc->setValue(vtxShaderText);
        cout << "vtxShaderSrc " << vtxShaderSrc->nodeId.toString() << endl;
        auto vtxShader = ctx.createNodeT(GLVertexShader);
        cout << "vtxShader " << vtxShader->nodeId.toString() << endl;
        vtxShader->linkTo(0, *vtxShaderSrc);

        auto frgShaderSrc = ctx.createNodeT(StringNode);
        frgShaderSrc->setValue(frgShaderText);
        cout << "frgShaderSrc " << frgShaderSrc->nodeId.toString() << endl;
        auto frgShader = ctx.createNodeT(GLFragmentShader);
        cout << "frgShader " << frgShader->nodeId.toString() << endl;
        frgShader->linkTo(0, *frgShaderSrc);

        auto program = ctx.createNodeT(GLProgram);
        cout << "program " << program->nodeId.toString() << endl;
        program->linkTo(0, *startNode);
        program->linkTo(1, *vtxShader);
        program->linkTo(2, *frgShader);

        auto vtxFilename = ctx.createNodeT(StringNode);
        vtxFilename->setValue("../vtxBuf.bin");
        auto clrFilename = ctx.createNodeT(StringNode);
        clrFilename->setValue("../clrBuf.bin");
        auto uvFilename = ctx.createNodeT(StringNode);
        uvFilename->setValue("../uvBuf.bin");

        auto vtxFile = ctx.createNodeT(BinaryFileInputNode);
        auto clrFile = ctx.createNodeT(BinaryFileInputNode);
        auto uvFile = ctx.createNodeT(BinaryFileInputNode);
        vtxFile->linkTo(0, *vtxFilename);
        clrFile->linkTo(0, *clrFilename);
        uvFile->linkTo(0, *uvFilename); 

        auto vtxBuf = ctx.createNodeT(GLV4BufferNode);
        auto clrBuf = ctx.createNodeT(GLV4BufferNode);
        auto uvBuf = ctx.createNodeT(GLV2BufferNode);
        vtxBuf->linkTo(0, *vtxFile);
        clrBuf->linkTo(0, *clrFile);
        uvBuf->linkTo(0, *uvFile);

        vtxBuf->setAttribName("iVtxPos");
        clrBuf->setAttribName("iVtxClr");
        uvBuf->setAttribName("iVtxUV");

        /*
        HostV4BufferNode* hostVtxBuf = new HostV4BufferNode();
        HostV4BufferNode* hostClrBuf = new HostV4BufferNode();
        HostV2BufferNode* hostUVBuf = new HostV2BufferNode();

        hostVtxBuf->blit((const vec<GLfloat,4>*) vtxData, 3);
        hostClrBuf->blit((const vec<GLfloat,4>*) clrData, 3);
        hostUVBuf->blit((const vec<GLfloat,2>*) uvData, 3);

        StringNode *outputFilename = new StringNode("../vtxBuf.bin");
        BinaryFileOutputNode* fileOutputNode = new BinaryFileOutputNode();
        fileOutputNode->linkTo(0, *outputFilename);
        fileOutputNode->linkTo(1, *hostVtxBuf);
        fileOutputNode->update(ctx);

        outputFilename->setValue("../clrBuf.bin");
        fileOutputNode->linkTo(1, *hostClrBuf);
        fileOutputNode->nodeFlags.set(Node::UPDATE_FLAG);
        fileOutputNode->update(ctx);

        outputFilename->setValue("../uvBuf.bin");
        fileOutputNode->linkTo(1, *hostUVBuf);
        fileOutputNode->nodeFlags.set(Node::UPDATE_FLAG);
        fileOutputNode->update(ctx);
        */

        auto geom = ctx.createNodeT(GLGeometry);
        geom->linkTo(0, *program);
        geom->linkTo(1, *vtxBuf);
        geom->linkTo(2, *clrBuf);
        geom->linkTo(3, *uvBuf);

        auto texFilename = ctx.createNodeT(StringNode);
        texFilename->setValue("../Burst.png");

        auto imageNode = ctx.createNodeT(ImageNode);
        imageNode->linkTo(0, *texFilename);

        auto tex = ctx.createNodeT(GL2DTexture);
        tex->linkTo(0, *imageNode);
        tex->setUnifName("tex");
        // tex->loadFromPNG("../Burst.png");

        auto material = ctx.createNodeT(GLMaterial);
        material->linkTo(0, *geom);
        material->addLinkTo(*tex);

        auto cameraXfm = ctx.createNodeT(GLTransform);
        (*cameraXfm) = mat4<GLfloat>(TRANSLATION, 0.0, 0.0, 3.0) * mat4<GLfloat>(ROTATION, -0.0625 * M_PI, 0.0, 1.0, 0.0);
        auto camera = ctx.createNodeT(GLCamera);
        camera->linkTo(0, *cameraXfm);

        auto xfm = ctx.createNodeT(GLTransform);
        xfm->linkTo(0, *material);
        xfm->addLinkTo(*camera);

        auto drawNode = ctx.createNodeT(GLDraw);
        drawNode->linkTo(0, *xfm);

        auto pipelineNode = ctx.createNodeT(GLPipeline);
        cout << "pipelineNode " << pipelineNode->nodeId.toString() << endl;
        pipelineNode->linkTo(0, *drawNode);

        ctx.setRoot(pipelineNode->nodeId);

        ofstream jsonFile("../test.json", ofstream::out);
        jsonFile << ctx.serialize();
        jsonFile.close();

        glutSetWindow(winId);
        glutSetWindowData((void*) this);

        glutPositionFunc(_didMove);
        glutReshapeFunc(_didReshape);
        glutCloseFunc(_willClose);

        glutKeyboardFunc(_keyDown);
        glutKeyboardUpFunc(_keyUp);

        glutSpecialFunc(_specialDown);
        glutSpecialUpFunc(_specialUp);

        glutPassiveMotionFunc(_mouseMove);
        glutMouseFunc(_mouse);
        
        glutMotionFunc(_mouseDrag);

        glutEntryFunc(_mouseSense);

        glutDisplayFunc(_render);
        glutOverlayDisplayFunc(_renderOverlay);
    }

    Win::~Win()
    {
        if(winId) {
            glutSetWindow(winId);
            glutSetWindowData(nullptr);

            glutPositionFunc(nullptr);
            glutReshapeFunc(nullptr);
            glutCloseFunc(nullptr);

            glutKeyboardFunc(nullptr);
            glutKeyboardUpFunc(nullptr);

            glutSpecialFunc(nullptr);
            glutSpecialUpFunc(nullptr);

            glutPassiveMotionFunc(nullptr);
            glutMouseFunc(nullptr);
            
            glutMotionFunc(nullptr);

            glutEntryFunc(nullptr);

            glutDestroyWindow(winId);
        }
        winId = 0;
    }

    void Win::setTitle(const string& iTitle)
    {
        glutSetWindow(winId);
        glutSetWindowTitle(iTitle.c_str());
    }

    bool Win::didReshape(int w, int h)
    {
        ctx.setViewport(rect<GLint, GLsizei>(0, 0, w, h));
        app.yieldToUI();
        return true;
    }

    bool Win::willClose()
    {
        app.removeWindow(winId);
        return true;
    }

    bool Win::keyDown(unsigned char k, int x, int y)
    {
        switch(k) {
            case 14: // ctrl-N
                return true;
                /*
                {
                    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
                    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
                    int winx = glutGet(GLUT_WINDOW_X);
                    int winy = glutGet(GLUT_WINDOW_Y);
                    int winw = glutGet(GLUT_WINDOW_WIDTH);
                    int winh = glutGet(GLUT_WINDOW_HEIGHT);
                    winx += 20;
                    winy += 10;
                    if((winx + winw + 20) > screenWidth) { winx = 20; }
                    if((winy + winh + 20) > screenHeight) { winy = 20; }
                    app.newWindow(winx, winy, winw, winh);
                } return true;
                */
            case 23: // ctrl-W
                glutDestroyWindow(winId);
                return true;
        }
        return false;
    }

    bool Win::keyUp(unsigned char k, int x, int y)
    {
        return false;
    }

    void Win::postDisplay()
    {
        ctx.update();

        if(!needsDisplay) {
            glutSetWindow(winId);
            glutPostRedisplay();
            needsDisplay = true;
        }
    }

    float Win::calculateFrameRate()
    {
        auto newTime = steady_clock::now();
        if(timestamp != time_point<steady_clock>(seconds(0))) {
            duration<float, micro> period(newTime - timestamp);
            float newFPS = seconds(1) / period;
            fpsAVG.push_back(newFPS);
            fpsWMA = fpsAVG.wma();
            
            if(emaWindow == 0) {
                fpsEMA = newFPS;
            } else {
                float k = 2.0f / (emaWindow + 1.0f);
                fpsEMA = newFPS * k + fpsEMA * (1.0 - k);
            }
            if(emaWindow < 15) emaWindow++;

        } else {
            fpsWMA = 0.0;
            fpsEMA = 0.0;
        }
        timestamp = newTime;
        return fpsEMA;
    }

    bool Win::render()
    {
        ctx.submit();
        float fpsEMA = calculateFrameRate();
        stringstream fpsSStream;
        fpsSStream << "FPS: " << setprecision(2) << fpsEMA;
        setTitle(fpsSStream.str());
        ctx.retract();
        needsDisplay = false;
        return true;
    }

    void _didMove(int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::DIDMOVE, 0, x, y));
    }

    void _didReshape(int w, int h)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::DIDRESHAPE, 0, w, h));
    }

    void _willClose()
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::WILLCLOSE));
    }

    void _keyDown(unsigned char k, int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::KEYDOWN, k, x, y));
    }

    void _keyUp(unsigned char k, int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::KEYUP, k, x, y));
    }

    void _specialDown(int k, int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::SPECIALDOWN, k, x, y));
    }

    void _specialUp(int k, int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::SPECIALUP, k, x, y));
    }

    void _mouseMove(int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::MOUSEMOVE, 0, x, y));
    }

    void _mouse(int b, int d, int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        uint32_t button = 0;
        switch(b) {
            case GLUT_LEFT_BUTTON:
                button = Win::PRIMARY_BUTTON; break;
            case GLUT_RIGHT_BUTTON:
                button = Win::SECONDARY_BUTTON; break;
            case GLUT_MIDDLE_BUTTON:
                button = Win::TERTIARY_BUTTON; break;
            default: break;
        }
        d ? ((win->mouseButtonState |= button) && win->dispatchEvent(Event(Event::MOUSEDOWN, button, x, y)))
        : ((win->mouseButtonState &= ~button) && win->dispatchEvent(Event(Event::MOUSEUP, button, x, y)));
    }

    void _mouseDrag(int x, int y)
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::MOUSEDRAG, 0, x, y));
    }

    void _mouseSense(int d)
    {
        Win* win = (Win*) glutGetWindowData();
        switch(d) {
            case GLUT_ENTERED:
                win->dispatchEvent(Event(Event::MOUSEENTERED)); break;
            case GLUT_LEFT:
                win->dispatchEvent(Event(Event::MOUSEEXITED)); break;
            default: break;
        }
    }

    void _render()
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::RENDER));
    }

    void _renderOverlay()
    {
        Win* win = (Win*) glutGetWindowData();
        win->dispatchEvent(Event(Event::RENDEROVERLAY)); 
    }
}
