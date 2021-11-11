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

    class RealSense : public Node
    {
        DECLARE_TYPE

        public:
            static bool scanDevices();
            static void pausePipeline();
            static void resumePipeline();
            static void devicesChangedCallback(rs2::event_information&);

        protected:
            static rs2::pointcloud pointcloud;
            static rs2::device_list deviceList;
            static rs2::pipeline pipeline;
            static rs2::context ctx;
            static vector<RealSense *> nodes;
            static rs2::frameset frames;
            /*
            static size_t colorWidth, colorHeight;
            static HostBufferT<vec4<float>> colorBuffer;
            static size_t depthWidth, depthHeight;
            static HostBufferT<vec4<float>> depthBuffer;
            */
            static vec3<float> gyroData, accelData;
            static mutex telemLock;
            static bool initialized;
            static thread* telemThread;
            static bool framesAvailable;
            static atomic<bool> alive;

        public:
            RealSense();
            virtual ~RealSense();

            virtual void lock();
            virtual void unlock();

            bool available() const { return framesAvailable; }
            rs2::video_frame getColorFrame() const { return frames.get_color_frame(); }
            rs2::depth_frame getDepthFrame() const { return frames.get_depth_frame(); }

            void onDevicesChanged(const rs2_device_list &iRemoved, const rs2_device_list &iAdded);

            virtual bool update(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);
    };

    class DepthTelemetry : public DataSourceNode, public DataSourceT<pnt3<float>>
    {
        DECLARE_TYPE

        public:
            DepthTelemetry();

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual uint32_t size() const;
        
            virtual const void* rawMap() const;
            virtual void* rawMap();
    };
    
    class ColorTelemetry : public DataSourceNode, public DataSourceT<vec3<uint8_t>>
    {
        DECLARE_TYPE
        
        public:
            ColorTelemetry();

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

            virtual uint32_t size() const;
        
            virtual const void* rawMap() const;
            virtual void* rawMap();
    };

    class IMUTelemetry : public Node
    {
        DECLARE_TYPE
        
        public:
            IMUTelemetry();
    };

}

#endif
