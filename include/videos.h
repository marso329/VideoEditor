#include "video.h"
#include <vector>
#include <string>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
}

class Videos{
public:
	Videos();
	~Videos();
	bool addVideo(std::string);
private:
	std::vector<Video*> videos;
protected:

};
