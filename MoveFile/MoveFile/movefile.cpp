#include "movefile.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileDevice>
#include <QMessageBox>
#include <QSettings>
#include <QCoreApplication>

MoveFile::MoveFile(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(slotGetFileList()));
	connect(ui.textEdit_2, SIGNAL(textChanged()), this, SLOT(slotGetDstPath()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(slotStartMove()));

	connect(ui.textEdit_filterKey, SIGNAL(textChanged()), this, SLOT(slotGetFilterKey()));
	connect(ui.pushButton_filter, SIGNAL(clicked()), this, SLOT(slotFilter()));
	
	QString sPath = QCoreApplication::applicationDirPath() + "/config.ini";
	QSettings setting(sPath, QSettings::IniFormat);
	m_DstDir  = setting.value("OutDir").toString();
	ui.textEdit_2->setPlainText(m_DstDir);
}

MoveFile::~MoveFile()
{

}


void MoveFile::slotGetFilterKey()
{
	m_filterKey = ui.textEdit_filterKey->toPlainText();
}

void MoveFile::slotGetFileList()
{
	m_fileList = ui.textEdit->toPlainText();
	qDebug() << m_fileList;
}



void MoveFile::slotGetDstPath()
{
	m_DstDir = ui.textEdit_2->toPlainText();
	QString sPath = QCoreApplication::applicationDirPath() + "/config.ini";
	QSettings setting(sPath, QSettings::IniFormat);
	setting.setValue("OutDir",m_DstDir);//�������ļ�дֵ��ɨ�����CScanWidget�ٰ������ļ���Ϊ0

	
	qDebug() << m_DstDir;
}


void MoveFile::slotStartMove()
{
	// ���ַ������Ϊ·���б�
	QStringList pathList = ui.textEdit->toPlainText().split("\n");
	
	QString outPrint;
	unsigned long long count = 0;
	for (auto filePath : pathList)
	{
		
		//����Դ�ļ�·��
		QFileInfo source(filePath);
		
		if (!source.isFile())
		{
			continue;
		}
		// �����ļ�
		QFile file;

		QString path = source.path();
		int index = path.indexOf('/');
		QString rootDir = path.left(index);

		//

		path.replace(rootDir, m_DstDir);

		QDir dstDir(path);
		dstDir.mkpath(path);

		auto ret = file.copy(filePath, path +"/"+ source.fileName());

		count++;
		
		QString line = QString("[%1] copy %2 [result:%3] \n").arg(QString::number(count)).arg(filePath).arg(ret ? "True" : "False");
		outPrint += line;
		
		
	}
	ui.textBrowser->insertPlainText(outPrint);
	
	QMessageBox box;

	// ��Ϣ��Ϣ 
	box.information(this, "Result", QString("copy success %1 files!").arg(QString::number(count) ) );
}

void MoveFile::slotFilter()
{
	QStringList pathList = m_fileList.split("\n");
	
	auto afterFilter = pathList.filter(m_filterKey);

	QString str = afterFilter.join("\n");
	ui.textEdit->blockSignals(true);

	ui.textEdit->setText(str);
	ui.textEdit->blockSignals(false);
}
