#pragma once

#include "ui_svrout.h"
#include "examplebase.h"
#include "api/avdoutgoing.h"

class SvrOutgoing : public ExampleBase, public tee3::avd::IAVDOutgoing::IListener
{
	Q_OBJECT

public:
	SvrOutgoing(const QString& roomId, QWidget *parent = Q_NULLPTR);
	~SvrOutgoing();

private:
	void start(bool status);
	bool createUser();
	void deleteUser();

private:
	virtual bool joinRoom();
	virtual void handleJoinSuccess();
	virtual void finish();

	virtual void timerEvent(QTimerEvent *event);

	// IVideoSink
	virtual void onCamera(const tee3::String& username, const tee3::String& devname);
	virtual void onCameraRemoved(int index);

	// IAVDOutgoing::IListener
	virtual void onCreateOutgoingUser(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::UserId& userid, const tee3::String& user_address);
	virtual void onDestoryOutgoingUser(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::UserId& userid, const tee3::String& user_address);
	virtual void onGetOutgoingUsers(uint32 callId, Result result, const tee3::RoomId& roomId, const tee3::avd::UsersType& users);

private:
	Ui::OutgoingDialog m_ui;
	tee3::avd::IAVDOutgoing* m_modOutgoing;
	tee3::avd::User m_user;
	tee3::String m_userAddress;
};
