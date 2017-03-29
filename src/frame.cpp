/*
 * frame.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: martin
 */
#include "frame.h"


Frame::Frame(QObject* parent):QObject(parent),width(0),height(0),buffer(NULL){

}

Frame::~Frame(){

}

bool Frame::insertData(AVFrame* package,struct SwsContext *pImgConvertCtx,int width_,int height_){
	width=width_;
	height=height_;
	AVFrame * frame = NULL;
		int bufferImgSize = avpicture_get_size(AV_PIX_FMT_RGB555, width, height);
		frame = av_frame_alloc();
		 buffer = (uint8_t*)av_mallocz(bufferImgSize);
		if (frame)
		{
			avpicture_fill((AVPicture*)frame, buffer, AV_PIX_FMT_RGB555, width, height);
			frame->width  = width;
			frame->height = height;
			//frame->data[0] = buffer;

			sws_scale(pImgConvertCtx, package->data, package->linesize,
				0, height, frame->data, frame->linesize);
			img = new QImage(buffer, frame->width, frame->height, QImage::Format_RGB555);
			item =new QGraphicsPixmapItem( QPixmap::fromImage(*img));
		return true;
		}
		else{
			return false;
		}

	return true;
}
