#ifndef RTC_FakeVideoCapturer_H_
#define RTC_FakeVideoCapturer_H_

#include "common.h"
#include "videorender.h"

namespace tee3 {
	namespace avd {

	/**
	* ��Ƶ������ӿ�.
	*
	* ��Ƶ������ع��ܽӿڡ�
	*/
	class RT_API_EXPORT FakeVideoCapturer {
	public:
		/**
		* ��Ƶ������ص��ӿ�.
		*
		* ��Ƶ����ص���ع��ܽӿڡ�
		*/
		class Listener {
		public:
			/** ��Ƶ���ɼ���ʼ�ص��ӿ�
			*
			* @return ��ʼ�ɹ�����ʧ�ܣ�Ԥ����
			* @note SDK��ʼ��Ƶ�ɼ������˽ӿڣ�����ֵĿǰ�����ģ�Ϊ�Ժ�Ԥ����
			*/
			virtual bool OnStart() = 0;
			/** ��Ƶ���ɼ������ص��ӿ�
			*
			* @note SDKֹͣ��Ƶ�ɼ������˽ӿڡ�
			*/
			virtual void OnStop() = 0;
		};

	public:
		/** ����һ��FOURCC_I420��Ƶ�ɼ�������
		*
		* @param[in] *listener �ص�ָ�롣
		* @param[in] isScreen �Ƿ������湲��
		* @return ��Ƶ�ɼ�������ָ�롣
		* @note �ӿ�Ĭ�ϴ�������FOURCC_I420 ���͵���Ƶ�ɼ�����
		*/
		static	FakeVideoCapturer* Create(FakeVideoCapturer::Listener* listener, bool isScreen = false);

		/** ����һ����Ƶ�ɼ�������
		*
		* @param[in] *listener �ص�ָ�롣
		* @param[in] fourFormat ��Ҫ�������Ƶ�������͡�
		* @param[in] isScreen �Ƿ������湲��
		* @return ��Ƶ�ɼ�������ָ�롣
		* @note ����FOURCC_H264������FourCC���ܻ�����������FourCC���Ի������롣
		*/
		static	FakeVideoCapturer* Create(FakeVideoCapturer::Listener* listener, FourCC fourFormat, bool isScreen = false);

		/** ����һ����Ƶ�ɼ�������
		*
		* @param[in] *capturer ��Ƶ�ɼ�������ָ�롣
		*/
		static	void Destroy(FakeVideoCapturer* capturer);

		/** �ж�Capturer�Ƿ���������
		* @return �Ƿ������С�
		*/
		virtual bool isRunning() = 0;
		/** ��Capturer����ԭʼͼ��
		*
		* @param[in] timestamp_ns ʱ���, nanos second
		* @param[in] format ԭʼͼ���ʽ����FourCCö��
		* @param[in] w ͼ����
		* @param[in] h ͼ��߶�
		* @param[in] data ͼ����������ָ��
		* @param[in] len  ͼ�����ݴ�С
		* @param[in] rotation ͼ����Ҫ��ת�ĽǶȣ�˳ʱ�뷽��ȡֵ��0,90,180,270
		* @param[in] mirror ����ͼ�����ҷ�ת
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		* 	RTC_ERR_VIDEO_CONVERT_FAILED	ת��ͼ���ʽʧ�ܣ��п������ڴ����ʧ�ܣ��ɿ�����������
		*	Err_Invalid_Arg				�������Ϸ����ɺ���
		*	Err_Wrong_Status			״̬���ԣ��ɺ���
		*	
		*/
		virtual Result inputCapturedFrame(
			uint64 timestamp_ns, uint32 format, int w, int h, const uint8* data, size_t len, int rotation, bool mirror) = 0;
		/** ��Capturer�������������
		*
		* @param[in] timestamp_ns ʱ���, nanos second
		* @param[in] w ͼ����
		* @param[in] h ͼ��߶�
		* @param[in] sample  ͼ����������ָ��
		* @param[in] sample_size ͼ�����ݴ�С
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		*	Err_Invalid_Arg				�������Ϸ����ɺ���
		*	Err_Wrong_Status			״̬���ԣ��ɺ���
		*
		*/
		virtual Result inputEncodedFrame(
			uint64 timestamp_ns, int w, int h, const uint8* sample, size_t sample_size) = 0;

		virtual FourCC format() = 0;
	protected:
		virtual ~FakeVideoCapturer() {};
	};

	} // namespace avd
} // namespace tee3

#endif //RTC_FakeVideoCapturer_H_
