#ifndef __REALSENSE_HPP__
#define __REALSENSE_HPP__

#include "DataSourceNode.hpp"
#include "Buffer.hpp"
#include "Type.hpp"
#include "Math.hpp"
#include "Buffer.hpp"
#include "HostBufferNode.hpp"

#include <librealsense2/rs.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

namespace mobo
{

    class RealSense : public Node, public MeshSegmentation
    {
        DECLARE_TYPE

        public:
            static bool scanDevices();
            static void pausePipeline();
            static void resumePipeline();
            static void devicesChangedCallback(rs2::event_information&);

            static void handleFrames();

            static rs2::pointcloud pointcloud;
            static rs2::device_list deviceList;
            static rs2::pipeline pipeline;
            static rs2::context ctx;
            static vector<RealSense *> nodes;
            static rs2::frameset frames;
            
            static size_t colorWidth, colorHeight;
            static HostBufferT<pnt4<uint8_t>> colorBuffer;
            static size_t depthWidth, depthHeight;
            static HostBufferT<pnt4<float>> depthBuffer;
            static vector<MeshSegmentation::Segment> segmentation;
            
            static vec3<float> gyroData, accelData;
            static mutex telemLock, nodeFlagsLock;
            static bool initialized;
            static thread* telemThread;
            static bool framesAvailable;
            static atomic_bool alive;

        public:
            RealSense();
            virtual ~RealSense();

            virtual void setNodeFlags(uint64_t iFlags) { nodeFlagsLock.lock(); nodeFlags.set(iFlags); nodeFlagsLock.unlock(); }
            virtual void clearNodeFlags(uint64_t iFlags) { nodeFlagsLock.lock(); nodeFlags.clear(iFlags); nodeFlagsLock.unlock(); }
            virtual uint64_t testNodeFlags(uint64_t iFlags) const { uint64_t flags; nodeFlagsLock.lock(); flags = nodeFlags.test(iFlags); nodeFlagsLock.unlock(); return flags; }

            virtual void lock();
            virtual void unlock();

            bool available() const { return framesAvailable; }
            rs2::video_frame getColorFrame() const { return frames.get_color_frame(); }
            rs2::depth_frame getDepthFrame() const { return frames.get_depth_frame(); }

            const vector<MeshSegmentation::Segment>& getMeshSegmentation() const { return segmentation; }

            void onDevicesChanged(const rs2_device_list &iRemoved, const rs2_device_list &iAdded);

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);
    };

    class DepthTelemetry : public FrameSourceNode, public DataSourceT<pnt4<float>>
    {
        DECLARE_TYPE

        public:
            DepthTelemetry();
            // virtual ~DepthTelemetry();
            /*
            virtual bool submit(Context& iCtx) { return true; }
            virtual bool retract(Context& iCtx) { return true; }
            */
            virtual bool update(Context& iCtx);
            virtual size_t size() const;
        
            virtual const void* rawMap() const;
            virtual void* rawMap();

        protected:
            virtual void setSize(size_t, bool) { } 
    };
    
    class ColorTelemetry : public FrameSourceNode, public DataSourceT<pnt4<uint8_t>>
    {
        DECLARE_TYPE
        
        public:
            ColorTelemetry();
            // virtual ~ColorTelemetry();
            /*
            virtual bool submit(Context& iCtx) { return true; }
            virtual bool retract(Context& iCtx) { return true; }
            */
            virtual bool update(Context& iCtx);
            virtual size_t size() const;
        
            virtual const void* rawMap() const;
            virtual void* rawMap();

        protected:
            virtual void setSize(size_t, bool) { } 
    };

    class IMUTelemetry : public Node
    {
        DECLARE_TYPE
        
        public:
            IMUTelemetry();
            virtual ~IMUTelemetry();
    };

}

#endif
