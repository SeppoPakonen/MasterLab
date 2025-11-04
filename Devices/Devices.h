#ifndef _Devices_Devices_h_
#define _Devices_Devices_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <plugin/PluginManager/PluginManager.h>
#include "IOMatrixService.h"
#include "RoutingRepository.h"

using namespace Upp;

namespace Devices {

// Device management functionality
class DeviceManager {
public:
    DeviceManager();
    void Initialize();
    void Shutdown();
};

// Audio device management
class AudioDeviceManager {
public:
    AudioDeviceManager();
    void EnumerateDevices();
    void SelectDevice(int index);
    bool IsInitialized() const { return initialized; }
    
private:
    bool initialized;
    Vector<String> deviceList;
};

// MIDI device management
class MidiDeviceManager {
public:
    MidiDeviceManager();
    void EnumerateDevices();
    void SelectDevice(int index);
    bool IsInitialized() const { return initialized; }
    
private:
    bool initialized;
    Vector<String> inputDevices;
    Vector<String> outputDevices;
};

// Plugin management
class PluginManager {
public:
    PluginManager();
    void ScanPlugins();
    void LoadPlugin(const String& path);
    void UnloadPlugin(const String& name);
    
private:
    Vector<String> pluginPaths;
    Vector<String> loadedPlugins;
};

// ReWire host functionality
class ReWireHost {
public:
    ReWireHost();
    void ConnectToHost(const String& hostName);
    bool IsConnected() const { return connected; }
    
private:
    bool connected;
    String currentHost;
};

// Video device management
class VideoDevice {
public:
    VideoDevice();
    void EnumerateDevices();
    void SelectDevice(int index);
    bool IsInitialized() const { return initialized; }
    
private:
    bool initialized;
    Vector<String> deviceList;
};

// Additional IOMatrixService functions (if needed)
// IOMatrixService and related structures are already defined in IOMatrixService.h
// which is included above

}

#endif

#endif