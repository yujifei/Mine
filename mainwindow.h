/************************************************************
> File Name: mainwindow.h
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月02日 星期三 00时31分19秒
************************************************************/
#ifndef __FILE_MAIN_WINDOW__
#define __FILE_MAIN_WINDOW__

#include <QDialog>
#include <QTimer>

class QWidget;
class QToolBar;
class QPushButton;
class QLabel;
class MineField;

class MainWindow: public QDialog
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	void onStartClicked();
	void onPauseClicked();
	void updateMarked();
	void ready();
	void startTimer();
	void stopTimer();
	void updateTime();

private:
	void showTime();

private:
	unsigned long m_second;
	QToolBar* m_toolBar;
	QPushButton* m_startButton;
	QPushButton* m_pauseButton;
	QLabel* m_markLabel;
	QLabel* m_timeLabel;
	QTimer  m_timer;
	MineField* m_mineField;
};

#endif
