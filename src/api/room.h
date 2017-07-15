#ifndef RT_Room_H
#define RT_Room_H

#include "common.h"

namespace tee3 {
	namespace avd {
		class User;
		class IMUserManager;


		/**
		* ����ӿ���
		*
		* ����ӿڶ����˷�����󴴽����ͷš����书�ܲ�����
		*/
		class RT_API_EXPORT IRoom {
		public:

			/**
			* ���뷿��ص��ӿ�
			* @param[in] result ���������롣
			* @sa join
			*/
			typedef  void(*FuncJoinResult) (const RoomId& roomId, Result result);

			/**
			* ����ص��ӿ���
			*
			* ����ص��ӿڶ����˷������������첽���أ�����֪ͨ������ָʾ��
			*/
			class IListener {
			public:
				/// �첽����
				/** ���뷿������첽����
				*
				* @param[in] result ���������롣
				* @return  0 �ɹ�
				*		Err_Stream_Connection_TimeOut		����ӻᳬʱ������ԭ���з�����û�����������ֵ�
				*		Err_Rest_GetMcu_Failure				��Ⱥ�л�ȡ����mcuʧ�ܣ�
				*		Err_Net_ChannelSignal_Failure		������������ʧ�ܣ�����������ַ�Ͷ˿ڣ����������磻
				*		Err_Net_ChannelData_Failure			������������ʧ�ܣ�δʵ�֣�
				* @sa join
				*/
				virtual void onJoinResult(Result result) = 0;

				/// ָʾ
				/** ָʾ�û��뿪����
				*
				* @param[in] reason �뿪�������ɴ��룬�����뿪ΪAVD_OK��
				* @param[in] fromId ָʾ�����û�Id��
				* @note SDK�ڲ��Ѿ���ʼ�ͷŷ�����Դ��Ӧ�ò���Բ�����leave
				* reason: 
				* Err_User_DuplicateJoin			�û�Id�ڱ𴦵�¼����ǰͬһId���߳���
				* Err_User_DataConnection_Failed	������������ʧ�ܣ��û��޷�����ʹ�÷��䣬�û����������߳���
				* ����								kickoutUser ����Ĵ����룬�������û��߳���Ӧ�ò��Լ����壻
				*/
				virtual void onLeaveIndication(Result reason, const UserId& fromId) = 0;

				/// ֪ͨ
				/** ͸��ͨ�������յ��㲥����֪ͨ
				*
				* @param[in] *data ���յ�������ָ�롣
				* @param[in] len ���յ������ݳ��ȡ�
				* @param[in] fromId ���ͷ��û�Id��
				*
				* @sa sendPublicData
				*/
				virtual void onPublicData(const char* data, uint32 len, const UserId& fromId) = 0;

				/** ͸��ͨ�������յ�˽������֪ͨ
				*
				* @param[in] *data ���յ�������ָ�롣
				* @param[in] len ���յ������ݳ��ȡ�
				* @param[in] fromId ���ͷ��û�Id��
				*
				* @sa sendPrivateData
				*/
				virtual void onPrivateData(const char* data, uint32 len, const UserId& fromId) = 0;

				/** ����Ӧ�ò����ݸ���֪ͨ
				*
				* @param[in] key Ӧ�ò����ݹؼ��֡�
				* @param[in] value Ӧ�ò����ݹؼ�������������ݡ�
				*
				* @sa updateAppData
				*/
				virtual void onAppDataNotify(const String& key, const String& value) = 0;

				/** ����״̬֪ͨ
				*
				* @param[in] status ����״̬��
				*/
				virtual void onRoomStatusNotify(RoomStatus status) = 0;

				/** ��������״̬֪ͨ
				*
				* @param[in] status ��ǰ����״̬��
				*/
				virtual void onConnectionStatus(ConnectionStatus status) = 0;
			protected:
				virtual ~IListener() {}
			};
		public:
			/** ��ȡ�򴴽�����ӿ�
			*
			* @param[in] roomId ����Id��
			* @note ֻ֧�ֵ��û�Ӧ�ã���֧�ֶ��û�Ӧ�á�
			* @return ���ط���ӿ�ָ�롣
			*/
			static IRoom* obtain(const RoomId& roomId);
			/** ��ȡ�򴴽�����ӿ�
			*
			* @param[in] roomId ����Id��
			* @param[in] userId �û�Id��
			* @note ֧��һ�������У�һ������������û���Ӧ�ã������ܲ��Թ��ߡ��������ص�Ӧ�ã������ɷ���Id���û�Id�����Ψһ��ʶ��
			*						Ҫע��˺�����obtain(const RoomId& roomId)�������ڶ��û�Ӧ���б�����ô˺�����ȡ���䣬�����û�
			*						Ӧ�ÿ��Ե�������һ��������ʹ�á�
			* @return ���ط���ӿ�ָ�롣
			*/
			static IRoom* obtain(const RoomId& roomId, const UserId& userId);
			/** �ͷŷ���ӿ�
			*
			*@note �ͷŷ����App�㲻����ʹ�õ�ǰ����ָ�룬�������÷���ָ�봦��������ΪNULL��
			*      ������onLeaveIndication�Ȼص������������ô˺�����������������
			*/
			virtual void release() = 0;

		public:
			/** ���÷���ص��ӿ�
			*
			* @param[in] *listener �ص��ӿ�ָ�롣
			*
			* @return ���ش�����롣
			* @see IListener
			*/
			virtual Result setListener(IListener* listener) = 0;

			/** ��ǰ�û����뷿��
			*
			* @param[in,out] user �û���Ϣ���û�Id(���ܰ���'{'��'}'�ַ�)���û������û����ݵȣ���Ӧ�ò㲻����user.userIdʱ��SDK������һ���µ�guid��Ϊuser.userId��ͬʱ���ظ�Ӧ�ò㡣
			* @param[in] password ���룺������������������������룻����������λ��ߣ����÷������롣
			* @param[in] joinresult �ӷ���ص��ӿڡ�
			* @note ���뷿��ʱ������ָ����������ص��ӿڣ����ָ��������ָ�������ӿڻص���������Listener��onJoinResult�ص���
			* @return ���ش�����롣
			* @sa User
			*/
			virtual Result join(const User& user, const String& password, FuncJoinResult joinresult) = 0;

			/** ��ǰ�û��뿪����
			*
			* @param[in] reason �û��뿪�����ԭ����룬�����뿪ΪAVD_OK��
			*
			* @note ��ǰ�û��뿪����󣬵�ǰ�������ͷ���ĸ�����ģ�鶼�������״̬�����ܲ�����Ч��
			*      ������onLeaveIndication�Ȼص������������ô˺�����������������
			* @return ���ش�����롣
			*/
			virtual Result leave(Result reason) = 0;				// leave myself

			/** �رշ���
			*
			* @note ֻ�������ˣ�host�����ܹرշ��䡣
			* @return ���ش�����롣
			*/
			virtual Result close() = 0;

			/** ���¼��뵱ǰ����
			*
			* @note ���û������뿪��������м�������ߺ��뿪����󣬿������µ��ô˺������뷿�䡣
			* @return ���ش�����롣
			*/
			virtual Result reJoin() = 0;

			/** ���÷�������������
			*
			* @note ���ϲ��⵽�����л�������£����Ե��ô˽ӿڽ��������������á�
			* @return ���ش�����롣
			*/
			virtual Result reConnect() = 0;

			/** �������߳��û�
			*
			* @param[in] reason �߳��û������ɴ��롣
			* @param[in] userId ���߳��û�Id��
			*
			* @note �����û�������onLeaveIndication�н��յ��ص��������û�ֱ�ӵ��� leave �뿪���伴�ɡ�
			* @return ���ش�����롣
			* @sa onLeaveIndication
			*/
			virtual Result kickoutUser(Result reason, const UserId& userId) = 0;  // leave someone else, who's onLeaveIndication

			/** ���·���״̬
			*
			* @param[in] status ����״̬��
			*
			* @return ���ش�����롣
			* @sa RoomStatus
			*/
			virtual Result updateRoomStatus(RoomStatus status) = 0;

			/** ��ȡ����״̬
			*
			* @return ���ط���״̬��
			* @sa RoomStatus
			*/
			virtual RoomStatus getRoomStatus() const = 0;

			/** ��ȡ����Id
			*
			* @return ���ط���Id��
			*/
			virtual const RoomId& getRoomId() const = 0;

			/** ��ȡ����Ӧ�ò�Id
			*
			* @note ����Ӧ�ò�Id��Ӧ�ò㰲�ŵ�ǰ�����ʱ����Ӧ�ò���ָ��������Ӧ�ò���ҡ���ʾ���䡣
			* @return ���ط���Ӧ�ò�Id��
			*/
			virtual const String& getAppRoomId() const = 0;

			/** ��ȡ������
			*
			* @return ���ط�������
			*/
			virtual const String& getRoomName() const = 0;

			/** ��ȡ��������
			*
			* @return ���ط������⡣
			*/
			virtual const String& getRoomTopic() const = 0;

			/** ��ȡ������Ϣ
			*
			* @return ���ط�����Ϣ��
			* @sa RoomInfo
			*/
			virtual const RoomInfo& getRoomInfo() const = 0;

			/** ͸��ͨ�������͹㲥����
			*
			* @param[in] *data ���͵�����ָ�롣
			* @param[in] len ���͵����ݳ��ȡ�
			*
			* @note ��͸��ͨ�����ڳ���Ӧ�ò����ݣ��㲥�����з������û���
			* @return ���ش�����롣
			*/
			virtual Result sendPublicData(const char* data, uint32 len) = 0;

			/** ͸��ͨ��������˽������
			*
			* @param[in] *data ���͵�����ָ�롣
			* @param[in] len ���͵����ݳ��ȡ�
			* @param[in] toId Ŀ���û�Id��
			*
			* @note ��͸��ͨ�����ڳ���Ӧ�ò����ݣ����͸�������ĳһ�ض��û���
			* @return ���ش�����롣
			*/
			virtual Result sendPrivateData(const char* data, uint32 len, const UserId& toId) = 0;

			/** ����Ӧ�ò�ķ�������
			*
			* @param[in] key �������ݹؼ��֡�
			*
			* @note Ӧ�ò�ķ������ݷ���Ӧ�ò��ڷ����б������ڷ����һЩҵ���߼����ݣ����Ի�ȡ���޸�Ӧ�ò�ķ������ݡ�
			* @return ����Ӧ�ò����Ӧ�ؼ��ֵķ������ݡ�
			*/
			virtual String getAppData(const String& key) const = 0;
			/** �޸�Ӧ�ò�ķ�������
			*
			* @param[in] key �������ݹؼ��֡�
			* @param[in] value �������ݶ�Ӧ�ؼ��ֵ���Ϣ����
			*
			* @return ���ش�����롣
			*/
			virtual Result updateAppData(const String& key, const String& value) = 0;
			/** ����ģ���豸Id���ڵ�������Ƶʱ����
			*
			* @param[in] fakeId �Զ���Id��
			* @return ģ���豸Id��
			* @note ģ������ͷ��Ϣ���ӿڻ�����deviceId�����ɹ���"userId_"+���û������fakeId), �˴�deviceId���ܰ���'_'��'{'��'}'�������ַ���
			* @sa previewLocalCamera
			* @sa publishLocalCamera
			*/
			virtual DeviceId createFakeDeviceID(const DeviceId& fakeId) = 0;

			virtual bool isWorking() const = 0;

			/** ��ǰ�û����뷿��
			*
			* @param[in,out] user �û���Ϣ���û�Id(���ܰ���'{'��'}'�ַ�)���û������û����ݵȣ���Ӧ�ò㲻����user.userIdʱ��SDK������һ���µ�guid��Ϊuser.userId��ͬʱ���ظ�Ӧ�ò㡣
			* @param[in] password ���룺������������������������룻����������λ��ߣ����÷������롣
			* @param[in] joinresult �ӷ���ص��ӿڡ�
			* @param[in] roomToken ����token��
			* @note ���뷿��ʱ������ָ����������ص��ӿڣ����ָ��������ָ�������ӿڻص���������Listener��onJoinResult�ص���
			* @return ���ش�����롣
			* @sa User
			*/
			virtual Result join(const User& user, const String& password, FuncJoinResult joinresult, const String& roomToken) = 0;

			/** ��ǰ�������û�ر�����ͳ�ƹ���
			* @param[in] isEnable ���û�رա�
			* @return ���ش�����룺
			* 	AVD_OK						�ɹ�
			*/
			virtual Result enableStats(bool isEnable) = 0;
			/** ��ȡ���������ͳ����Ϣ
			* @return ���ط�������ͳ����Ϣ��
			* @sa RoomStats
			*/
			virtual const RoomStats& getRoomStats() const = 0;
			/** ��ȡĳ·ý�壨��Ƶ������Ƶ��������ͳ����Ϣ
			* @param[in] deviceId �豸Id��
			* @return ����ý��ͳ����Ϣ��
			* @sa MediaStats
			*/
			virtual const MediaStats& getMediaStats(const DeviceId& deviceId) const = 0;
			virtual const MediaStats& getAudioStats() = 0;

		public:
			/** ���÷���ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @param[in] *value ����ѡ��ֵָ�롣
			*
			* @return ���ش�����롣
			*/
			virtual Result setOption(RoomOption type, void* value) = 0;
			virtual Result setOption(RoomOption type, const String& value) = 0;
			/** ��ȡ����ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @param[out] *value ����ѡ���ֵָ�롣
			*
			* @return ���ش�����롣
			*/
			virtual Result getOption(RoomOption type, void* value) = 0;
			virtual String getOption(RoomOption type) = 0;

		protected:
			virtual ~IRoom() {}
		};

		/**
		* ����ģ��ӿ���
		*
		* ����ģ��ӿڶ����˷���ģ�鹫���Ĳ�����
		*/
		class RT_API_EXPORT IModule {
		public:
			/** ��ȡ����ӿ�ָ��
			*
			* @return ���ط���ӿ�ָ�롣
			* @sa IRoom
			*/
			virtual IRoom* getRoom() = 0;

			/** ��ȡ�����û�����ģ��ָ��
			*
			* @return �����û�����ģ��ָ�롣
			* @sa IMUserManager
			*/
			virtual IMUserManager* getUserManager() = 0;

			/** �ж��Ƿ����Լ����û�Id
			* @param[in] userId �û�Id
			* @return �����Ƿ����Լ���
			*/
			virtual bool isSelfUser(const UserId& userId) const = 0;

			/** �ж��豸Id�Ƿ��������Լ���
			* @param[in] deviceId �豸Id
			* @return �����豸Id�Ƿ��������Լ��ġ�
			*/
			virtual bool isSelfDevice(const DeviceId& deviceId) const = 0;

			/** ��ȡ�豸Id�Ĺ����û�Id
			* @param[in] deviceId �豸Id
			* @return �����û�Id��
			*/
			virtual const UserId getOwnerId(const DeviceId& deviceId) const = 0;
			/** ��ȡ�豸Id�Ĺ����û�����
			* @param[in] deviceId �豸Id
			* @return �����û����ơ�
			*/
			virtual const String& getOwnerName(const DeviceId& deviceId) const = 0;

		protected:
			virtual ~IModule() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_Room_H
