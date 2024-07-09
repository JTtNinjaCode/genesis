#pragma once
#include <filesystem>
#include <fmod_studio.hpp>
#include <unordered_map>

namespace genesis {
class AudioManager {
 public:
  static void Init();
  static void Uninit();
  static void Update();

  static void LoadBankFile(const std::filesystem::path& path);
  static void UnloadBankFile(const std::filesystem::path& path);
  static void LoadEvent(const std::string& event_name);
  static void ReleaseEvent(const std::string& event_name);
  static void StartEvent(const std::string& event_name);
  static void StopEvent(const std::string& event_name, const FMOD_STUDIO_STOP_MODE& mode);
  static void SetEventParameter(const std::string& event_name, const std::string& parameter_name, const float value);
  static void SetEventAttribute(const std::string& event_name, const FMOD_3D_ATTRIBUTES& attribute);
  static void SetListenerAttribute(const int listener, const FMOD_3D_ATTRIBUTES& attribute);

 private:
  static FMOD::Studio::System* system;
  static std::unordered_map<std::string, FMOD::Studio::EventInstance*> events;
  static std::unordered_map<std::filesystem::path, FMOD::Studio::Bank*> banks;
};
}  // namespace genesis