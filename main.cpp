/************************************************************
> File Name: main.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月02日 星期三 21时44分43秒
************************************************************/

#include "mainwindow.h"
#include "config.h"
#include <QApplication>
#include <QTextCodec>

const char* configFile = "mine.conf";

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	readConfigure(configFile);

	MainWindow mainWindow;
	mainWindow.show();
	int result = app.exec();

	writeConfigure(configFile);
	return result;
}

