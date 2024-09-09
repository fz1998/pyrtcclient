﻿#ifndef RT_Audio_H_
#define RT_Audio_H_

#include "common.h"
#include "room.h"

namespace rtc {
    class IRoom;

		/**
		* 音频设备管理接口.
		*
		* 音频设备管理接口定义房间中音频设备相关功能接口。
		*/
		class RT_API_EXPORT IAudioDevice {
		public:
			/**
			* 音频设备管理回调接口.
			*
			* 音频设备管理回调接口定义了音频设备相关通知。
			*/
			class IListener {
			public:
				/// 通知
				/** 麦克风插入通知
				*
				* @param[in] item 麦克风信息。
				* @note 当系统中有麦克风设备插入时，此回调触发。
				*/
				virtual void onMicrophonePlugin(const Microphone& item) = 0;
				/** 麦克风拔出通知
				*
				* @param[in] item 麦克风信息。
				* @note 当系统中有麦克风设备拔出时，此回调触发。
				*/
				virtual void onMicrophonePlugout(const Microphone& item) = 0;
				/** 扬声器插入通知
				*
				* @param[in] item 扬声器信息。
				* @note 当系统中有扬声器设备插入时，此回调触发。
				*/
				virtual void onSpeakerPlugin(const Speaker& item) = 0;
				/** 扬声器拔出通知
				*
				* @param[in] item 扬声器信息。
				* @note 当系统中有扬声器设备拔出时，此回调触发。
				*/
				virtual void onSpeakerPlugout(const Speaker& item) = 0;

				/** 麦克风音量变化通知
				*
				* @param[in] volume 麦克风音量，取值：0 至 100，0为最小，100最大。
				* @note 当系统中有麦克风音量变化时，此回调触发。
				*/
				virtual void onMicrophoneVolumeChanged(uint32 volume) = 0;
				/** 扬声器音量变化通知
				*
				* @param[in] volume 扬声器音量，取值：0 至 100，0为最小，100最大。
				* @note 当系统中有扬声器音量变化时，此回调触发。
				*/
				virtual void onSpeakerVolumeChanged(uint32 volume) = 0;
			protected:
				virtual ~IListener() {}
			};
		public:
			/** 设置音频设备管理回调接口
			*
			* @param[in] *listener 音频设备管理回调接口指针。
			* @return 返回错误代码。
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			///microphone
			/** 获取本机麦克风设备信息列表
			*
			* @param[in,out] items 麦克风设备集合存放列表。
			* @return 返回错误代码。
			*/
			virtual Result getMicrophones(MicrophonesType& items) const = 0;
			/** 获取指定设备Id的本机麦克风设备信息
			*
			* @param[in] id 设备Id。
			* @return 返回麦克风设备信息。
			*/
			virtual const Microphone& getMicrophone(const DeviceId& id) const = 0;
			/** 获取当前默认使用的本机麦克风设备信息
			* @return 返回麦克风设备信息。
			*/
			virtual const Microphone& getRecordingMicrophone() const = 0;
			/** 设置当前默认使用的本机麦克风设备
			*
			* @param[in] id 设备Id。
			* @return 返回错误代码。
			*/
			virtual Result setRecordingMicrophone(const DeviceId& id) = 0;
			/** 设置录音的音量大小
			*
			* @param[in] volume 麦克风音量，取值：0 至 100，0为最小，100最大。
			* @return 返回错误代码。
			*/
			virtual Result setRecordingVolume(uint32 volume) = 0;
			/** 获取播放的音量大小
			*
			* @return 麦克风音量，取值：0 至 100，0为最小，100最大。
			*/
			virtual uint32 getRecordingVolume() const = 0;
			/** 获取虚拟录音设备ID
			*
			* @return 获取虚拟录音设备ID。
			*/
			virtual DeviceId getFakeMicrophoneId() const = 0;
			///speaker
			/** 获取本机扬声器设备信息列表
			*
			* @param[in,out] items 扬声器设备集合存放列表。
			* @return 返回错误代码。
			*/
			virtual Result getSpeakers(SpeakersType& items) const = 0;
			/** 获取指定设备Id的本机扬声器设备信息
			*
			* @param[in] id 设备Id。
			* @return 返回扬声器设备信息。
			*/
			virtual const Speaker& getSpeaker(const DeviceId& id) const = 0;
			/** 获取当前默认使用的本机扬声器设备信息
			* @return 返回扬声器设备信息。
			*/
			virtual const Speaker&	getPlayoutSpeaker() const = 0;
			/** 设置当前默认使用的本机扬声器设备
			*
			* @param[in] id 设备Id。
			* @return 返回错误代码。
			*/
			virtual Result setPlayoutSpeaker(const DeviceId& id) = 0;
			/** 设置当前默认扬声器的音量大小
			*
			* @param[in] volume 扬声器音量，取值：0 至 100，0为最小，100最大。
			* @return 返回错误代码。
			*/
			virtual Result setPlayoutVolume(uint32 volume) = 0;
			/** 获取当前默认扬声器的音量大小
			*
			* @return 扬声器音量，取值：0 至 100，0为最小，100最大。
			*/
			virtual uint32 getPlayoutVolume() const = 0;

			///for testing
			/** 开始录制并且播放声音
			*
			* @return 返回错误代码。
			* @note 用于测试麦克风和扬声器是否工作正常。
			*/
			virtual Result recordPlayStart() = 0;
			/** 停止录制并且播放声音
			*
			* @return 返回错误代码。
			*/
			virtual Result recordPlayStop() = 0;
			/** 开始播放声音文件
			*
			* @param[in] file 音频文件。
			* @param[in] loop 单次播放结束后，是否重复播放。
			* @param[in] format 指定音频文件格式。
			* @return 返回错误代码。
			* @note 用于测试扬声器是否工作正常。
			*/
			virtual Result playVoice(const String& file, bool loop, FileFormats format) = 0;
			/** 停止播放声音文件
			*
			* @return 返回错误代码。
			*/
			virtual Result stopVoice() = 0;

			/** 是否正在播放声音文件
			*
			* @return true,false。
			*/
			virtual bool isPlayingVoice() = 0;
			/** 获取录音能级0-9
			*
			* @return 能级。
			*/
			virtual uint32 getRecordLevel() = 0;
			/** 获取播放声音能级0-9
			*
			* @return 能级。
			*/
			virtual uint32 getPlayoutLevel() = 0;

		protected:
			virtual ~IAudioDevice() {}
		};
			
		/**
		* 房间中音频数据回调接口.
		*/
		class IAudioDataListener {
		public:
			/** 音频数据回调接口
            * @param[in] timestamp 时间戳, mi second。
            * @param[in] sampleRate 采样率。
			* @param[in] channels 通道数。
			* @param[in] buf 数据存储指针。
			* @param[in] len 数据长度。
			*/
			virtual void onAudioData(const UserId& userId, uint64 timestamp, uint32 sampleRate, uint32 channels, const void *data, uint32 len) = 0;

		protected:
			virtual ~IAudioDataListener() {}
		};

		/**
		* 房间中音频模块接口.
		*
		* 房间音频模块定义房间音频相关如麦克风、扬声器相关操作功能接口。
		*/
		class RT_API_EXPORT IMAudio : public IModule {
		public:
			/**
			* 房间中音频模块回调接口.
			*
			* 音频模块回调接口定义了房间中音频相关如麦克风、扬声器的通知和异步操作返回。
			*/
			class IListener {
			public:
				/// 通知
				/** 麦克风状态更改通知
				*
				* @param[in] status 麦克风状态。
				* @param[in] fromUserId 设备关联用户Id。
				* @note 当麦克风状态更改后，房间内所有用户接收到此通知。
				* @sa openMicrophone
				* @sa closeMicrophone
				*/
				virtual void onMicrophoneStatusNotify(MicrophoneStatus status, const UserId& fromUserId) = 0;
				/** 语音激励通知
				*
				* @param[in] info 语音激励信息。
				* @note 语音激励通知，只有启用语音激励后才会有语音激励通知。启用语音激励接口为：monitorAudioLevel。
				* @sa monitorAudioLevel
				*/
				virtual void onAudioLevelMonitorNotify(const AudioInfo& info) = 0;

				/// 异步返回
				/** 本用户打开麦克风异步返回
				*
				* @param[in] result 错误代码。
				* @sa openMicrophone
				*/
				virtual void onOpenMicrophoneResult(Result result) = 0;
				/** 本用户关闭麦克风异步返回
				*
				* @param[in] result 错误代码。
				* @sa closeMicrophone
				*/
				virtual void onCloseMicrophoneResult(Result result) = 0;

				/// 异步返回
				/** 本用户订阅音频异步返回
				*
				* @param[in] result 错误代码。
				* @param[in] fromId 用户Id，唯一标示一个用户。
				*
				* @sa subscribe
				*/
				virtual void onSubscribeResult(Result result, const UserId& fromId){}
				/** 本用户取消订阅音频异步返回
				*
				* @param[in] result 错误代码。
				* @param[in] fromId 用户Id，唯一标示一个用户。
				*
				* @sa unsubscribe
				*/
				virtual void onUnsubscribeResult(Result result, const UserId& fromId){}

				/** 媒体播放状态通知
				*
				* @param[in] rid 房间号。
				* @param[in] pyid 播放id。
				* @param[in] uid  用户id。
				* @param[in] playevent 播放事件0:开发播放，1:停止播放
				*
				* @sa 
				*/
				virtual void onMediaPlayNotify(RoomId rid, String pyid, UserId uid,MediaPlayEvents playevent) {}
				/** 媒体播放进度通知
				*
				* @param[in] rid 房间号。
				* @param[in] pyid 播放id。
				* @param[in] uid 用户id
				* @param[in] currProgressValue 播放时长,毫秒(ms)
				*
				* @sa
				*/
				virtual void onMediaPlayProgressNotify(uint32 currProgressValue) {}
			protected:
				virtual ~IListener() {}
			};
			/** 获取音频模块接口
			*
			* @param[in] room 房间对象指针。
			*
			* @return 返回音频模块接口指针。
			*/
			static IMAudio* getAudio(IRoom* room);
			//
			/** 设置音频模块回调接口
			*
			* @param[in] *listener 音频模块回调接口指针。
			* @return 返回错误代码。
			* @sa IListener
			*/
			virtual Result setListener(IListener* listener) = 0;
			/** 打开本地麦克风发布到房间中
			*
			* @return 返回错误代码。
			* @note 为异步操作，操作结果在 onOpenMicrophoneResult 中返回。
			* @sa onOpenMicrophoneResult
			*/
			virtual Result openMicrophone() = 0;
			/** 关闭本地麦克风发布到房间中
			*
			* @return 返回错误代码。
			* @note 为异步操作，操作结果在 onCloseMicrophoneResult 中返回。
			* @sa onCloseMicrophoneResult
			*/
			virtual Result closeMicrophone() = 0;
			/** 获取本地麦克风状态
			* @return 返回麦克风状态。
			*/
			virtual MicrophoneStatus getMicrophoneStatus() const = 0;
			// no input audio, anyone cann't listen my speak; like pause mic
			/** 本地麦克风静默
			*
			* @return 返回错误代码。
			* @note 麦克风静默表示本地没有声音传递到房间中，房间中用户不会听到本地的任何声音。
			*/
			virtual Result muteMicrophone() = 0;
			/** 本地麦克风取消静默
			* @return 返回错误代码。
			*/
			virtual Result unmuteMicrophone() = 0;
			/** 判断本地麦克风是否静默
			* @return 麦克风是否被静默。
			*/
			virtual bool ismuteMicrophone() const = 0;
			// no output audio, cann't listen anyone sound
			/** 本地扬声器静默
			*
			* @return 返回错误代码。
			* @note 扬声器静默表示房间中的声音不会在本地扬声器播放，本用户不会听到任何房间中的声音。
			*/
			virtual Result muteSpeaker() = 0;
			/** 本地扬声器取消静默
			* @return 返回错误代码。
			*/
			virtual Result unmuteSpeaker() = 0;
			/** 判断本地扬声器是否静默
			*/
			virtual bool ismuteSpeaker() const = 0;

			/*** 禁默指定用户的声音
			*/
			virtual Result muteAudio(const UserId& userId) = 0;
			virtual Result unmuteAudio(const UserId& userId) = 0;
			virtual bool ismuteAudio(const UserId& userId) const =0;
			/// remote microphone control
			/** 获取远端麦克风状态
			* @param[in] userId 关联用户Id。
			* @return 返回麦克风状态。
			*/
			virtual MicrophoneStatus getRemoteMicrophoneStatus(const UserId& userId) const = 0;
			/** 命令远端用户打开麦克风
			* @param[in] userId 关联用户Id。
			* @return 返回错误代码。
			*/
			virtual Result remotecmdOpenMicrophone(const UserId& userId) = 0;
			/** 命令远端用户关闭麦克风
			* @param[in] userId 关联用户Id。
			* @return 返回错误代码。
			*/
			virtual Result remotecmdCloseMicrophone(const UserId& userId) = 0;

			/** 命令远端用户静默麦克风
			* @param[in] userId 关联用户Id。
			* @return 返回错误代码。
			*/
			virtual Result remotecmdMuteMicrophone(const UserId& userId) = 0;
			/** 命令远端用户取消静默麦克风
			* @param[in] userId 关联用户Id。
			* @return 返回错误代码。
			*/
			virtual Result remotecmdUnmuteMicrophone(const UserId& userId) = 0;

			/** 获取音频设备管理接口
			*
			* @return 返回音频设备管理接口指针。
			* @sa IAudioDevice
			*/
			virtual IAudioDevice* getAudioDevice() = 0;

			/** 开启语音激励功能
			* @return 返回错误代码。
			*/
			virtual Result monitorAudioLevel() = 0;
			/** 关闭语音激励
			* @return 返回错误代码。
			*/
			virtual Result unmonitorAudioLevel() = 0;
			/** 判断是否开启语音激励
			*/
			virtual bool ismonitorAudioLevel() const = 0;
			
			///
		public:
            /// audio listener
            /** 注册某一路音频数据回调接口
            * @param[in] userId 音频对应的用户ID。
            * @param[in] listener 混音数据回调指针。
			* @param[in] freq 采样频率 8000，16000 ，44100，48000
			* @param[in] channels 通道数 1，2
            * @return 返回错误代码。
            * @sa IAudioDataListener
            */
            virtual Result registerPCMDataListener(const UserId& userId, IAudioDataListener* listener, int freq , int channels) = 0;
            /** 取消某一路音频数据回调接口
            * @param[in] userId 音频对应的用户ID。
            * @return 返回错误代码。
            * @sa IAudioDataListener
            */
            virtual Result unregisterPCMDataListener(const UserId& userId) = 0;

			/** 设置获取混音数据回调接口
			* @param[in] listener 混音数据回调指针。
			* @param[in] sampleRate 导出混音数据的采样率：16000,44100,48000。
			* @param[in] channels 导出混音数据的通道数：1，2。
			* @return 返回错误代码。
			* @sa IAudioDataListener
			* @sa ro_audio_mixerdata_callback_buffered 单次混音数据回调“10ms数据”还是“1024samples数据”
			* @note 如果音视频同时混合出流，建议先设置视频，再设置音频的回调接口，有助于音视频时间戳对齐。
			*/
			virtual Result setMixerDataListener(IAudioDataListener* listener) = 0;
			virtual Result setMixerDataListener(IAudioDataListener* listener, uint32 sampleRate, uint32 channels) = 0;
            ///

			/// subscribe
			/** 订阅一个用户的音频
			*
			* @param[in] userId 用户Id。
			* @return 返回错误代码。
			* @note 订阅操作为异步操作，操作结果在 onSubscribeResult 中返回。房间中发布的音频缺省已经订阅，所以一般不需要调用
			* 此函数，只有调用了unsubscribe后，若又需要此音频时才调用此函数。
			* @sa onSubscribeResult
			*/
			virtual Result subscribe(const UserId& userId) = 0;
			/** 取消订阅一个用户的音频
			*
			* @param[in] userId 用户Id。
			* @return 返回错误代码。
			* @note 取消订阅操作为异步操作，操作结果在 onUnsubscribeResult 中返回。房间中发布的音频缺省已经订阅，如果不想听某
			* 用户的声音，可以调用此函数来取消订阅。
			* @sa onUnsubscribeResult
			*/
			virtual Result unsubscribe(const UserId& userId) = 0;

			/** 获取已经publish的音频用户
			*
			* @param[in,out] items 用户列表。
			* @return 返回错误代码。
			*/
			virtual Result getPubAudioUsers(std::vector<UserId>& items) = 0;
			/** 获取已经Subscrib的音频用户
			*
			* @param[in,out] items 用户列表。
			* @return 返回错误代码。
			*/
			virtual Result getSubAudioUsers(std::vector<UserId>& items) = 0;
			/** 判断用户音频是否已经发布
			* @param[in] userId 摄像头Id，唯一标示用户ID。
			* @return 返回是否是已发布的用户。
			*/
			virtual bool isAudioPublished(const UserId& userId) = 0;
			/** 判断用户音频是否已经订阅
			* @param[in] userId 摄像头Id，唯一标示用户ID。
			* @return 返回是否是已订阅的用户。
			*/
			virtual bool isAudioSubscribed(const UserId& userId) = 0;

			/** 设置当前音频流推送的保活时长(单位为毫秒)
			*
			*/
			virtual void setPublishKeepAliveTime(int timeout) = 0;

		protected:
			virtual ~IMAudio() {}
		};

} // namespace rtc
#endif//RT_Audio_H_
