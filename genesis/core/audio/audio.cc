#include "audio.h"

#include <core/log/log.h>
#define FMOD_ERROR_CHECK(x) \
  if ((x) != FMOD_OK) CORE_LOG_ERROR("fmod error.{}, {}", __FILE__, __LINE__);
namespace genesis {
FMOD::Studio::System* AudioManager::system = nullptr;
std::unordered_map<std::string, FMOD::Studio::EventInstance*> AudioManager::events;
std::unordered_map<std::filesystem::path, FMOD::Studio::Bank*> AudioManager::banks;

void AudioManager::Init() {
  FMOD_ERROR_CHECK(FMOD::Studio::System::create(&system));
  FMOD_ERROR_CHECK(
      system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, nullptr));
  FMOD::System* coreSystem = nullptr;
  system->getCoreSystem(&coreSystem);
  coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
}

void AudioManager::Uninit() { FMOD_ERROR_CHECK(system->release()); }

void AudioManager::Update() { FMOD_ERROR_CHECK(system->update()); }

void AudioManager::LoadBankFile(const std::filesystem::path& path) {
  FMOD::Studio::Bank* bank = nullptr;
  FMOD_ERROR_CHECK(system->loadBankFile(path.string().c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
  banks[path] = bank;
}

void AudioManager::UnloadBankFile(const std::filesystem::path& path) {
  FMOD_ERROR_CHECK(banks[path]->unload());
  banks.erase(path);
}

void AudioManager::LoadEvent(const std::string& event_name) {
  FMOD::Studio::EventDescription* event_description = nullptr;
  system->getEvent(event_name.c_str(), &event_description);
  FMOD::Studio::EventInstance* event_instance = nullptr;
  event_description->createInstance(&event_instance);
  events[event_name] = event_instance;
}
void AudioManager::ReleaseEvent(const std::string& event_name) { FMOD_ERROR_CHECK(events[event_name]->release()); }

void AudioManager::SetEventParameter(const std::string& event_name, const std::string& parameter_name,
                                     const float value) {
  FMOD_ERROR_CHECK(events[event_name]->setParameterByName(parameter_name.c_str(), value));
}

void AudioManager::StartEvent(const std::string& event_name) { FMOD_ERROR_CHECK(events[event_name]->start()); }
void AudioManager::StopEvent(const std::string& event_name, const FMOD_STUDIO_STOP_MODE& mode) {
  FMOD_ERROR_CHECK(events[event_name]->stop(mode));
}
void AudioManager::SetEventAttribute(const std::string& event_name, const FMOD_3D_ATTRIBUTES& attribute) {
  FMOD_ERROR_CHECK(events[event_name]->set3DAttributes(&attribute));
}
void AudioManager::SetListenerAttribute(const int listener, const FMOD_3D_ATTRIBUTES& attribute) {
  FMOD_ERROR_CHECK(system->setListenerAttributes(listener, &attribute));
}

}  // namespace genesis