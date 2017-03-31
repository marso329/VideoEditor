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
	~Frame();
	  // Width of image
	  public:
	size_t width;

	  // Height of image
	size_t height;
	uint8_t * buffer ;
	std::vector<uint8_t> getRGB(size_t,size_t);
	QImage *img ;
	QGraphicsPixmapItem* item;
};


#endif /* VIDEOEDITOR_INCLUDE_FRAME_H_ */
