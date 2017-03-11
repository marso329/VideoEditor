#include "videos.h"

Videos::Videos(){
	av_register_all();
}

Videos::~Videos(){

}

bool Videos::addVideo(std::string filename){
	Video* video=new Video(filename);
	if (video->open()){
		videos.push_back(video);
		return true;
	}
	else{
		delete video;
		return false;
	}

}
