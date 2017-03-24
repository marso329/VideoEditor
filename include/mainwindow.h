
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
protected:

Q_SIGNALS:
void addFileToListWidget(QString);
public Q_SLOTS:
void openFiles(QStringList);
void openFilesMenu();

};
#endif
