#include <QObject>
#include "audio.h"

using std::weak_ptr;

Audio::Audio(weak_ptr<Room> room)
 : m_modAudio(nullptr),
   m_room(room),
   m_isOpen(false)
{
}

Audio::~Audio()
{
}

bool Audio::init(tee3::avd::IRoom* room)
{
	m_modAudio = tee3::avd::IMAudio::getAudio(room);
	m_modAudio->setListener(this);
	return true;
}

bool Audio::uninit()
{
	if (!m_modAudio)
		return false;

	close();
	m_modAudio->setListener(nullptr);
	m_modAudio = nullptr;
	return true;
}

bool Audio::open()
{
	Result r = m_modAudio->openMicrophone();
	if (RT_SUCCEEDED(r))
		m_isOpen = true;
	return RT_SUCCEEDED(r);
}

bool Audio::close()
{
	if (!m_isOpen)
		return false;
	return RT_SUCCEEDED(m_modAudio->closeMicrophone());
}

void Audio::onMicrophoneStatusNotify(tee3::avd::MicrophoneStatus status, const tee3::UserId& fromUserId)
{
}

void Audio::onAudioLevelMonitorNotify(const tee3::avd::AudioInfo& info)
{
}

void Audio::onOpenMicrophoneResult(Result result)
{
}

void Audio::onCloseMicrophoneResult(Result result)
{
}
