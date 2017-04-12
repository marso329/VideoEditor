/*
 * frame.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: martin
 */
#include "frame.h"

Frame::Frame(QObject* parent, AVFormatContext* pFormatCtx,int64_t dts,int videoStreamIndex ) :
		QObject(parent), buffer(NULL), loaded(
				false), img(NULL), item(NULL),pFormatCtx(pFormatCtx), package(NULL), pVideoCodecCtx(
						pFormatCtx->streams[videoStreamIndex]->codec), pos(0),dts(dts),videoStreamIndex(videoStreamIndex) {

//decode();
}

Frame::~Frame() {

}
void Frame::decode() {
	av_seek_frame(pFormatCtx,videoStreamIndex,dts,AVSEEK_FLAG_BACKWARD);
	AVPacket temp_package;

//	while(true){
	av_read_frame(pFormatCtx, &temp_package);
//	if(temp_package.dts==dts){
//		break;
//	}
//	}
	package=&temp_package;

	AVFrame *pVideoYuv = av_frame_alloc();
	bool res = false;

	if (pVideoCodecCtx) {
		if (package && pVideoYuv) {
			int got_picture_ptr = 0;
			int videoFrameBytes = avcodec_decode_video2(pVideoCodecCtx,
					pVideoYuv, &got_picture_ptr, package);
			res = (videoFrameBytes > 0);
		}
	}
	if (!res) {
		return;
	}
	AVFrame * frame = NULL;
	int bufferImgSize = av_image_get_buffer_size(AV_PIX_FMT_RGB555, pVideoCodecCtx->coded_width, pVideoCodecCtx->coded_height,32);
	frame = av_frame_alloc();
	buffer = (uint8_t*) av_mallocz(bufferImgSize);
	if (frame) {
		avpicture_fill((AVPicture*) frame, buffer, AV_PIX_FMT_RGB555, pVideoCodecCtx->coded_width,
				pVideoCodecCtx->coded_height);
		frame->width = pVideoCodecCtx->coded_width;
		frame->height = pVideoCodecCtx->coded_height;
		struct SwsContext * pImgConvertCtx = sws_getContext(
				pVideoCodecCtx->width, pVideoCodecCtx->height,
				pVideoCodecCtx->pix_fmt, pVideoCodecCtx->width,
				pVideoCodecCtx->height,
				AV_PIX_FMT_RGB555,
				SWS_BICUBIC, NULL, NULL, NULL);


		sws_scale(pImgConvertCtx, pVideoYuv->data, pVideoYuv->linesize, 0,
				 pVideoCodecCtx->height, frame->data, frame->linesize);
		img = new QImage(buffer, frame->width, frame->height,
				QImage::Format_RGB555);
		item = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
		std::cout<<"img: "<<item<<std::endl;
		res = true;
	}
	loaded = res;
	//std::cout<<"frame loaded "<<loaded<<" "<<width<<" " <<height<<std::endl;
	if(package->buf==NULL){
		std::cout<<"buffer is zero"<<std::endl;

	}
	if(package->data==NULL){
		std::cout<<"data is null"<<std::endl;
	}
}

void Frame::setRGB(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
	if (!loaded) {
		decode();
	}
	if (x >= (size_t)pVideoCodecCtx->coded_width) {
		return;
	}
	if (y >= (size_t)pVideoCodecCtx->coded_height) {
		return;
	}
	if (r < 31 || g < 31 || b < 31) {
		return;
	}
	uint8_t* buffer_pos = buffer + (pVideoCodecCtx->coded_width * y + x) * 2;
	uint16_t temp_data = 0;
	temp_data += r & 0x1f;
	temp_data += ((g & 0x3e0) >> 5);
	temp_data += ((b & 0x7c00) >> 10);
	memcpy(buffer_pos, &temp_data, 2);
}

boost::python::list Frame::getRGB(size_t x, size_t y) {
	if (!loaded) {
		decode();
	}
	boost::python::list data;
	if (x >=(size_t) pVideoCodecCtx->coded_width) {
		return data;
	}
	if (y >=(size_t) pVideoCodecCtx->coded_height) {
		return data;
	}
	uint8_t* buffer_pos = buffer + (pVideoCodecCtx->coded_width * y + x) * 2;
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	uint16_t temp_data;
	memcpy(&temp_data, buffer_pos, 2);
	red = temp_data & 0x1f;
	green = (temp_data & 0x3e0) >> 5;
	blue = (temp_data & 0x7c00) >> 10;
	data.append((uint8_t) red);
	data.append((uint8_t) green);
	data.append((uint8_t) blue);
	return data;

}
QGraphicsPixmapItem* Frame::getPixmap() {
	if (!loaded) {
		decode();
	}
	return item;
}
