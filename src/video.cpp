#include "video.h"

Video::Video(std::string filename) : pImgConvertCtx(NULL), audioBaseTime(0.0), videoBaseTime(0.0),
videoFramePerSecond(0.0), isOpen(false), audioStreamIndex(-1), videoStreamIndex(-1),
pAudioCodec(NULL), pAudioCodecCtx(NULL), pVideoCodec(NULL), pVideoCodecCtx(NULL),
pFormatCtx(NULL) {
	open_=false;
	// Open file
	if (avformat_open_input(&pFormatCtx, filename.c_str(), NULL, NULL) != 0) {
		if (pFormatCtx)
		{
			CloseFile();
		}
		return;
	}
	// Get infromation about streams
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		if (pFormatCtx)
		{
			CloseFile();
		}
		return;
	}
	bool res = false;

	if (pFormatCtx)
	{
		videoStreamIndex = -1;

		for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
		{
			if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoStreamIndex = i;
				pVideoCodecCtx = pFormatCtx->streams[i]->codec;
				pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);

				if (pVideoCodec)
				{
					res     = !(avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0);
					width   = pVideoCodecCtx->coded_width;
					height  = pVideoCodecCtx->coded_height;
				}

				break;
			}
		}

		if (!res)
		{
			CloseVideo();
		}
		else
		{
			pImgConvertCtx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height,
				pVideoCodecCtx->pix_fmt,
				pVideoCodecCtx->width, pVideoCodecCtx->height,
				AV_PIX_FMT_BGR24,
				SWS_BICUBIC, NULL, NULL, NULL);
		}
	}



	open_=true;
	_filename=filename;
	_filenameWithoutPath=_filename.substr( _filename.find_last_of("\\/")+1,_filename.size()- _filename.find_last_of("\\/")-1);
}

Video::~Video() {

}
std::string Video::getFilenameWithoutPath(){
	return _filenameWithoutPath;
}

bool Video::open() {
	return open_;
}

void Video::CloseVideo()
{
	if (pVideoCodecCtx)
	{
		avcodec_close(pVideoCodecCtx);
		pVideoCodecCtx = NULL;
		pVideoCodec = NULL;
		videoStreamIndex = 0;
	}
}

void Video::CloseAudio()
{
	if (pAudioCodecCtx)
	{
		avcodec_close(pAudioCodecCtx);
		pAudioCodecCtx   = NULL;
		pAudioCodec      = NULL;
		audioStreamIndex = 0;
	}
}
bool Video::CloseFile()
{
	isOpen = false;

	// Close video and audio.
	CloseVideo();
	CloseAudio();

	if (pFormatCtx)
	{
		avformat_close_input(&pFormatCtx);
		pFormatCtx = NULL;
	}

	return true;
}

