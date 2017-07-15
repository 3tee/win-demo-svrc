#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_svrc.h"
#include "engine.h"

enum SvrcExample
{
	SE_NONE,
	SE_LIVE,
	SE_RECORD,
	SE_OUTGOING,
	SE_MAX
};

class Svrc : public QMainWindow, public IEngineSink
{
    Q_OBJECT

public:
    Svrc(QWidget *parent = Q_NULLPTR);

private:
	void handleItemChanged();
	void scheduleRoom();
	void start();
	void startTheExample();

private:
	// IEngineSink
	virtual void onInitResult(Result result);
	virtual void onGetRoomResult(uint32 callId, Result result);
	virtual void onScheduleResult(uint32 callId, Result result, const tee3::RoomId& roomId);

private:
    Ui::svrcClass m_ui;
	SvrcExample m_currExample;
	uint32 m_callId;
	uint32 m_appId;
};
