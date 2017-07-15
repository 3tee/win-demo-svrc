#ifndef RT_Audio_H_
#define RT_Audio_H_

#include "common.h"
#include "room.h"

namespace tee3 {
	namespace avd {
		class IRoom;

		/**
		* ��Ƶ�豸����ӿ�.
		*
		* ��Ƶ�豸����ӿڶ��巿������Ƶ�豸��ع��ܽӿڡ�
		*/
		class RT_API_EXPORT IAudioDevice {
		public:
			/**
			* ��Ƶ�豸����ص��ӿ�.
			*
			* ��Ƶ�豸����ص��ӿڶ�������Ƶ�豸���֪ͨ��
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ��˷����֪ͨ
				*
				* @param[in] item ��˷���Ϣ��
				* @note ��ϵͳ������˷��豸����ʱ���˻ص�������
				*/
				virtual void onMicrophonePlugin(const Microphone& item) = 0;
				/** ��˷�γ�֪ͨ
				*
				* @param[in] item ��˷���Ϣ��
				* @note ��ϵͳ������˷��豸�γ�ʱ���˻ص�������
				*/
				virtual void onMicrophonePlugout(const Microphone& item) = 0;
				/** ����������֪ͨ
				*
				* @param[in] item ��������Ϣ��
				* @note ��ϵͳ�����������豸����ʱ���˻ص�������
				*/
				virtual void onSpeakerPlugin(const Speaker& item) = 0;
				/** �������γ�֪ͨ
				*
				* @param[in] item ��������Ϣ��
				* @note ��ϵͳ�����������豸�γ�ʱ���˻ص�������
				*/
				virtual void onSpeakerPlugout(const Speaker& item) = 0;

				/** ��˷������仯֪ͨ
				*
				* @param[in] volume ��˷�������ȡֵ��0 �� 100��0Ϊ��С��100���
				* @note ��ϵͳ������˷������仯ʱ���˻ص�������
				*/
				virtual void onMicrophoneVolumeChanged(uint32 volume) = 0;
				/** �����������仯֪ͨ
				*
				* @param[in] volume ������������ȡֵ��0 �� 100��0Ϊ��С��100���
				* @note ��ϵͳ���������������仯ʱ���˻ص�������
				*/
				virtual void onSpeakerVolumeChanged(uint32 volume) = 0;
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
			static IAudioDevice* Instance();
		public:
			/** ������Ƶ�豸����ص��ӿ�
			*
			* @param[in] *listener ��Ƶ�豸����ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			///microphone
			/** ��ȡ������˷��豸��Ϣ�б�
			*
			* @param[in,out] items ��˷��豸���ϴ���б�
			* @return ���ش�����롣
			*/
			virtual Result getMicrophones(MicrophonesType& items) const = 0;
			/** ��ȡָ���豸Id�ı�����˷��豸��Ϣ
			*
			* @param[in] id �豸Id��
			* @return ������˷��豸��Ϣ��
			*/
			virtual const Microphone& getMicrophone(const DeviceId& id) const = 0;
			/** ��ȡ��ǰĬ��ʹ�õı�����˷��豸��Ϣ
			* @return ������˷��豸��Ϣ��
			*/
			virtual const Microphone& getRecordingMicrophone() const = 0;
			/** ���õ�ǰĬ��ʹ�õı�����˷��豸
			*
			* @param[in] id �豸Id��
			* @return ���ش�����롣
			*/
			virtual Result setRecordingMicrophone(const DeviceId& id) = 0;
			/** ����¼����������С
			*
			* @param[in] volume ��˷�������ȡֵ��0 �� 100��0Ϊ��С��100���
			* @return ���ش�����롣
			*/
			virtual Result setRecordingVolume(uint32 volume) = 0;
			/** ��ȡ���ŵ�������С
			*
			* @return ��˷�������ȡֵ��0 �� 100��0Ϊ��С��100���
			*/
			virtual uint32 getRecordingVolume() const = 0;
			/** ��ȡ����¼���豸ID
			*
			* @return ��ȡ����¼���豸ID��
			*/
			virtual DeviceId getFakeMicrophoneId() const = 0;
			///speaker
			/** ��ȡ�����������豸��Ϣ�б�
			*
			* @param[in,out] items �������豸���ϴ���б�
			* @return ���ش�����롣
			*/
			virtual Result getSpeakers(SpeakersType& items) const = 0;
			/** ��ȡָ���豸Id�ı����������豸��Ϣ
			*
			* @param[in] id �豸Id��
			* @return �����������豸��Ϣ��
			*/
			virtual const Speaker& getSpeaker(const DeviceId& id) const = 0;
			/** ��ȡ��ǰĬ��ʹ�õı����������豸��Ϣ
			* @return �����������豸��Ϣ��
			*/
			virtual const Speaker&	getPlayoutSpeaker() const = 0;
			/** ���õ�ǰĬ��ʹ�õı����������豸
			*
			* @param[in] id �豸Id��
			* @return ���ش�����롣
			*/
			virtual Result setPlayoutSpeaker(const DeviceId& id) = 0;
			/** ���õ�ǰĬ����������������С
			*
			* @param[in] volume ������������ȡֵ��0 �� 100��0Ϊ��С��100���
			* @return ���ش�����롣
			*/
			virtual Result setPlayoutVolume(uint32 volume) = 0;
			/** ��ȡ��ǰĬ����������������С
			*
			* @return ������������ȡֵ��0 �� 100��0Ϊ��С��100���
			*/
			virtual uint32 getPlayoutVolume() const = 0;

			///for testing
			/** ��ʼ¼�Ʋ��Ҳ�������
			*
			* @return ���ش�����롣
			* @note ���ڲ�����˷���������Ƿ���������
			*/
			virtual Result recordPlayStart() = 0;
			/** ֹͣ¼�Ʋ��Ҳ�������
			*
			* @return ���ش�����롣
			*/
			virtual Result recordPlayStop() = 0;
			/** ��ʼ���������ļ�
			*
			* @param[in] file ��Ƶ�ļ���
			* @param[in] loop ���β��Ž������Ƿ��ظ����š�
			* @param[in] format ָ����Ƶ�ļ���ʽ��
			* @return ���ش�����롣
			* @note ���ڲ����������Ƿ���������
			*/
			virtual Result playVoice(const String& file, bool loop, FileFormats format) = 0;
			/** ֹͣ���������ļ�
			*
			* @return ���ش�����롣
			*/
			virtual Result stopVoice() = 0;

			/** �Ƿ����ڲ��������ļ�
			*
			* @return true,false��
			*/
			virtual bool isPlayingVoice() = 0;
			/** ��ȡ¼���ܼ�0-9
			*
			* @return �ܼ���
			*/
			virtual uint32 getRecordLevel() = 0;
			/** ��ȡ���������ܼ�0-9
			*
			* @return �ܼ���
			*/
			virtual uint32 getPlayoutLevel() = 0;

		protected:
			virtual ~IAudioDevice() {}
		};
				
		/**
		* ��������Ƶģ��ӿ�.
		*
		* ������Ƶģ�鶨�巿����Ƶ�������˷硢��������ز������ܽӿڡ�
		*/
		class RT_API_EXPORT IMAudio : public IModule {
		public:
			/**
			* ��������Ƶģ��ص��ӿ�.
			*
			* ��Ƶģ��ص��ӿڶ����˷�������Ƶ�������˷硢��������֪ͨ���첽�������ء�
			*/
			class IListener {
			public:
				/// ֪ͨ
				/** ��˷�״̬����֪ͨ
				*
				* @param[in] status ��˷�״̬��
				* @param[in] fromUserId �豸�����û�Id��
				* @note ����˷�״̬���ĺ󣬷����������û����յ���֪ͨ��
				* @sa openMicrophone
				* @sa closeMicrophone
				*/
				virtual void onMicrophoneStatusNotify(MicrophoneStatus status, const UserId& fromUserId) = 0;
				/** ��������֪ͨ
				*
				* @param[in] info ����������Ϣ��
				* @note ��������֪ͨ��ֻ����������������Ż�����������֪ͨ���������������ӿ�Ϊ��monitorAudioLevel��
				* @sa monitorAudioLevel
				*/
				virtual void onAudioLevelMonitorNotify(const AudioInfo& info) = 0;
				
				/// �첽����
				/** ���û�����˷��첽����
				*
				* @param[in] result ������롣
				* @sa openMicrophone
				*/
				virtual void onOpenMicrophoneResult(Result result) = 0;
				/** ���û��ر���˷��첽����
				*
				* @param[in] result ������롣
				* @sa closeMicrophone
				*/
				virtual void onCloseMicrophoneResult(Result result) = 0;

				/// �첽����
				///** ���û�������Ƶ�첽����
				//*
				//* @param[in] result ������롣
				//* @param[in] fromId �û�Id��Ψһ��ʾһ���û���
				//*
				//* @sa subscribe
				//*/
				//virtual void onSubscribeResult(Result result, const UserId& fromId) = 0;
				///** ���û�ȡ��������Ƶ�첽����
				//*
				//* @param[in] result ������롣
				//* @param[in] fromId �û�Id��Ψһ��ʾһ���û���
				//*
				//* @sa unsubscribe
				//*/
				//virtual void onUnsubscribeResult(Result result, const UserId& fromId) = 0;
			protected:
				virtual ~IListener() {}
			};
			/** ��ȡ��Ƶģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			*
			* @return ������Ƶģ��ӿ�ָ�롣
			*/
			static IMAudio* getAudio(IRoom* room);
			//
			/** ������Ƶģ��ص��ӿ�
			*
			* @param[in] *listener ��Ƶģ��ص��ӿ�ָ�롣
			* @return ���ش�����롣
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** �򿪱�����˷緢����������
			*
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onOpenMicrophoneResult �з��ء�
			* @sa onOpenMicrophoneResult
			*/
			virtual Result openMicrophone() = 0;
			/** �رձ�����˷緢����������
			*
			* @return ���ش�����롣
			* @note Ϊ�첽��������������� onCloseMicrophoneResult �з��ء�
			* @sa onCloseMicrophoneResult
			*/
			virtual Result closeMicrophone() = 0;
			/** ��ȡ������˷�״̬
			* @return ������˷�״̬��
			*/
			virtual MicrophoneStatus getMicrophoneStatus() const = 0;
			// no input audio, anyone cann't listen my speak; like pause mic
			/** ������˷羲Ĭ
			*
			* @return ���ش�����롣
			* @note ��˷羲Ĭ��ʾ����û���������ݵ������У��������û������������ص��κ�������
			*/
			virtual Result muteMicrophone() = 0;
			/** ������˷�ȡ����Ĭ
			* @return ���ش�����롣
			*/
			virtual Result unmuteMicrophone() = 0;
			/** �жϱ�����˷��Ƿ�Ĭ
			* @return ��˷��Ƿ񱻾�Ĭ��
			*/
			virtual bool ismuteMicrophone() const = 0;
			// no output audio, cann't listen anyone sound
			/** ������������Ĭ
			*
			* @return ���ش�����롣
			* @note ��������Ĭ��ʾ�����е����������ڱ������������ţ����û����������κη����е�������
			*/
			virtual Result muteSpeaker() = 0;
			/** ����������ȡ����Ĭ
			* @return ���ش�����롣
			*/
			virtual Result unmuteSpeaker() = 0;
			/** �жϱ����������Ƿ�Ĭ
			*/
			virtual bool ismuteSpeaker() const = 0;

			/// remote microphone control
			/** ��ȡԶ����˷�״̬
			* @param[in] userId �����û�Id��
			* @return ������˷�״̬��
			*/
			virtual MicrophoneStatus getRemoteMicrophoneStatus(const UserId& userId) const = 0;
			/** ����Զ���û�����˷�
			* @param[in] userId �����û�Id��
			* @return ���ش�����롣
			*/
			virtual Result remotecmdOpenMicrophone(const UserId& userId) = 0;
			/** ����Զ���û��ر���˷�
			* @param[in] userId �����û�Id��
			* @return ���ش�����롣
			*/
			virtual Result remotecmdCloseMicrophone(const UserId& userId) = 0;

			/** ��ȡ��Ƶ�豸����ӿ�
			*
			* @return ������Ƶ�豸����ӿ�ָ�롣
			* @sa IAudioDevice
			*/
			virtual IAudioDevice* getAudioDevice() = 0;

			/** ����������������
			* @return ���ش�����롣
			*/
			virtual Result monitorAudioLevel() = 0;
			/** �ر���������
			* @return ���ش�����롣
			*/
			virtual Result unmonitorAudioLevel() = 0;
			/** �ж��Ƿ�����������
			*/
			virtual bool ismonitorAudioLevel() const = 0;
					protected:
						virtual ~IMAudio() {}
		};

		/**
		* ��Ƶ����ģ��ӿ�.
		*
		* ��Ƶ����ģ�鶨�巿������Ƶ����Ļ�ӿڡ�
		*/
		class RT_API_EXPORT IAudioMixer {
			
		public:
			/**
			* ��������Ƶ�������ݻص��ӿ�.
			*/
			class IDataListener {
			public:
				/** ��Ƶ��ʽ�ص��ӿ�
				* @param[in] sampleRate �����ʡ�
				* @param[in] channels ͨ������
				*/
				virtual void onAudioParam(uint32 sampleRate, uint32 channels) = 0;
				/** ��Ƶ���ݻص��ӿ�
				* @param[in] timestamp_ns ʱ���, nanos second��
				* @param[in] buf ���ݴ洢ָ�롣
				* @param[in] len ���ݳ��ȡ�
				*/
				virtual void onAudioData(uint64 timestamp_ns, const void *buf, uint32 len) = 0;

			protected:
				virtual ~IDataListener() {}
			};
		public:
			/** ��ȡ��������Ƶģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			* @param[in] listener �������ݻص�ָ�롣
			* @return ������Ƶģ��ӿ�ָ�롣
			* @sa IMixerDataListener
			* @sa ro_audio_mixerdata_callback_buffered ���λ������ݻص���10ms���ݡ����ǡ�1024samples���ݡ�
			* @note �������Ƶͬʱ��ϳ�����������������Ƶ����������Ƶ�Ļص��ӿڣ�����������Ƶʱ������롣
			*/
			static IVideoMixer* getVideoMixer(IMAudio* maudio, IDataListener* listener);
			/** ���û�ȡ�������ݻص��ӿ�
			* @param[in] sampleRate �����������ݵĲ����ʣ�16000,44100,48000��
			* @return ���ش�����롣
			*/
			virtual Result setOutputSampleRate(uint32 sampleRate) = 0;

		protected:
			virtual ~IAudioMixer() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_Audio_H_
