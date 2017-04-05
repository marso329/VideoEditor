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
extern "C" {
#include "avcodec.h"
#include "avformat.h"
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
}
class Frame: public QObject {
	Q_OBJECT
public:
	Frame(QObject* parent);
	bool insertData(AVFrame*,struct SwsContext *,int,int);
	static void do_nothing_deleter(Frame*)
	{
	    return;
	}
	~Frame();
	  // Width of image
	  public:
	size_t width;

	  // Height of image
	size_t height;
	uint8_t * buffer ;
	boost::python::list getRGB(size_t,size_t);
	void setRGB(size_t,size_t,uint8_t,uint8_t,uint8_t);
	QImage *img ;
	QGraphicsPixmapItem* item;
};


#endif /* VIDEOEDITOR_INCLUDE_FRAME_H_ */
