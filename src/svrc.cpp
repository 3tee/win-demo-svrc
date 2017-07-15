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
	{ Utf8Str("��������·ֱ��"), Utf8Str("��������·ֱ��һ·��Ƶ���û�����RTMP��HLS��ʽ�鿴\n\n��ο��� SvrLive") },
	{ Utf8Str("������¼��"), Utf8Str("������¼���û�ָ����һ·��Ƶ����ɺ�������ص����أ�Ҳ���������������\n\n��ο��� SvrRecord") },
	{ Utf8Str("���������"), Utf8Str("���������RTSP, H.323��SIP�豸\n\n��ο��� SvrOutgoing") }
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
		statusBar()->showMessage(Utf8Str("�����뷿�����"), 2000);
		return;
	}

	if ( !((m_currExample > SE_NONE) && (m_currExample < SE_MAX)) ) {
		statusBar()->showMessage(Utf8Str("��ѡ��һ��ʾ��"), 2000);
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
		statusBar()->showMessage(Utf8Str("�����뷿�����"), 2000);
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
		QMessageBox::warning(this, Utf8Str("����"), Utf8Str("���ŷ���ʧ��"));
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
		statusBar()->showMessage(Utf8Str("��ѡ��һ��ʾ��"), 2000);
		break;
	}
}

void Svrc::onInitResult(Result result)
{
	if (RT_SUCCEEDED(result)) {
		statusBar()->showMessage(Utf8Str("�����ʼ���ɹ�"), 2000);
		m_ui.startBtn->setEnabled(true);
		m_ui.schedulePushButton->setEnabled(true);
	}
	else {
		statusBar()->showMessage(Utf8Str("�����ʼ��ʧ��"));
		QMessageBox::warning(this, Utf8Str("����"), Utf8Str("�����ʼ��ʧ��"));
	}
}

void Svrc::onGetRoomResult(uint32 callId, Result result)
{
	if (RT_SUCCEEDED(result)) {
		statusBar()->showMessage(Utf8Str("�������"), 2000);
		startTheExample();
		m_ui.startBtn->setEnabled(true);
	}
	else {
		QMessageBox::warning(this, Utf8Str("����"), Utf8Str("����Ų����ڣ����ȵ�����ŷ���!"));
	}
	m_ui.schedulePushButton->setEnabled(true);
}

void Svrc::onScheduleResult(uint32 callId, Result result, const tee3::RoomId& roomId)
{
	if (RT_SUCCEEDED(result)) {
		m_ui.roomLineEdit->setText(roomId.c_str());
		statusBar()->showMessage(Utf8Str("���ŷ���ɹ�!"), 2000);
	}
	else {
		QString msg = Utf8Str("��������ʧ��: ");
		msg += "%1";
		QMessageBox::warning(this, Utf8Str("����"), msg.arg(Engine::getErrorMessage(result).c_str()));
	}
	m_ui.schedulePushButton->setEnabled(true);
	m_ui.startBtn->setEnabled(true);
}
