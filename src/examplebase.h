#pragma once

#include <memory>
#include <QDialog>
#include <QTime>
#include "console.h"
#include "engine.h"
#include "room.h"
#include "audio.h"
#include "video.h"

class ExampleBase : public QDialog, public IRoomSink, public IVideoSink
{
	Q_OBJECT

public:
	ExampleBase(const QString& roomId, QWidget *parent = Q_NULLPTR);
	~ExampleBase();

	template<typename UI>
	void init(UI& ui)
	{
		m_consoleInit.reset(new ConsoleInitializer(ui.consoleTextEdit));

		joinRoom();
	}

protected:
	virtual bool joinRoom() = 0;
	virtual void handleJoinSuccess() = 0;
	virtual void finish() = 0;

	template<typename UI>
	void handleTimingTick(UI& ui)
	{
		QTime now = QTime::currentTime();
		QTime zero(0, 0, 0);
		QTime elps = zero.addMSecs(m_startTime.msecsTo(now));
		ui.timeLabel->setText(elps.toString("hh:mm:ss"));
	}

	template<typename UI>
	bool startTimingTimer(UI& ui)
	{
		m_timingTimerId = startTimer(1000);
		m_startTime = QTime::currentTime();
		ui.timeLabel->setText("00:00:00");
		return true;
	}

	void stopTimingTimer()
	{
		killTimer(m_timingTimerId);
		m_timingTimerId = -1;
	}

private:
	// IRoomEvents
	virtual void onJoinResult(Result result);

	// IVideoSink
	virtual void onCamera(const tee3::String& username, const tee3::String& devname);
	virtual void onCameraRemoved(int index);

private:
	void finished();

protected:
	std::unique_ptr<ConsoleInitializer> m_consoleInit;
	QString m_roomId;
	std::shared_ptr<Room> m_room;
	std::shared_ptr<Audio> m_audio;
	std::shared_ptr<Video> m_video;
	QTime m_startTime;
	int m_timingTimerId;
};
