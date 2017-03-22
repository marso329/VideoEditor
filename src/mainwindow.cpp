#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent):QMainWindow(parent),ui(new Ui::MainWindow){
	ui->setupUi(this);
	_videos=new Videos(this);
	QObject::connect( ui->listWidget,
			&ListWidget::openFiles,this, &MainWindow::openFiles);

	QObject::connect( _videos,
			&Videos::newVideo,ui->listWidget, &ListWidget::_addItem);
	QObject::connect( ui->actionOpen,
			&QAction::triggered,this, &MainWindow::openFilesMenu);
}
MainWindow::~MainWindow(){

}

void MainWindow::openFiles(QStringList files){
	for (auto it=files.begin();it!=files.end();it++){
		_videos->addVideo((*it).toStdString() );
	}

}

void MainWindow::openFilesMenu(){
	std::vector<std::string> extensions=_videos->getSupportedExtensions();
	std::ostringstream temp;
	temp<<"Video Files (";
	for (auto it=extensions.begin();it!=extensions.end();it++){
		temp<<"*."<<*it<<" ";
	}
	temp<<")";
	QString fileName = QFileDialog::getOpenFileName(this,
	    tr("Open Video"), "/home/martin", tr(temp.str().c_str()));
	_videos->addVideo(fileName.toStdString() );
}
