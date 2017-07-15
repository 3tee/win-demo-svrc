#ifndef RT_EasyRoom_H
#define RT_EasyRoom_H

#include "common.h"
#include "videorender.h"
#include "videocapture.h"
#include "audiocapture.h"
#include "musermanager.h"
#include "mvideomixer.h"
#include "maudio.h"

namespace tee3 {
	namespace avd {
		class User;

		/**
		* ���׷���ӿ���
		*
		* ���׷���ӿڶ����˶����ļ��׷�����󴴽����ͷš����书�ܲ�����
		*/
		class RT_API_EXPORT IEasyRoom {
		public:
			/**
			* ���뷿��ص��ӿ�
			* @param[in] result ���������롣
			* @sa join
			*/
			typedef  void(*FuncJoinResult) (const RoomId& roomId, Result result);

			/**
			* �첽��������.
			*/
			enum OperateType {
				ot_publishMicrophone = 1,		/**< �����з�������Ƶ  */
				ot_unpublishMicrophone = 2,		/**< �����йرշ�������Ƶ   */
				ot_publishCamera = 3,			/**< �����з�������Ƶ  */
				ot_unpublishCamera = 4,			/**< �����йرշ�������Ƶ  */
				ot_attachRender = 5,			/**< �����ж�����ʾ��Ƶ  */
				ot_detachRender = 6,			/**< ������ȡ��������ʾ��Ƶ  */
			};

			/**
			* ���׷���ص��ӿ���
			*
			* ���׷���ص��ӿڶ����˷������������첽���أ�����֪ͨ������ָʾ��
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

				/** ��������״̬֪ͨ
				*
				* @param[in] status ��ǰ����״̬��
				*/
				virtual void onConnectionStatus(ConnectionStatus status) = 0;

				///
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

				///
				/** ��˷�״̬����֪ͨ
				*
				* @param[in] status ��˷�״̬��
				* @param[in] fromId �豸�����û�Id��
				* @note ����˷�״̬���ĺ󣬷����������û����յ���֪ͨ��
				* @sa openMicrophone
				* @sa closeMicrophone
				*/
				virtual void onMicrophoneStatusNotify(MicrophoneStatus status, const UserId& fromId) = 0;
				/** ����ͷ״̬����֪ͨ
				*
				* @param[in] status ����ͷ״̬��
				* @param[in] fromId �豸�����û�Id��
				* @note ������ͷ״̬���ĺ󣬷����������û����յ���֪ͨ, notify when publishCamera, unpublishCamera��
				*/
				virtual void onCameraStatusNotify(CameraStatus status, const UserId& fromId) = 0;

				/// �첽����
				/** �첽����
				* @param[in] type �������͡�
				* @param[in] result ����������롣
				* @note ���첽����ʱ,�첽���ؽ����
				*/
				virtual void onOperateResult(OperateType type, Result result) = 0;
			protected:
				virtual ~IListener() {}
			};

		///
		public:
			/** ��ȡ�򴴽�����ӿ�
			*
			* @param[in] roomId ����Id��
			* @note ֻ֧�ֵ��û�Ӧ�ã���֧�ֶ��û�Ӧ�á�
			* @return ���ط���ӿ�ָ�롣
			*/
			static IEasyRoom* obtain(const RoomId& roomId);
			/** �ͷŷ���ӿ�
			*
			*@note �ͷŷ����App�㲻����ʹ�õ�ǰ����ָ�룬�������÷���ָ�봦��������ΪNULL��
			*/
			virtual void release() = 0;

		public: /// ��������˳��߼�
			/** ���÷���ص��ӿ�
			*
			* @param[in] *listener �ص��ӿ�ָ�롣
			*
			* @return ���ش�����롣
			* @see IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** ���뷿��
			*
			* @param[in,out] user �û���Ϣ���û�Id(���ܰ���'{'��'}'�ַ�)���û������û����ݵȣ���Ӧ�ò㲻����user.userIdʱ��SDK������һ���µ�guid��Ϊuser.userId��ͬʱ���ظ�Ӧ�ò㡣
			* @param[in] joinresult �ӷ���ص��ӿڡ�
			* @note ���뷿��ʱ������ָ����������ص��ӿڣ����ָ��������ָ�������ӿڻص���������Listener��onJoinResult�ص���
			* @return ���ش�����롣
			* @sa User
			*/
			virtual Result join(const User& user, FuncJoinResult joinresult) = 0;
			virtual bool   isWorking() const = 0;
			/** ��ǰ�û��뿪����
			*
			* @param[in] reason �û��뿪�����ԭ����룬�����뿪ΪAVD_OK��
			*
			* @note ��ǰ�û��뿪����󣬵�ǰ�������ͷ���ĸ�����ģ�鶼�������״̬�����ܲ�����Ч��
			* @return ���ش�����롣
			*/
			virtual Result leave(Result reason) = 0;				// leave myself
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

		public: /// ������Ϣ���û���Ϣ����
			/** ��ȡ����Id
			*
			* @return ���ط���Id��
			*/
			virtual const RoomId& getRoomId() const = 0;
			/** ��ȡ������Ϣ
			*
			* @return ���ط�����Ϣ��
			* @sa RoomInfo
			*/
			virtual const RoomInfo& getRoomInfo() const = 0;
			/** ��ȡ���û���Ϣ
			* @return ���ر��û���Ϣ��
			*/
			virtual const User& getSelfUser() const = 0;
			/** ��ȡ���û�Id
			* @return ���ر��û�Id��
			*/
			virtual const UserId& getSelfUserId() const = 0;
			virtual uint32 getParticipantsCount() const = 0;
			/** ��ȡ�����е��û��б�
			* @param[in] begindex ��ʼ������
			* @param[in,out] ncount ����������ʵ�ʷ���������
			* @param[out] users �û��б��ϡ�
			* @note �û��б��������û���
			* @return ���ش�����롣
			*/
			virtual Result getParticipants(uint32 begindex, uint32& ncount, UsersType& users) = 0;

		public: /// ����Ƶ����
			/** ������Ƶ����ͷ�ɼ��������Ȳ���
			* @param[in] param ��Ƶ������
			* @return ���ش�����롣
			*/
			virtual Result setVideoParams(const VideoParams& param) = 0;
			virtual VideoParams getVideoParams() const = 0;
			/** ������Ƶ��˷�ɼ��������Ȳ���
			* @param[in] param ��Ƶ������
			* @return ���ش�����롣
			*/
			virtual Result setAudioParams(const AudioParams& param) = 0;
			virtual AudioParams getAudioParams() const = 0;
			/** ����ֱ������������Խ������ڣ�ǰ: ������Ƶ����������Դ
			*
			* @param[in] *vcapturer ��Ƶ����������Դ��
			* @return ���ش�����롣
			* @sa FakeVideoCapturer
			*/
			virtual Result setVideoSource(FakeVideoCapturer* vcapturer) = 0;
			/** ����ֱ������������Խ������ڣ�ǰ: ������Ƶ����������Դ
			*
			* @param[in] *acapturer ��Ƶ����������Դ��
			* @return ���ش�����롣
			* @sa FakeAudioCapturer
			*/
			virtual Result setAudioSource(FakeAudioCapturer* acapturer) = 0;

			/** �򿪱�����˷緢����������
			*
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onOpenMicrophoneResult �з��ء�
			* ֻ֧�ֵ�����Ƶ�����豸����������� FakeAudioCapturer����ʹ���ⲿ������Ƶ�� 
			* ���û�������ⲿ������ƵԴ����������ʹ��ȱʡ��Ƶ�豸��
			* @sa onOpenMicrophoneResult
			*/
			virtual Result publishMicrophone() = 0;
			/** �رձ�����˷緢����������
			*
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onCloseMicrophoneResult �з��ء�
			* @sa onCloseMicrophoneResult
			*/
			virtual Result unpublishMicrophone() = 0;

			/** Ԥ������ȱʡ����ͷ��Ƶ
			*
			* @param[in] *render ��ʾ����ӿ�ָ��
			* @note ������Ƶ�ڷ���������ǰ�����Ե��ô˽ӿڽ�����ƵԤ������Ƶ�����������к���Ҫʹ��attachRender�ӿ���������Ƶ��ʾ����ʱ�˽ӿ���Ч��
			* ֻ֧�ֵ�����Ƶ�����豸����������� FakeVideoCapturer ����ʹ���ⲿ������Ƶ��
			* ���û�������ⲿ������ƵԴ����������ʹ��ȱʡ��Ƶ�豸��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result previewCamera(IVideoRender* render) = 0;
			/** ȡ��Ԥ��ȱʡ����ͷ��Ƶ
			* @return ���ش�����롣
			*/
			virtual Result unpreviewCamera() = 0;
			/** ����ȱʡ����ͷ��Ƶ
			*
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishResult �з��ء�
			* @sa onPublishResult
			*/
			virtual Result publishCamera() = 0;
			/** ȡ������ȱʡ����ͷ��Ƶ
			*
			* @return ���ش�����롣
			* @note ȡ����������Ϊ�첽��������������� onUnpublishResult �з��ء�
			* @sa onUnpublishResult
			*/
			virtual Result unpublishCamera() = 0;
			/** ������Ƶ���ݺ���ʾ������render����ʾ��Ƶ
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] *render ��ʾ����ӿ�ָ�롣
			*
			* @note ��Ƶ���ݿ����ڶ����ʾ��������ʾ����һ����ʾ����ĳһʱ��ֻ����ʾһ·��Ƶ��
			*		�ڱ�����Ƶ�����������У�����Զ����Ƶ���ĳɹ��󣬵��ô˽ӿ������Ƶ����ʾ����ĶԽӣ��Ӷ�����ʾ��������ʾ��Ƶ��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result attachRender(const UserId& userId, IVideoRender* render) = 0;
			/** �������ͷ��Ƶ���ݵ�������ʾ�������
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			*/
			virtual Result detachRender(const UserId& userId) = 0;
			/** ��Ƶ�л�����ͷ
			* @return ���ش�����롣
			*/
			virtual Result switchCamera() = 0;

			/** �жϱ�����˷��Ƿ�Ĭ
			* @return ���ؾ�Ĭ״̬��
			*/
			virtual bool ismuteMicrophone() const = 0;
			/** ������˷羲Ĭ
			* @return ���ش�����롣
			*/
			virtual Result muteMicrophone() = 0;
			/** ������˷羲Ĭȡ��
			* @return ���ش�����롣
			*/
			virtual Result unmuteMicrophone() = 0;

		public: /// ����Ƶ��������
			/** ���û�ȡ�������ݻص��ӿ�
			* @param[in] listener �������ݻص�ָ�롣
			* @param[in] sampleRate �����������ݵĲ����ʣ�16000,44100,48000��
			* @return ���ش�����롣
			* @sa IAudioRender
			* @sa ro_audio_mixerdata_callback_buffered ���λ������ݻص���10ms���ݡ����ǡ�1024samples���ݡ�
			* @note �������Ƶͬʱ��ϳ�����������������Ƶ����������Ƶ�Ļص��ӿڣ�����������Ƶʱ������롣
			*/
			virtual Result setAudioMixerDataListener(IAudioRender* listener, uint32 sampleRate) = 0;
			/** ���û�ȡ��Ƶ���ݻص��ӿ�,�����ݽ��ص�һ�����ݣ�����Ϊ����Ƶ+����Overlay����Ƶ����Ƶ��СΪ����Ƶ��С����ʹ��ILivecast�ӿڣ�����Ҫ���ô˽ӿڡ�
			*
			* @return ���ش�����롣
			* @sa IVideoRender
			* @note �������Ƶͬʱ��ϳ�����������������Ƶ����������Ƶ�Ļص��ӿڣ�����������Ƶʱ������롣
			*/
			virtual Result setVideoMixerDataListener(IVideoRender* listener) = 0;
			/** ��ȡ��Ƶ��Ƶ���ֽӿ�
			* @return ��Ƶ���ֽӿ�
			*/
			virtual IMVideoMixer* getVideoMixer() = 0;

		public: /// ����ͳ����Ϣ
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
		public:
			/** ���÷���ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @param[in] value ����ѡ��ֵ�ַ�����
			* @return ���ش�����롣
			*/
			virtual Result setOption(RoomOption type, const String& value) = 0;
			/** ��ȡ����ѡ��
			*
			* @param[in] type ����ѡ�����͡�
			* @return ���ط���ѡ���ַ�����
			*/
			virtual String getOption(RoomOption type) = 0;

		protected:
			virtual ~IEasyRoom() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_EasyRoom_H
