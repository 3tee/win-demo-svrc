#ifndef RT_AVDOutgoing_H_
#define RT_AVDOutgoing_H_

#include "common.h"
#include "avdengine.h"
#include "musermanager.h"

namespace tee3 {
	namespace avd {
		/**
		* ����豸�������ӿ�.
		*
		* ����豸��������������з������rtsp����h323��sip�豸�ȹ��ܡ�
		* ͬһ�����ڣ�ͬһuser_addressֻ��һ�����룻��ͬ�����У�ͬһuser_address�ĺ������ͬʱ���ڡ�
		*/
		class RT_API_EXPORT IAVDOutgoing {
		public:
			/**
			* ����豸����ص��ӿ���
			*
			* ����豸����ص��ӿڶ���������ӿڲ������첽���ء�
			*/
			class IListener {
				/// �첽����
			public:
				/** ����û����������첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result �û�����������롣
				* @param[in] roomId ����Id��
				* @param[in] userId �û�Id��
				* @param[in] user_address �û���ʵ��ַ
				* @sa createOutgoingUser
				*/
				virtual void onCreateOutgoingUser(uint32 callId, Result result, const RoomId& roomId, const UserId& userid, const String& user_address) = 0;
				/** ����û�ɾ�������첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result �û�ɾ��������롣
				* @param[in] roomId ����Id��
				* @param[in] userId �û�Id��
				* @param[in] user_address �û���ʵ��ַ
				* @sa destoryOutgoingUser
				*/
				virtual void onDestoryOutgoingUser(uint32 callId, Result result, const RoomId& roomId, const UserId& userid, const String& user_address) = 0;
				/** ����û��б��ѯ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result �û��б��ѯ������롣
				* @param[in] roomId ����Id��
				*
				* @sa getOutgoingUsers
				*/
				virtual void onGetOutgoingUsers(uint32 callId, Result result, const RoomId& roomId, const UsersType& users) = 0;

			protected:
				virtual ~IListener() {
				}
			};
		public:
			/** ��ȡ����豸����ӿ�
			*
			* @return ��������豸����ӿڡ�
			*/
			static IAVDOutgoing* getOutgoing(IAVDEngine *engine);
			/** �ͷŹ��ܶ���
			*/
			static void release();
			/** ��������豸���빦�ܻص�
			*
			* @param[in] *listener �ص�ָ�롣
			* @return ���ش�����롣
			*/
			virtual Result setListener(IListener* listener) = 0;

		public:
			// ����ӿ�
			/** ����û�����
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id��
			* @param[in] user �û���Ϣ���ο�Room.join�ж�user��˵����
			* @param[in] user_address �û���ʵ��ַ����������û�������������
			* ��rtspΪ��rtsp://192.168.0.1:6549/avd��
			*	sip Ϊ��sip://192.168.0.1:6549/avd"
			*	h323Ϊ��h323://192.168.0.1:6549/avd"
			* @param[in] loginName �û���ʵ��ַ�ĵ�½����
			* @param[in] loginPass �û���ʵ��ַ�ĵ�½���롣
			* @note����û�����Ϊ�첽���������ô˽ӿں�ȴ��ص��к���onCreateOutgoingUserResult�ص����ж��Ƿ��ȡ�ɹ���
			*	   ����û������� rtsp�����h323�����sip����ȣ�
			* @return ���ش�����롣
			* @sa onCreateOutgoingUser
			*/
			virtual Result createOutgoingUser(uint32& callId, const RoomId& roomId, const User& user,
				const String& user_address, const String& loginName, const String& loginPass) = 0;
			/** ����û�ɾ��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id��
			* @param[in] userId �û�Id��
			* @param[in] user_address �û���ʵ��ַ��
			* @note����û�ɾ��Ϊ�첽���������ô˽ӿں�ȴ��ص��к���onDestoryOutgoingUser�ص����ж��Ƿ��ȡ�ɹ���
			* @return ���ش�����롣
			* @sa onDestoryOutgoingUser
			*/
			virtual Result destoryOutgoingUser(uint32& callId, const RoomId& roomId, const UserId& userid, const String& user_address) = 0;
			/** ����û��б��ѯ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] roomId ����Id���˲�����Ϊ�գ����Ϊ�գ����������������ϵ�����û��б����򷵻�ĳһ���������û��б�
			* @note����û��б��ѯΪ�첽���������ô˽ӿں�ȴ��ص��к���onGetOutgoingUsers�ص����ж��Ƿ��ȡ�ɹ���
			* @return ���ش�����롣
			* @sa onGetOutgoingUsers
			*/
			virtual Result getOutgoingUsers(uint32& callId, const RoomId& roomId) = 0;

		protected:
			virtual ~IAVDOutgoing() {
			}
		};
	} // namespace avd
} // namespace tee3
#endif//RT_AVDOutgoing_H_
