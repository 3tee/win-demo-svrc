#ifndef RT_Screen_H_
#define RT_Screen_H_

#include "common.h"
#include "room.h"
#include "videocapture.h"

namespace tee3 {
	namespace avd {
		class IRoom;
		class IVideoRender;

		/**
		* ��������Ļ���ڹ���ģ��ӿ�.
		*
		* ������Ļ���ڹ���ģ�鶨�巿������Ļ���ڹ�����ع��ܽӿڡ�
		*/
		class RT_API_EXPORT IMScreen : public IModule {
		public:
			/**
			* ��������Ļ���ڹ���ģ��ص��ӿ�.
			*
			* ��Ļ���ڹ���ģ��ص��ӿڶ����˷�������Ļ���ڹ�����ص�֪ͨ���첽�������ء�
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ��Ļ����״̬����֪ͨ
				*
				* @param[in] status ��Ļ����״̬��
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ����һ��Ӧ�ô��ڡ�
				* @note ����Ļ����״̬���ĺ󣬷����������û����յ���֪ͨ��
				*/
				virtual void onScreenStatusNotify(ScreenStatus status, const DeviceId& fromId) = 0;
				/** ��Ļ�������ݸ���֪ͨ
				*
				* @param[in] level ��Ļ�����������ݡ�
				* @param[in] description ��Ļ�����ַ������ݡ�
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ���ڡ�
				* @note ����Ļ�������ݸ��ĺ󣬷����������û����յ���֪ͨ, notify when publishLocalScreen(Camera), updateScreenData��
				*/
				virtual void onScreenDataNotify(int level, const String& description, const DeviceId& fromId) = 0;
				/** ��Ļ������Ƶ����֪ͨ
				*
				* @param[in] screen ��Ļ������Ϣ����Ļ��Ϣ��level��descriptionΪӦ�ò����ݣ�Ӧ�ò����ʹ����Щ�ֶα������Ļ������ص�Ӧ���߼����ݣ������ʾ��������Ƶ��
				*
				* @note ����Ļ������Ƶ����ʱ�������������û����յ���֪ͨ����֪ͨ����Ҫ�̶ȣ�����onScreenStatusNotify�з������״̬��
				* @sa publishScreen
				*/
				virtual void onPublishScreenNotify(const ScreenWindow& screen) = 0;
				/** ��Ļ������Ƶȡ������֪ͨ
				*
				* @param[in] screen ��Ļ������Ϣ��
				*
				* @note ����Ļ������Ƶȡ������ʱ�������������û����յ���֪ͨ����֪ͨ����Ҫ�̶ȣ�����onScreenStatusNotify�з������״̬��
				* @sa unpublishScreen
				*/
				virtual void onUnpublishScreenNotify(const ScreenWindow& screen) = 0;

				/// �첽����
				/** ���û�������Ļ�����첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ����һ��Ӧ�ô��ڡ�
				*
				* @sa subscribe
				*/
				virtual void onSubscribeScreenResult(Result result, const DeviceId& fromId) = 0;
				/** ���û�ȡ��������Ļ�����첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ����һ��Ӧ�ô��ڡ�
				*
				* @sa unsubscribe
				*/
				virtual void onUnsubscribeScreenResult(Result result, const DeviceId& fromId) = 0;
				/** ���û�������Ļ�����첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ����һ��Ӧ�ô��ڡ�
				*
				* @sa publishScreen
				*/
				virtual void onPublishScreenResult(Result result, const DeviceId& fromId) = 0;
				/** ���û�ȡ��������Ļ�����첽����
				*
				* @param[in] result ������롣
				* @param[in] fromId ��Ļ����Id��Ψһ��ʾһ����Ļ����һ��Ӧ�ô��ڡ�
				*
				* @sa unpublishScreen
				*/
				virtual void onUnpublishScreenResult(Result result, const DeviceId& fromId) = 0;

			protected:
				virtual ~IListener() {
				}
			};
		public:
			/** ��ȡ��������Ļ���ڹ���ģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			* @return ������Ļ���ڹ���ģ��ӿ�ָ�롣
			*/
			static IMScreen* getScreen(IRoom* room);
			//
			/** ���÷�����Ļ���ڹ���ģ��ص��ӿ�
			*
			* @param[in] *listener Զ����Ļ���ڹ���ģ��ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** Ԥ��������Ļ������Ƶ
			*
			* @param[in] device ��Ļ������Ϣ��
			* @param[in] render ��Ļ������Ϣ��
			* @return ���ش�����롣
			*/
			virtual Result previewScreen(const ScreenWindow& device, IVideoRender* render) = 0;
			/** ȡ��Ԥ��������Ļ������Ƶ
			*
			* @return ���ش�����롣
			*/
			virtual Result unpreviewScreen() = 0;
			/** ����������Ļ������Ƶ
			*
			* @param[in] screen ��Ļ������Ϣ���û���������Ϣ�ṹ��level��description�ֶ��з���Ӧ�ò��߼����ݣ�������Ƶ�����Ͷ��ġ�
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishScreenResult �з��ء�
			* @sa onPublishScreenResult
			*/
			virtual Result publishScreen(const ScreenWindow& screen) = 0;

			// Define platform specific window types.
#if defined(RT_DESKTOP)
			/** ���ù�����Ļʱ�ų�����Ĵ����б�
			*
			* @param[in] excluded �ų�����Ĵ����б�
			* @return ���ش�����롣
			*/
			virtual Result setExcludedWindows(std::vector<WindowId>& excluded) = 0;
#endif//RT_DESKTOP

			/** ����ģ����Ļ������Ƶ
			*
			* @param[in,out] fakeDevice ģ����Ļ������Ϣ���ӿڻ�����deviceId�����ɹ���"userId_"+���û������deviceId), �˴�deviceId���ܰ���'_'��'{'��'}'�������ַ���
			* @param[in] *capture ģ����Ļ������Ƶ����ӿڡ�
			* @return ���ش�����롣
			* @note ��������Ϊ�첽��������������� onPublishLocalResult �з��ء�
			* ģ����Ļ���������ڷ����е����ض��Ѿ����ڵ���Ƶ��������Ϊ������Ļ��������Ƶ�ļ���¼��ϵͳ��Ƶ���ȡ�
			* @sa onPublishLocalResult
			* @sa FakeVideoCapturer
			*/
			virtual Result publishScreen(ScreenWindow& fakeDevice, FakeVideoCapturer* capture) = 0;
			/** ȡ������������Ļ��Ƶ
			*
			* @return ���ش�����롣
			* @note ȡ����������Ϊ�첽��������������� onUnpublishScreenResult �з��ء�
			* @sa onUnpublishScreenResult
			*/
			virtual Result unpublishScreen() = 0;
			/** ������Ļ������Ƶ�л�����һ��Ļ����
			*
			* @param[in] deviceId ��Ļ����Id��
			* @return ���ش�����롣
			*/
			virtual Result swithToScreen(const DeviceId& deviceId) = 0;
			/** ������Ļ�������ݸ���
			*
			* @param[in] deviceId ��Ļ����Id��Ψһ��ʾһ����Ļ���ڡ�
			* @param[in] level ��Ļ�����������ݡ�
			* @param[in] description ��Ļ�����ַ������ݡ�
			* @sa onScreenDataNotify
			*/
			virtual Result updateScreenData(const DeviceId& deviceId, int level, const String& description) = 0;
			/** ���Ĺ�����Ļ������Ƶ
			*
			* @param[in] deviceId ��Ļ����Id��Ψһ��ʾһ·�������Ļ������Ƶ��
			* @return ���ش�����롣
			* @note ���Ĳ���Ϊ�첽��������������� onSubscribeResult �з��ء�
			* @sa onSubscribeResult
			*/
			virtual Result subscribe(const DeviceId& deviceId) = 0;
			/** ȡ�����Ĺ�����Ļ������Ƶ
			*
			* @param[in] deviceId ��Ļ����Id��Ψһ��ʾһ·�������Ļ������Ƶ��
			* @return ���ش�����롣
			* @note ȡ�����Ĳ���Ϊ�첽��������������� onUnsubscribeResult �з��ء�
			* @sa onUnsubscribeResult
			*/
			virtual Result unsubscribe(const DeviceId& deviceId) = 0;
			/** ��ȡ�ѹ�����Ļ������Ϣ
			*
			* @param[in,out] items ��Ļ���ڼ��ϴ���б�
			* @return ���ش�����롣
			*/
			virtual Result getPublishedScreens(ScreensType& items) const = 0;
			/** ��ȡ�Ѷ�����Ļ������Ϣ
			*
			* @param[in,out] items ��Ļ���ڼ��ϴ���б�
			* @return ���ش�����롣
			*/
			virtual Result getSubscribedScreens(ScreensType& items) const = 0;
			/** �ж���Ļ�����Ƿ��Ѿ������û�����
			* @param[in] fromId ��Ļ����Id��
			* @return �����Ƿ����Ѷ�����Ļ���ڡ�
			*/
			virtual bool isScreenSubscribed(const DeviceId& fromId) const = 0;

			/// render screen
			/** �����������Ļ������Ƶ���ݺ���ʾ������render����ʾ��Ƶ
			*
			* @param[in] deviceId ��Ļ����Id��Ψһ��ʾһ·�������Ļ������Ƶ��
			* @param[in] *render ��ʾ����ӿ�ָ�롣
			*
			* @note ��Ƶ���ݿ����ڶ����ʾ��������ʾ����һ����ʾ����ĳһʱ��ֻ����ʾһ·��Ƶ��
			*		����Ļ������Ƶ�����������У�����Զ����Ļ������Ƶ���ĳɹ��󣬵��ô˽ӿ������Ƶ����ʾ����ĶԽӣ��Ӷ�����ʾ��������ʾ��Ƶ��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result attachRender(const DeviceId& deviceId, IVideoRender* render) = 0;
			/** �����Ļ������Ƶ��������ʾ�������
			*
			* @param[in] deviceId ��Ļ����Id��Ψһ��ʾһ·�������Ļ������Ƶ��
			* @return ���ش�����롣
			* @sa IVideoRender
			*/
			virtual Result detachRender(const DeviceId& deviceId) = 0;
			/** ���ĳһ��ʾ��������Ļ������Ƶ�Ĺ���
			*
			* @param[in] *render ��ʾ����ӿ�ָ�롣
			* @sa IVideoRender
			*/
			virtual Result detachRender(IVideoRender* render) = 0;

			/// screen manager
			/** ��ȡ������Ļ������Ϣ�б�
			*
			* @param[in,out] items ��Ļ���ڼ��ϴ���б�
			* @return ���ش�����롣
			*/
			virtual Result getScreenWindows(ScreensType& items) = 0;

#if defined(RT_DESKTOP)
			/// ע��
			/**
			* ����ˣ� ��ʾע�͹��������״�׼��͸�����ڣ�appӦ������ע�����򣻽���ע�Ͷ����ݣ��ط�ע�Ͷ����ݣ�
			* ����ˣ� �ۿ�������Ƶ
			* ע�Ͷˣ� ��ʾע�͹�������׼��͸�����ڣ�����ע������    ע��-->���ռ����+ע��״̬+�û���Ϣ��--> ���͸�����ˣ�
			*
			*/

			/** ����ע��
			*
			* @param[in] screenId �Ѿ�publish��ScreenWindow ��ID��
			* @return ���ش�����롣
			* @note 
			* ����˵��õ�ǰ�������ǣ�screenIdָ���ScreenWindow�ѹ���
			* ����˵��õ�ǰ�������ǣ�screenIdָ���ScreenWindow�Ѷ��ģ���������Render����Ⱦ��
			* �ڲ������Renderȷ��ע���ڱ�����ʾ�Ĵ��ڣ�����startOtherAnnotation(screenId, render)
			* ���øýӿڣ���������SDK�ڲ���ʵ�֣������Ҫ�Լ����ƹ����� �����mannotation.h�ļ�
			* @sa startOtherAnnotation
			*/
			virtual Result startAnnotation(const DeviceId& screenId) = 0;
			/** �ر�ע��
			*
			* @param[in] screenId �Ѿ�publish��ScreenWindow ��ID��
			* @return ���ش�����롣
			* @note
			* ֻ��ֹͣע�ͣ��ڲ��������UnpublishScreen��
			*/
			virtual Result stopAnnotation(const DeviceId& screenId) = 0;

			/** ��ʼ�����ע��
			*
			* @param[in] screenId Ҫע�͵ģ��Ѿ�publish��ScreenWindow ��ID��
			* @param[in] render �Ѿ�publish��Screen���ڵ���Ⱦ���ڣ��������½�����Ⱦ���ڡ�
			* @return ���ش�����롣
			* @note
			* screenIdָ���ScreenWindow�Ѷ��ģ����һ���Render����Ⱦ
			*/
			virtual Result startOtherAnnotation(const DeviceId& screenId, IVideoRender* render) = 0;
#endif//RT_DESKTOP

		protected:
			virtual ~IMScreen() {
			}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_Screen_H_
