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

std::vector<uint8_t> Frame::getRGB(size_t x,size_t y){
	std::vector<uint8_t> data;
	if(x>=width){
		return data;
	}
	if(y>=height){
		return data;
	}
	uint8_t* buffer_pos=buffer+ (width*y+x)*2;
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	uint16_t temp_data;
	memcpy(&temp_data,buffer_pos,2);
	red=temp_data&0x1f;
	green=(temp_data&0x3e0)>>5;
	blue=(temp_data&0x7c00)>>10;
	data.push_back((uint8_t)red);
	data.push_back((uint8_t)green);
	data.push_back((uint8_t)blue);
return data;

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
