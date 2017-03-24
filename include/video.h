#ifndef VIDEO_H
#define VIDEO_H
#include <string>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
}


class Video{
public:
	Video(std::string);
	~Video();
	bool open();
	std::string getFilenameWithoutPath();
	void CloseVideo();
	void CloseAudio();
	bool CloseFile();
private:
	bool open_;
	std::string _filename;
	std::string _filenameWithoutPath;
	// FFmpeg file format.
	  private: AVFormatContext* pFormatCtx;

	  // FFmpeg codec context.
	  private: AVCodecContext* pVideoCodecCtx;

	  // FFmpeg codec for video.
	  private: AVCodec* pVideoCodec;

	  // FFmpeg codec context for audio.
	  private: AVCodecContext* pAudioCodecCtx;

	  // FFmpeg codec for audio.
	  private: AVCodec* pAudioCodec;

	  // Video stream number in file.
	  private: int videoStreamIndex;

	  // Audio stream number in file.
	  private: int audioStreamIndex;

	  // File is open or not.
	  private: bool isOpen;

	  // Video frame per seconds.
	  private: double videoFramePerSecond;

	  // FFmpeg timebase for video.
	  private: double videoBaseTime;

	  // FFmpeg timebase for audio.
	  private: double audioBaseTime;

	  // FFmpeg context convert image.
	  private: struct SwsContext *pImgConvertCtx;

	  // Width of image
	  private: int width;

	  // Height of image
	private: int height;
};
#endif
