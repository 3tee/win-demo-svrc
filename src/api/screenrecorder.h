#ifndef RT_AVDScreenRecorder_H_
#define RT_AVDScreenRecorder_H_

#include "api/defines.h"
#include "api/common.h"
namespace tee3 {
	namespace avd {

		/**
		* ��Ļ¼�ƽӿ�.
		*
		* ��Ļ¼�ƽӿ��ṩ¼����Ļ��¼��Ӧ����������ֱ��¼��Ӧ�ã�¼��ϵͳ������������������Ӧ�ã��ȹ��ܡ�
		* �����ӿڰ�������ȡ��¼�ƶ�����Ϣ����ʼ¼�ƣ���ͣ¼�ƣ�ֹͣ¼�ƣ�����¼��֡�ʣ�������Ƶ�����ʽ��������Ƶ�����ʽ��������Ƶ�ɼ������������ʣ�ͨ������ÿ֡��ռ�ñ���λ��
		*/
		class RT_API_EXPORT IAVDScreenRecorder {
		public:

			struct IMG {

			};
			struct ScreenImgType {
				ScreensType screen;
				IMG img;
			};
			typedef std::vector<ScreenImgType> ScreensImgType;

			static IAVDScreenRecorder* create();
			static void destroy(IAVDScreenRecorder* recorder);
			//Listener 
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
				virtual void videoEncodedOut(VideoEncodedType format, uint64 timestamp_ns, unsigned int width, unsigned int height, bool isKeyFrame, const uint8 *data, unsigned int len) = 0;

				/** ��Ƶ�ɼ�YUV���ݻص��ӿ�
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
				/** ��Ƶ�ɼ��ص��ӿ�
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

			virtual Result setVideoListener(IVideoListener* listener) = 0;
			virtual Result setAudioListener(IAudioListener* listener) = 0;

			//Setting interface
			virtual Result setRecorderFile(std::string filePath) = 0;
			virtual Result setVideoFps(uint8 fps) = 0;
			virtual Result setVideoBitRate(uint32 bitRate) = 0;
			//virtual Result setVideoFrameRate(uint8 frameRate) = 0;
			virtual Result setAudioInfo(uint32 frameRate, uint8 channel, uint8 bitPerSample) = 0;
			virtual Result setVideoEncodedType(VideoEncodedType format) = 0;
			virtual Result setAudioEncodedType(AudioEncodedType format) = 0;
			virtual Result setRecordedAudio(AudioRecordedType recordedAudio) = 0;
			virtual Result setRecordedScreen(const ScreenWindow& screen) = 0;
			//Control interface
			virtual Result getScreenWindows(ScreensType& wnds) = 0;
			virtual Result getScreenWindows(ScreensImgType& wnds) = 0;
			virtual Result startScreenRecord() = 0;
			virtual Result stopScreenRecord() = 0;
			virtual Result pauseScreenRecord() = 0;
			virtual Result restoreScreenRecord() = 0;
		protected:
			virtual ~IAVDScreenRecorder() {}
		};
	}
}

#endif//RT_AVDScreenRecorder_H_
