#ifndef RT_AVImporter_H
#define RT_AVImporter_H

#include "common.h"
#include "errorcode.h"

namespace tee3 {
	namespace avd {
	class User;

	/**
	* ����Ƶ������ӿ�.
	*
	* ��ɶ���������Ƶ���빦�ܽӿڡ�
	*/
	class RT_API_EXPORT IAVImporter {
	public:
		/**
		* ��������ص��ӿ�.
		*/
		class EngineListener {
		public:
			/** ��ʼ����������첽����
			*
			* @param[in] result ��ʼ��������롣
			* @sa init
			*/
			virtual void onInitResult(Result result) = 0;
		protected:
			virtual ~EngineListener() {}
		};

		/**
		* ����Ƶ������ص��ӿ�.
		*/
		class IListener {
		public:
			/** ����״̬֪ͨ
			*
			* @param[in] result ��ǰ����״̬��
			*/
			virtual void onStatus(Result result) = 0;

			/** ����֪ͨ
			*
			* @param[in] reason ����״̬��
			* @note 
			*		Err_Importer_Video_Failure
			*		Err_Importer_Audio_Failure
			*		Err_User_DuplicateJoin
			*		Err_Room_OutofVideo
			*		Err_Room_OutofAudio
			*		Err_Room_Close
			*		Err_Network_Failure
			*		Err_Importer_BeKicked
			*/
			virtual void onError (Result reason) = 0;

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
		protected:
			virtual ~IListener() {}
		};

	public:
		/** ��ʼ������
		*
		* @param[in] severuri ������uri��
		* @param[in] appkey ���幫˾�ַ���Ӧ�ù�˾��Ӧ����Կ��
		* @param[in] secretkey ���幫˾�ַ���Ӧ�ù�˾�İ�ȫ��Կ��
		* @param[in] cb �����ʼ���ص�����ָ�롣
		* @note AVD���������κι��ܲ���ǰ��������Ҫ��ʼ������ɹ��������ʼ����һ���첽���������ô˽ӿں�ȴ��ص��к���initresult�ص����ж��Ƿ��ʼ���ɹ���
		* @return ���ش�����롣
		*/
		static Result initEngine(EngineListener* cb, const String& severuri, const String& appkey, const String& secretkey);

		/** ����ʼ������
		*
		* @note AVD����ʼ�����������漰�����з��������Ч�������ϵĹ��ܺ������޷�����ʹ�á�
		* @return ���ش�����롣
		*/
		static Result uninitEngine();

		static bool   isEngineWorking();

	public:
		/** ��������Ƶ���������
		*
		* @param[in] roomId ����Id��
		* @param[in] *listener �����ص��ӿڡ�
		* @return ������Ƶ���������
		*/
		static IAVImporter* obtain(const RoomId& roomId);
		/** �ͷ�����Ƶ���������
		*
		*@note �ͷ�����Ƶ����������App�㲻����ʹ�õ�ǰ����Ƶ���������ָ�룬�������ô���������ΪNULL��
		*/
		virtual void release() = 0;
	public:
		/** ��������Ƶ������ص��ӿ�
		*
		* @param[in] *listener �ص��ӿ�ָ�롣
		*
		* @return ���ش�����롣
		* @see IListener
		*/
		virtual Result setListener(IListener* listener) = 0;
		/** ��ȡ����Id
		*
		* @return ���ط���Id��
		*/
		virtual const RoomId& getRoomId() const = 0;
		/** ���뷿��
		*
		* @param[in,out] user �û���Ϣ���û�Id(���ܰ���'{'��'}'�ַ�)���û������û����ݵȣ���Ӧ�ò㲻����user.userIdʱ��SDK������һ���µ�guid��Ϊuser.userId��ͬʱ���ظ�Ӧ�ò㡣
		* @note ���뷿��ʱ������ָ����������ص��ӿڣ����ָ��������ָ�������ӿڻص���������Listener��onJoinResult�ص���
		* @return ���ش�����롣
		* @sa User
		*/
		virtual Result join(const User& user) = 0;

		/** ���õ�����Ƶ
		*
		* @param[in] enable ���á�
		* @return ���ش�����롣
		*/
		virtual Result enableAudio(bool enable) = 0;
		/** ���õ�����Ƶ
		*
		* @param[in] enable ���á�
		* @return ���ش�����롣
		*/
		virtual Result enableVideo(bool enable) = 0;

		/** �жϷ����Ƿ���������
		* @return �Ƿ������С�
		*/
		virtual bool isWorking() const = 0;

		/// audio
		/** ��Ƶ������PCMԭʼ����
		*
		* @param[in] timestamp_ns ʱ���, nanos second��
		* @param[in] sampleRate ��Ƶ������
		* @param[in] channels ��Ƶ�ɼ�ͨ����
		* @param[in] data ��Ƶ��������ָ��
		* @param[in] len  ��Ƶ���ݴ�С
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		* @note sampleRate��channels���Ա仯(���ǲ���Ƶ���仯����ÿ�ζ���һ�����ڲ�ÿ�α仯��ʱ����Ҫ���´�������)��ÿ���������Ƶ�������ݲ���̫�࣬��󲻳���4K��
		*/
		virtual Result audio_inputPCMFrame(
			uint64 timestamp_ns, int sampleRate, int channels, const uint8* data, size_t len) = 0;

		/** ��Ƶ������AAC����������
		*
		* @param[in] timestamp_ns ʱ���, nanos second��
		* @param[in] sampleRate ��Ƶ������
		* @param[in] channels ��Ƶ�ɼ�ͨ����
		* @param[in] data ��Ƶ��������ָ��
		* @param[in] len  ��Ƶ���ݴ�С
		* @param[in] samplesOfEncodedData  ��Ƶ�������ݰ����Ĳ�������һ�����AACÿ�α��붼��1024 * channels��������
		* @return ���ش�����룺
		* 	AVD_OK						�ɹ�
		*/
		virtual Result audio_inputAACFrame(
			uint64 timestamp_ns, int sampleRate, int channels, const uint8* data, size_t len, int samplesOfEncodedData) = 0;

		/// video
		/** ��Ƶ������ԭʼͼ��
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
		virtual Result video_inputRAWFrame(
			uint64 timestamp_ns, uint32 format, int w, int h, const uint8* data, size_t len, int rotation, bool mirror) = 0;
		/** ��Ƶ������h264����������
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
		virtual Result video_input264Frame(
			uint64 timestamp_ns, int w, int h, const uint8* sample, size_t sample_size) = 0;

	protected:
		virtual ~IAVImporter() {};
	};

	} // namespace avd
} // namespace tee3

#endif //RT_AVImporter_H
