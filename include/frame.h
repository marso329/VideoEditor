/*
 * frame.h
 *
 *  Created on: Mar 26, 2017
 *      Author: martin
 */

#ifndef VIDEOEDITOR_INCLUDE_FRAME_H_
#define VIDEOEDITOR_INCLUDE_FRAME_H_

#include <QObject>
#include <smmintrin.h>
#include <pmmintrin.h>
#include <immintrin.h>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <iostream>
#include <chrono>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
#include <libavutil/imgutils.h>
}
class Frame: public QObject {
	Q_OBJECT
public:
	Frame(QObject* parent, AVFormatContext* pFormatCtx,int64_t dts,int);
	bool insertData(AVFrame*,struct SwsContext *,int,int);
	static void do_nothing_deleter(Frame*)
	{
	    return;
	}
	~Frame();boost::python::list getRGB(size_t,size_t);
	void setRGB(size_t,size_t,uint8_t,uint8_t,uint8_t);
	QGraphicsPixmapItem* getPixmap();
	  // Width of image
	  private:
	void decode();
	uint8_t * buffer ;
	bool loaded;
	QImage *img ;
	QGraphicsPixmapItem* item;
	AVFormatContext* pFormatCtx;
	AVPacket* package;
	AVCodecContext* pVideoCodecCtx;
	size_t pos;
	 std::chrono::high_resolution_clock::time_point last_time_used;
	 int64_t dts;
	 int videoStreamIndex;
};


#endif /* VIDEOEDITOR_INCLUDE_FRAME_H_ */
