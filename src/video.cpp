#include "video.h"

Video::Video(std::string filename) {
	AVFormatContext *pFormatCtx = NULL;
	open_=false;
	// Open file
	if (avformat_open_input(&pFormatCtx, filename.c_str(), NULL, NULL) != 0) {
		if (pFormatCtx)
		{
			 avformat_close_input(&pFormatCtx);
			pFormatCtx = NULL;
		}
		return;
	}
	// Get infromation about streams
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		if (pFormatCtx)
		{
			 avformat_close_input(&pFormatCtx);
			pFormatCtx = NULL;
		}
		return;
	}
	av_dump_format(pFormatCtx, 0, filename.c_str(), 0);
	open_=true;
}

Video::~Video() {

}

bool Video::open() {
	return open_;
}
