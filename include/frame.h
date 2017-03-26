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
	int width;

	  // Height of image
	int height;
	uint8_t * buffer ;
};


#endif /* VIDEOEDITOR_INCLUDE_FRAME_H_ */
