#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	_videos = new Videos(this);
	QObject::connect(ui->listWidget, &ListWidget::openFiles, this,
			&MainWindow::openFiles);

	QObject::connect(_videos, &Videos::newVideo, ui->listWidget,
			&ListWidget::_addItem);
	QObject::connect(ui->actionOpen, &QAction::triggered, this,
			&MainWindow::openFilesMenu);
	QObject::connect(ui->listWidget, &ListWidget::currentItemChanged, this,
			&MainWindow::currentVideoChangedListWidget);
	QObject::connect(_videos, &Videos::newCurrentVideo, this,
			&MainWindow::changeCurrentVideo);
	QObject::connect(this, &MainWindow::newCurrentVideo, _videos,
			&Videos::setCurrentVideo);

createProperties();
initPython();
}

void MainWindow::currentVideoChangedListWidget(QListWidgetItem * current, QListWidgetItem * previous){
QString shortFilename=current->text();
Q_EMIT newCurrentVideo(shortFilename);
std::cout<<"curretnVideochangedListwidget: "<<shortFilename.toStdString()<<std::endl;
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
}

void MainWindow::initPython(){
	boost::python::dict main_namespace=ui->widget->getMainNamespace();

	try {
		main_namespace["Video"] = class_<Video,boost::noncopyable>(
				"Video", boost::python::no_init).def_readonly("FPS", &Video::videoFramePerSecond)
				.def_readonly("Width", &Video::width).
				def_readonly("Height", &Video::height).
				def_readonly("Duration_sec", &Video::durationS).
				def_readonly("Duration_usec", &Video::durationUs);
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
