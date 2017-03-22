#ifndef VIDEO_H
#define VIDEO_H
#include <string>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
}


class Video{
public:
	Video(std::string);
	~Video();
	bool open();
	std::string getFilenameWithoutPath();
private:
	bool open_;
	std::string _filename;
	std::string _filenameWithoutPath;
protected:
};
#endif
