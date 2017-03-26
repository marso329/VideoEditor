#include "videos.h"

Videos::Videos(QObject* parent):QObject(parent){
	av_register_all();
	extensions=createSupportedExtensions();
	currentVideo=NULL;
}

Videos::~Videos(){
}


bool Videos::addVideo(std::string filename){
	Video* video=new Video(filename);
	if (video->open()){
		videos.push_back(video);
		Q_EMIT newVideo(QString::fromStdString(video->getFilenameWithoutPath()));
		if(currentVideo==NULL){
			currentVideo=video;
		}
		Q_EMIT newCurrentVideo(video);
		return true;
	}
	else{
		delete video;
		return false;
	}

}

std::vector<std::string> Videos::createSupportedExtensions(){
 std::vector<std::string> extensions;
 AVOutputFormat * oformat = av_oformat_next(NULL);
 while(oformat != NULL)
 {
     const char* ext= oformat->extensions;
     std::ostringstream temp;
     temp<<ext;
     std::string s=temp.str();
     std::string delimiter = ",";
     size_t pos = 0;
     while ((pos = s.find(delimiter)) != std::string::npos) {
    	 std::string str=s.substr(0, pos);
    	 str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    	 if(str.size()>0){
         extensions.push_back( str);
    	 }
         s.erase(0, pos + delimiter.length());
     }
	 s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
	 if(s.size()>0){
     extensions.push_back( s);
	 }
     oformat = av_oformat_next(oformat);
 }
 std::sort(extensions.begin(), extensions.end());
 extensions.erase(std::unique(extensions.begin(), extensions.end()), extensions.end());
 return extensions;
}
std::vector<std::string> Videos::getSupportedExtensions(){
	return extensions;
}

void Videos::setCurrentVideo(QString name){
	std::cout<<"setcurrent"<<std::endl;
	for (auto it= videos.begin();it!=videos.end();it++){
		std::cout<<(*it)->_filenameWithoutPath<<std::endl;
		if((*it)->_filenameWithoutPath==name.toStdString()){
			std::cout<<"setCUrrentvideo "<<(*it)->_filenameWithoutPath<<std::endl;
			currentVideo=*it;
			Q_EMIT newCurrentVideo(*it);
		}
	}
}

void Videos::addVideoPython(std::string filename){
	Video* video=new Video(filename);
	if (video->open()){
		videos.push_back(video);
		Q_EMIT newVideo(QString::fromStdString(video->getFilenameWithoutPath()));
		if(currentVideo==NULL){
			currentVideo=video;
		}
		Q_EMIT newCurrentVideo(video);

	}
	else{
		delete video;
	}
}

boost::shared_ptr<Video>  Videos::getCurrentVideoPython(){
	return boost::shared_ptr<Video> (currentVideo,Video::do_nothing_deleter);
}
