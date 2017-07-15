#pragma once

#include "ui_svrlive.h"
#include "examplebase.h"
#include "api/avdlive.h"

class SvrLive : public ExampleBase, public tee3::avd::IAVDLive::IListener
{
	Q_OBJECT

public:
	SvrLive(const QString& roomId, QWidget *parent = Q_NULLPTR);
	~SvrLive();

private:
	void start(bool status);
	void getLive();
	bool startLive();
	void stopLive();
	void copyRtmp();
	void playRtmp();
	void showHls();
	tee3::avd::RecordVideoType getH264Stream(const QString& videoId);

private:
	virtual bool joinRoom();
	virtual void handleJoinSuccess();
	virtual void finish();

	virtual void timerEvent(QTimerEvent *event);

	// IVideoSink
	virtual void onCamera(const tee3::String& username, const tee3::String& devname);
	virtual void onCameraRemoved(int index);

	// IAVDLive::IListener
	virtual void onWorkingRooms(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RoomInfosType& items);
	virtual void onPublishedVideos(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::VideoDevicesType& items);
	virtual void onCreateLive(uint32 callId, Result result, const tee3::avd::LiveInfo& info);
	virtual void onSelectMedia4Live(uint32 callId, Result result, const tee3::LiveId& lvbc_id, const tee3::DeviceId& selectedVideo);
	virtual void onCreateUserLive(uint32 callId, Result result, const tee3::avd::LiveInfo& info);
	virtual void onStopLive(uint32 callId, Result result, const tee3::LiveId& lvbc_id);
	virtual void onLiveInfo(uint32 callId, Result result, const tee3::avd::LiveInfo& info);
	virtual void onLiveInfos(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::LiveInfosType& items);
	virtual void onDeleteLive(uint32 callId, Result result, const tee3::LiveId& lvbc_id);

private:
	enum State
	{
		S_NONE,
		S_INIT,
		S_JOINING,
		S_JOINED,
		S_LIVING
	};

	Ui::LiveDialog m_ui;
	State m_state;
	tee3::avd::IAVDLive* m_modLive;
	tee3::avd::LiveInfo m_liveInfo;
	QString m_urlBase;
};
