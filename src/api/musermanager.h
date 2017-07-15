#ifndef RT_UserManager_H_
#define RT_UserManager_H_

#include "common.h"

namespace tee3 {
	namespace avd {
		class IRoom;
		/**
		* �û����ݽṹ.
		*
		* �û����ݶ������û��Ļ�����Ϣ��
		*/
		class User {
		public:
			UserId userId;							/**< �û�Id��Ӧ�ò������ */
			UserStatus status;						/**< �û�״̬����  */
			String userName;						/**< �û����ƣ�Ӧ�ò�����  */
			String userData;						/**< �û����ݣ�Ӧ�ò�����  */
			uint32 nodeId;
		public:
			bool isValid() const { return !userId.empty(); }
			User() : nodeId(0) {}
		};
		/**< �û��������� */
		typedef std::vector<User> UsersType;

		/**
		* �û�����ӿ���
		*
		* �û�����ӿڶ����˷����������û����û��б���صĹ��ܲ�����
		*/
		class RT_API_EXPORT IMUserManager {
		public:
			/**
			* �û�����ص��ӿ���
			*
			* �û�����ص��ӿڶ����˷����û����û��б�������첽���أ������û�֪ͨ��
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** �û����뷿��֪ͨ
				*
				* @param[in] user �û���Ϣ���ݡ�
				*
				* @note ĳ�û����÷����е�join���뷿��󣬷����������û�����յ���֪ͨ
				* @sa join
				*/
				virtual void onUserJoinNotify(const User& user) = 0;
				/** �û��뿪����֪ͨ
				*
				* @param[in] user �û���Ϣ���ݡ�
				*
				* @note ĳ�û����÷����е�leave�뿪����󣬷����������û�����յ���֪ͨ
				* @sa leave
				*/
				virtual void onUserLeaveNotify(const User& user) = 0;
				/** �û���Ϣ����֪ͨ
				*
				* @param[in] user �û���Ϣ���ݡ�
				*
				* @note ĳ�û�����updateUser�����Լ���Ϣ�󣬷����������û�����յ���֪ͨ
				* @sa updateUser
				*/
				virtual void onUserUpdateNotify(const User& user) = 0;
				/** �û�״̬����֪ͨ
				*
				* @param[in] status ��ǰ�û�״̬��
				* @param[in] fromId �������û�Id��
				*
				* @note ĳ�û�����updateSelfUserStatus�����Լ�״̬�󣬷����������û�����յ���֪ͨ��
				*       ��֪ͨ��onUserUpdateNotify�з�����������û�״̬���Ľ�ΪƵ��
				* @sa updateSelfUserStatus
				* @sa onUserUpdateNotify
				*/
				virtual void onUserStatusNotify(UserStatus status, const UserId& fromId) = 0;
				/** �û�Ӧ�ò����ݸ���֪ͨ
				*
				* @param[in] userData ��ǰ�û�Ӧ�ò����ݡ�
				* @param[in] fromId �������û�Id��
				*
				* @note ĳ�û�����updateSelfUserData�����Լ�Ӧ�ò����ݺ󣬷����������û�����յ���֪ͨ
				*       ��֪ͨ��onUserUpdateNotify�з����������Ӧ�ò������û���Ϊ��ע
				* @sa updateSelfUserData
				* @sa onUserUpdateNotify
				*/
				virtual void onUserDataNotify(const String& userData, const UserId& fromId) = 0;

			protected:
				virtual ~IListener() {}
			};
		public:
			/** ��ȡ�������û�����ģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			*
			* @return �����û�����ģ��ӿ�ָ�롣
			*/
			static IMUserManager* getUserManager(IRoom* room);

			//
			/** �����û�����ص��ӿ�
			*
			* @param[in] *listener �ص��ӿ�ָ�롣
			*
			* @return ���ش�����롣
			* @see IListener
			*/
			virtual Result setListener(IListener* listener) = 0;

			/** ���±��û���Ϣ
			*
			* @param[in] user �û���Ϣ��
			*
			* @return ���ش�����롣
			*/
			virtual Result updateUser(const User& user) = 0;
			/** �ж��û��Ƿ����
			*
			* @param[in] userId �û�Id��
			*
			* @return �Ƿ�����û���
			*/
			virtual bool hasUser(const UserId& userId) const = 0;
			/** ��ȡ����Id���û���Ϣ
			*
			* @param[in] userId �û�Id��
			*
			* @return ���ع���Id���û���Ϣ��
			*/
			virtual const User& getUser(const UserId& userId) const = 0;
			/** ��ȡ��������Ϣ
			* @return ������������Ϣ��
			*/
			virtual const User& getHost() const = 0;
			/** ��ȡ���û���Ϣ
			* @return ���ر��û���Ϣ��
			*/
			virtual const User& getSelfUser() const = 0;
			/** ��ȡ���û�Id
			* @return ���ر��û�Id��
			*/
			virtual const UserId& getSelfUserId() const = 0;
			/** ��ȡ���û�Ӧ�ò�����
			* @return ���ر��û�Ӧ�ò����ݡ�
			*/
			virtual const String& getSelfUserData() const = 0;
			/** ���ı��û���Ӧ�ò�����
			*
			* @param[in] userData ���û�Ӧ�ò����ݡ�
			* @return ���ش�����롣
			*/
			virtual Result updateSelfUserData(const String& userData) = 0;
			/** ���ı��û����û�״̬
			*
			* @param[in] status �û�״̬��
			* @return ���ش�����롣
			*/
			virtual Result updateSelfUserStatus(uint32 status) = 0;
			/** ��ȡ�����е��û�����
			* @return ���ر��û�������
			*/
			virtual uint32 getParticipantsCount() const = 0;
			/** ��ȡ�����е��û��б�
			*
			* @param[in] begindex ��ʼ������
			* @param[in,out] ncount ����������ʵ�ʷ���������
			* @param[out] users �û��б��ϡ�
			* @note �û��б��������û���
			* @return ���ش�����롣
			*/
			virtual Result getParticipants(uint32 begindex, uint32& ncount, UsersType& users) = 0;

		protected:
			virtual ~IMUserManager() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_UserManager_H_
