#include "RealSense.hpp"

#include <iostream>
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

void _intelIsFuckingStupid(rs2::event_information& iInfo);

namespace mobo
{
    DERIVE_TYPE(RealSense, "26a52b11-915a-4337-b49f-3a60acfa3f64", {&Node::_type});
    DERIVE_TYPE(DepthTelemetry, "ac99dd2b-741b-4b86-bb8d-1dc9d0f85ae4", {&DataSourceNode::_type});
    DERIVE_TYPE(ColorTelemetry, "d19490fe-454a-4e40-8621-98d59d1cc1ea", {&DataSourceNode::_type});
    DERIVE_TYPE(IMUTelemetry, "bffd9cdc-9dc0-4128-b5ef-c2c4a6228cbf", {&Node::_type});

    rs2::pointcloud RealSense::pointcloud;
    rs2::device_list RealSense::deviceList;
    rs2::pipeline RealSense::pipeline;
    rs2::context RealSense::ctx;
    vector<RealSense*> RealSense::nodes;
    rs2::frameset frames;
    /*
    size_t colorWidth, RealSense::colorHeight;
    HostBufferT<vec4<float>> RealSense::colorBuffer;
    size_t depthWidth, depthHeight;
    HostBufferT<vec4<float>> RealSense::depthBuffer;
    */
    vec3<float> gyroData, RealSense::accelData;
    mutex RealSense::telemLock;
    bool RealSense::initialized;
    thread* RealSense::telemThread;
    bool RealSense::framesAvailable = false;
    atomic<bool> RealSense::alive;


    #define COLORDIMS 640, 480
    #define DEPTHDIMS 640, 480
    #define INFRAREDDIMS 640, 480

    #define COLORSIZE 640 * 480
    #define DEPTHSIZE 640 * 480
    #define INFRAREDSIZE 640 * 480

    RealSense::RealSense()
    : Node()
    {
        if(!initialized) {
            ctx.set_devices_changed_callback<>(RealSense::devicesChangedCallback);

            scanDevices();

            initialized = true;
        }

        if(!nodes.size())
            resumePipeline();

        nodes.push_back(this);
    }

    RealSense::~RealSense()
    {
        auto index = nodes.begin();
        while(index != nodes.end()) {
            if(*(index.base()) == this) {
                nodes.erase(index);
                break;
            }
        }

        if(!nodes.size()) {
            pausePipeline();
        }
    }

    void RealSense::lock()
    {
        telemLock.lock();
    }

    void RealSense::unlock()
    {
        telemLock.unlock();
    }

    bool RealSense::scanDevices()
    {
        rs2::config pipelineCfg;
        bool gyro = false;
        bool accel = false;
        bool streamsAvailable = false;
        deviceList = ctx.query_devices();

        for(auto device : deviceList) {
            cout << "Discovered: " << device.get_info(RS2_CAMERA_INFO_NAME) << endl;
            for(auto sensor : device.query_sensors()) {
                for(auto profile : sensor.get_stream_profiles()) {
                    rs2_format fmt = profile.format();
                    switch(profile.stream_type()) {
                        case RS2_STREAM_COLOR:
                            pipelineCfg.enable_stream(RS2_STREAM_COLOR, profile.stream_index());
                            // pipelineCfg.enable_stream(RS2_STREAM_COLOR, profile.stream_index(), COLORSIZE, RS2_FORMAT_RGB8, 30);
                            streamsAvailable = true;
                            break;
                        case RS2_STREAM_DEPTH:
                            pipelineCfg.enable_stream(RS2_STREAM_DEPTH);
                            // pipelineCfg.enable_stream(RS2_STREAM_DEPTH, -1, DEPTHSIZE, RS2_FORMAT_Z16, 30);
                            streamsAvailable = true;
                            break;
                        case RS2_STREAM_GYRO:
                            gyro = true;
                            if(accel) {
                                pipelineCfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F);
                                pipelineCfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F);
                                streamsAvailable = true;
                            }
                            break;
                        case RS2_STREAM_ACCEL:
                            accel = true;
                            if(gyro) {
                                pipelineCfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F);
                                pipelineCfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F);
                                streamsAvailable = true;
                            }
                            break;
                        case RS2_STREAM_INFRARED:
                            /*
                            _pipelineCfg.enable_stream(RS2_STREAM_INFRARED);
                            telemetry[3]->setFlags(Telem::AVAILABLE);
                            */
                            break;
                        case RS2_STREAM_FISHEYE:
                            break;
                        case RS2_STREAM_POSE:
                            break;
                    }
                }
            }
        }
        return streamsAvailable;
    }

    void RealSense::pausePipeline()
    {
        if(alive) {
            if(telemThread) {
                alive = false;
                telemThread->join();
                delete telemThread;
                telemThread = nullptr;
            }
            pipeline.stop();
        }
    }

    void RealSense::resumePipeline()
    {
        if(!alive) {
            pipeline.start();
            if(!telemThread) {
                telemThread = new thread(
                    [&](void) {
                        alive = true;
                        while(alive) {
                            telemLock.lock();
                            rs2::frameset frames;
                            auto startTime = steady_clock::now();
                            if(framesAvailable = pipeline.poll_for_frames(&frames)) {
                                //colorFrame = &frames.get_color_frame();
                                /*
                                if(colorFrame) {
                                    colorBuffer.resizeIfNeeded(colorFrame.get_width() * colorFrame.get_height());
                                    const vec3<uint8_t>* src = static_cast<const vec3<uint8_t>*>(colorFrame.get_data());
                                    vec4<float>* dst = static_cast<vec4<float>*>(colorBuffer.rawMap());
                                    size_t i = colorBuffer.size();
                                    while(i--) {
                                        size_t j = 3; dst[i][j] = 1.0;
                                        while(j--) dst[i][j] = src[i][j];
                                    }
                                    colorBuffer.unmap();
                                    colorWidth = colorFrame.get_width();
                                    colorHeight = colorFrame.get_height();
                                }
                                */
                                //depthFrame = &frames.get_depth_frame();
                                /*
                                if(depthFrame) {
                                    depthBuffer.resizeIfNeeded(depthFrame.get_width() * colorFrame.get_height());
                                    const rs2::points p = pointcloud.calculate(depthFrame);
                                    const vec3<float>* src = static_cast<const vec3<float>*>(p.get_data());
                                    vec4<float>* dst = static_cast<vec4<float>*>(depthBuffer.rawMap());
                                    size_t i = depthBuffer.size();
                                    while(i--) {
                                        size_t j = 3; dst[i][j] = 1.0;
                                        while(j--) dst[i][j] = src[i][j];
                                    }
                                    depthBuffer.unmap();
                                    depthWidth = depthFrame.get_width();
                                    depthHeight = depthFrame.get_height();
                                }
                                */
                                bool gyro = false;
                                bool accel = false;
                                for(auto frame : frames) {
                                    if(frame.is<rs2::motion_frame>()) {
                                        rs2::motion_frame motionFrame = frame.as<rs2::motion_frame>();
                                        rs2::motion_stream_profile profile = motionFrame.get_profile().as<rs2::motion_stream_profile>();
                                        if(profile.stream_type() == RS2_STREAM_GYRO) {
                                            gyro = true;
                                            rs2_vector v = motionFrame.get_motion_data();
                                            gyroData = vec3<float>(v.x, v.y, v.z);
                                        }
                                        if(profile.stream_type() == RS2_STREAM_ACCEL) {
                                            accel = true;
                                            rs2_vector v = motionFrame.get_motion_data();
                                            accelData = vec3<float>(v.x, v.y, v.z);
                                        }
                                        if(gyro && accel) {
                                        }
                                    }
                                }
                            }
                            telemLock.unlock();
                            auto elapsed = steady_clock::now() - startTime;
                            this_thread::sleep_for(microseconds(33333) - elapsed);
                        }
                        return nullptr;
                    }
                );
            }
        }
    }

    void RealSense::devicesChangedCallback(rs2::event_information& iInfo)
    {
        pausePipeline();

        const rs2::device_list newDevices(iInfo.get_new_devices());
        
        /*
        const rs2::device_list existingDevices(ctx.query_devices());
        for(auto oldDevice : deviceList) {
            if(!existingDevices.contains(oldDevice)) {
                cout << "detached: " << oldDevice.get_info(RS2_CAMERA_INFO_NAME) << endl;
            }
        }
        */

        if(newDevices.size() == 0) {
            cout << "Realsense devices detached.";
        } else {
            cout << "Realsense devices attached:";
            bool first = true;
            for(auto newDevice : newDevices) {
                cout << (first ? " " : ", ") << newDevice.get_info(RS2_CAMERA_INFO_NAME);
                first = false;
            }
            cout << ".";
        }

        cout << " Reconfiguring.\n";
        if(scanDevices())
            resumePipeline();
    }

    bool RealSense::update(Context& iCtx)
    {
   
        return true;
    }

    bool RealSense::submit(Context& iCtx)
    {
        lock();
        /*
        if(outputTelems[0]->testFlags(Telem::AVAILABLE)) {
        }
        if(outputTelems[1]->testFlags(Telem::AVAILABLE)) {
        }
        if(outputTelems[2]->testFlags(Telem::AVAILABLE)) {
        }
        */
        return true;
    }

    bool RealSense::retract(Context& iCtx)
    {
        unlock();
        return true;
    }

    DepthTelemetry::DepthTelemetry()
    : DataSourceNode()
    {
        addInput(RealSense::_type);
    }

    uint32_t DepthTelemetry::size() const
    {
        const RealSense* rs = getInput<RealSense>(0);
        if(rs && rs->available()) {
            rs2::depth_frame df = rs->getDepthFrame();
            return df.get_width() * df.get_height();
        }
        return 0;
    }

    const void* DepthTelemetry::rawMap() const
    {
        const RealSense* rs = getInput<RealSense>(0);
        if(rs && rs->available()) {
            rs2::depth_frame df = rs->getDepthFrame();
            return static_cast<const void*>(df.get_data());
        }
        return nullptr;
    }

    void* DepthTelemetry::rawMap()
    {
        return nullptr;
    }

    ColorTelemetry::ColorTelemetry()
    : DataSourceNode()
    {
        addInput(RealSense::_type);
    }

    uint32_t ColorTelemetry::size() const
    {
        const RealSense* rs = getInput<RealSense>(0);
        if(rs && rs->available()) {
            rs2::video_frame cf = rs->getColorFrame();
            return cf.get_width() * cf.get_height();
        }
    }

    const void* ColorTelemetry::rawMap() const
    {
        const RealSense* rs = getInput<RealSense>(0);
        if(rs && rs->available()) {
            rs2::video_frame cf = rs->getColorFrame();
            return static_cast<const void*>(cf.get_data());
        }
        return nullptr;
    }
    
    void* ColorTelemetry::rawMap()
    {
        return nullptr;
    }
}

void _intelIsFuckingStupid(rs2::event_information& iInfo)
{
    mobo::RealSense::devicesChangedCallback(iInfo);
}

