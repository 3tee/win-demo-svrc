#ifndef RTC_RtspClient_H_
#define RTC_RtspClient_H_

#include "common.h"

namespace tee3 {
	namespace avd {
		/**
		* Rtsp�ͻ���.
		*
		*/
		class FakeAudioCapturer;
		class FakeVideoCapturer;
		class IVideoRender;
		class RT_API_EXPORT RtspClient {
		public:
			/**
			* �ص��ӿ�.
			*
			*/
			class IVideoListener {
			public:
				/// �첽����
				/** ��Ƶ����ص��ӿ�
				*
				* @param[in] type �������͡�
				* @param[in] timestamp_ns ʱ�����
				* @param[in] width	��ȡ�
				* @param[in] height	�߶ȡ�
				* @param[in] isKeyFrame  �Ƿ��ǹؼ�֡��
				* @param[in] data ��Ƶ���ݵ�ַ��
				* @param[in] len ��Ƶ�����ֽڳ��ȡ�
				*
				* @sa
				*/
				virtual void videoEncodedOut(VideoEncodedType type, uint64 timestamp_ns, unsigned int width, unsigned int height, bool isKeyFrame, const uint8 *data, unsigned int len) = 0;

				/** ��ƵYUV���ݻص��ӿ�
				*
				* @param[in] timestamp_ns ʱ�����
				* @param[in] dataY	Y���ݵ�ַ��
				* @param[in] dataU	U���ݵ�ַ��
				* @param[in] dataV	V���ݵ�ַ��
				* @param[in] width	��ȡ�
				* @param[in] height	�߶ȡ�
				* @param[in] strideY	Y���ݵ������س��ȡ�
				* @param[in] strideU	U���ݵ������س��ȡ�
				* @param[in] strideV	V���ݵ������س��ȡ�
				* @param[in] rotation	ͼ��Ƕȡ�
				*
				* @sa
				*/
				virtual void videoYUVOut(uint64 timestamp_ns,
					const uint8_t* dataY,
					const uint8_t* dataU,
					const uint8_t* dataV,
					int width,
					int height,
					int strideY,
					int strideU,
					int strideV,
					int rotation) = 0;


			};
			class IAudioListener {
			public:
				/// �첽����
				/** ��Ƶ����ص��ӿ�
				*
				* @param[in] type �������͡�
				* @param[in] timestamp_ns ʱ�����
				* @param[in] sampleRate	�����ʡ�
				* @param[in] channels	ͨ������
				* @param[in] data  ��Ƶ���ݵ�ַ��
				* @param[in] len ��Ƶ�����ֽڳ��ȡ�
				*
				* @sa
				*/
				virtual void audioEncodedOut(AudioEncodedType type, uint64 timestamp_ns, int sampleRate, int channels, const uint8 *data, unsigned int len) = 0;
				/** ��ƵPCMԭʼ���ݻص��ӿ�
				*
				* @param[in] timestamp_ns ʱ�����
				* @param[in] sampleRate	�����ʡ�
				* @param[in] channels	ͨ������
				* @param[in] data  ��Ƶ���ݵ�ַ��
				* @param[in] len ��Ƶ�����ֽڳ��ȡ�
				*
				* @sa
				*/
				virtual void audioPCMOut(uint64 timestamp_ns, int sampleRate, int channels, const uint8 *data, unsigned int len) = 0;
			};

		public:
			/** ����һ��Rtsp�ͻ���
			*
			* @sa
			*/
			static	RtspClient* create();

			/** ����һ��Rtsp�ͻ���
			*
			* @sa
			*/
			static	void destroy(RtspClient*);

			/** ��ʼ������
			*
			* @param[in] uri rtsp����ַ��
			* @param[in] username	��֤�û�����
			* @param[in] password	��֤���롣
			* @sa
			*/
			virtual Result start(const String& uri, String username = "", String password = "") = 0;
			/** ֹͣ������
			*
			* @sa
			*/
			virtual Result stop() = 0;

			/** ������Ƶ���ص��ӿ�
			*
			* @param[in] listener ��Ƶ���ص��ӿ�ָ�롣
			* @note Ĭ�ϻص�Encoded���ݣ������ҪYUV������Ҫ����enableVideoCallbackYUV��
			* @sa enableVideoCallbackEncoded
			* @sa enableVideoCallbackYUV
			* @return �����롣
			*/
			virtual Result setVideoListener(IVideoListener* listener) = 0;

			/** ������Ƶ���ص��ӿ�
			*
			* @param[in] listener ��Ƶ���ص��ӿ�ָ�롣
			* @note Ĭ�ϻص�Encoded���ݣ������ҪPCM������Ҫ����enableAudioCallbackPCM��
			* @sa enableAudioCallbackEncoded
			* @sa enableAudioCallbackPCM
			* @return �����롣
			*/
			virtual Result setAudioListener(IAudioListener* listener) = 0;


			/** ������Ⱦ�ӿ�ָ��
			*
			* @param[in] render ��Ⱦ�ӿ�ָ�롣
			* @sa
			*/
			virtual Result setRender(IVideoRender* render) = 0;

			/** ����ģ����Ƶ�ɼ��ӿ�ָ��
			*
			* @param[in] capture ģ����Ƶ�ɼ��ӿ�ָ�롣
			* @note ����Ĭ�ϻص�Encoded���ݣ�ֻ��ʹ�õ���������ݵ�VideoCapture�������Ҫ������ǵ���YUV���ݵ�FakeVideoCapture��Ҫ����enableVideoCallbackYUV�����ҵ���enableVideoCallbackEncoded(false)��
			* @sa enableVideoCallbackEncoded
			* @sa enableVideoCallbackYUV
			* @return �����롣
			*/
			virtual Result setVideoCapture(tee3::avd::FakeVideoCapturer* capture) = 0;
			/** ����ģ����Ƶ�ɼ��ӿ�ָ��
			*
			* @param[in] capture ģ����Ƶ�ɼ��ӿ�ָ�롣
			* @note ������Ƶ����ֻ�ܵ���һ�����ݣ�PCM���߱��������ݣ�����enableAudioCallbackEncoded enableAudioCallbackPCMֻ����һ����Ч�����߽�Ĭ�ϵ���encoded���ݡ�
			* @note PCM��enableAudioCallbackEncoded(false)  enableAudioCallbackPCM(true); ����encoded���ݣ�enableAudioCallbackEncoded(true)  enableAudioCallbackPCM(false);
			* @sa enableVideoCallbackEncoded
			* @sa enableVideoCallbackYUV
			* @return �����롣
			*/
			virtual Result setAudioCapture(tee3::avd::FakeAudioCapturer* capture) = 0;

			/** �����Ƿ�ص����������Ƶ����
			*
			* @param[in] callbackEncodedData ���ܿ�����رա�
			* @note Ĭ��Ϊtrue��enableVideoCallbackYUV��enableVideoCallbackEncoded���ܿ�ͬʱ������
			* @sa videoEncodedOut
			* @sa enableVideoCallbackYUV
			* @return �����롣
			*/
			virtual Result enableVideoCallbackEncoded(bool callbackEncodedData = true) = 0;
			/** �����Ƿ�ص���������Ƶ����
			*
			* @param[in] callbackYUVData ���ܿ�����رա�
			* @note Ĭ��Ϊfalse, enableVideoCallbackYUV(true)���ú�videoYUVOut�ӿڲŻ������ݻص���
			* @sa videoYUVOut
			* @sa enableVideoCallbackYUV
			* @return �����롣
			*/
			virtual Result enableVideoCallbackYUV(bool callbackYUVData = true) = 0;
			/** �����Ƿ�ص����������Ƶ����
			*
			* @param[in] callbackEncodedData ���ܿ�����رա�
			* @note Ĭ��Ϊtrue��enableAudioCallbackEncoded��enableAudioCallbackPCM���ܿ�ͬʱ������
			* @sa audioEncodedOut
			* @sa enableAudioCallbackPCM
			* @return �����롣
			*/
			virtual Result enableAudioCallbackEncoded(bool callbackEncodedData = true) = 0;
			/** �����Ƿ�ص���������Ƶ����
			*
			* @param[in] callbackPcmData ���ܿ�����رա�
			* @note Ĭ��Ϊfalse, enableAudioCallbackPCM(true)���ú�audioPCMOut�ӿڲŻ������ݻص���
			* @sa audioPCMOut
			* @sa enableAudioCallbackEncoded
			* @return �����롣
			*/
			virtual Result enableAudioCallbackPCM(bool callbackPcmData = true) = 0;
		protected:
			virtual ~RtspClient() {};
		};

	} // namespace avd
} // namespace tee3

#endif //RTC_RtspClient_H_
