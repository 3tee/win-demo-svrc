#ifndef RT_Chat_H_
#define RT_Chat_H_

#include "common.h"
#include "room.h"

namespace tee3 {
	namespace avd {
		class IRoom;

		/**
		* ������Ϣ�ṹ.
		*
		* ������Ϣ������һ�δ����������Ϣ��
		*/
		struct Message {
			uint32	 timestamp;						/**< ��Ϣʱ�������Ӧ�ò��Ǳ���ʱ�䣬��������GMTʱ�� */
			UserId   fromId;						/**< ��Ϣ������Id */
			String	 fromName;						/**< ��Ϣ�������� */
			String   message;						/**< ��Ϣ���� */
		};
		/**
		* ������Ϣ�б�����.
		*/
		typedef std::vector<Message> MessagesType;

		/**
		* ����������ģ��ӿ�.
		*
		* ��������ģ�鶨�巿���й��ĺ�˽�ĵ����칦�ܽӿڡ�
		*/
		class RT_API_EXPORT IMChat : public IModule {
		public:
			/**
			* ����������ģ��ص��ӿ�.
			*
			* ����ģ��ص��ӿڶ����˷�����������ص�֪ͨ��
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ���յ�������Ϣ֪ͨ
				*
				* @param[in] message ��Ϣ���ݡ�
				* @note ���û����͹�����Ϣ�󣬷����������û����������ⶼ�����յ���֪ͨ��
				* @sa Message
				* @sa sendPublicMessage
				*/
				virtual void onPublicMessage(const Message& message) = 0;
				/** ���յ�˽����Ϣ֪ͨ
				*
				* @param[in] message ��Ϣ���ݡ�
				* @note ���û�����˽����Ϣ��ֻ����ϢĿ���û����յ�����Ϣ֪ͨ��
				* @sa Message
				* @sa sendPrivateMessage
				*/
				virtual void onPrivateMessage(const Message& message) = 0;
			protected:
				virtual ~IListener() {
				}
			};

			/** ��ȡ����������ģ��ӿ�
			*
			* @param[in] room �������
			* @return ����ģ��ӿڡ�
			* @sa IRoom
			*/
			static IMChat* getChat(IRoom* room);

			/** ���÷�������ģ��ص��ӿ�
			*
			* @param[in] *listener ����ģ��ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** ���͹�����Ϣ
			*
			* @param[in] message ��Ϣ���ݡ�
			*
			* @return ���ش�����롣
			*/
			virtual Result sendPublicMessage(const String& message) = 0;
			/** ����˽����Ϣ
			*
			* @param[in] message ��Ϣ���ݡ�
			* @param[in] toId ˽����ϢĿ���û�Id��
			*
			* @return ���ش�����롣
			*/
			virtual Result sendPrivateMessage(const String& message, const UserId& toId) = 0;

			/** ��ȡ������ʷ��Ϣ��¼
			*
			* @param[in] latest �Ƿ������¼�¼�������򣩡�
			* @param[in] begindex ��Ϣ��ʼ������
			* @param[in,out] ncount ������Ϣ������ʵ����Ϣ����������
			* @param[out] msgs ������Ϣ�б�
			*
			* @return ���ش�����롣
			*/
			virtual Result getPublicHistoryMessage(bool latest, uint32 begindex, uint32& ncount, MessagesType& msgs) = 0;
			/** ��ȡ˽����ʷ��Ϣ��¼
			*
			* @param[in] userId ����Է����û�Id��
			* @param[in] latest �Ƿ������¼�¼�������򣩡�
			* @param[in] begindex ��Ϣ��ʼ������
			* @param[in,out] ncount ������Ϣ������ʵ����Ϣ����������
			* @param[out] msgs ������Ϣ�б�
			*
			* @return ���ش�����롣
			*/
			virtual Result getPrivateHistoryMessage(const UserId& userId, bool latest, uint32 begindex, uint32& ncount, MessagesType& msgs) = 0;

		protected:
			virtual ~IMChat() {
			}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_Chat_H_
