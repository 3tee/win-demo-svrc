#ifndef RT_WhiteBoard_H_
#define RT_WhiteBoard_H_

#include "common.h"
#include "room.h"
namespace tee3 {
	namespace avd {
		class IMAnnotation;
		class IRoom;
		/**
		* �װ���Ϣ�ṹ.
		*/
		typedef struct  tagWhiteboardInfo {
			DeviceId	id;
			String			title;
			String			description;
			bool			isShared;
			tagWhiteboardInfo() :isShared(false) {}
		}Whiteboard;
		/**
		* �װ弯������.
		*/
		typedef std::vector<Whiteboard> WhiteboardsType;

		class RT_API_EXPORT IMWhiteboard : public IModule{
		public:
			//class IListener {
			//public:
			//	virtual void onShareWhiteboardResult(Result rv, WhiteboardId id) = 0;
			//	virtual void onCloseWhiteboardResult(Result rv, WhiteboardId id) = 0;
			//protected:
			//	virtual ~IListener() {}
			//};
			/** ��ȡ�װ�ģ��ӿ�
			*
			* @param[in] room �������ָ�롣
			*
			* @return ���ذװ�ģ��ӿ�ָ�롣
			*/
			static IMWhiteboard* getWhiteboard(IRoom* room);
			virtual Result shareWhiteboard(Whiteboard& wb) = 0;
			virtual Result closeWhiteboard(DeviceId id) = 0;
			virtual IMAnnotation* getAnnotation(DeviceId id) = 0;

			virtual Result setBackground(DeviceId id, String filePath) = 0;
			virtual Result setBackground(DeviceId id, uint8 r, uint8 g, uint8 b, uint8 a) = 0;
			virtual Result setWidth(DeviceId id, uint32 w) = 0;
			virtual Result setHeight(DeviceId id, uint32 h) = 0;
			virtual Result getSharedWhiteboards(WhiteboardsType& wbs) = 0;
		protected:
			virtual ~IMWhiteboard() {}
		};
	}
}
#endif
