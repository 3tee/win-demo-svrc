#ifndef RTC_FakeAudioCapturer_H_
#define RTC_FakeAudioCapturer_H_

#include "common.h"
namespace tee3 {
	namespace avd {
	/**
	* ��Ƶ������ӿ�.
	*
	* ��Ƶ������ع��ܽӿڡ�
	*/
	class RT_API_EXPORT FakeAudioCapturer {
	public:
		/** ��ȡ��Ƶ�ɼ�����������
		*
		* @return ��Ƶ�ɼ�������ָ�롣
		*/
		static	FakeAudioCapturer* Instance();

		/** ����һ����Ƶ�ɼ�������
		*
		* @param[in] *capturer ��Ƶ�ɼ�������ָ�롣
		*/
		static	void Destroy(FakeAudioCapturer* capturer);
		static  bool hasUsedCapturer();

		/** �ж�Capturer�Ƿ���������
		* @return �Ƿ������С�
		*/
		virtual bool isRunning() const = 0;

		/** ��Capturer����PCMԭʼ����
		*
		* @param[in] timestamp_ns ʱ���, nanos second��
		* @param[in] sampleRate ��Ƶ������
		* @param[in] channels ��Ƶ�ɼ�ͨ����
		* @param[in] data ��Ƶ��������ָ��
		* @param[in] len  ��Ƶ���ݴ�С
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		* @note sampleRate��channels���Ա仯(���ǲ���Ƶ���仯����ÿ�ζ���һ�����ڲ�ÿ�α仯��ʱ����Ҫ���´�������)��ÿ���������Ƶ�������ݲ���̫�࣬��󲻳���4K��
		*	
		*/
		virtual Result inputCapturedFrame(
			uint64 timestamp_ns, int sampleRate, int channels, const uint8* data, size_t len) = 0;

		/** ��Capturer����AAC����������
		*
		* @param[in] timestamp_ns ʱ���, nanos second��
		* @param[in] sampleRate ��Ƶ������
		* @param[in] channels ��Ƶ�ɼ�ͨ����
		* @param[in] data ��Ƶ��������ָ��
		* @param[in] len  ��Ƶ���ݴ�С
		* @param[in] samplesOfEncodedData  ��Ƶ�������ݰ����Ĳ�������һ�����AACÿ�α��붼��1024 * channels��������
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		*
		*/
		virtual Result inputAACFrame(
			uint64 timestamp_ns, int sampleRate, int channels, const uint8* data, size_t len, int samplesOfEncodedData) = 0;

		/** ��ǰAVD����ʹ����Ƶ������Ϊȱʡ��ƵԴ
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		*/
		virtual Result enable(bool isEnable) = 0;

	protected:
		virtual ~FakeAudioCapturer() {};
	};

	} // namespace avd
} // namespace tee3

#endif //RTC_FakeAudioCapturer_H_
