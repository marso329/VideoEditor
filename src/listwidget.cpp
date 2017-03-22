#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent):QListWidget(parent){

}

void ListWidget::dropEvent(QDropEvent *event){
	   const QMimeData* mimeData = event->mimeData();

	   // check for our needed mime type, here a file or a list of files
	   if (mimeData->hasUrls())
	   {
	     QStringList pathList;
	     QList<QUrl> urlList = mimeData->urls();

	     // extract the local paths of the files
	     for (int i = 0; i < urlList.size() && i < 32; i++)
	     {
	    	 std::cout<<urlList.at(i).toLocalFile().toStdString()<<std::endl;
	       pathList.append(urlList.at(i).toLocalFile());
	     }

	     // call a function to open the files
	    Q_EMIT openFiles(pathList);
	   }
	   event->accept();

}
  void ListWidget::dragEnterEvent(QDragEnterEvent *event){
	  event->acceptProposedAction();
  }

  void ListWidget::dragMoveEvent(QDragMoveEvent *event){
	  event->acceptProposedAction();
  }

  void ListWidget::dragLeaveEvent(QDragLeaveEvent *event){
event->accept();
  }

  void ListWidget::_addItem(QString name){
	  addItem(name);

  }
