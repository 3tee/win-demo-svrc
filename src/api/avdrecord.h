#ifndef RT_AVDRecord_H_
#define RT_AVDRecord_H_

#include "common.h"
#include "avdengine.h"

namespace tee3 {
	namespace avd {
		/**
		* ¼�����ݽṹ.
		*
		* ¼�����ݶ�����һ��¼�ƵĻ�����Ϣ��
		*/
		struct RecordInfo {
			RecordId id;					/**< ¼��ID */
			String name;					/**< ¼�Ƶ����� */
			String description;				/**< ¼������ */
			String tags;					/**< ¼�Ʊ�� */
			UserId userId;					/**< �û��ţ��ɲ����ڣ�����ʱ��audioType��videoTypeһ��ʹ�ã�¼�ƴ��û��������Ƶ����Ƶ���� */
			MediaFileType   fileType;		/**< ý���ļ����� */
			RecordAudioType audioType;		/**< ��Ƶ���� */
			RecordVideoType videoType;		/**< ��Ƶ���� */
			String url;						/**< ����¼������ */
			uint64 size;					/**< ¼���ļ���С */
			String createTime;				/**< ¼�ƴ�����ʼʱ�� */
			uint64 duration;				/**< ¼�ƴӴ��������ڵ�ʱ�� */
			RecordStatus status;			/**< ¼��״̬ */
			RoomId roomId;					/**< Ƶ����������� */
		public:
			RecordInfo() :fileType(mt_mp4), audioType(ra_user_single), videoType(rv_main), size(0), duration(0), status(rs_created){}
			bool isValid() const { return !id.empty(); }
		};
		typedef RecordInfo* LPRecordInfo;
		const String toString(const RecordInfo&  obj);

		/**
		* ¼����Ϣ��������.
		*/
		typedef std::vector<RecordInfo> RecordInfosType;

		/**
		* ��·¼�ƹ���ӿ�.
		*
		* ��·¼�ƹ�����������¼�ƵĴ�����ɾ������Ϣ��ȡ��¼�ƿ��Ƶȹ��ܣ���¼�Ƴɹ����ļ��洢��RecorderServer�ϣ������Ǳ��ء�
		*/
		class RT_API_EXPORT IAVDRecord {
		public:
			/**
			* ��·¼�ƻص��ӿ���
			*
			* ��·¼�ƻص��ӿڶ�����¼�ƹ���������첽���ء�
			*/
			class IListener {
			public:
				/** ��ȡ��ǰ���ڽ��з����б���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] total  �ܹ�ֱ������
				* @param[in] begin  ��ǰ��ʼ��š�
				* @param[in] items ������Ϣ���ϡ�
				*
				* @sa getWorkingRooms
				*/
				virtual void onWorkingRooms(uint32 callId, Result result, uint32 total, uint32 begin, const RoomInfosType& items) = 0;
				/** ��ȡ�ض������Ѿ���������Ƶ�б�
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] roomId ����š�
				* @param[in] items �ѷ�������Ƶ��Ϣ���ϡ�
				*
				* @sa getWorkingRooms
				*/
				virtual void onPublishedVideos(uint32 callId, Result result, const RoomId& roomId, const VideoDevicesType& items) = 0;
				
				///
				/** ����¼�Ƶ��첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ¼����Ϣ��
				*
				* @sa createRecord
				*/
				virtual void onCreateRecord(uint32 callId, Result result, const RecordInfo& info) = 0;
				/** Ϊ�ض�¼�����õ�ǰ��ƵԴ���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] recordId ¼�ƺš�
				* @param[in] selectedVideo �ѷ�������ƵId��
				*
				* @sa selectVideo4Record
				*/
				virtual void onSelectMedia4Record(uint32 callId, Result result, const RecordId& recordId, const DeviceId& selectedVideo) = 0;
				/** �����ض��û�¼�Ƶ��첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ¼����Ϣ��
				*
				* @sa createUserRecord
				*/
				virtual void onCreateUserRecord(uint32 callId, Result result, const RecordInfo& info) = 0;
				/** ֹͣ�ض�¼�Ƶ��첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] recordId ¼�ƺš�
				*
				* @sa stopRecord
				*/
				virtual void onStopRecord(uint32 callId, Result result, const RecordId& recordId) = 0;
				
				///
				/** ��ȡ�ض�¼����ϸ��Ϣ���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ¼����Ϣ��
				*
				* @sa getRecordInfo
				*/
				virtual void onRecordInfo(uint32 callId, Result result, const RecordInfo& info) = 0;
				/** ��ȡ��������¼���б���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] total  �ܹ�ֱ������
				* @param[in] begin  ��ǰ��ʼ��š�
				* @param[in] items ¼����Ϣ���ϡ�
				*
				* @sa getWorkingRecords
				*/
				virtual void onRecordInfos(uint32 callId, Result result, uint32 total, uint32 begin, const RecordInfosType& items) = 0;
				/** ɾ���ض�¼�Ƶ��첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] recordId ¼�ƺš�
				*
				* @sa deleteRecord
				*/
				virtual void onDeleteRecord(uint32 callId, Result result, const RecordId& recordId) = 0;
			protected:
				virtual ~IListener() {}
			};

		public:
			/** ��ȡ��ǰ���ڽ��з����б�
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  begindex ��ҳ����ʼ������
			* @param[in]  ncount ��ҳ������������
			* @return ���ش�����롣
			* @note ��ʱδʵ�֣� Ϊ�첽��������������� onWorkingRooms �з��ء�
			* @sa onWorkingRooms
			*/
			virtual Result getWorkingRooms(uint32& callId, uint32 begindex, uint32 ncount) = 0;
			/** ��ȡ�ض������Ѿ���������Ƶ�б�
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  roomId ����š�
			* @return ���ش�����롣
			* @note ��ʱδʵ�֣� Ϊ�첽��������������� onPublishedVideos �з��ء�
			* @sa onPublishedVideos
			*/
			virtual Result getPublishedVideos(uint32& callId, const RoomId& roomId) = 0;
		public:
			/** ��ȡ�������·¼�ƹ��ܽӿ�
			*
			* @return ������·¼�ƽӿڡ�
			*/
			static IAVDRecord* getRecord(IAVDEngine *engine);
			/** �ͷŹ��ܶ���
			*/
			static void release();
			/** ����¼�ƹ��ܻص�
			*
			* @param[in] *listener �ص�ָ�롣
			* @return ���ش�����롣
			*/
			virtual Result setListener(IListener* listener) = 0;	
			//
			/** ����һ��¼��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  info ��roomId��name�������ã������ɹ�ʱid�����ó��´�����¼��Id�����첽�����з��ء�
			* @note ��ʱδʵ�֣� Ϊ�첽��������������� onCreateRecord �з��ء�
			* @sa onCreateRecord
			*/
			virtual Result createRecord(uint32& callId, const RecordInfo& info) = 0;
			/** Ϊ�ض�¼�����õ�ǰ��ƵԴ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in] recordId ¼�ƺš�
			* @param[in] roomId ��Ƶ��ط���š�
			* @param[in] selectedVideo �ѷ�������ƵId��
			* @return ���ش�����롣
			* @note ��ʱδʵ�֣� Ϊ�첽��������������� onSelectMedia4Record �з��ء�
			* @sa onSelectMedia4Record
			*/
			virtual Result selectMedia4Record(uint32& callId, const RecordId& recordId, const RoomId& roomId, const DeviceId& selectedVideo) = 0;
			/** �����ض��û�¼��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  info ��roomId��name, userid, fileType�������ã������ɹ�ʱid�����ó��´�����¼��Id�����첽�����з��ء�
			* @return ���ش�����롣
			* @note �����ṹ�е���Ƶ����ȱʡΪ��ra_user_single
								��Ƶ����ȱʡΪ��rv_main
			*		Ϊ�첽��������������� onCreateUserRecord �з��ء�
			* @sa onCreateUserRecord
			*/
			virtual Result createUserRecord(uint32& callId, const RecordInfo& info) = 0;
			/** ֹͣ�ض�¼��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  recordId ¼�ƺš�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onStopRecord �з��ء�
			* @sa onStopRecord
			*/
			virtual Result stopRecord(uint32& callId, const RecordId& recordId) = 0;

			/** ��ȡ�ض�¼����ϸ��Ϣ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  recordId ¼�ƺš�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onRecordInfo �з��ء�
			* @sa onRecordInfo
			*/
			virtual Result getRecordInfo(uint32& callId, const RecordId& recordId) = 0;
			/** ��ȡ�������ϵ�¼���б�
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  begindex ��ҳ����ʼ������
			* @param[in]  ncount ��ҳ������������
			* @param[in]  filter ��ѯ��������json��ʾ���磺{ "roomId":"hafds2324" }��
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onRecordInfos �з��ء�
			* @sa onRecordInfos
			*/
			virtual Result findRecordInfos(uint32& callId, uint32 begindex, uint32 ncount, const String& filter) = 0;
			/** ɾ���ض�¼��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  recordId ¼�ƺš�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onDeleteRecord �з��ء�
			* @sa onDeleteRecord
			*/
			virtual Result deleteRecord(uint32& callId, const RecordId& recordId) = 0;
		protected:
			virtual ~IAVDRecord() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_AVDRecord_H_
