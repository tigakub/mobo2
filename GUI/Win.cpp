#include "Win.hpp"

#include "GLPipeline.hpp"
#include "GLPipelineStart.hpp"
#include "GLShader.hpp"
#include "StringNode.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace mobo
{
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

    const string vtxShaderText(R"(
        #version 330 core

        layout(location = 0) in vec4 iVtxPos;
        layout(location = 1) in vec4 iVtxClr;
        layout(location = 2) in vec2 iVtxUV;

        out vec4 fVtxClr;
        out vec2 fVtxUV;

        void main() {
            gl_Position = iVtxPos;
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
            oColor = texture(tex, fVtxUV);
        }
    )");

    Win::Win(App& iApp)
    : app(iApp), winId(glutCreateWindow("")),
      mouseButtonState(0), renderer(nullptr), needsDisplay(false),
      timestamp(time_point<steady_clock>(seconds(0))), emaWindow(0.0), fpsWMA(0.0), fpsEMA(0.0), fpsAVG(30),
      ctx()
    {
        GLPipelineStart *startNode = new GLPipelineStart();
        cout << "startNode " << startNode->nodeId.toString() << endl;

        StringNode *vtxShaderSrc = new StringNode(vtxShaderText);
        cout << "vtxShaderSrc " << vtxShaderSrc->nodeId.toString() << endl;
        GLVertexShader *vtxShader = new GLVertexShader();
        cout << "vtxShader " << vtxShader->nodeId.toString() << endl;
        vtxShader->linkTo(0, *vtxShaderSrc);

        StringNode *frgShaderSrc = new StringNode(frgShaderText);
        cout << "frgShaderSrc " << frgShaderSrc->nodeId.toString() << endl;
        GLFragmentShader *frgShader = new GLFragmentShader();
        cout << "frgShader " << frgShader->nodeId.toString() << endl;
        frgShader->linkTo(0, *frgShaderSrc);

        GLProgram *program = new GLProgram();
        cout << "program " << program->nodeId.toString() << endl;
        program->linkTo(0, *startNode);
        program->linkTo(1, *vtxShader);
        program->linkTo(2, *frgShader);

        GLPipeline *pipelineNode = new GLPipeline();
        cout << "pipelineNode " << pipelineNode->nodeId.toString() << endl;
        pipelineNode->linkTo(0, *program);

        ctx.addNode(pipelineNode);
        ctx.addNode(vtxShaderSrc);
        ctx.addNode(frgShaderSrc);
        ctx.addNode(program);
        ctx.setRoot(pipelineNode->nodeId);

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

        /*
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClearDepth(1.0f);
        */
    }

    Win::~Win()
    {
        if(renderer) {
            delete renderer;
            renderer = nullptr;
        }

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
        if(renderer) {
            renderer->didReshape(w, h);
        }
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
        if(!renderer) {
            Renderer* rend = new Renderer();
            setRenderer(rend);
            ctx.update();
        }

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
        if(renderer) {
            renderer->render();
            float fpsEMA = calculateFrameRate();
            stringstream fpsSStream;
            fpsSStream << "FPS: " << setprecision(2) << fpsEMA;
            setTitle(fpsSStream.str());
        } else {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glutSwapBuffers();
        }
        ctx.retract();
        needsDisplay = false;
        return true;
    }

}
