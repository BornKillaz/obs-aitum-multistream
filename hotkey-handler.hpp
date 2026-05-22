#pragma once

#include <obs.h>
#include <string>
#include <vector>
#include <map>

class HotkeyHandler {
public:
	HotkeyHandler();
	~HotkeyHandler();

	// Register hotkeys for main stream and output streams
	void RegisterHotkeys(const std::vector<std::string>& output_names);
	
	// Unregister all hotkeys
	void UnregisterHotkeys();
	
	// Set callbacks
	void SetToggleMainStreamCallback(std::function<void()> callback);
	void SetToggleOutputCallback(const std::string& output_name, std::function<void()> callback);
	void SetStartOutputCallback(const std::string& output_name, std::function<void()> callback);
	void SetStopOutputCallback(const std::string& output_name, std::function<void()> callback);

private:
	struct OutputHotkey {
		obs_hotkey_id toggle_id;
		obs_hotkey_id start_id;
		obs_hotkey_id stop_id;
		std::function<void()> toggle_callback;
		std::function<void()> start_callback;
		std::function<void()> stop_callback;
	};

	obs_hotkey_id main_stream_toggle_id;
	std::function<void()> main_stream_callback;
	std::map<std::string, OutputHotkey> output_hotkeys;

	// Static callbacks for OBS
	static void MainStreamHotkeyCallback(void* data, obs_hotkey_id id, obs_hotkey_t* hotkey, bool pressed);
	static void OutputToggleHotkeyCallback(void* data, obs_hotkey_id id, obs_hotkey_t* hotkey, bool pressed);
	static void OutputStartHotkeyCallback(void* data, obs_hotkey_id id, obs_hotkey_t* hotkey, bool pressed);
	static void OutputStopHotkeyCallback(void* data, obs_hotkey_id id, obs_hotkey_t* hotkey, bool pressed);
};
