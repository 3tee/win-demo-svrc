#include <QClipboard>
#include <QDesktopServices>
#include "svrlive.h"
#include "common.h"
#include "console.h"
#include "api/musermanager.h"
#include "engine.h"

using std::make_shared;

using namespace tee3;
using namespace tee3::avd;

SvrLive::SvrLive(const QString& roomId, QWidget *parent)
 : ExampleBase(roomId, parent),
   m_state(S_NONE),
   m_modLive(nullptr)
{
	m_ui.setupUi(this);
	init(m_ui);
	m_ui.startButton->setEnabled(false);
	m_ui.copyRtmpButton->setEnabled(false);
	m_ui.playRtmpButton->setEnabled(false);
	m_ui.HlsQrcodeButton->setEnabled(false);
	connect(m_ui.startButton, &QPushButton::clicked, this, &SvrLive::start);
	connect(m_ui.copyRtmpButton, &QPushButton::clicked, this, &SvrLive::copyRtmp);
	connect(m_ui.playRtmpButton, &QPushButton::clicked, this, &SvrLive::playRtmp);
	connect(m_ui.HlsQrcodeButton, &QPushButton::clicked, this, &SvrLive::showHls);

	m_state = S_INIT;
}

SvrLive::~SvrLive()
{
}

void SvrLive::start(bool status)
{
	if (status) {
		if (!startLive()) {
			m_ui.startButton->setChecked(false);
			return;
		}
		startTimingTimer(m_ui);
		m_ui.startButton->setText(Utf8Str("Í£Ö¹"));
	}
	else {
		stopLive();
		stopTimingTimer();
		m_ui.startButton->setText(Utf8Str("¿ªÊ¼"));
	}
}

void SvrLive::getLive()
{
	// SvrLive step 3: get live info
	if (m_modLive) {
		uint32 callid = 0;
		m_modLive->getLiveInfo(callid, m_liveInfo.id);

		tee3::String urlbase;
		Engine::instance().getOption(tee3::avd::eo_demo_urlbase_liverecord, &urlbase);
		m_urlBase = "http://" + QString::fromUtf8(urlbase.c_str());
	}
}

RecordVideoType SvrLive::getH264Stream(const QString& videoId)
{
	DeviceId sid = videoId.toUtf8().data();
	const Camera& camera = m_video->getCameraDevice()->getCamera(sid);
	VideoCodec codec = camera.publishedQualities.getStreamCodec(stream_main);
	if (codec_h264 == codec) {
		return rv_main;
	}
	if (camera.publishedQualities.hasAssist1()) {
		codec = camera.publishedQualities.getStreamCodec(stream_assist1);
		if (codec_h264 == codec) {
			return rv_ass1;
		}
	}
	if (camera.publishedQualities.hasAssist2()) {
		codec = camera.publishedQualities.getStreamCodec(stream_assist2);
		if (codec_h264 == codec) {
			return rv_ass2;
		}
	}
	return rv_none;
}

bool SvrLive::startLive()
{
	// SvrLive step 2: get live module, set listener, set live info, create live
	if (!m_modLive) {
		m_modLive = IAVDLive::getLive(IAVDEngine::Instance());
		m_modLive->setListener(this);
	}

	int index = -1;
	QList<QListWidgetItem*> items = m_ui.videoList->selectedItems();
	if (items.empty()) {
		CONSOLE_LOG_CRITICAL("Please select one video.");
		return false;
	}
	index = m_ui.videoList->row(items.first());
	VideoInfo vi = m_video->getInfo(index);
	if (vi.userId.empty() && vi.deviceId.empty()) {
		CONSOLE_LOG_CRITICAL("Can not get video info.");
		return false;
	}

	User user = m_video->getUserManager()->getUser(vi.userId);
	if (!user.isValid()) {
		return false;
	}
	if (S_LIVING == m_state) {
		CONSOLE_LOG_CRITICAL("Live already started.");
		return false;
	}
	m_liveInfo = LiveInfo();
	m_liveInfo.roomId = m_roomId.toUtf8().constData();
	m_liveInfo.userId = user.userId;
	m_liveInfo.name = user.userName + "_live_" + QDateTime::currentDateTime().toString(Qt::ISODate).toUtf8().constData();
	m_liveInfo.audioType = tee3::avd::ra_user_single;
	m_liveInfo.videoType = getH264Stream(vi.deviceId.c_str());
	uint32 callid = 0;
	Result ret = m_modLive->createUserLive(callid, m_liveInfo);
	if (RT_SUCCEEDED(ret)) {
		m_ui.copyRtmpButton->setEnabled(false);
		m_ui.playRtmpButton->setEnabled(false);
		m_ui.HlsQrcodeButton->setEnabled(false);
		m_state = S_LIVING;
	}
	return RT_SUCCEEDED(ret);
}

void SvrLive::stopLive()
{
	uint32 callid = 0;
	m_modLive->stopLive(callid, m_liveInfo.id);
	m_state = S_JOINED;
}

void SvrLive::copyRtmp()
{
	if (!m_liveInfo.rtmpurl.empty()) {
		QString url = m_urlBase + QString("/admin/live/rtmpPlayer.html?src=") + m_liveInfo.rtmpurl.c_str();
		QApplication::clipboard()->setText(url);
		CONSOLE_LOG_IMPORTANT("RTMP URL copied to clipboard.");
	}
}

void SvrLive::playRtmp()
{
	if (!m_liveInfo.rtmpurl.empty()) {
		CONSOLE_LOG_IMPORTANT("Playing RTMP.");
		QString url = m_urlBase + QString("/admin/live/rtmpPlayer.html?src=") + m_liveInfo.rtmpurl.c_str();
		QDesktopServices::openUrl(QUrl(url));
	}
}

void SvrLive::showHls()
{
	if (!m_liveInfo.hlsurl.empty()) {
		CONSOLE_LOG_IMPORTANT("Showing HLS QR code.");
		QString url = m_urlBase + QString("/admin/live/qrcode.html?src=")
					+ m_urlBase + QString("/admin/live/hlsPlayer.html?src=") + m_liveInfo.hlsurl.c_str();
		QDesktopServices::openUrl(QUrl(url));
	}
}

bool SvrLive::joinRoom()
{
	// SvrLive step 1: join room
	m_room = make_shared<Room>(this);
	m_audio = make_shared<Audio>(m_room);
	m_video = make_shared<Video>(m_room, this);
	m_room->init(m_audio, m_video);

	m_room->join(m_roomId.toStdString());

	m_state = S_JOINING;

	return true;
}

void SvrLive::handleJoinSuccess()
{
	m_state = S_JOINED;
	m_ui.startButton->setEnabled(true);
}

void SvrLive::finish()
{
}

void SvrLive::timerEvent(QTimerEvent *event)
{
	int id = event->timerId();
	if (id == m_timingTimerId) {
		handleTimingTick(m_ui);
		return;
	}
}

void SvrLive::onCamera(const tee3::String& username, const tee3::String& devname)
{
	QString devItem = "%1 : %2";
	m_ui.videoList->addItem(devItem.arg(username.c_str()).arg(devname.c_str()));
}

void SvrLive::onCameraRemoved(int index)
{
	m_ui.videoList->takeItem(index);
}

void SvrLive::onWorkingRooms(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RoomInfosType& items)
{
}

void SvrLive::onPublishedVideos(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::VideoDevicesType& items)
{
}

void SvrLive::onCreateLive(uint32 callId, Result result, const tee3::avd::LiveInfo& info)
{
}

void SvrLive::onSelectMedia4Live(uint32 callId, Result result, const tee3::LiveId& lvbc_id, const tee3::DeviceId& selectedVideo)
{
}

void SvrLive::onCreateUserLive(uint32 callId, Result result, const tee3::avd::LiveInfo& info)
{
	m_liveInfo = info;
	if (RT_SUCCEEDED(result)) {
		CONSOLE_LOG_IMPORTANT("Live started.");
		getLive();
	}
	else {
		CONSOLE_LOG_CRITICAL(QString("Live start failed: %1.").arg(Engine::getErrorMessage(result).c_str()));
		m_state = S_JOINED;
		start(false);
	}
}

void SvrLive::onStopLive(uint32 callId, Result result, const tee3::LiveId& lvbc_id)
{
	CONSOLE_LOG("Live stopped.");
}

void SvrLive::onLiveInfo(uint32 callId, Result result, const tee3::avd::LiveInfo& info)
{
	QString msg = "Got live info: %1, rtmp=%2, hls=%3.";
	CONSOLE_LOG_DETAIL(msg.arg(result).arg(info.rtmpurl.c_str()).arg(info.hlsurl.c_str()));
	if (RT_SUCCEEDED(result)) {
		m_ui.copyRtmpButton->setEnabled(true);
		m_ui.playRtmpButton->setEnabled(true);
		m_ui.HlsQrcodeButton->setEnabled(true);
	}
}

void SvrLive::onLiveInfos(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::LiveInfosType& items)
{
}

void SvrLive::onDeleteLive(uint32 callId, Result result, const tee3::LiveId& lvbc_id)
{
}
