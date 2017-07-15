#include <QClipboard>
#include <QDesktopServices>
#include "svrrecord.h"
#include "common.h"
#include "console.h"
#include "api/musermanager.h"
#include "engine.h"

using std::make_shared;

using tee3::avd::IAVDRecord;
using tee3::avd::IAVDEngine;
using tee3::DeviceId;
using tee3::avd::User;
using tee3::avd::VideoCodec;

SvrRecord::SvrRecord(const QString& roomId, QWidget *parent)
 : ExampleBase(roomId, parent),
   m_modRecord(nullptr)
{
	m_ui.setupUi(this);
	init(m_ui);
	m_ui.startButton->setEnabled(false);
	m_ui.copyLinkButton->setEnabled(false);
	m_ui.playFileButton->setEnabled(false);
	m_ui.downloadFileButton->setEnabled(false);
	connect(m_ui.startButton, &QPushButton::clicked, this, &SvrRecord::start);
	connect(m_ui.copyLinkButton, &QPushButton::clicked, this, &SvrRecord::copyLink);
	connect(m_ui.playFileButton, &QPushButton::clicked, this, &SvrRecord::playFile);
	connect(m_ui.downloadFileButton, &QPushButton::clicked, this, &SvrRecord::downloadFile);
}

SvrRecord::~SvrRecord()
{
}

void SvrRecord::start(bool status)
{
	if (status) {
		if (!startRecord()) {
			m_ui.startButton->setChecked(false);
			return;
		}
		startTimingTimer(m_ui);
		m_ui.startButton->setText(Utf8Str("Í£Ö¹"));
	}
	else {
		stopRecord();
		stopTimingTimer();
		m_ui.startButton->setText(Utf8Str("¿ªÊ¼"));
	}
}

void SvrRecord::getRecord()
{
	// SvrRecord step 3: get record info
	if (!m_modRecord) {
		m_modRecord = IAVDRecord::getRecord(IAVDEngine::Instance());
		m_modRecord->setListener(this);
	}

	uint32 callid = 0;
	m_modRecord->getRecordInfo(callid, m_recordId);

	tee3::String surlbase;
	Engine::instance().getOption(tee3::avd::eo_demo_urlbase_liverecord, &surlbase);
	m_urlBase = "http://" + QString::fromUtf8(surlbase.c_str());
}

bool SvrRecord::startRecord()
{
	// SvrRecord step 2: get record module, set listener, set record info, create record
	if (!m_modRecord) {
		m_modRecord = IAVDRecord::getRecord(IAVDEngine::Instance());
		m_modRecord->setListener(this);
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
	if (m_recordInfo.isValid()) {
		qDebug() << "recordStart, user has begin record. recordId=" << m_recordInfo.id.c_str();
		return false;
	}
	m_recordInfo.roomId = m_roomId.toUtf8().constData();
	m_recordInfo.userId = user.userId;
	m_recordInfo.name = user.userName + "_rec_" + QDateTime::currentDateTime().toString(Qt::ISODate).toUtf8().constData();
	m_recordInfo.audioType = tee3::avd::ra_user_single;
	m_recordInfo.videoType = tee3::avd::rv_main;
	VideoCodec codec;
	IAVDEngine::Instance()->getOption(tee3::avd::eo_video_codec_priority, &codec);
	m_recordInfo.fileType = (tee3::avd::codec_vp8 == codec) ? tee3::avd::mt_webm : tee3::avd::mt_mp4;
	uint32 callid = 0;
	Result ret = m_modRecord->createUserRecord(callid, m_recordInfo);
	if (RT_SUCCEEDED(ret)) {
		m_ui.copyLinkButton->setEnabled(false);
		m_ui.playFileButton->setEnabled(false);
		m_ui.downloadFileButton->setEnabled(false);
	}
	return RT_SUCCEEDED(ret);
}

void SvrRecord::stopRecord()
{
	uint32 callid = 0;
	m_modRecord->stopRecord(callid, m_recordId);
}

void SvrRecord::copyLink()
{
	if (!m_url.empty()) {
		CONSOLE_LOG_IMPORTANT("URL of recorded file copied to clipboard.");
		QApplication::clipboard()->setText(m_url.c_str());
	}
}

void SvrRecord::playFile()
{
	if (!m_url.empty()) {
		CONSOLE_LOG_IMPORTANT("Playing recorded file.");
		QString url = m_urlBase + QString("/admin/record/recordPlayer.html?src=") + m_url.c_str();
		QDesktopServices::openUrl(QUrl(url));
	}
}

void SvrRecord::downloadFile()
{
	if (!m_url.empty()) {
		CONSOLE_LOG_IMPORTANT("Downloading recorded file.");
		QDesktopServices::openUrl(QUrl(m_url.c_str()));
	}
}

bool SvrRecord::joinRoom()
{
	m_room = make_shared<Room>(this);
	m_audio = make_shared<Audio>(m_room);
	m_video = make_shared<Video>(m_room, this);
	m_room->init(m_audio, m_video);

	// SvrRecord step 1: join room
	m_room->join(m_roomId.toStdString());

	return true;
}

void SvrRecord::handleJoinSuccess()
{
	m_ui.startButton->setEnabled(true);
}

void SvrRecord::finish()
{
}

void SvrRecord::timerEvent(QTimerEvent *event)
{
	int id = event->timerId();
	if (id == m_timingTimerId) {
		handleTimingTick(m_ui);
		return;
	}
}

void SvrRecord::onCamera(const tee3::String& username, const tee3::String& devname)
{
	QString devItem = "%1 : %2";
	m_ui.videoList->addItem(devItem.arg(username.c_str()).arg(devname.c_str()));
}

void SvrRecord::onCameraRemoved(int index)
{
	m_ui.videoList->takeItem(index);
}

void SvrRecord::onWorkingRooms(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RoomInfosType& items)
{
}

void SvrRecord::onPublishedVideos(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::VideoDevicesType& items)
{
}

void SvrRecord::onCreateRecord(uint32 callId, Result result, const tee3::avd::RecordInfo& info)
{
}

void SvrRecord::onSelectMedia4Record(uint32 callId, Result result, const tee3::RecordId& recordId, const tee3::DeviceId& selectedVideo)
{
}

void SvrRecord::onCreateUserRecord(uint32 callId, Result result, const tee3::avd::RecordInfo& info)
{
	if (RT_SUCCEEDED(result)) {
		CONSOLE_LOG_IMPORTANT("Recording...");
		m_recordId = info.id;
	}
	else {
		QString msg = "Record failed: %1.";
		CONSOLE_LOG_CRITICAL(msg.arg(Engine::getErrorMessage(result).c_str()));
	}
}

void SvrRecord::onStopRecord(uint32 callId, Result result, const tee3::RecordId& recordId)
{
	CONSOLE_LOG_IMPORTANT("Record stopped.");
	if (RT_SUCCEEDED(result)) {
		getRecord();
	}
}

void SvrRecord::onRecordInfo(uint32 callId, Result result, const tee3::avd::RecordInfo& info)
{
	QString msg = "Got record info: %1, url=%2.";
	CONSOLE_LOG_DETAIL(msg.arg(result).arg(info.url.c_str()));
	if (RT_SUCCEEDED(result)) {
		m_url = info.url;
		m_ui.copyLinkButton->setEnabled(true);
		m_ui.playFileButton->setEnabled(true);
		m_ui.downloadFileButton->setEnabled(true);
	}
}

void SvrRecord::onRecordInfos(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RecordInfosType& items)
{
}

void SvrRecord::onDeleteRecord(uint32 callId, Result result, const tee3::RecordId& recordId)
{
}
