#ifndef RT_VideoMixer_H_
#define RT_VideoMixer_H_

#include "common.h"
#include "videorender.h"

namespace tee3 {
	namespace avd {
		class ILivecast;
		class IVideoRender;

		/**
		* ��Ƶ����ģ��ӿ�.
		*
		* ��Ƶ����ģ�鶨�巿������Ƶ���������֡����Ĺ��ܽӿڡ�
		*/
		class RT_API_EXPORT IMVideoMixer {
		public:
			/** ����ֱ����Ƶ����
			*
			* @param[in] layout ������Ƶ��ֱ����Ƶ�еĲ�������
			* @param[in] width  ֱ����Ƶͼ���
			* @param[in] height ֱ����Ƶͼ���
			* @return ���ش�����롣
			*/
			virtual Result setMixerTypeaSize(MixerVideoLayoutType layout, int width, int height) = 0;
			/** ����ֱ����Ƶ����ʱ���õ����췽ʽ
			* @param[in] scale	������Ƶ����ʱ���õ����췽ʽ���ο�ScaleType
			* @return ���ش�����롣
			*/
			virtual Result setScaleType(IVideoRenderView::ScalingType scale) = 0;
			/** ����ֱ����Ƶ����ͼƬ
			* @param[in] background ֱ������ͼ
			* @return ���ش�����롣
			*/
			virtual Result setBackgroud(const String& background) = 0;
			/** ��������еĻ�����Ƶ����������Ƶ�������Ҫ�ٴο�����������Ҫ��������ֱ����Ƶ��Overlay��Ƶ��
			*
			* @return ���ش�����롣
			*/
			virtual void   clearSubVideos() = 0;

			//�Զ�����(layout auto)�������Զ����ֲ���������Ƶ��sdk�Զ�����������Ƶ��ϳ�ֱ����Ƶ
			/** �л�ֱ����Ƶ������Ƶ��������Ƶ���ߣ�����������Ƶ��Ϊ����Ƶ��
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			* @note ֱ����Ƶ������Ƶ��vl_auto_overlayģʽ�¿������л���ȱʡΪ������Ƶ
			*/
			virtual Result setMainVideo(const UserId& userId) = 0;
			/** ֱ����Ƶ�Զ����ֵĲ��ֲ�������
			*
			* @param[in] isTopdown  ������Ƶ��ֱ����Ƶ�ϵ�����˳��true: �������£����ң����У� false: �������ϣ����ң�����
			* @param[in] w			������Ƶ���ֱ����Ƶ�Ŀ�ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x W
			* @param[in] h			������Ƶ���ֱ����Ƶ�ĸ߶ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x H
			* @param[in] x_begin    ��ʼ����Ƶ��ֱ����Ƶ�����Ͻ����λ�ã���x���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x x_begin
			* @param[in] y_begin    ��ʼ����Ƶ��ֱ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x y_begin
			* @return ���ش�����롣
			* @note ȱʡ����Ϊ��vl_auto_overlay�������ͣ�������������; w=h=0.3f; x_begin=0.7f; y_begin=0.7f;
			*/
			virtual Result autoLayoutParams(bool isTopdown, float w, float h, float x_begin, float y_begin) = 0;

			//�ֶ�����(layout manual)����ȫ�ֶ���������ֱ����Ƶ�����Խ�һ��������Ƶ�Ų���ֱ����Ƶ������λ��
			/** �����Ƶ��ֱ����Ƶ�ض�λ��
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ��ǰ�棬����ᱻ���ǣ�ȡֵ0-n
			* @param[in] x ����Ƶ��ֱ����Ƶ�����Ͻ����λ�ã���x���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x X
			* @param[in] y ����Ƶ��ֱ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x Y
			* @param[in] w ����Ƶ��ֱ����Ƶ�Ŀ�ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x W
			* @param[in] h ����Ƶ��ֱ����Ƶ�ĸ߶ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x H
			* @return ���ش�����롣
			* @sa addMixerOverlayVideo
			*/
			virtual Result addSubVideo(const UserId& userId) = 0;
			virtual Result addSubVideo(const UserId& userId, int zorder, float x, float y, float w, float h) = 0;
			/** ���¸�����Ƶ��ֱ����Ƶ����ʾ��λ��
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @param[in] zorder �����Ƶ����ʱ��ǰ��λ�ã�zorderԽС����ƵԽ��ǰ�棬����ᱻ���ǣ�ȡֵ0-n
			* @param[in] x ����Ƶ��ֱ����Ƶ�����Ͻ����λ�ã���x���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x X
			* @param[in] y ����Ƶ��ֱ����Ƶ�����Ͻ��ϱ�λ�ã���y���꣬ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x Y
			* @param[in] w ����Ƶ��ֱ����Ƶ�Ŀ�ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��width (ֱ����Ƶ��x W
			* @param[in] h ����Ƶ��ֱ����Ƶ�ĸ߶ȱ�����ȡֵ0.0~1.0���ڲ�ȡֵΪ��height(ֱ����Ƶ��x H
			* @return ���ش�����롣
			*/
			virtual Result updateSubVideo(const UserId& userId, int zorder, float x, float y, float w, float h) = 0;
			/** �Ƴ�ֱ����Ƶ�ϵ�ĳһ��Ƶ
			*
			* @param[in] userId ����ͷId��Ψһ��ʾһ·���������ͷ��Ƶ��
			* @return ���ش�����롣
			*/
			virtual void   removeSubVideo(const UserId& userId) = 0;

		protected:
			virtual ~IMVideoMixer() {}
		};

	} // namespace avd
} // namespace tee3
#endif//RT_VideoMixer_H_
