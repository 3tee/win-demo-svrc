#ifndef RT_Video_H_
#define RT_Video_H_

#include "common.h"
#include "room.h"
#include "videocapture.h"

namespace tee3 {
	namespace avd {
		class IRoom;
		class IVideoRender;

		/**
		* ��Ƶ�豸����ӿ�.
		*
		* ��Ƶ�豸����ӿڶ��巿������Ƶ�豸��ع��ܽӿڡ�
		*/
		class RT_API_EXPORT ICameraDevice {
		public:
			/**
			* ��Ƶ�豸����ص��ӿ�.
			*
			* ��Ƶ�豸����ص��ӿڶ�������Ƶ�豸���֪ͨ��
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ����ͷ����֪ͨ
				*
				* @param[in] item ����ͷ��Ϣ��
				* @note ��ϵͳ��������ͷ�豸����ʱ���˻ص�������
				*/
				virtual void onCameraPlugin(const Camera& item) = 0;
				/** ����ͷ�γ�֪ͨ
				*
				* @param[in] item ����ͷ��Ϣ��
				* @note ��ϵͳ��������ͷ�豸�γ�ʱ���˻ص�������
				*/
				virtual void onCameraPlugout(const Camera& item) = 0;
			protected:
				virtual ~IListener() {}
			};
		public:
			/** ������Ƶ�豸����ص��ӿ�
			*
			* @param[in] *listener ��Ƶ�豸����ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;

			/** ��ȡָ���豸Id������ͷ��Ϣ
			*
			* @param[in] deviceId �豸Id��
			* @return ��������ͷ��Ϣ��
			* @note ���Է��ر����û���Զ���û�������ͷ��Ϣ��
			*/
			virtual const Camera& getCamera(const DeviceId& deviceId) const = 0;
			/** ��ȡָ���豸Id������ͷ����
			*
			* @param[in] deviceId �豸Id��
			* @return ��������ͷ���͡�
			* @note ���Է��ر����û���Զ���û�������ͷ��Ϣ��
			*/
			virtual CameraType getCameraType(const DeviceId& deviceId) const = 0;
			/** ��ȡָ���豸Id������ͷ�ɼ������б�
			*
			* @param[in] deviceId �豸Id��
			* @return ���زɼ������б�
			* @sa CapabilitiesType
			*/
			virtual CapabilitiesType getCameraCapability(const DeviceId& deviceId) const = 0;
			///local
			/** ��ȡ����ȱʡ����ͷ��Ϣ
			* @return ��������ͷ��Ϣ��
			*/
			virtual const Camera& getDefaultCamera() const = 0;
			/** ���ñ���ȱʡ����ͷ��Ϣ
			*
			* @param[in] deviceId �豸Id��
			* @return ���ش�����롣
			*/
			virtual Result setDefaultCamera(const DeviceId& deviceId) = 0;
			/** ���ñ���ȱʡ����ͷ��Ϣ
			*
			* @param[in] type ����ͷ���͡�
			* @return ���ش�����롣
			*/
			virtual Result setDefaultCamera(CameraType type) = 0;
			/** ��ȡ������ͷ�豸�б�
			*
			* @param[in,out] items ����ͷ�豸�б�
			* @return ���ش�����롣
			*/
			virtual Result getLocalCameras(CamerasType& items) const = 0;
			/** ��ȡָ�����͵ı�������ͷ��Ϣ
			*
			* @param[in] type ����ͷ���͡�
			* @return ��������ͷ�豸��Ϣ��
			* @sa CameraType
			*/
			virtual const Camera& getLocalCamera(CameraType type) const = 0;
			
			///remote 
			/** ��ȡԶ���û�������ͷ�豸�б�
			*
			* @param[in] userId �û�Id��
			* @param[in,out] items ����ͷ�豸�б�
			* @return ���ش�����롣
			*/
			virtual Result getRemoteCameras(const UserId& userId, CamerasType& items) const = 0;

		protected:
			virtual ~ICameraDevice() {}
		};

		/**
		* ��������Ƶģ��ӿ�.
		*
		* ������Ƶģ�鶨�巿������Ƶ���������Ĺ��ܽӿڡ�
		*/
		class RT_API_EXPORT IMVideo : public IModule {
		public:
			/**
			* ��������Ƶģ��ص��ӿ�.
			*
			* ��Ƶģ��ص��ӿڶ����˷�������Ƶ��ص�֪ͨ����Ƶ�첽�������ء�
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ����ͷ״̬����֪ͨ
				*
				* @param[in] status ����ͷ״̬��
				* @param[in] fromId ����ͷId��Ψһ��ʾһ������ͷ��
				* @note ������ͷ״̬���ĺ󣬷����������û����յ���֪ͨ, notify when publishLocalCamera,publishRemoteCamera��
				*/
				virtual void onCameraStatusNotify(CameraStatus status, const DeviceId& fromId) = 0;
				/** ����ͷ���ݸ���֪ͨ
				*
				* @param[in] level ����ͷ�������ݡ�
				* @param[in] description ����ͷ�ַ������ݡ�
				* @param[in] fromId ����ͷId��Ψһ��ʾһ������ͷ��
				* @note ������ͷ���ݸ��ĺ󣬷����������û����յ���֪ͨ, notify when publishLocalCamera(Camera), updateCameraData��
				*/
				virtual void onCameraDataNotify(int level, const String& description, const DeviceId& fromId) = 0;
				/** ����ͷ��Ƶ����֪ͨ
				*
				* @param[in] camera ����ͷ��Ϣ������ͷ��Ϣ��level��descriptionΪӦ�ò����ݣ�Ӧ�ò����ʹ����Щ�ֶα��������ͷ��Ƶ��ص�Ӧ���߼����ݣ������ʾ��������Ƶ��
				*
				* @note ������ͷ��Ƶ����ʱ�������������û����յ���֪ͨ����֪ͨ����Ҫ�̶ȣ�����onCameraStatusNotify�з������״̬��
				* @sa publishLocalCamera
				*/
				virtual void onPublishCameraNotify(const Camera& camera) = 0;
				/** ����ͷ��Ƶȡ������֪ͨ
				*
				* @param[in] camera ����ͷ��Ϣ��
				*
				* @note ������ͷ��Ƶȡ������ʱ�������������û����յ���֪ͨ����֪ͨ����Ҫ�̶ȣ�����onCameraStatusNotify�з������״̬��
				* @sa unpublishLocalCamera
				*/
				virtual void onUnpublishCameraNotify(const Camera& camera) = 0;

				/// �첽����
				/** ���û�������Ƶ�첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ����ͷId��Ψһ��ʾһ·��Ƶ��
				*
				* @sa subscribe
				*/
				virtual void onSubscribeResult(Result result, const DeviceId& fromId) = 0;
				/** ���û�ȡ��������Ƶ�첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ����ͷId��Ψһ��ʾһ·��Ƶ��
				*
				* @sa unsubscribe
				*/
				virtual void onUnsubscribeResult(Result result, const DeviceId& fromId) = 0;
				/** ���û���������ͷ��Ƶ�첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ����ͷId��Ψһ��ʾһ·��Ƶ��
				*
				* @sa publishLocalCamera
				*/
				virtual void onPublishLocalResult(Result result, const DeviceId& fromId) = 0;
				/** ���û�ȡ����������ͷ��Ƶ�첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ����ͷId��Ψһ��ʾһ·��Ƶ��
				*
				* @sa unpublishLocalCamera
				*/
				virtual void onUnpublishLocalResult(Result result, const DeviceId& fromId) = 0;

			protected:
				virtual ~IListener() {}
			};
		public:
			/** ��ȡ��������Ƶģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			*
			* @return ������Ƶģ��ӿ�ָ�롣
			*/
			static IMVideo* getVideo(IRoom* room);
			//
			/** ������Ƶģ��ص��ӿ�
			*
			* @param[in] *listener ��Ƶģ��ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** ������Ƶ��̬���ʵ����ķ�Χ����С���������ʣ�
			*
			* @param[in]  deviceId ��Ƶ�豸��ӦID��
			* @param[in] minBitrateBps ��С������,��λbps
			* @param[in] maxBitrateBps ��������,��λbps
			* @return ���ش�����롣
			* @note ����30k/s = 30*8*1000 bps(bits/s)����min��max���ʱ�����ʹ̶��������ᶯ̬������
			*		��Ҫ����Ƶpublish�ɹ�����������á�
			* �ο�������
			*	1920x1080		[2000*1000, 4000*1000]
			*	1280x720		[1000*1000, 2000*1000]
			*	640x480			[500*1000,  1000*1000]
			*	320x240			[250*1000,	500*1000]
			*/
			virtual Result setVideoBitrate(const DeviceId& deviceId, int minBitrateBps, int maxBitrateBps) = 0;

			/// main(default) camera operate
			virtual bool   isLocalCameraInPreview(const DeviceId& fromId) = 0;
			/** Ԥ������ȱʡ����ͷ��Ƶ
			*
			* @param[in] *render ��ʾ����ӿ�ָ��
			* @note ������Ƶ�ڷ���������ǰ�����Ե��ô˽ӿڽ�����ƵԤ������Ƶ�����������к���Ҫʹ��attachRender�ӿ���������Ƶ��ʾ����ʱ�˽ӿ���Ч��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result previewLocalCamera(IVideoRender* render) = 0;
			/** Ԥ��ģ������ͷ��Ƶ
			*
			* @param[in,out] fakeDevice ģ������ͷ��Ϣ���ӿڻ�����deviceId�����ɹ���"userId_"+���û������deviceId), �˴�deviceId���ܰ���'_'��'{'��'}'�������ַ���
			* @param[in] *capture ģ������ͷ��Ƶ����ӿڡ�
			* @param[in] *render ��ʾ����ӿ�ָ��
			* @return ���ش�����롣
			* ģ������ͷ�����ڷ����е����ض��Ѿ����ڵ���Ƶ��������������Ƶ�ļ���¼��ϵͳ��Ƶ���ȡ�
			* @sa FakeVideoCapturer
			* @note render ��������ΪNULL��
			* @note fakeDevice.id �ᰴ��3tee�豸id�������¹���ɡ�
			*/
			virtual Result previewLocalCamera(Camera& fakeDevice, FakeVideoCapturer* capture, IVideoRender* render) = 0;
			/** ȡ��Ԥ��ȱʡ����ͷ��Ƶ
			* @return ���ش�����롣
			*/
			virtual Result unpreviewLocalCamera() = 0;
			/** ��������ʹ�õ�����ͷ����Ƶ�������ֱ��ʺ�֡�ʣ�
			* @param[in] deviceId ����ͷId��
			* @param[in] quality ��Ƶ������
			* @return ���ش�����롣
			*/
			virtual Result updateCaptureCapability(const DeviceId& deviceId, CameraCapability& quality) = 0;

			/** ����ȱʡ����ͷ��Ƶ
			*
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishLocalResult �з��ء�
			* @sa onPublishLocalResult
			*/
			virtual Result publishLocalCamera() = 0;
			/** ȡ������ȱʡ����ͷ��Ƶ
			*
			* @return ���ش�����롣
			* @note ȡ����������Ϊ�첽��������������� onUnpublishLocalResult �з��ء�
			* @sa onUnpublishLocalResult
			*/
			virtual Result unpublishLocalCamera() = 0;

			/// ������ͷ����ģʽ����ͬʱ�򿪶������ͷ��������ǰ�����������ͷ��						*************************
			/** Ԥ������ĳһ����ͷ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @param[in] *render ��ʾ����ӿ�ָ��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result previewLocalCamera(const DeviceId& deviceId, IVideoRender* render) = 0;
			virtual Result previewLocalCamera(const Camera& device, IVideoRender* render) = 0;
			/** ȡ��Ԥ������ͷ��Ƶ
			* @param[in] deviceId ����ͷId��
			* @return ���ش�����롣
			*/
			virtual Result unpreviewLocalCamera(const DeviceId& deviceId) = 0;
			/** ��������ͷ��Ƶ
			*
			* @param[in] device ����ͷ��Ϣ��
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishLocalResult �з��ء�
			* @sa onPublishLocalResult
			*/
			virtual Result publishLocalCamera(const Camera& device) = 0;
			/** ����ģ������ͷ��Ƶ
			*
			* @param[in,out] fakeDevice ģ������ͷ��Ϣ���ӿڻ�����deviceId�����ɹ���"userId_"+���û������deviceId), �˴�deviceId���ܰ���'_'��'{'��'}'�������ַ���
			* @param[in] *capture ģ������ͷ��Ƶ����ӿڡ�
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishLocalResult �з��ء�
			* ģ������ͷ�����ڷ����е����ض��Ѿ����ڵ���Ƶ��������������Ƶ�ļ���¼��ϵͳ��Ƶ���ȡ�
			* @sa onPublishLocalResult
			* @sa FakeVideoCapturer
			*/
			virtual Result publishLocalCamera(Camera& fakeDevice, FakeVideoCapturer* capture) = 0;
			/** ȡ����������ͷ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @return ���ش�����롣
			* @note ȡ����������Ϊ�첽��������������� onUnpublishLocalResult �з��ء�
			* @sa onUnpublishLocalResult
			*/
			virtual Result unpublishLocalCamera(const DeviceId& deviceId) = 0;
			/** �л���ƵԴ
			*
			* @param[in] fromId ԭ����ͷId��
			* @param[in] toId �л�������ͷId��
			* @return ���ش�����롣
			*/
			virtual Result switchLocalCamera(const DeviceId& fromId, const DeviceId& toId) = 0;

			/// ǰ��������ͷ����ģʽ��ÿһʱ��ֻ�ܴ�ǰ����ߺ�������ͷ�е�һ·��������ǰ���л���		*************************
			/** Ԥ������ǰ�û��ߺ�������ͷ��Ƶ
			*
			* @param[in] type ����ͷ���͡�
			* @param[in] *render ��ʾ����ӿ�ָ��
			* @note ��ǰ��������ͷ����ģʽ����Ч������ͷģʽ������AVDEngine��SetOption�ӿ���ʵ�֣�ȡ��Ԥ���ӿ�ΪunpreviewLocalCamera�����������
			* @return ���ش�����룻����֧�ִ˲������� Err_Not_Available��
			* @sa IVideoRender
			* @sa CameraType
			*/
			virtual Result previewLocalCamera(CameraType type, IVideoRender* render) = 0;
			/** �����ض���������ͷ��Ƶ
			*
			* @param[in] type ����ͷ���͡�
			* @return ���ش�����룻����֧�ִ˲������� Err_Not_Available��
			* @note ��������Ϊ�첽��������������� onPublishLocalResult �з��ء���ǰ��������ͷ����ģʽ����Ч��ȡ��Ԥ���ӿ�ΪunpublishLocalCamera�����������
			* @sa onPublishLocalResult
			*/
			virtual Result publishLocalCamera(CameraType type) = 0;
			/** �л��ض���������ͷ��ƵԴ
			*
			* @param[in] toType ����ͷ���͡�
			* @note ��ǰ��������ͷ����ģʽ����Ч��
			* @return ���ش�����룻����֧�ִ˲������� Err_Not_Available��
			*/
			virtual Result switchToLocalCamera(CameraType toType) = 0;
			/** ��ȡ��ǰʹ�õ�����ͷ����
			*
			* @note ��ǰ��������ͷ����ģʽ����Ч��
			* @return ��������ͷ���͡�
			*/
			virtual CameraType getCurrentCameraType() const = 0;
			/** ��ȡ����ʹ�õ�����ͷ�Ĳɼ���Ϣ
			*
			* @param[in] deviceId ����ͷ�豸ID��
			* @return ���زɼ�������
			*/
			virtual CameraCapability getRealCaptureCapability(const DeviceId& deviceId) = 0;
			/** ����ͷ���ݸ���
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ������ͷ��
			* @param[in] level ����ͷ�������ݡ�
			* @param[in] description ����ͷ�ַ������ݡ�
			* @sa onCameraDataNotify
			*/
			virtual Result updateCameraData(const DeviceId& deviceId, int level, const String& description) = 0;
			/** �Ѿ�published��preview����Ƶ��ͣ����Ƶ��ס����Ҳ�����͵�������
			*
			* @param[in] deviceId ����ͷ�豸ID��
			* @return ���ش�����롣
			*/
			virtual Result muteLocalCamera(const DeviceId& deviceId) = 0;
			/** ȡ����Ƶ��ͣ
			*
			* @param[in] deviceId ����ͷ�豸ID��
			* @return ���ش�����롣
			* @note muteLocalCamera
			*/
			virtual Result unmuteLocalCamera(const DeviceId& deviceId) = 0;

			/// subscribe and publish list
			/** ��������ͷ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @return ���ش�����롣
			* @note ���Ĳ���Ϊ�첽��������������� onSubscribeResult �з��ء�
			* ������Ƶ����
			*	��������Ҫ��ѡ�������������Ƶ��
			*	����������Ҫ������ѡ��Ӳ������������Ƶ��
			*	��Ӳ������������ѡ��ȱʡ���������ȣ�
			*	ͬһ������������·���������Ƿ�֧��Ӳ��������ѡ��������
			* @sa onSubscribeResult
			*/
			virtual Result subscribe(const DeviceId& deviceId) = 0;
			/** ��������ͷ��Ƶָ����Ƶ������Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @param[in] qualityType ָ����Ƶ������
			* @return ���ش�����롣
			* @note ����˵����ͬ���ӿ���������
			*/
			virtual Result subscribe(const DeviceId& deviceId, VideoQuality qualityType) = 0;
			/** ȡ����������ͷ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @return ���ش�����롣
			* @note ȡ�����Ĳ���Ϊ�첽��������������� onUnsubscribeResult �з��ء�
			* @sa onUnsubscribeResult
			*/
			virtual Result unsubscribe(const DeviceId& deviceId) = 0;
			/** ��ȡ�������ѷ�����Ƶ����ͷ�б�
			*
			* @param[in,out] items ����ͷ�豸�б�
			* @return ���ش�����롣
			* @note ����ͷ�б�������ط���������ͷ�ͷ����������û����������ڷ���������ͷ������ͷ��ƵҪ�ڽ�������ʾ��Զ������ͷ��Ҫ������subcribe��
			*		����������ͷ��ʾʱ����Ҫsubscribe��Ӧ�ò㿪��ʱ��Ҫע�⡣
			*/
			virtual Result getPublishedCameras(CamerasType& items) const = 0;
			/** �ж�����ͷ�Ƿ��Ѿ�������������
			* @param[in] fromId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @return �����Ƿ����ѷ���������ͷ��
			*/
			virtual bool isCameraPublished(const DeviceId& fromId) const = 0;
			/** ��ȡ���û����ĵ�����ͷ��Ƶ�б�
			*
			* @param[in,out] items ����ͷ�豸�б�
			* @return ���ش�����롣
			*/
			virtual Result getSubscribedCameras(CamerasType& items) const = 0;
			/** �ж�����ͷ�Ƿ��Ѿ������û�����
			* @param[in] fromId ����ͷId��Ψһ��ʾһ·����ͷ��Ƶ��
			* @return �����Ƿ����Ѷ��ĵ�����ͷ��
			*/
			virtual bool isCameraSubscribed(const DeviceId& fromId) const = 0;
			/// remote camera control
			/** ����Զ���û�����ĳһ����ͷ��Ƶ
			* @param[in] device Զ������ͷ��Ϣ��
			* @return ���ش�����롣
			*/
			virtual Result remotecmdPublishCamera(const Camera& device) = 0;
			/** ����Զ���û�ȡ����������ͷ��Ƶ
			* @param[in] deviceId ����ͷId��
			* @return ���ش�����롣
			*/
			virtual Result remotecmdUnpublishCamera(const DeviceId& deviceId) = 0;

			/// render video
			/** ������Ƶ���ݺ���ʾ������render����ʾ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] *render ��ʾ����ӿ�ָ�롣
			*
			* @note ��Ƶ���ݿ����ڶ����ʾ��������ʾ����һ����ʾ����ĳһʱ��ֻ����ʾһ·��Ƶ��
			*		�ڱ�����Ƶ�����������У�����Զ����Ƶ���ĳɹ��󣬵��ô˽ӿ������Ƶ����ʾ����ĶԽӣ��Ӷ�����ʾ��������ʾ��Ƶ��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result attachRender(const DeviceId& deviceId, IVideoRender* render) = 0;
			/** �������ͷ��Ƶ���ݵ�������ʾ�������
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			*/
			virtual Result detachRender(const DeviceId& deviceId) = 0;
			/** ���ĳһ��ʾ����������ͷ��Ƶ���ݵĹ���
			*
			* @param[in] *render ��ʾ����ӿ�ָ�롣
			* @sa IVideoRender
			*/
			virtual Result detachRender(IVideoRender* render) = 0;

			/// device manager
			/** ��ȡ����ͷ����ӿ�
			*
			* @return ��������ͷ����ӿ�ָ�롣
			* @sa ICameraDevice
			*/
			virtual ICameraDevice* getCameraDevice() = 0;

			///
			/** ���û�ȡ��Ƶ���ݻص��ӿ�,�����ݽ��ص�һ�����ݣ�����Ϊ����Ƶ+����Overlay����Ƶ����Ƶ��СΪ����Ƶ��С����ʹ��ILivecast�ӿڣ�����Ҫ���ô˽ӿڡ�
			*
			* @return ���ش�����롣
			* @sa IVideoRender
			* @note �������Ƶͬʱ��ϳ�����������������Ƶ����������Ƶ�Ļص��ӿڣ�����������Ƶʱ������롣
			*/
			virtual Result setMixerDataListener(IVideoRender* listener) = 0;
			/** ���ûص���Ƶ���ݵ���Ƶ����Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			* @note ���û���������Ƶ��Ч�ڣ�setMixerVideoSizeΪ����Ƶ��С��ͬʱaddMixerOverlayVideo������Ƶ���뵽�����У��ҳ���ȫ����
			*/
			virtual Result setMixerMainVideo(const DeviceId& deviceId) = 0;
			/** ���û�Ƶ����Ƶ���ݵĳߴ�
			*
			* @param[in] width ��Ƶͼ���
			* @param[in] height ��Ƶͼ��ߡ�
			* @param[in] background ����ͼ��
			* @return ���ش�����롣
			* @sa addMixerOverlayVideo
			*/
			virtual Result setMixerVideoSize(int width, int height, const String& background) = 0;
			/** �����Ƶ������Ƶ�ض�λ��
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ���²㣬�ᱻ���ǣ�ȡֵ0-10
			* @param[in] x ����Ƶ�����Ͻ����λ�ã���x���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��width * X
			* @param[in] y ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��height * Y
			* @param[in] w ����Ƶ��ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��width * W
			* @param[in] h ����Ƶ�߶ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��height * H
			* @return ���ش�����롣
			* @sa addMixerOverlayVideo
			*/
			virtual Result addMixerOverlayVideo(const DeviceId& deviceId, int zorder, float x, float y, float w, float h) = 0;
			/** �����Ƶ������Ƶ�ض�λ��
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ���²㣬�ᱻ���ǣ�ȡֵ0-10
			* @param[in] x ����Ƶ�����Ͻ����λ�ã���x���꣬
			* @param[in] y ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬
			* @param[in] w ����Ƶ���, 0ʱȡ��Ƶ������
			* @param[in] h ����Ƶ�߶�, 0ʱȡ��Ƶ����߶�
			* @return ���ش�����롣
			* @sa addMixerOverlayVideo
			*/
			virtual Result addMixerOverlayVideoPixel(const DeviceId& deviceId, int zorder, int x, int y, int w, int h) = 0;
			/** ���¸�����Ƶ������Ƶ����ʾ��λ��
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ���²㣬�ᱻ���ǣ�ȡֵ0-10
			* @param[in] x ����Ƶ�����Ͻ����λ�ã���x���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��width * X
			* @param[in] y ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��height * Y
			* @param[in] w ����Ƶ��ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��width * W
			* @param[in] h ����Ƶ�߶ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��height * H
			* @return ���ش�����롣
			*/
			virtual Result updateMixerOverlayVideo(const DeviceId& deviceId, int zorder, float x, float y, float w, float h) = 0;
			/** ���¸�����Ƶ������Ƶ����ʾ��λ��
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ���²㣬�ᱻ���ǣ�ȡֵ0-10
			* @param[in] x ����Ƶ�����Ͻ����λ�ã���x���꣬
			* @param[in] y ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬
			* @param[in] w ����Ƶ���, 0ʱȡ��Ƶ������
			* @param[in] h ����Ƶ�߶�, 0ʱȡ��Ƶ����߶�
			* @return ���ش�����롣
			*/
			virtual Result updateMixerOverlayVideoPixel(const DeviceId& deviceId, int zorder, int x, int y, int w, int h) = 0;
			/** �Ƴ�����Ƶ�ϵ�ĳһ��Ƶ
			*
			* @param[in] deviceId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			*/
			virtual Result removeMixerOverlayVideo(const DeviceId& deviceId) = 0;
			/** ��������еĻ�����Ƶ����������Ƶ�������Ҫ�ٴο�����������Ҫ������������Ƶ��Overlay��Ƶ��
			*
			* @return ���ش�����롣
			*/
			virtual Result clearMixerVideos() = 0;

			//Interface for test
			virtual bool isCameraWait(const DeviceId& fromId, const String& opt) const {return false;}
			virtual bool isCameraOngoing(const DeviceId& fromId, const String& opt) const {return false;}

		protected:
			virtual ~IMVideo() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_Video_H_
