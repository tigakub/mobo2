#ifndef __EVENTHANDLER_HPP__
#define __EVENTHANDLER_HPP__

#include <cstdint> // for size_t

using namespace std;

namespace mobo
{
    typedef struct Event
    {
        enum {
            IDLE = 100,
            DIDMOVE,
            DIDRESHAPE,
            WILLCLOSE,
            KEYDOWN,
            KEYUP,
            SPECIALDOWN,
            SPECIALUP,
            MOUSEMOVE,
            MOUSEDOWN,
            MOUSEUP,
            MOUSEDRAG,
            MOUSEENTERED,
            MOUSEEXITED,
            RENDER,
            RENDEROVERLAY
        };

        Event(int iId, size_t iK = 0, int iX = 0, int iY = 0, void* iData = nullptr)
        : id(iId), k(iK), x(iX), y(iY), data(iData) { }

        int id;
        size_t k;
        int x, y;
        void* data;
    } Event;

    class EventHandler
    {
        public:
            EventHandler() { }
            virtual ~EventHandler() { } 

            virtual bool dispatchEvent(const Event &);

            virtual bool idle() { return true; }
            virtual bool didMove(int x, int y) { return true; }
            virtual bool didReshape(int w, int h) { return true; }
            virtual bool willClose() { return true; }
            virtual bool keyDown(unsigned char k, int x, int y) { return true; }
            virtual bool keyUp(unsigned char k, int x, int y) { return true; }
            virtual bool specialDown(int k, int x, int y) { return true; }
            virtual bool specialUp(int k, int x, int y) { return true; }
            virtual bool mouseMove(int x, int y) { return true; }
            virtual bool mouseDown(size_t b, int x, int y) { return true; }
            virtual bool mouseUp(size_t b, int x, int y) { return true; }
            virtual bool mouseDrag(int x, int y) { return true; }
            virtual bool mouseEntered() { return true; }
            virtual bool mouseExited() { return true; }

            virtual bool render() { return true; }
            virtual bool renderOverlay() { return true; }
    };
}

#endif
