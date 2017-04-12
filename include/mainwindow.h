
#ifndef MAINWINDOW_
#define MAINWINDOW_
#include "ui_mainwindow.h"
#include <QString>
#include <QDropEvent>
#include "videos.h"
#include <QAction>
#include <QFileDialog>
#include <sstream>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QGraphicsPixmapItem>
#include <boost/python.hpp>
#include <qimage.h>
#include <QImage>

#include <map>
class MainWindow: public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
	Videos* _videos;
private:
	Ui::MainWindow* ui;
	void createProperties();
	void clearProperties();
	void setProperty(std::string,std::string);
	std::map<std::string,QStandardItem *> _properties;
	QGraphicsScene* scene;
protected:
Q_SIGNALS:
void addFileToListWidget(QString);
void newCurrentVideo(QString);
void newCurrentFrame(float);
void newVideoListwidget(QString);
public Q_SLOTS:
void openFiles(QStringList);
void openFilesMenu();
void currentVideoChangedListWidget(QListWidgetItem * current, QListWidgetItem * previous);
void changeCurrentVideo(Video*);
void changeCurrentFrame(Frame*);
void initPython();
void sliderChanged(int);
void newVideo(QString);
};
#endif
