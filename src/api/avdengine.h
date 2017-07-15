#ifndef RT_AVDEngine_H_
#define RT_AVDEngine_H_

#include "common.h"
#include "room.h"

namespace tee3 {
	namespace avd {
		/**
		* AVD����ӿ���
		*
		* AVD����ӿڶ���������ȫ�ֳ�ʼ�������ͷ��䰲�š���ѯ��ɾ���Ȳ�����
		*/
		class RT_API_EXPORT IAVDEngine {
		public:
			/**
			* AVD����ص��ӿ���
			*
			* AVD����ص��ӿڶ���������ӿڲ������첽���ء�
			*/
			class IListener {
			public:
				/// �첽����
				/** ��ʼ����������첽����
				*
				* @param[in] result ��ʼ��������롣
				* @sa init
				*/
				virtual void onInitResult(Result result) = 0;

				/** ����ʼ������֪ͨ
				*
				* @param[in] reason ����ʼ��������롣
				* @note �˺������������uninit���첽���أ�uninit��ͬ���������˺�����SDK�ڲ���⵽��������������֪ͨӦ�ò�Ļص���
				*/
				virtual void onUninitResult(Result reason) = 0;


				/** ��ȡ������Ϣ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ��ȡ���������롣
				* @param[in] room ������Ϣ��
				*
				* @sa getRoomByRoomId
				* @sa getRoomByAppRoomId
				*/
				virtual void onGetRoomResult(uint32 callId, Result result, const RoomInfo& room) = 0;
				/** ��ѯ������Ϣ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ��ѯ���������롣
				* @param[in] rooms ������Ϣ�б�
				*
				* @sa findRoom
				*/
				virtual void onFindRoomsResult(uint32 callId, Result result, const RoomInfosType& rooms) = 0;
				/** ���ŷ�������첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ���ŷ��������롣
				* @param[in] roomId ����Id��
				*
				* @sa scheduleRoom
				*/
				virtual void onScheduleRoomResult(uint32 callId, Result result, const RoomId& roomId) = 0;
				/** ȡ����������첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ȡ�����������롣
				* @param[in] roomId ����Id��
				*
				* @sa cancelRoom
				*/
				virtual void onCancelRoomResult(uint32 callId, Result result, const RoomId& roomId) = 0;
				/** ��ȡ�����вλ��������첽����
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] usersCount ����λ���������
				* @param[in] roomId ����Id��
				* @sa getUsersCount
				*/
				virtual void onGetUsersCountResult(uint32 callId, Result result, uint32 usersCount, const RoomId& roomId) = 0;
			protected:
				virtual ~IListener() {
				}
			};
		public:
			/** ��ȡAVD�������
			*
			* @note AVD������һ����������һ�����̿ռ�ֻ����һ�����档
			* @return ����AVD���档
			*/
			static IAVDEngine* Instance();
			/** �ͷ�AVD�������
			*/
			virtual void release() = 0;
		public:
			/** ��ʼ������
			*
			* @param[in] *listener ����ص�ָ�롣
			* @param[in] severuri ������uri��
			* @param[in] appkey ���幫˾�ַ���Ӧ�ù�˾��Ӧ����Կ��
			* @param[in] secretkey ���幫˾�ַ���Ӧ�ù�˾�İ�ȫ��Կ��
			* @note AVD���������κι��ܲ���ǰ��������Ҫ��ʼ������ɹ��������ʼ����һ���첽���������ô˽ӿں�ȴ��ص��к���onInitResult�ص����ж��Ƿ��ʼ���ɹ���
			* @return ���ش�����롣
			*/
			virtual Result init(
				IListener* listener, const String& severuri, const String& appkey, const String& secretkey) = 0;

			/** ��ʼ������
			*
			* @param[in] *listener ����ص�ָ�롣
			* @param[in] severuri ������uri��
			* @param[in] token ��֤���ƾ֤��
			* @note AVD���������κι��ܲ���ǰ��������Ҫ��ʼ������ɹ��������ʼ����һ���첽���������ô˽ӿں�ȴ��ص��к���onInitResult�ص����ж��Ƿ��ʼ���ɹ���
			* @return ���ش�����롣
			*/
			virtual Result init(IAVDEngine::IListener* listener, const String& severuri, const String& token) = 0;

			/** ��ʼ������
			*
			* @param[in] *listener ����ص�ָ�롣
			* @param[in] severuri ������uri��
			* @param[in] oemName ���幫˾Open-AVD��ƷOEM�ĳ������ơ�
			* @note AVD���������κι��ܲ���ǰ��������Ҫ��ʼ������ɹ��������ʼ����һ���첽���������ô˽ӿں�ȴ��ص��к���onInitResult�ص����ж��Ƿ��ʼ���ɹ���
			* @return ���ش�����롣
			*/
			virtual Result initWithOEM(
				IListener* listener, const String& severuri, const String& oemName) = 0;

			/** ����ʼ������
			*
			* @note AVD����ʼ�����������漰�����з��������Ч�������ϵĹ��ܺ������޷�����ʹ�á�
			* @return ���ش�����롣
			*/
			virtual Result uninit() = 0;

			/** �ж������Ƿ���������
			*
			* @return ���������Ƿ�����������
			*/
			virtual bool isWorking() const = 0;

			//
			/** ���ݷ���Id��ȡ������Ϣ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id��
			*
			* @note ��ȡ������ϢΪ�첽���������ô˽ӿں�ȴ��ص��к���onGetRoomResult�ص����ж��Ƿ��ȡ�ɹ���
			* @return ���ش�����롣
			*/
			virtual Result getRoomByRoomId(uint32& callId, const String& roomId) = 0;

			typedef void(*FuncGetRoomResult) (uint32 callId, Result result, const RoomInfo& room);
			virtual Result getRoomByRoomId(uint32& callId, const String& roomId, FuncGetRoomResult func) = 0;

			/** ����Ӧ�ò㷿��Id��ȡ������Ϣ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] appRoomId Ӧ�ò㷿��Id��
			*
			* @note ��ȡ������ϢΪ�첽���������ô˽ӿں�ȴ��ص��к���onGetRoomResult�ص����ж��Ƿ��ȡ�ɹ���
			* @return ���ش�����롣
			*/
			virtual Result getRoomByAppRoomId(uint32& callId, const String& appRoomId) = 0;
			virtual Result getRoomByAppRoomId(uint32& callId, const String& appRoomId, FuncGetRoomResult func) = 0;

			/** ���ҷ�����Ϣ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] filter ����������json�ַ������÷�����Ϣ�ṹ�е��ֶΡ�fieldname=value,...������ʾ��
			*
			* @note ���ҷ�����ϢΪ�첽���������ô˽ӿں�ȴ��ص��к���onFindRoomsResult�ص����ж��Ƿ���ҳɹ���
			* @return ���ش�����롣
			*/
			virtual Result findRooms(uint32& callId, const String& filter) = 0;
			/** ���ŷ���
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomInfo ������Ϣ��
			*
			* @note ���ŷ���Ϊ�첽���������ô˽ӿں�ȴ��ص��к���onScheduleRoomResult�ص����ж��Ƿ��ųɹ���
			* RoomInfo ��  
			room.roomName  = "xxx";			//�������ƣ�һ����Ҫ��д��
			room.appRoomId = "xxxxxx";		//����Ӧ�ò�Id��Ӧ�ò㴴������ʱ���ã�Ӧ�ò�����ڱ�ʾ���䣻 ������д������Ҫȷ��Ψһ��
			room.maxAttendee = 5;			//��������û�������, ����ʵ����Ҫ��д��	
			room.maxAudio = 3;				//���������Ƶ������, ����ʵ����Ҫ��д��
			room.maxVideo = 2;				//���������Ƶ������, ����ʵ����Ҫ��д��
			room.setRoomMode(tee3::avd::rm_mcu); //����ģʽ������Ϊmcuģʽ
			���ϲ�������Ҫ��д�� �����������Ը�����������á�
			*
			* @return ���ش�����롣
			*/
			virtual Result scheduleRoom(uint32& callId, const RoomInfo& roomInfo) = 0;

			typedef void(*FuncScheduleRoomResult) (uint32 callId, Result result, const RoomId& roomId);
			virtual Result scheduleRoom(uint32& callId, const RoomInfo& roomInfo, FuncScheduleRoomResult func) = 0;

			/** ɾ������
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id��
			*
			* @note ɾ������Ϊ�첽���������ô˽ӿں�ȴ��ص��к���onCancelRoomResult�ص����ж��Ƿ�ȡ���ɹ���
			* @return ���ش�����롣
			*/
			virtual Result cancelRoom(uint32& callId, const RoomId& roomId) = 0;

			/** ���ݷ���Ż�ȡ��������
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id��
			*
			* @note ��ȡ��������Ϊ�첽���������ô˽ӿں�ȴ��ص��к���onGetUsersCountResult�ص����ж��Ƿ�ȡ���ɹ���
			* @return ���ش�����롣
			*/
			virtual Result getUsersCount(uint32& callId, const RoomId& roomId) = 0;

		public:
			/** ����������־����
			*
			* @param[in] params ��־�ȼ�[sensitive verbose info warning error none ]������ֻ��ȡһ��ֵ��[debug]�Ƿ��ڵ������������ֵʱ�м�ո�ָ���
			* @param[in] filename ��־�ļ�����������־�ļ�������д�ļ���
			*
			* @return ���ش�����롣
			*/
			static Result setLogParams(const String& params, const String& filename);

			/** �ϴ���ǰ��־�ļ�
			* @param[in] rooturl url·����
			*
			* @return ���ش�����롣
			*/
			static Result uploadLogFile(const String& rooturl);

			/** ��ȡ����汾��
			*
			* @return ��������汾�š�
			*/
			static String getVersion();
			/** ���ݴ�������ȡ�����Ĵ�����Ϣ����
			* @param[in] code ������롣
			* @return ���ش�����Ϣ������
			*/
			static String getErrorMessage(Result code);

			/** �ж��Ƿ�ӵ�й���
			* @param[in] ft ����ö�١�
			* @return �����Ƿ�ӵ�С�
			*/
			virtual bool hasFunction(FunctionType ft) const = 0;
			/** ��ȡ���ܼ�
			* @return ���ع��ܼ���
			* @sa FunctionType
			*/
			virtual uint32 getFunctions() const = 0;
		public:
			/** ��������ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @param[in] *value ����ѡ��ֵָ�롣
			*
			* @return ���ش�����롣
			*/
			virtual Result setOption(EngineOption type, void* value) = 0;
			virtual Result setOption(EngineOption type, const String& value) = 0;
			/** ��ȡ����ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @param[out] *value ����ѡ���ֵָ�롣
			*
			* @return ���ش�����롣
			*/
			virtual Result getOption(EngineOption type, void* value) = 0;
			virtual String getOption(EngineOption type) = 0;

		public:
			/** ����ȫ���û���Ϣ
			*
			* @param[in] info �û���Ϣ��
			*
			* @return ���ش�����롣
			* @note ȫ���û���Ϣ���ú����з����ֱ��������붼ʹ�ô��û���Ϣ
			*/
			virtual Result setUserInfo(const User& info) = 0;
			/** ��ȡȫ���û���Ϣ
			* @return �����û���Ϣ��
			*/
			virtual const User& getUserInfo() const = 0;

			virtual const String& getTempDir() const = 0;
		protected:
			virtual ~IAVDEngine() {
			}
		};

	} // namespace avd
} // namespace tee3

#endif//RT_AVDEngine_H_
