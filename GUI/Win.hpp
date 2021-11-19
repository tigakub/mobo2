#ifndef __WIN_HPP__
#define __WIN_HPP__

#include "App.hpp"
#include "MovingAverage.hpp"

#include "GLContext.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace mobo
{
    class Win : public EventHandler
    {
        public:
            enum {
                PRIMARY_BUTTON = 1,
                SECONDARY_BUTTON = PRIMARY_BUTTON << 1,
                TERTIARY_BUTTON = SECONDARY_BUTTON << 1
            };

            Win(App&);
            virtual ~Win();

            virtual void setTitle(const string& iTitle);

            virtual bool dispatchEvent(const Event &e) {
                return EventHandler::dispatchEvent(e) || app.dispatchEvent(e);
            }

            virtual bool didMove(int x, int y) { return true; }
            virtual bool didReshape(int w, int h);
            virtual bool willClose();
            virtual bool keyDown(unsigned char k, int x, int y);
            virtual bool keyUp(unsigned char k, int x, int y);
            virtual bool specialDown(int k, int x, int y) { return false; }
            virtual bool specialUp(int k, int x, int y) { return false; }
            virtual bool mouseMove(int x, int y) { return true; }
            virtual bool mouseDown(size_t b, int x, int y) { return true; }
            virtual bool mouseUp(size_t b, int x, int y) { return true; }
            virtual bool mouseDrag(int x, int y) { return true; }
            virtual bool mouseEntered() { return true; }
            virtual bool mouseExited() { return true; }

            void postDisplay();
            virtual bool render();
            virtual bool renderOverlay() { return true; }

            virtual float calculateFrameRate();
            
            App& app;
            int winId;
            size_t mouseButtonState;
            float needsDisplay;
            time_point<steady_clock> timestamp;
            float emaWindow;
            float fpsWMA;
            float fpsEMA;
            MovingAverage fpsAVG;

            GLContext ctx;
    };

}

#endif
