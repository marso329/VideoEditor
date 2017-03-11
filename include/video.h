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
private:
	bool open_;
protected:
};
