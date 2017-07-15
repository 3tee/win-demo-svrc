#ifndef RT_ILocalRecord_H_
#define RT_ILocalRecord_H_

#include "common.h"
#include "room.h"

namespace tee3 {
	namespace avd {

		/**
		* ¼�ƹ���ӿڣ�¼���ļ�������.
		*
		* ¼�ƹ�����������¼�ƵĴ�����ֹͣ��¼�ƿ��Ƶȹ��ܡ�
		*/
		class RT_API_EXPORT IMLocalRecord : public IModule {
		public:
			/**
			* ¼����¼������Ƶ���ص��ӿ�.
			*/
			class RT_API_EXPORT StreamOut {
			public:
				/** ��Ƶ���ص��ӿ�
				*
				* @param[in] recHandle ¼��ģ������
				* @param[in] timestamp_ns ʱ���, nanos second
				* @param[in] w ͼ����
				* @param[in] h ͼ��߶�
				* @param[in] data ͼ����������ָ��
				* @param[in] len  ͼ�����ݴ�С
				* @note ��Ƶ�������ݸ�ʽΪh264����vp8�ȱ�����ʽ����������Ƶ�����˷���ʱȷ����
				* ��Ƶʱ�������Ƶʱ����Ļص��Ƕ����ģ��ص�ʱû��ǰ���ϵ������Ƶ�ص�ĳһʱ���A����Ƶ�����ص���ʱ���B���ܱ�AС����֮��Ȼ��
				* ����Ƶ�����ݻص������в��ܶ�������������ʱ������
				* @sa avd_localrecord_createRecorder
				*/
				virtual void videoStreamOut(const String& recHandle, uint64 timestamp_ns, unsigned int w, unsigned int h, bool isKeyFrame, const uint8 *data, unsigned int len) = 0;

				/** ��Ƶ���ص��ӿ�
				*
				* @param[in] recHandle ¼��ģ������
				* @param[in] timestamp_ns ʱ���, nanos second��
				* @param[in] sampleRate ��Ƶ������
				* @param[in] channels ��Ƶ�ɼ�ͨ����
				* @param[in] data ��Ƶ��������ָ��
				* @param[in] len  ��Ƶ���ݴ�С
				* @note ��Ƶ�������ݸ�ʽΪPCM 16λ��
				* ��Ƶʱ�������Ƶʱ����Ļص��Ƕ����ģ��ص�ʱû��ǰ���ϵ������Ƶ�ص�ĳһʱ���A����Ƶ�����ص���ʱ���B���ܱ�AС����֮��Ȼ��
				* ����Ƶ�����ݻص������в��ܶ�������������ʱ������
				* @sa avd_localrecord_createRecorder
				*/
				virtual void audioStreamOut(const String& recHandle, uint64 timestamp_ns, int sampleRate, int channels, const uint8 *data, unsigned int len) = 0;
			protected:
				virtual ~StreamOut() {}
			};
			/** ��ȡ�����ڱ���¼��ģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			*
			* @return ���ر���¼��ģ��ӿ�ָ�롣
			*/
			static IMLocalRecord* getRecord(IRoom* room);
			/** ����һ��¼������
			*
			* @param[in] filePath ¼���ļ���ַ��
			* @param[in] recorderId �ⲿ����¼��ID�����뱣֤�����ڸ�¼��ģ���о���Ψһ�ԣ������null��""���ڲ�����һ��UUID����ͨ��return ���ء�
			* @param[in] continueDecode SDK�Ƿ�����ڲ����루��Ҫ��SDK�ڲ�����Ƶ��Ⱦ�ȹ��ܣ�����Ҫ���룩��
			* @return ��Ч�ı���¼��ID���������null����""����ʾ����ʧ�ܡ�
			*/
			virtual Result createRecorder(const String& filePath, String& recorderId, bool continueDecode=true) = 0;
			/** ����һ��¼������
			*
			* @param[in] StreamOut ¼����������ӿ�ָ�롣
			* @param[in] recorderId �ⲿ����¼��ID�����뱣֤�����ڸ�¼��ģ���о���Ψһ�ԣ������null��""���ڲ�����һ��UUID����ͨ��return ���ء�
			* @param[in] continueDecode SDK�Ƿ�����ڲ����루��Ҫ��SDK�ڲ�����Ƶ��Ⱦ�ȹ��ܣ�����Ҫ���룩��
			* @return ��Ч�ı���¼��ID���������null����""����ʾ����ʧ�ܡ�
			*/
			virtual Result createRecorder(StreamOut* out, String& recorderId, bool continueDecode=true) = 0;
			/** Ϊ¼������ѡ�񷿼��ڵ�ĳ·��Ƶ
			*
			* @param[in] recorderId ¼��ID��
			* @param[in] deviceId ��Ƶ����Ӧ���豸ID��
			*
			* @return ���ش�����롣
			* @note ���deviceId�豸��Ӧ����Ƶ�ж�·��pub��sub��������MainStream > Assistant1Stream > Assistant2Stream�����ȼ�ѡ������ǵ���������ѡ�е���pub��sub����·��
			*	
			*/
			virtual Result selectVideo4Recorder(const String& recorderId, const String& deviceId) = 0;
			/** Ϊ¼������ѡ�񷿼��ڵ�ĳ·��Ƶ
			*
			* @param[in] recorderId ¼��ID��
			* @param[in] userId ��Ƶ�������û�ID��
			*
			* @return ���ش�����롣
			*/
			virtual Result selectAudio4Recorder(const String& recorderId, const UserId& userId) = 0;
			/** Ϊĳ��¼������ѡ��¼�Ʒ����ڵ�������Ƶ
			*
			* @param[in] recorderId ¼��ID��
			*
			* @return ���ش�����롣
			*/
			virtual Result selectAllAudio4Recorder(const String& recorderId) = 0;
			/** Ϊĳ��¼������ѡ��¼�Ʒ����ڵĳ������Լ����������Ƶ
			*
			* @param[in] recorderId ¼��ID��
			*
			* @return ���ش�����롣
			*/
			virtual Result selectAllAudioWithoutMe4Recorder(const String& recorderId) = 0;
			/** ֹͣ��¼��ģ���е�ĳ��¼��
			*
			* @param[in] recorderId ¼��ID��
			*
			* @return ������Ϣ�б�
			*/
			virtual Result stopRecorder(const String& recorderId) = 0;
			/** ֹͣ��¼��ģ��������¼��
			*
			* @return ���ش�����롣
			*/
			virtual Result stopRecorderAll() = 0;
		protected:
			virtual ~IMLocalRecord() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_ILocalRecord_H_
