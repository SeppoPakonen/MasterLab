#include "RoutingRepository.h"

namespace Devices {

RoutingRepository::RoutingRepository() {
    BuildIOLists();
    LoadDefaultPresets();
}

RoutingRepository::~RoutingRepository() {
    // Clean up
}

Vector<String> RoutingRepository::GetAvailableSources() const {
    return availableSources;
}

Vector<String> RoutingRepository::GetAvailableDestinations() const {
    return availableDestinations;
}

void RoutingRepository::RefreshIO() {
    BuildIOLists();
}

bool RoutingRepository::LoadPreset(const String& presetName) {
    // Load a routing preset by name
    // In a real implementation, this would load from a file/database
    if(find(availablePresets, presetName) >= 0) {
        // Load the preset and update availableSources/availableDestinations
        return true;
    }
    return false;
}

bool RoutingRepository::SavePreset(const String& presetName) {
    // Save a routing preset by name
    // In a real implementation, this would save to a file/database
    if(find(availablePresets, presetName) < 0) {
        availablePresets.Add(presetName);
    }
    return true;
}

Vector<String> RoutingRepository::GetPresets() const {
    return availablePresets;
}

bool RoutingRepository::ApplyPreset(const String& presetName) {
    // Apply preset routing configuration
    return LoadPreset(presetName);
}

Vector<String> RoutingRepository::GetAvailablePlugins() const {
    Vector<String> plugins;
    // In a real implementation, this would query the PluginManager
    plugins.Add("Plugin A");
    plugins.Add("Plugin B");
    plugins.Add("Plugin C");
    return plugins;
}

Vector<String> RoutingRepository::GetAvailableAudioTracks() const {
    Vector<String> tracks;
    // In a real implementation, this would query the project
    tracks.Add("Audio Track 1");
    tracks.Add("Audio Track 2");
    tracks.Add("Audio Track 3");
    return tracks;
}

Vector<String> RoutingRepository::GetAvailableMIDITracks() const {
    Vector<String> tracks;
    // In a real implementation, this would query the project
    tracks.Add("MIDI Track 1");
    tracks.Add("MIDI Track 2");
    return tracks;
}

Vector<String> RoutingRepository::GetAvailableHardwarePorts() const {
    Vector<String> ports;
    // In a real implementation, this would query the audio hardware
    ports.Add("Audio Input 1-2");
    ports.Add("Audio Output 1-2");
    ports.Add("MIDI Input");
    ports.Add("MIDI Output");
    return ports;
}

String RoutingRepository::GetConfigurationAsJson() const {
    // In a real implementation, this would serialize the current routing configuration to JSON
    return String("[{\"source\": \"Audio Input 1-2\", \"destination\": \"Audio Track 1\", \"channel\": 1}]");
}

bool RoutingRepository::LoadConfigurationFromJson(const String& jsonStr) {
    // In a real implementation, this would deserialize the routing configuration from JSON
    return true;
}

void RoutingRepository::BuildIOLists() {
    availableSources.Clear();
    availableDestinations.Clear();
    
    // Add plugins to both sources and destinations
    Vector<String> plugins = GetAvailablePlugins();
    for(const String& plugin : plugins) {
        availableSources.Add(plugin);
        availableDestinations.Add(plugin);
    }
    
    // Add audio tracks
    Vector<String> audioTracks = GetAvailableAudioTracks();
    for(const String& track : audioTracks) {
        availableSources.Add(track);
        availableDestinations.Add(track);
    }
    
    // Add MIDI tracks
    Vector<String> midiTracks = GetAvailableMIDITracks();
    for(const String& track : midiTracks) {
        availableSources.Add(track);
        availableDestinations.Add(track);
    }
    
    // Add hardware ports
    Vector<String> hwPorts = GetAvailableHardwarePorts();
    for(const String& port : hwPorts) {
        availableSources.Add(port);
        availableDestinations.Add(port);
    }
}

void RoutingRepository::LoadDefaultPresets() {
    availablePresets.Clear();
    availablePresets.Add("Default");
    availablePresets.Add("Stereo Out");
    availablePresets.Add("Multi-Channel");
    availablePresets.Add("MIDI Only");
}

}