#include <QWidget>
#include <QGraphicsView>
#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>

#include <iostream>
#include <QString>
#include <QMimeData>
#include <QStringList>

class ListWidget:public QListWidget{
Q_OBJECT
public:
	ListWidget(QWidget *parent);                        // implement
private:
protected:
Q_SIGNALS:
	void openFiles(QStringList);

public Q_SLOTS:
    void dropEvent(QDropEvent *ev) override;            // implement
    void dragEnterEvent(QDragEnterEvent *ev) override;  // implement
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void _addItem(QString);
};
