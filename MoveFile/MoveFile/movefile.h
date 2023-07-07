#ifndef MOVEFILE_H
#define MOVEFILE_H

#include <QtWidgets/QMainWindow>
#include "ui_movefile.h"

class MoveFile : public QMainWindow
{
	Q_OBJECT

public:
	MoveFile(QWidget *parent = 0);
	~MoveFile();
public slots:
	void slotGetFileList();
	void slotStartMove();
	void slotGetDstPath();
	void slotGetFilterKey();

	void slotFilter();
private:
	Ui::MoveFileClass ui;

	QString m_fileList;
	QString m_DstDir;
	QString m_filterKey;
};

#endif // MOVEFILE_H
