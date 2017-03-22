#include "video.h"
#include <vector>
#include <string>
#include <QObject>
#include <QString>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
extern "C" {
#include "avcodec.h"
#include "avformat.h"
}

class Videos:public QObject{
Q_OBJECT
public:
	Videos(QObject* parent);
	~Videos();
	bool addVideo(std::string);
std::vector<std::string> getSupportedExtensions();
private:
std::vector<std::string> createSupportedExtensions();
	std::vector<Video*> videos;
	std::vector<std::string> extensions;
protected:
Q_SIGNALS:
void newVideo(QString);

};
