#ifndef RT_COMMON_H
#define RT_COMMON_H

#include "combase.h"
#include <string>
#include <vector>
#include <sstream>

NAMESPACE_TEE3_BEGIN
typedef std::string String;					/**< tee3�����String���� */
typedef String		RoomId;					/**< ��������ͣ�Ψһ��ʶ������һ�����䣬���Ȳ�����Max_RoomId���壻�������£�[RId_P|T_H|F_P|M_type_guid]�����ֶεĺ���Ϊ�� */
typedef String		DeviceId;				/**< �豸�����ͣ�Ψһ��ʶ������һ���豸�����Ȳ�����Max_DeviceId���壻�������£�userId+"_"+md5[os.getdeviceid() or os.getsystemid()] */
typedef String		UserId;					/**< �û������ͣ�Ψһ��ʶ������һ���û������Ȳ�����Max_UserId���壻��Ӧ�ò㶨�崫�ݸ�AVD SDK��Ҫ��֤������Ψһ  */
typedef String		StreamId;				/**< ý����Id���ͣ�SDK�ڲ�ʹ�� */
typedef DeviceId	RecordId;				/**< ¼��ID����  */
typedef DeviceId	LiveId;					/**< ֱ��Ƶ��ID����  */
typedef DeviceId	AnnotationId;			/**< ֱ��Ƶ��ID����  */
///
extern RT_API_EXPORT const UserId	AVD_userId_allUser;			/**< AVD���������û�Id�����ڱ�ʶ�����������û�  */
extern RT_API_EXPORT const UserId	AVD_userId_allUserWithoutMe;/**< AVD���������û�Id�����ڱ�ʶ�����г����Լ���������û�  */
NAMESPACE_TEE3_END

NAMESPACE_TEE3_AVD_BEGIN

/**
* ������Ϣ�ṹ.
*
* ������Ϣ�����˰��ŷ���ʱ��������Ϣ��
*/
struct RoomInfo {
	RoomInfo() : startTime(0), duration(0), bandwidth(0),
		maxAttendee(0), maxAudio(0), maxVideo(0), roomMode(0), status(rs_scheduled) {}
	RoomId roomId;							/**< ����Id��SDK���ɣ�Ψһ��ʾһ�����䣻����ȡMax_RoomId */
	String roomName;						/**< ��������Ӧ�ò㴴������ʱ���� */
	String appRoomId;						/**< ����Ӧ�ò�Id��Ӧ�ò㴴������ʱ���ã�Ӧ�ò�����ڱ�ʾ���䣻����ȡMax_RoomId */
	String roomTopic;						/**< �������⣬Ӧ�ò㴴������ʱ���� */
	String ownerId;							/**< ���䴴����UserId������ȡMax_UserId */
	String hostId;							/**< ����������UserId������ȡMax_UserId */
	String hostPassword;					/**< �������������룻����ȡMax_Password */
	String confPassword;					/**< �������룬���������������벻ͬ������ȡMax_Password */
	uint32 startTime;						/**< ������ʼʱ�� */
	uint32 duration;						/**< ��������ʱ��,��λ���� */
	uint32 bandwidth;						/**< �����������,��λ��kps */
	uint32 maxAttendee;						/**< ��������û������� */
	uint32 maxAudio;						/**< ���������Ƶ������,��ͬʱ�򿪻�Ͳ�� */
	uint32 maxVideo;						/**< ���������Ƶ������,��ͬʱ������ͷ�� */
	uint32 roomMode;						/**< ����ģʽ������ѡ�ο�RoomMode��ȱʡΪp2p */
	RoomStatus status;
public:
	/** �ж���mcuģʽ���� */
	bool isMcu() const { return isFlagSet(roomMode, rm_mcu); }
	/** �ж������ɷ���ģʽ���� */
	bool isFree() const { return isFlagSet(roomMode, rm_free); }
	/** �ж�����ʱ���� */
	bool isTemperary() const { return isFlagSet(roomMode, rm_temperary); }
	/** ���÷���ģʽ
	* @param[in] flag ����ֵ��
	* @note ÿ��ģʽ���뵥������,����ͨ�� | �����ϲ����á�
	*/
	void setRoomMode(RoomMode flag) {
		if (isFlagSet(flag, clear_set)) {
			uint32 dwFlag = flag;
			clearFlag(dwFlag, clear_set);
			clearFlag(roomMode, dwFlag);
		}
		else {
			avdSetFlag(roomMode, flag);
		}
	}
};
/**
* ������Ϣ��������.
*/
typedef std::vector<RoomInfo> RoomInfosType;

/**
* �豸��Ϣ�ṹ.
*
* �豸��Ϣ�ṹ�������豸������Ϣ���˴��豸������˷硢������������ͷ����Ļ���ڡ�
*/
struct Device {
	DeviceId id;							/**< �豸Id��Ψһ��ʶһ���豸������������Ƶ�豸Ϊ���û����Ψһ�ţ���Ƶ�豸userId+deviceId(MD5(idd) or mobileId+0(front)1(back)) */
	String   name;							/**< �豸���ƣ�Ӧ�ò�������豸��ʾ  */
	DeviceStatus status;					/**< �豸״̬  */
	Device() :status(tee3::avd::ds_none) {}
	/** �ж��豸�Ƿ���Ч */
	bool isValid() const { return !id.empty(); }
	bool operator ==(const Device& right) const { return this->id == right.id; }
};

/**
* ��Ƶ�ɼ���Ϣ�ṹ.
*
* ��Ƶ�ɼ��ṹ��������Ƶ�ɼ���ز�����������Ƶ�ֱ��ʺ�֡�ʡ�
*/
struct CameraCapability {
	uint32 width;							/**< ��Ƶ���  */
	uint32 height;							/**< ��Ƶ�߶�  */
	uint32 maxFPS;							/**< ��Ƶ֡��  */
	uint32 rotation;						/**< ��Ƶ�Ƕ�  */
	CameraCapability() :width(0), height(0), maxFPS(0), rotation(0) {}
	CameraCapability(uint32 w, uint32 h, uint32 fps) :width(w), height(h), maxFPS(fps), rotation(0) {}
	CameraCapability(uint32 w, uint32 h, uint32 fps, uint32 rotation) :width(w), height(h), maxFPS(fps), rotation(rotation) {}
	/** �жϷֱ����Ƿ���Ч */
	bool isValid() const { return 0 != width && 0 != height; }
	bool operator==(const CameraCapability& o) const {
		return (width == o.width) && (height == o.height) && (maxFPS == o.maxFPS) && (rotation == o.rotation);
	}
	CameraCapability& operator=(const CameraCapability& o) {
		if (this != &o) {
			width = o.width;
			height = o.height;
			maxFPS = o.maxFPS;
			rotation = o.rotation;
		}
		return *this;
	}
	friend std::ostream& operator <<(std::ostream& ost, const CameraCapability& o) {
		ost << "cap:[" << "width = " << o.width << ",height = " << o.height << ",maxFPS = " << o.maxFPS << ",rotation = " << o.rotation << "],";
		return ost;
	}
};
/**
* ��������Ϣ�ṹ.
*/
struct Speaker : public Device {};
/**
* ��������������.
*/
typedef std::vector<Speaker> SpeakersType;
/**
* ��˷���Ϣ�ṹ.
*/
struct Microphone : public Device {};
/**
* ��˷缯������.
*/
typedef std::vector<Microphone> MicrophonesType;

/**
* ��Ƶ�ɼ���������.
*/
typedef std::vector<CameraCapability> CapabilitiesType;

/**
* ��Ƶ�豸ѡ����.
*
* ��Ƶ�豸ѡ���ඨ������Ƶ�豸���������е���Ƶ�������ֱ��ʵȲ������ϡ�
*/
class RT_API_EXPORT VideoDeviceOptions {
public:
	VideoDeviceOptions();
	VideoDeviceOptions(uint32 aoptionset);
	/** �ж��豸�Ƿ�֧��ָ����Ƶ����
	* @param[in] value ָ����Ƶ������
	* @return �����Ƿ�֧�֡�
	*/
	bool hasQuality(VideoQuality value) const;
	bool hasCapability(CameraCapability cap) const;
	/** ��ȡ�豸֧�ֵķֱ��ʼ���
	* @return ���طֱ��ʼ��ϡ�
	*/
	CapabilitiesType getCapabilities() const;
	/** �����豸֧�ֵķֱ��ʼ��ϣ�SDK�ڲ�ʹ��
	* @param[in] caps �ֱ��ʼ��ϡ�
	* @return ���������Ƿ�ɹ���
	*/
	Result setCapabilities(const CapabilitiesType& caps);
public:
	/** ��ȡָ���ֱ��ʵ���Ƶ�������࣬SDK�ڲ�ʹ��
	* @param[in] cap ָ���ֱ��ʡ�
	* @return ������Ƶ������
	*/
	static VideoQuality getQualityByCapability(const CameraCapability& cap);
	/** ��ȡָ���ֱ��ʵĿ�߱����ͣ�SDK�ڲ�ʹ��
	* @param[in] cap ָ���ֱ��ʡ�
	* @return ���ؿ�߱����͡�
	*/
	static VideoRatio getRatioByCapability(const CameraCapability& cap);
	/** ��ȡָ����Ƶ�����Ϳ�߱ȵķֱ��ʣ�SDK�ڲ�ʹ��
	* @param[in] quality ָ�������ȡ�
	* @param[in] ratio ��߱����͡�
	* @return ���طֱ��ʡ�
	*/
	static CameraCapability getDefaultCapability(VideoQuality quality, VideoRatio ratio);
public:
	uint32 optionset;	// λ������0-1����߱�����2-4����Ƶ������5-26: high:5-12, normal:13-20, low:21-28��
};

/**
* ��Ƶ����ѡ����.
*
* ��Ƶ����ѡ���ඨ����ĳ��Ƶ�豸����Ƶ����ʱ��Ƶ��ָ������Ƶ�������ֱ��ʡ���߱Ⱥͱ��뷽ʽ�Ȳ������ϡ�
*/
class RT_API_EXPORT PublishVideoOptions {
public:
	PublishVideoOptions();
	PublishVideoOptions(uint32 aoptionset);
public:
	/** �ж���Ƶ�������Ƿ�֧��ָ����Ƶ����
	* @param[in] value ָ����Ƶ������
	* @return �����Ƿ�֧�֡�
	*/
	bool hasQuality(VideoQuality value) const;
	/** ��ȡ��Ƶ�����в��õĿ�߱�����
	* @return ������Ƶ��߱����͡�
	*/
	VideoRatio getRatio() const;
	/** ������Ƶ�����в��õĿ�߱�����
	* @param[in] value ָ����Ƶ��߱ȡ�
	*/
	void setRatio(VideoRatio value);
	/** ��ȡ��Ƶ�����в��õĽǶ���Ϣ����
	* @return ������Ƶ�Ƕ���Ϣ���͡�
	*/
	VideoRotation getRotation() const;
	/** ������Ƶ�����в��õĽǶ���Ϣ����
	* @param[in] value ָ���Ƕ���Ϣ��
	*/
	void setRotation(VideoRotation value);
public: // Stream options
	/** ����ָ��������Ƶ��������
	*
	* @param[in] type �����͡�
	* @param[in] quality ��Ƶ������
	* @param[in] codec �������͡�
	*
	* @note ��ǰÿ������ͷ�豸���ݻ������������Է�����·��Ƶ�����ֱ�Ϊ����������1�͸���2��
	* ÿ·��Ƶ���Ĳ������Ը���Ӧ�ó������á�chrome�������ǰ��֧��VP8���룻�ƶ��˶�H264��֧��
	* �Ϻã�PC�����ֱ��붼֧�����á�
	* @return ���ش�����롣
	*/
	Result setStreamOptions(StreamType type, VideoQuality quality, VideoCodec codec = codec_default);
	/** ����ָ��������Ƶ��������
	*
	* @param[in] type �����͡�
	* @param[in] cap ��Ƶ�ֱ���֡�ʡ�
	* @param[in] codec �������͡�
	* @return ���ش�����롣
	*/
	Result setStreamOptions(StreamType type, const CameraCapability& cap, VideoCodec codec = codec_default);
	/** ��ȡָ�����ķֱ���֡�� */
	CameraCapability getStreamCapability(StreamType type) const;
	/** ��ȡָ��������Ƶ���� */
	VideoQuality getStreamQuality(StreamType type) const;
	/** ��ȡָ�����ı������ */
	VideoCodec getStreamCodec(StreamType type) const;
	/** ��ȡָ������payload������SDK�ڲ�ʹ�� */
	int getStreamPayload(StreamType type) const;
public:
	/** �ж���Ƶ�������Ƿ���������SDK�ڲ�ʹ�� */
	bool hasMainStream() const;
	/** �ж���Ƶ�������Ƿ��и���1��SDK�ڲ�ʹ�� */
	bool hasAssist1() const;
	/** �ж���Ƶ�������Ƿ��и���2��SDK�ڲ�ʹ�� */
	bool hasAssist2() const;
	/** �淶����Ƶ����ѡ�SDK�ڲ�ʹ�� */
	void normalize(uint32 deviceOptions);
	/** �ж�ָ�����Ƿ�֧��Ӳ�����룬SDK�ڲ�ʹ�� */
	bool isCodecHWSupported(StreamType type) const;
	/** �ж�ָ�����Ƿ�֧�ֱ��룬SDK�ڲ�ʹ�� */
	bool isCodecSupported(StreamType type) const;
	/** ��ȡ��Ƶ�����е�ǰ��������ȶ�������SDK�ڲ�ʹ��
	*
	* @param[in] quality ָ����Ƶ������
	* @param[in] mustQuality �Ƿ����ѡָ������Ƶ������
	*
	* @note ��ȡ��Ƶ�����е�ǰ��������ȶ�����ȡ��������߿ͻ��˵���������Բο�IMVideo.subscribe�е�������
	* @return ������Ƶ����
	*/
	StreamType getPrioritySubscribeStream(VideoQuality quality, bool mustQuality) const;
public:
	uint32 optionset; // λ������0-1����߱�����2-4��ȱʡ��Ƶ������5-26: ���� 5-12(0-1 ���룬2-7 ���)������1 13-20������2 20-28��
};

/**
* ��Ƶ���豸�ṹ.
*
* ��Ƶ���豸�ṹ��������Ƶ���豸�Ļ�����Ϣ����Ҫ��������ͷ����Ļ�����豸��
*/
struct VideoDevice : public Device {
	VideoDevice() :Device(), level(0) {}
	int		level;							/**< Ӧ�ò���豸���õ����ݣ������ڱ�ʾ��ƵȨ�ص�, Ӧ�ò㿪������  */
	String	description;					/**< Ӧ�ò���豸��������Ӧ�ò㿪������  */
	VideoDeviceOptions  deviceQualities;	/**< ��Ƶ�豸�������ͼ�������ͷ֪ͨʱ��������ͷ֧�ֵ���Ƶ��������  */
	PublishVideoOptions publishedQualities;	/**< ��Ƶ�����������ͼ����豸����ʱ�����ķ�����Ƶ���������� */
public:
	/** �ж���Ƶ�豸�Ƿ��Ѵ��ڷ���״̬ */
	bool isPublished() const {
		return ds_published == status || ds_muted == status;
	}
};
/**
* ��Ƶ�豸��������.
*/
typedef std::vector<VideoDevice> VideoDevicesType;

/**
* ��Ļ�����豸��Ϣ�ṹ.
*/
struct ScreenWindow : public VideoDevice {
	ScreenType type;						/**< ��������  */
public:
	ScreenWindow() :type(tee3::avd::st_unknown) {}
};
/**
* ��Ļ���ڼ�������.
*/
typedef std::vector<ScreenWindow> ScreensType;

/**
* ��Ƶ����ͷ��Ϣ�ṹ.
*
* ��Ƶ����ͷ�ṹ����������ͷ��ز�������Ҫ������ͷ������Ϣ����Ƶ�ֱ�����Ϣ��
*/
struct Camera : public VideoDevice {
	CameraType type;						/**< ����ͷ����  */
public:
	Camera() :type(tee3::avd::ct_unknown) {}
};
/**
* ��Ƶ����ͷ��������.
*/
typedef std::vector<Camera> CamerasType;

/**
* ����������Ϣ�ṹ.
*
* ����������Ϣ��Ϣ�����˵�ǰ�����б����������������������Լ�Զ���û�������������Ϣ��
* �����������ȣ�0-9������0Ϊ��������9Ϊ�������
*/
struct AudioInfo {
	int input_level;						/**< ���������������� */
	int output_level;						/**< ��������������� */

	typedef std::vector<std::pair<UserId, int> > RemoteUser2LevelType;
	RemoteUser2LevelType active_streams;	/**< Զ���û�������������Ӧ��ֻ������������0���û� */

	AudioInfo() :input_level(0), output_level(0) {}
	AudioInfo(int il, int ol, const RemoteUser2LevelType& streams)
		: input_level(il), output_level(ol), active_streams(streams) {}
};

/**
* ����ͳ����Ϣ�ṹ.
*
* ����ͳ����Ϣ�ṹ�����˷��伶�����磬ý���ͳ����Ϣ��
*/
struct RoomStats : public NetworkStats {
	int available_receive_bandwidth;/**< ���ƽ��մ���  */
	int available_send_bandwidth;	/**< ���Ʒ��ʹ���  */
	tee3::String local_address;		/**< ���ص�ַ  */
	tee3::String remote_address;	/**< Զ�˵�ַ  */
	tee3::String transport_type;	/**< �������ͣ�udp : tcp  */
	RoomStats() :available_receive_bandwidth(0), available_send_bandwidth(0) {}
	void Clear() {
		NetworkStats::Clear();
		available_receive_bandwidth = 0;
		available_send_bandwidth = 0;
		local_address.clear();
		remote_address.clear();
		transport_type.clear();
	}
};

/**
* ý��ͳ����Ϣ�ṹ.
*
* ý��ͳ����Ϣ�ṹ������ý�弶�����磬ý���ͳ����Ϣ��
*/
struct MediaStats : public NetworkStats {
	tee3::String media_type;		/**< ý�����ͣ�audio : video  */
	tee3::String codec_name;		/**< ý���������  */
	int audio_input_level;			/**< ��Ƶ��������  */
	int audio_output_level;			/**< ��Ƶ�������  */
	int frame_width;				/**< ��Ƶ���  */
	int frame_height;				/**< ��Ƶ�߶�  */
	int frame_rate;					/**< ��Ƶ֡��  */

	MediaStats() :audio_input_level(0), audio_output_level(0)
		, frame_width(0), frame_height(0), frame_rate(0) {}
	void Clear() {
		NetworkStats::Clear();
		audio_input_level = 0;
		audio_output_level = 0;
		frame_width = 0;
		frame_height = 0;
		frame_rate = 0;
		media_type.clear();
		codec_name.clear();
	}
};
extern RT_API_EXPORT const RoomStats g_emptyRoomStats;
extern RT_API_EXPORT const MediaStats g_emptyMediaStats;
RT_API_EXPORT const String toString(const RoomStats& obj);
RT_API_EXPORT const String toString(const MediaStats& obj);

//#if defined(RT_DESKTOP)
class WindowId {
public:
	// Define WindowT for each platform.
#if defined(RT_LINUX) && !defined(RT_ANDROID)
	typedef Window WindowT;
#elif defined(RT_WIN32)
	typedef HWND WindowT;
#elif defined(RT_MAC) && !defined(RT_IOS)
	typedef CGWindowID WindowT;
#else
	typedef unsigned int WindowT;
#endif

	static WindowId Cast(uint64 id) {
#if defined(RT_WIN32)
		return WindowId(reinterpret_cast<WindowId::WindowT>(id));
#else
		return WindowId(static_cast<WindowId::WindowT>(id));
#endif
	}

	static uint64 Format(const WindowT& id) {
#if defined(RT_WIN32)
		return static_cast<uint64>(reinterpret_cast<uintptr_t>(id));
#else
		return static_cast<uint64>(id);
#endif
	}

	WindowId() : id_(0) {}
	WindowId(const WindowT& id) : id_(id) {}  // NOLINT
	const WindowT& id() const { return id_; }
	bool IsValid() const { return id_ != 0; }
	bool Equals(const WindowId& other) const {
		return id_ == other.id();
	}

private:
	WindowT id_;
};
typedef std::vector<WindowId> WindowIds;
class DesktopId {
public:
	// Define DesktopT for each platform.
#if defined(RT_LINUX) && !defined(RT_ANDROID)
	typedef Window DesktopT;
#elif defined(RT_WIN32)
	typedef HMONITOR DesktopT;
#elif defined(RT_MAC) && !defined(RT_IOS)
	typedef CGDirectDisplayID DesktopT;
#else
	typedef unsigned int DesktopT;
#endif

	static DesktopId Cast(int id, int index) {
#if defined(RT_WIN32)
		return DesktopId(reinterpret_cast<DesktopId::DesktopT>(id), index);
#else
		return DesktopId(static_cast<DesktopId::DesktopT>(id), index);
#endif
	}

	DesktopId() : id_(0), index_(-1) {}
	DesktopId(const DesktopT& id, int index)  // NOLINT
		: id_(id), index_(index) {}
	const DesktopT& id() const { return id_; }
	int index() const { return index_; }
	bool IsValid() const { return index_ != -1; }
	bool Equals(const DesktopId& other) const {
		return id_ == other.id() && index_ == other.index();
	}

private:
	// Id is the platform specific desktop identifier.
	DesktopT id_;
	// Index is the desktop index as enumerated by each platform.
	// Desktop capturer typically takes the index instead of id.
	int index_;
};

//#endif

//#if defined(RT_ANNOTATION)
enum AnnotationToolType {
	annotation_tool_mouse = 1 << 0,
	annotation_tool_line = 1 << 1,
	annotation_tool_rectangle = 1 << 2,
	annotation_tool_ellipse = 1 << 3,
	annotation_tool_polyline = 1 << 4,
	annotation_tool_polygon = 1 << 5,
	annotation_tool_hlight_point = 1 << 6,
	annotation_tool_hlight_texttag = 1 << 7,
	annotation_tool_eraser_line = 1 << 8,
	annotation_tool_eraser_rectangle = 1 << 9,
	annotation_tool_rhomb = 1 << 10,
	annotation_tool_arrow = 1 << 11,
	annotation_tool_success = 1 << 12,
	annotation_tool_failure = 1 << 13,
};
extern RT_API_EXPORT const uint32 AVD_supportedAnnotationTools;
enum LineArrowType {
	line_arrow_none = 1,
	line_arrow_begin = 1 << 1,
	line_arrow_end = 1 << 2,
	line_arrow_2 = line_arrow_begin | line_arrow_end,
};

enum ClearType {
	annotation_clear_all = 1 << 8,
	annotation_clear_myall = 1 << 9,
	annotation_clear_others = 1 << 10,
};
//#endif


/**
* ��Ƶ�����ṹ.
*
* ��Ƶ�����ṹ��������Ƶ�ɼ����������ز�����Ϣ��
*/
typedef CameraCapability VideoParams;

/**
* ��Ƶ�����ṹ.
*
* ��Ƶ�����ṹ��������Ƶ�ɼ����������ز�����Ϣ��
*/
struct AudioParams {
	uint32 channel;							/**< ͨ������Ĭ��1  */
	uint32 sampleRate;						/**< �����ʣ�Ĭ��44100  */
	uint32 bitrate;							/**< ��������ʣ�Ĭ��96kbps  */
	AudioParams() :channel(1), sampleRate(44100), bitrate(96000) {}
	AudioParams(uint32 c, uint32 s, uint32 b) :channel(c), sampleRate(s), bitrate(b) {}

	friend std::ostream& operator <<(std::ostream& ost, const AudioParams& o) {
		ost << "audioParams:[" << "channel=" << o.channel << ",sampleRate=" << o.sampleRate << ",bitrate=" << o.bitrate << "],";
		return ost;
	}
};

NAMESPACE_TEE3_AVD_END

#endif//RT_COMMON_H
