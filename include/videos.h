#include "video.h"
#include <vector>
#include <string>
#include <QObject>
#include <QString>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <cmath>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
}

class Videos: public QObject {
	Q_OBJECT
public:
	Videos(QObject* parent);
	~Videos();
	bool addVideo(std::string);
	std::vector<std::string> getSupportedExtensions();
	void addVideoPython(std::string);
	boost::shared_ptr<Video>  getCurrentVideoPython();
private:
	std::vector<std::string> createSupportedExtensions();
	std::vector<Video*> videos;
	Video* currentVideo;
	std::vector<std::string> extensions;

protected:
	Q_SIGNALS:
	void newVideo(QString);
	void newCurrentVideo(Video*);
	void changeCurrentFrame(Frame*);
	public Q_SLOTS:
	void setCurrentVideo(QString);
	void newCurrentFrame(float);

};
