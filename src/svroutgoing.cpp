#include "svroutgoing.h"
#include "common.h"

using namespace tee3;
using namespace tee3::avd;

using std::make_shared;

SvrOutgoing::SvrOutgoing(const QString& roomId, QWidget *parent)
 : ExampleBase(roomId, parent),
   m_modOutgoing(nullptr)
{
	m_ui.setupUi(this);
	init(m_ui);
	connect(m_ui.startButton, &QPushButton::clicked, this, &SvrOutgoing::start);
}

SvrOutgoing::~SvrOutgoing()
{
	if (m_modOutgoing) {
		m_modOutgoing->setListener(nullptr);
		m_modOutgoing->release();
		m_modOutgoing = nullptr;
	}
}

void SvrOutgoing::start(bool status)
{
	if (status) {
		if (!createUser()) {
			m_ui.startButton->setChecked(false);
			return;
		}
		startTimingTimer(m_ui);
		m_ui.startButton->setText(Utf8Str("Í£Ö¹"));
	}
	else {
		deleteUser();
		stopTimingTimer();
		m_ui.startButton->setText(Utf8Str("¿ªÊ¼"));
	}
}

bool SvrOutgoing::createUser()
{
	// SvrOutgoing step 2: get outgoing module, set listener, create outgoing user
	if (!m_modOutgoing) {
		m_modOutgoing = IAVDOutgoing::getOutgoing(IAVDEngine::Instance());
		m_modOutgoing->setListener(this);
	}

	uint32 callid = 0;

	User user;
	user.userId = "1009";
	user.userName = "demo out";

	String addr = "rtsp://192.168.1.121:554/hikvision://192.168.1.121:8000:0:0";
	String name = "admin";
	String pass = "Hik12345";
	Result r = m_modOutgoing->createOutgoingUser(callid, m_roomId.toStdString(), user, addr, name, pass);
	if (RT_FAILED(r)) {
		CONSOLE_LOG_CRITICAL(QString("Create outgoing failed: %1.").arg(Engine::getErrorMessage(r).c_str()));
		return false;
	}

	m_user = user;
	m_userAddress = addr;

	return true;
}

void SvrOutgoing::deleteUser()
{
	if (!m_modOutgoing) {
		CONSOLE_LOG_CRITICAL("Not init.");
		return;
	}

	CONSOLE_LOG(QString("Deleting outgoing user, room:%1 user:%2 addr:%3.").arg(m_roomId).arg(m_user.userId.c_str()).arg(m_userAddress.c_str()));
	uint32 callid = 0;
	m_modOutgoing->destoryOutgoingUser(callid, m_roomId.toStdString(), m_user.userId, m_userAddress);
}

bool SvrOutgoing::joinRoom()
{
	// SvrOutgoing step 1: join room
	m_room = make_shared<Room>(this);
	m_audio = make_shared<Audio>(m_room);
	m_video = make_shared<Video>(m_room, this);
	m_room->init(m_audio, m_video);

	m_room->join(m_roomId.toStdString());

	return true;
}

void SvrOutgoing::handleJoinSuccess()
{
}

void SvrOutgoing::finish()
{
}

void SvrOutgoing::timerEvent(QTimerEvent *event)
{
	int id = event->timerId();
	if (id == m_timingTimerId) {
		handleTimingTick(m_ui);
		return;
	}
}

void SvrOutgoing::onCamera(const tee3::String& username, const tee3::String& devname)
{
	QString devItem = "%1 : %2";
	m_ui.videoList->addItem(devItem.arg(username.c_str()).arg(devname.c_str()));
}

void SvrOutgoing::onCameraRemoved(int index)
{
	m_ui.videoList->takeItem(index);
}

void SvrOutgoing::onCreateOutgoingUser(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::UserId& userid, const tee3::String& user_address)
{
	if (RT_SUCCEEDED(result)) {
		CONSOLE_LOG_IMPORTANT("Create outgoing user success.");
	}
	else {
		QString msg = "Create outgoing user failed: %1.";
		CONSOLE_LOG_CRITICAL(msg.arg(result));
	}
}

void SvrOutgoing::onDestoryOutgoingUser(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::UserId& userid, const tee3::String& user_address)
{
}

void SvrOutgoing::onGetOutgoingUsers(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::UsersType& users)
{
}
