#include <QMessageBox>
#include "svrc.h"
#include "common.h"
#include "svrrecord.h"
#include "svrlive.h"
#include "svroutgoing.h"

struct DemoItem
{
	QString name;
	QString desc;
};

static DemoItem demoItems[] = {
	{ Utf8Str("服务器旁路直播"), Utf8Str("服务器旁路直播一路视频，用户可以RTMP或HLS方式查看\n\n请参考类 SvrLive") },
	{ Utf8Str("服务器录制"), Utf8Str("服务器录制用户指定的一路视频，完成后可以下载到本地，也可以用浏览器播放\n\n请参考类 SvrRecord") },
	{ Utf8Str("服务器外呼"), Utf8Str("服务器外呼RTSP, H.323或SIP设备\n\n请参考类 SvrOutgoing") }
};
const size_t DemoNum(3);

Svrc::Svrc(QWidget *parent)
 : QMainWindow(parent),
   m_currExample(SE_NONE),
   m_callId(0),
   m_appId(0)
{
	m_ui.setupUi(this);

	m_ui.roomLineEdit->setFocus();

	for (size_t i = 0; i < DemoNum; ++i)
		m_ui.demoListWidget->addItem(demoItems[i].name);

	connect(m_ui.demoListWidget, &QListWidget::itemSelectionChanged, this, &Svrc::handleItemChanged);

	connect(m_ui.schedulePushButton, &QPushButton::clicked, this, &Svrc::scheduleRoom);
	connect(m_ui.startBtn, &QPushButton::clicked, this, &Svrc::start);

	m_ui.startBtn->setEnabled(false);
	m_ui.schedulePushButton->setEnabled(false);
	Engine::instance().init(this);
}

void Svrc::handleItemChanged()
{
	int row = m_ui.demoListWidget->currentRow();
	m_currExample = static_cast<SvrcExample>(SE_LIVE + row);
	m_ui.descLabel->setText(demoItems[row].desc);
}

void Svrc::start()
{
	QString roomId = m_ui.roomLineEdit->text();
	if (roomId.isEmpty()) {
		statusBar()->showMessage(Utf8Str("请输入房间号先"), 2000);
		return;
	}

	if ( !((m_currExample > SE_NONE) && (m_currExample < SE_MAX)) ) {
		statusBar()->showMessage(Utf8Str("请选择一个示例"), 2000);
		return;
	}

	++m_callId;
	Engine::instance().getRoom(m_callId, roomId.toStdString());

	m_ui.schedulePushButton->setEnabled(false);
	m_ui.startBtn->setEnabled(false);
}

void Svrc::scheduleRoom()
{
	QString roomId = m_ui.roomLineEdit->text();
	if (roomId.isEmpty()) {
		statusBar()->showMessage(Utf8Str("请输入房间号先"), 2000);
		return;
	}

	++m_callId;
	++m_appId;

	tee3::avd::RoomInfo ri;
	ri.roomName = "svrc";
	ri.appRoomId = std::to_string(m_appId);
	ri.maxAttendee = 10;
	ri.maxAudio = 10;
	ri.maxVideo = 20;
	ri.setRoomMode(tee3::avd::rm_mcu);

	bool r = Engine::instance().schedule(m_callId, ri);
	if (!r) {
		QMessageBox::warning(this, Utf8Str("出错"), Utf8Str("安排房间失败"));
		return;
	}

	m_ui.schedulePushButton->setEnabled(false);
	m_ui.startBtn->setEnabled(false);
}

void Svrc::startTheExample()
{
	QString roomId = m_ui.roomLineEdit->text();

	switch (m_currExample)
	{
	case SE_LIVE:
	{
		SvrLive live(roomId);
		live.exec();
		break;
	}
	case SE_RECORD:
	{
		SvrRecord rec(roomId);
		rec.exec();
		break;
	}
	case SE_OUTGOING:
	{
		SvrOutgoing out(roomId);
		out.exec();
		break;
	}
	default:
		statusBar()->showMessage(Utf8Str("请选择一个示例"), 2000);
		break;
	}
}

void Svrc::onInitResult(Result result)
{
	if (RT_SUCCEEDED(result)) {
		statusBar()->showMessage(Utf8Str("引擎初始化成功"), 2000);
		m_ui.startBtn->setEnabled(true);
		m_ui.schedulePushButton->setEnabled(true);
	}
	else {
		statusBar()->showMessage(Utf8Str("引擎初始化失败"));
		QMessageBox::warning(this, Utf8Str("出错"), Utf8Str("引擎初始化失败"));
	}
}

void Svrc::onGetRoomResult(uint32 callId, Result result)
{
	if (RT_SUCCEEDED(result)) {
		statusBar()->showMessage(Utf8Str("房间存在"), 2000);
		startTheExample();
		m_ui.startBtn->setEnabled(true);
	}
	else {
		QMessageBox::warning(this, Utf8Str("提醒"), Utf8Str("房间号不存在，请先点击安排房间!"));
	}
	m_ui.schedulePushButton->setEnabled(true);
}

void Svrc::onScheduleResult(uint32 callId, Result result, const tee3::RoomId& roomId)
{
	if (RT_SUCCEEDED(result)) {
		m_ui.roomLineEdit->setText(roomId.c_str());
		statusBar()->showMessage(Utf8Str("安排房间成功!"), 2000);
	}
	else {
		QString msg = Utf8Str("创建房间失败: ");
		msg += "%1";
		QMessageBox::warning(this, Utf8Str("提醒"), msg.arg(Engine::getErrorMessage(result).c_str()));
	}
	m_ui.schedulePushButton->setEnabled(true);
	m_ui.startBtn->setEnabled(true);
}
