#pragma once

#include "ui_svrrecord.h"
#include "examplebase.h"
#include "api/avdrecord.h"

class SvrRecord : public ExampleBase, public tee3::avd::IAVDRecord::IListener
{
	Q_OBJECT

public:
	SvrRecord(const QString& roomId, QWidget *parent = Q_NULLPTR);
	~SvrRecord();

private:
	void start(bool status);
	void getRecord();
	bool startRecord();
	void stopRecord();
	void copyLink();
	void playFile();
	void downloadFile();

private:
	virtual bool joinRoom();
	virtual void handleJoinSuccess();
	virtual void finish();

	virtual void timerEvent(QTimerEvent *event);

	// IVideoSink
	virtual void onCamera(const tee3::String& username, const tee3::String& devname);
	virtual void onCameraRemoved(int index);

	virtual void onWorkingRooms(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RoomInfosType& items);
	virtual void onPublishedVideos(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::VideoDevicesType& items);
	virtual void onCreateRecord(uint32 callId, Result result, const tee3::avd::RecordInfo& info);
	virtual void onSelectMedia4Record(uint32 callId, Result result, const tee3::RecordId& recordId, const tee3::DeviceId& selectedVideo);
	virtual void onCreateUserRecord(uint32 callId, Result result, const tee3::avd::RecordInfo& info);
	virtual void onStopRecord(uint32 callId, Result result, const tee3::RecordId& recordId);
	virtual void onRecordInfo(uint32 callId, Result result, const tee3::avd::RecordInfo& info);
	virtual void onRecordInfos(uint32 callId, Result result, uint32 total, uint32 begin, const tee3::avd::RecordInfosType& items);
	virtual void onDeleteRecord(uint32 callId, Result result, const tee3::RecordId& recordId);

private:
	Ui::RecordDialog m_ui;
	tee3::avd::IAVDRecord* m_modRecord;
	tee3::avd::RecordInfo m_recordInfo;
	tee3::RecordId m_recordId;
	QString m_urlBase;
	tee3::String m_url;
};
