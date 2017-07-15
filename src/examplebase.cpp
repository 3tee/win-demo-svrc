#include <QMessageBox>
#include "examplebase.h"
#include "common.h"

ExampleBase::ExampleBase(const QString& roomId, QWidget *parent)
: QDialog(parent),
  m_roomId(roomId),
  m_timingTimerId(-1)
{
	connect(this, &QDialog::finished, this, &ExampleBase::finished);
}

ExampleBase::~ExampleBase()
{
	if (m_room.get()) {
		//m_room->leave();
		//m_room.reset();
	}
}

void ExampleBase::onJoinResult(Result result)
{
	if (RT_FAILED(result)) {
		QString msg = "Join failed (%1).";
		CONSOLE_LOG_CRITICAL(msg.arg(result));
		return;
	}

	CONSOLE_LOG_IMPORTANT("Join success.");

	handleJoinSuccess();
}

void ExampleBase::onCamera(const tee3::String& username, const tee3::String& devname)
{
}

void ExampleBase::onCameraRemoved(int index)
{
}

void ExampleBase::finished()
{
	finish();
}
