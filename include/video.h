#ifndef VIDEO_H
#define VIDEO_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "frame.h"
#include <QObject>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
}


class Video: public QObject{
	Q_OBJECT
public:
	Video(std::string,QObject* parent);
	Video(QObject* parent);
	~Video();
	static void do_nothing_deleter(Video*)
	{
	    return;
	}
	bool open();
	std::string getFilenameWithoutPath();
	void CloseVideo();
	void CloseAudio();
	bool CloseFile();
	std::string getProperty(std::string);
	static const std::vector<std::string> _properties;
	std::vector<Frame*> frames;
private:
	int64_t countFrames();
	bool DecodeVideo(const AVPacket *avpkt, AVFrame * pOutFrame);
	void insertFrames();
	bool open_;
	std::string _filename;
public: std::string _filenameWithoutPath;
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

	  public: std::string codecName;

	  // Video stream number in file.
	  private: int videoStreamIndex;

	  // Audio stream number in file.
	  private: int audioStreamIndex;

	  // File is open or not.
	  private: bool isOpen;

	  // Video frame per seconds.
	  public: double videoFramePerSecond;

	  public: int64_t durationUs;

	  public: int64_t durationS;

	  public: int64_t nb_frames;

	  // FFmpeg timebase for video.
	  private: double videoBaseTime;

	  // FFmpeg timebase for audio.
	  private: double audioBaseTime;

	  // FFmpeg context convert image.
	  private: struct SwsContext *pImgConvertCtx;

	  // Width of image
	  public: int width;

	  // Height of image
	public: int height;
};

#endif
