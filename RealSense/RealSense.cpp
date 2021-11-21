#include "RealSense.hpp"
#include "Math.hpp"

#include <iostream>
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

void _intelIsFuckingStupid(rs2::event_information& iInfo);

namespace mobo
{
    DERIVE_TYPE(RealSense, "26a52b11-915a-4337-b49f-3a60acfa3f64", {&Node::_type});
    DERIVE_TYPE(DepthTelemetry, "ac99dd2b-741b-4b86-bb8d-1dc9d0f85ae4", {&FrameSourceNode::_type});
    DERIVE_TYPE(ColorTelemetry, "d19490fe-454a-4e40-8621-98d59d1cc1ea", {&FrameSourceNode::_type});
    DERIVE_TYPE(IMUTelemetry, "bffd9cdc-9dc0-4128-b5ef-c2c4a6228cbf", {&Node::_type});

    rs2::pointcloud RealSense::pointcloud;
    rs2::device_list RealSense::deviceList;
    rs2::pipeline RealSense::pipeline;
    rs2::context RealSense::ctx;
    vector<RealSense*> RealSense::nodes;
    rs2::frameset RealSense::frames;
    
    size_t RealSense::colorWidth = 0, RealSense::colorHeight = 0;
    HostBufferT<pnt4<uint8_t>> RealSense::colorBuffer;

    size_t RealSense::depthWidth = 0, RealSense::depthHeight = 0;
    HostBufferT<pnt4<float>> RealSense::depthBuffer;
    vector<MeshSegmentation::Segment> RealSense::segmentation;
    
    vec3<float> RealSense::gyroData, RealSense::accelData;
    mutex RealSense::telemLock, RealSense::nodeFlagsLock;
    bool RealSense::initialized = false;
    thread* RealSense::telemThread;
    bool RealSense::framesAvailable = false;
    atomic_bool RealSense::alive;

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
        //cout << "RealSense::lock()" << endl;
        telemLock.lock();
    }

    void RealSense::unlock()
    {
        telemLock.unlock();
        //cout << "RealSense::unlock()" << endl;
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
                            pipelineCfg.enable_stream(RS2_STREAM_COLOR, profile.stream_index(), RS2_FORMAT_RGB8, 30);
                            streamsAvailable = true;
                            break;
                        case RS2_STREAM_DEPTH:
                            pipelineCfg.enable_stream(RS2_STREAM_DEPTH, profile.stream_index(), RS2_FORMAT_Z16, 30);
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

    #define USE_NATIVE_DEPTH true

    #if USE_NATIVE_DEPTH
    bool depthInRange(uint16_t iDepth)
    {
        return 0 < iDepth;
    }
    #else
    bool depthInRange(float iDepth)
    {
        return 0.0 < iDepth;
    }
    #endif

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
                            auto startTime = steady_clock::now();
                            if(framesAvailable = pipeline.poll_for_frames(&frames)) {
                                for(auto node : nodes) {
                                    node->setNodeFlags(UPDATE_FLAG);
                                }
                                {
                                    auto colorFrame = frames.get_color_frame();
                                    colorWidth = colorFrame.get_width();
                                    colorHeight = colorFrame.get_height();
                                    if(colorWidth == -1) {
                                        colorWidth = 0;
                                    }
                                    if(colorHeight == -1) {
                                        colorHeight = 0;
                                    }
                                    colorBuffer.resizeIfNeeded(colorWidth * colorHeight);
                                    auto src = static_cast<const vec3<uint8_t>*>(colorFrame.get_data());
                                    auto dst = static_cast<pnt4<uint8_t>*>(colorBuffer.rawMap());
                                    size_t i = colorBuffer.size();
                                    while(i--) {
                                        dst[i][0] = src[i][0];
                                        dst[i][1] = src[i][1];
                                        dst[i][2] = src[i][2];
                                        dst[i][3] = 255;
                                    }
                                    colorBuffer.unmap();
                                }
                                {
                                    auto depthFrame = frames.get_depth_frame();
                                    depthWidth = depthFrame.get_width();
                                    depthHeight = depthFrame.get_height();

                                    if(depthWidth && depthHeight) {
                                        depthBuffer.resizeIfNeeded(depthWidth * depthHeight);

                                        auto p = pointcloud.calculate(depthFrame);
                                        auto src = (const vec3<float>*) p.get_vertices();
                                        auto dst = static_cast<pnt4<float>*>(depthBuffer.rawMap());
                                        size_t i = p.size();
                                        while(i--) {
                                            dst[i] = src[i];
                                        }
                                        
                                        size_t hCrop = 0;
                                        size_t vCrop = 0;

                                        size_t stripCount = depthHeight - 1;
                                        size_t stripIndexCount = depthWidth << 1;
                                        segmentation.clear();
                                        bool inSegment = false;
                                        Segment segment;
                                        size_t n;

                                        #if USE_NATIVE_DEPTH
                                        const uint16_t* depthData = static_cast<const uint16_t*>(depthFrame.get_data());
                                        #endif

                                        for(size_t j = vCrop; j < stripCount-(vCrop << 1); j++) {
                                            size_t ro0 = j * depthWidth + hCrop;
                                            size_t ro1 = ro0 + depthWidth;
                                            i = depthWidth - (hCrop << 1);
                                            n = j * stripIndexCount + (hCrop << 1);
                                            while(i--) {
                                                #if USE_NATIVE_DEPTH
                                                // cout << "ro0: " << depthData[ro0 + i] << ", ro1: " << depthData[ro1 + i] << endl;
                                                uint16_t depthValue0 = depthData[ro0];
                                                uint16_t depthValue1 = depthData[ro1];
                                                #else
                                                float depthValue0 = dst[ro0][2];
                                                float depthValue1 = dst[ro1][2];
                                                #endif
                                                if(depthInRange(depthValue0)) {
                                                    segment.count++;
                                                    if(depthInRange(depthValue1)) {
                                                        segment.count++;
                                                        if(!inSegment) {
                                                            segment.offset = n;
                                                            segment.count = 2;
                                                            inSegment = true;
                                                        }
                                                    } else {
                                                        if(inSegment) {
                                                            if(segment.count > 4) {
                                                                segment.count &= (~1);
                                                                segmentation.push_back(segment);
                                                            }
                                                            inSegment = false;
                                                        }
                                                    }
                                                } else {
                                                    if(inSegment) {
                                                        if(segment.count > 4) {
                                                            segment.count &= (~1);
                                                            segmentation.push_back(segment);
                                                        }
                                                        inSegment = false;
                                                    }
                                                }
                                                ro0++;
                                                ro1++;
                                                n += 2;
                                            }
                                            if(inSegment) {
                                                if(segment.count > 4) {
                                                    segment.count &= (~1);
                                                    segmentation.push_back(segment);
                                                }
                                                inSegment = false;
                                            }
                                        }

                                        /*
                                        cout << "[";
                                        for(i = 0; i < depthBuffer.size(); i++) {
                                            cout << (i ? ", " : "") << dst[i];
                                        }
                                        cout << "]" << endl;
                                        */
                                        depthBuffer.unmap();
                                    }
                                }
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
                            auto sleepTime = microseconds(33333) - (steady_clock::now() - startTime);
                            if(sleepTime > microseconds(0)) {
                                this_thread::sleep_for(sleepTime);
                            }
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
        // cout << "RealSense::update()" << endl;
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
    : FrameSourceNode(), DataSourceT<pnt4<float>>()
    {
        addInput(RealSense::_type);
    }
    /*
    DepthTelemetry::~DepthTelemetry()
    { }
    */

    bool DepthTelemetry::update(Context& iCtx)
    {
        // cout << "depthWidth: " << RealSense::depthWidth << ", depthHeight: " << RealSense::depthHeight<< endl;
        imgWidth = RealSense::depthWidth;
        imgHeight = RealSense::depthHeight;
        return true;
    }

    size_t DepthTelemetry::size() const
    {
        return imgWidth * imgHeight;
    }

    const void* DepthTelemetry::rawMap() const
    {
        //cout << "DepthTelemetry::rawMap() const" << endl;
        return RealSense::depthBuffer.rawMap();
    }

    void* DepthTelemetry::rawMap()
    {
        //cout << "DepthTelemetry::rawMap()" << endl;
        return RealSense::depthBuffer.rawMap();
    }

    ColorTelemetry::ColorTelemetry()
    : FrameSourceNode(), DataSourceT<pnt4<uint8_t>>()
    {
        addInput(RealSense::_type);
    }
    /*
    ColorTelemetry::~ColorTelemetry()
    { }
    */

    bool ColorTelemetry::update(Context& iCtx)
    {
        imgWidth = RealSense::colorWidth;
        imgHeight = RealSense::colorHeight;
        return true;
    }

    size_t ColorTelemetry::size() const
    {
        return imgWidth * imgHeight;
    }

    const void* ColorTelemetry::rawMap() const
    {
        return RealSense::colorBuffer.rawMap();
    }
    
    void* ColorTelemetry::rawMap()
    {
        return RealSense::colorBuffer.rawMap();
    }

    IMUTelemetry::IMUTelemetry()
    : Node()
    { }

    IMUTelemetry::~IMUTelemetry()
    { }
}

void _intelIsFuckingStupid(rs2::event_information& iInfo)
{
    mobo::RealSense::devicesChangedCallback(iInfo);
}

