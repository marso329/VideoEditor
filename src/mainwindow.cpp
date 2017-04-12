#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	_videos = new Videos(this);
	QObject::connect(ui->listWidget, &ListWidget::openFiles, this,
			&MainWindow::openFiles);

	QObject::connect(_videos, &Videos::newVideo,this,&MainWindow::newVideo);
	QObject::connect(this,&MainWindow::newVideoListwidget, ui->listWidget,
			&ListWidget::_addItem);
	QObject::connect(ui->actionOpen, &QAction::triggered, this,
			&MainWindow::openFilesMenu);
	QObject::connect(ui->listWidget, &ListWidget::currentItemChanged, this,
			&MainWindow::currentVideoChangedListWidget);
	QObject::connect(_videos, &Videos::newCurrentVideo, this,
			&MainWindow::changeCurrentVideo);
	QObject::connect(this, &MainWindow::newCurrentVideo, _videos,
			&Videos::setCurrentVideo);
	 scene = new QGraphicsScene();
	ui->graphicsView->setScene(scene);
	ui->graphicsView->show();
	ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio );
	ui->horizontalSlider->setMinimum(0);
	ui->horizontalSlider->setMaximum(5400);
	QObject::connect(ui->horizontalSlider, &QSlider::valueChanged,this,
			&MainWindow::sliderChanged);
	QObject::connect(this, &MainWindow::newCurrentFrame,_videos,
			&Videos::newCurrentFrame);
	QObject::connect(_videos, &Videos::changeCurrentFrame,this,
				&MainWindow::changeCurrentFrame);

createProperties();
initPython();
}

void MainWindow::changeCurrentFrame(Frame* frame){
	QList<QGraphicsItem *> items =scene->items();
	for (auto it = items.begin();it!=items.end();it++){
		scene->removeItem(*it);
	}
	    scene->addItem(frame->getPixmap());
	    scene->update();
	    ui->graphicsView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
ui->graphicsView->show();
}
void MainWindow::sliderChanged(int value){
	float pos=(float)value/(float)ui->horizontalSlider->maximum();
	Q_EMIT newCurrentFrame(pos);
}
void MainWindow::currentVideoChangedListWidget(QListWidgetItem * current, QListWidgetItem * previous __attribute__ ((unused))){
QString shortFilename=current->text();
Q_EMIT newCurrentVideo(shortFilename);
}

void MainWindow::createProperties(){
	//properties widget
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->horizontalHeader()->setSectionResizeMode(
			QHeaderView::Stretch);
	QStandardItemModel *model = new QStandardItemModel(Video::_properties.size(), 2, this); //2 Rows and 3 Columns
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Properties")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));
	ui->tableView->setModel(model);
	std::size_t index=0;
	for (auto it=Video::_properties.begin();it!=Video::_properties.end();it++){
		QStandardItem * item = new QStandardItem();
		QStandardItem * data = new QStandardItem();
		item->setData(QVariant((*it).c_str()));
		item->setText(tr((*it).c_str()));
		model->setItem(index, 0, item);
		model->setItem(index, 1, data);
		_properties[*it]=data;
		index++;
	}
}
MainWindow::~MainWindow() {

}
void MainWindow::clearProperties(){
	for(auto it=_properties.begin();it!=_properties.end();it++){
		it->second->setText(tr(""));
	}
}

void MainWindow::setProperty(std::string key,std::string value){
if(_properties.find(key)!=_properties.end()){
	_properties[key]->setText(tr(value.c_str()));

}
}

void MainWindow::openFiles(QStringList files) {
	for (auto it = files.begin(); it != files.end(); it++) {
		_videos->addVideo((*it).toStdString());
	}

}

void MainWindow::openFilesMenu() {
	std::vector<std::string> extensions = _videos->getSupportedExtensions();
	std::ostringstream temp;
	temp << "Video Files (";
	for (auto it = extensions.begin(); it != extensions.end(); it++) {
		temp << "*." << *it << " ";
	}
	temp << ")";
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"),
			"/home/martin", tr(temp.str().c_str()));
	_videos->addVideo(fileName.toStdString());
}

void MainWindow::changeCurrentVideo(Video* newCurrentVideo){
	std::cout<<"changeCurerntVideo: "<<newCurrentVideo->_filenameWithoutPath<<std::endl;
	clearProperties();
	for (auto it = Video::_properties.begin();it!=Video::_properties.end();it++){
		setProperty(*it,newCurrentVideo->getProperty(*it));
	}
	ui->horizontalSlider->setValue(floorf(newCurrentVideo->getPosition()*(float)ui->horizontalSlider->maximum()));
	//Frame* frame= newCurrentVideo->frames.front();
	//scene->removeItem(frame->getPixmap());
	 //   scene->addItem(frame->getPixmap());
//ui->graphicsView->show();
}

void MainWindow::initPython(){
	boost::python::dict main_namespace=ui->widget->getMainNamespace();
	try {
		main_namespace["Frame"] = class_<Frame,boost::noncopyable>(
				"Frame", boost::python::no_init).def("getRGB",
				&Frame::getRGB).def("setRGB",&Frame::setRGB);
		boost::python::register_ptr_to_python<boost::shared_ptr<Frame>>();
	} catch (error_already_set ) {
		PyErr_Print();
	}
	try {
		main_namespace["Video"] = class_<Video,boost::noncopyable>(
				"Video", boost::python::no_init).def_readonly("FPS", &Video::videoFramePerSecond)
				.def_readonly("Width", &Video::width).
				def_readonly("Height", &Video::height).
				def_readonly("Duration_sec", &Video::durationS).
				def_readonly("Duration_usec", &Video::durationUs).def("getCurrentFrame",&Video::getCurrentFramePython);
		boost::python::register_ptr_to_python<boost::shared_ptr<Video>>();
	} catch (error_already_set ) {
		PyErr_Print();
	}
	//expose videos
	try {
		main_namespace["Videos"] = class_<Videos,boost::noncopyable>(
				"Videos", boost::python::no_init).def("open",
				&Videos::addVideoPython).def("getCurrent",&Videos::getCurrentVideoPython);
		boost::python::register_ptr_to_python<boost::shared_ptr<Videos>>();
		main_namespace["videos"] = ptr(_videos);
	} catch (error_already_set ) {
		PyErr_Print();
	}

}
void MainWindow::newVideo(QString value){
Q_EMIT newVideoListwidget(value);
}
