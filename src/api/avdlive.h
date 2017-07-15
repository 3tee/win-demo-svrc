#ifndef RT_AVDLive_H_
#define RT_AVDLive_H_

#include "common.h"
#include "avdengine.h"
#include "room.h"

namespace tee3 {
	namespace avd {
		/**
		* ֱ��Ƶ�����ݽṹ.
		*
		* ֱ��Ƶ�����ݶ�����һ��ֱ��Ƶ���Ļ�����Ϣ��
		*/
		struct LiveInfo {
			LiveId id;						/**< Ƶ����ID */
			String name;					/**< ֱ��Ƶ�������� */
			String description;				/**< ֱ��Ƶ������ */
			String tags;					/**< ֱ����� */
			UserId userId;					/**< �û��ţ��ɲ����ڣ�����ʱ��audioType��videoTypeһ��ʹ�ã�ֱ�����û��������Ƶ����Ƶ���� */
			RecordAudioType audioType;		/**< ��Ƶ���� */
			RecordVideoType videoType;		/**< ��Ƶ���� */
			String createTime;				/**< Ƶ��������ʼʱ�� */
			uint32 duration;				/**< Ƶ���Ӵ��������ڵ�ʱ�� */
			String playerPassword;			/**< �������� */
			RoomId roomId;					/**< Ƶ����������� */
			LiveStatus status;				/**< ֱ��״̬ */
			String publishurl;				/**< ������ַ������ʱ�ɴ��ϣ������ڣ��������������ʹ˵�ַ */
			String rtmpurl;					/**< ����rtmp���� */
			String hlsurl;					/**< ����hls���� */
		public:
			LiveInfo() :audioType(ra_user_single), videoType(rv_main), duration(0), status(ls_created){}
			bool isValid() const { return !id.empty(); }
		};
		const String toString(const LiveInfo&  obj);

		/**
		* ֱ��Ƶ����Ϣ��������.
		*/
		typedef std::vector<LiveInfo> LiveInfosType;

		/**
		* ֱ��Ƶ������ӿ�.
		*
		* ֱ��Ƶ��������������ֱ��Ƶ���Ĵ�����ɾ������Ϣ��ȡ��Ƶ�����Ƶȹ��ܡ�
		* ֱ��Ƶ�������Ƶ���Ƶ�����ܹ�����һ·��Ƶ����Ƶ��һ���߼�ͨ����ֱ��Դͨ��ֱ��Ƶ��������Ƶ��ֱ�����Ŷ�ͨ��ֱ��Ƶ�����ĺ͹ۿ�ֱ������Ƶ��
		*/
		class RT_API_EXPORT IAVDLive {
		public:
			/**
			* ֱ��Ƶ���ص��ӿ���
			*
			* ֱ��Ƶ���ص��ӿڶ�����ֱ��Ƶ������������첽���ء�
			*/
			class IListener {
			public:
				/// �첽����
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
				/** ����ֱ��Ƶ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ֱ��Ƶ����Ϣ��
				*
				* @sa createLive
				*/
				virtual void onCreateLive(uint32 callId, Result result, const LiveInfo& info) = 0;
				/** Ϊ�ض�ֱ��Ƶ�����õ�ǰ��ƵԴ���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] lvbc_id Ƶ���š�
				* @param[in] selectedVideo �ѷ�������ƵId��
				*
				* @sa selectMedia4Live
				*/
				virtual void onSelectMedia4Live(uint32 callId, Result result, const LiveId& lvbc_id, const DeviceId& selectedVideo) = 0;
				/** �����ض��û�ֱ��Ƶ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ¼����Ϣ��
				*
				* @sa createUserLive
				*/
				virtual void onCreateUserLive(uint32 callId, Result result, const LiveInfo& info) = 0;
				/** ֹͣ�ض�ֱ��Ƶ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] lvbc_id Ƶ���š�
				*
				* @sa stopLive
				*/
				virtual void onStopLive(uint32 callId, Result result, const LiveId& lvbc_id) = 0;
				/** ��ȡ�ض�Ƶ����ϸ��Ϣ���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] info ֱ��Ƶ����Ϣ��
				*
				* @sa getLiveInfo
				*/
				virtual void onLiveInfo(uint32 callId, Result result, const LiveInfo& info) = 0;
				/** ��ȡ��ǰ����ֱ��Ƶ���б���첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] total  �ܹ�ֱ������
				* @param[in] begin  ��ǰ��ʼ��š�
				* @param[in] items ֱ��Ƶ����Ϣ���ϡ�
				*
				* @sa getLiveInfos
				*/
				virtual void onLiveInfos(uint32 callId, Result result, uint32 total, uint32 begin, const LiveInfosType& items) = 0;
				/** ɾ���ض�Ƶ�����첽����
				*
				* @param[in] callId ����Id��
				* @param[in] result ������롣
				* @param[in] lvbc_id Ƶ���š�
				*
				* @sa deleteLive
				*/
				virtual void onDeleteLive(uint32 callId, Result result, const LiveId& lvbc_id) = 0;
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
			* @note Ϊ�첽��������������� onWorkingRooms �з��ء�
			* @sa onWorkingRooms
			*/
			virtual Result getWorkingRooms(uint32& callId, uint32 begindex, uint32 ncount) = 0;
			/** ��ȡ�ض������Ѿ���������Ƶ�б�
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  roomId ����š�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onPublishedVideos �з��ء�
			* @sa onPublishedVideos
			*/
			virtual Result getPublishedVideos(uint32& callId, const RoomId& roomId) = 0;
		public:
			/** ��ȡ�����ֱ�����ܽӿ�
			*
			* @return ����ֱ���ӿڡ�
			*/
			static IAVDLive* getLive(IAVDEngine *engine);
			/** �ͷŹ��ܶ���
			*/
			static void release();
			/** ����ֱ�����ܻص�
			*
			* @param[in] *listener �ص�ָ�롣
			* @return ���ش�����롣
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** ����ֱ��Ƶ��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in,out] info ��roomId��name�������ã������ɹ�ʱid�����ó��´�����ֱ��Ƶ��Id��
			* @note Ϊ�첽��������������� onCreateLive �з��ء�
			* @sa onCreateLive
			*/
			virtual Result createLive(uint32& callId, const LiveInfo& info) = 0;
			/** Ϊ�ض�ֱ��Ƶ�����õ�ǰ��ƵԴ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  lvbc_id Ƶ���š�
			* @param[in]  roomId ��Ƶ��ط���š�
			* @param[in]  selectedVideo �ѷ�������ƵId��
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onSelectVideo4Live �з��ء�
			* @sa onSelectMedia4Live
			*/
			virtual Result selectMedia4Live(uint32& callId, const LiveId& lvbc_id, const RoomId& roomId, const DeviceId& selectedVideo) = 0;
			/** �����ض��û�ֱ��Ƶ��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  info ��roomId��name, userid�������ã������ɹ�ʱid�����ó��´�����¼��Id�����첽�����з��ء�
			* @return ���ش�����롣
			* @note �����ṹ�е���Ƶ����ȱʡΪ��ra_user_single
			��Ƶ����ȱʡΪ��rv_main
			*		Ϊ�첽��������������� onCreateUserLive �з��ء�
			* @sa onCreateUserLive
			*/
			virtual Result createUserLive(uint32& callId, const LiveInfo& info) = 0;
			/** ��ͣ�ض�Ƶ��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  lvbc_id Ƶ���š�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onStopLive �з��ء�
			* @sa onStopLive
			*/
			virtual Result stopLive(uint32& callId, const LiveId& lvbc_id) = 0;
			/** ��ȡ�ض�Ƶ����ϸ��Ϣ
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  lvbc_id Ƶ���š�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onLiveInfo �з��ء�
			* @sa onLiveInfo
			*/
			virtual Result getLiveInfo(uint32& callId, const LiveId& lvbc_id) = 0;
			/** ��ȡ��ǰ����ֱ����Ƶ���б�
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  begindex ��ҳ����ʼ������
			* @param[in]  ncount ��ҳ������������
			* @param[in]  filter ��ѯ��������json��ʾ���磺{ "roomId":"hafds2324" }��
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onLiveInfos �з��ء�
			* @sa onLiveInfos
			*/
			virtual Result findLiveInfos(uint32& callId, uint32 begindex, uint32 ncount, const String& filter) = 0;

			/** ɾ���ض�Ƶ��
			*
			* @param[in,out] callId ����Id�����������ε��ã��ڻص��л���ϴ˵���Id������Ӧ�ò�����ÿ�ε��ã�������ʱΪ0���ڲ�����һ����š�
			* @param[in]  lvbc_id Ƶ���š�
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onDeleteLive �з��ء�
			* @sa onDeleteLive
			*/
			virtual Result deleteLive(uint32& callId, const LiveId& lvbc_id) = 0;
		protected:
			virtual ~IAVDLive() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_AVDLive_H_
