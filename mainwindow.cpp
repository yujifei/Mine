/************************************************************
> File Name: mainwindow.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月02日 星期三 01时18分54秒
************************************************************/

#include "mainwindow.h"
#include "minefield.h"
#include <QToolBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <cstdlib>

MainWindow::MainWindow(QWidget* parent): QDialog(parent)
{
	m_startButton = new QPushButton(tr("开始"));
	m_pauseButton = new QPushButton(tr("暂停"));
	m_timeLabel   = new QLabel;
	m_markLabel   = new QLabel;
	m_toolBar     = new QToolBar;
	m_mineField   = new MineField;

	connect(m_startButton, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(onPauseClicked()));
	connect(m_mineField, SIGNAL(gameReady()), this, SLOT(ready()));
	connect(m_mineField, SIGNAL(gameStart()), this, SLOT(startTimer()));
	connect(m_mineField, SIGNAL(gamePause()), this, SLOT(stopTimer()));
	connect(m_mineField, SIGNAL(gameStop()), this, SLOT(stopTimer()));
	connect(m_mineField, SIGNAL(gameRestart()), this, SLOT(startTimer()));
	connect(m_mineField, SIGNAL(gameMark()), this, SLOT(updateMarked()));
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	m_timer.setInterval(1000);

	m_pauseButton->setEnabled(false);
	m_toolBar->addWidget(m_startButton);
	m_toolBar->addWidget(m_pauseButton);
	m_toolBar->addSeparator();
	m_toolBar->addWidget(m_markLabel);
	m_toolBar->addSeparator();
	m_toolBar->addWidget(m_timeLabel);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_toolBar);
	mainLayout->addWidget(m_mineField);
	
	setSizeGripEnabled(true);
	setWindowTitle(tr("扫雷"));
	setLayout(mainLayout);
	adjustSize();
}

void MainWindow::onStartClicked()
{
	if(m_mineField->getState() == MineField::GameStateUnstart)
	{
		m_startButton->setText(tr("新建"));
		m_mineField->start();
	}
	else
	{
		m_startButton->setText(tr("开始"));
		m_mineField->stop();
		m_pauseButton->setEnabled(false);
		m_markLabel->setText(tr(""));
	}
	m_second = 0;
	showTime();
}

void MainWindow::onPauseClicked()
{
	if(!m_mineField->running())
		return;
	if(m_mineField->getState() == MineField::GameStatePause)
	{
		m_pauseButton->setText(tr("暂停"));
		m_mineField->restart();
	}
	else
	{
		m_pauseButton->setText(tr("继续"));
		m_mineField->pause();
	}
}

void MainWindow::updateMarked()
{
	QString markString = tr("旗标：%0/%1")
		.arg(m_mineField->getDocument().getMarkedNum())
		.arg(m_mineField->getDocument().getMineNum());
	m_markLabel->setText(markString);
}

void MainWindow::ready()
{
	m_startButton->setText(tr("新建"));
	m_pauseButton->setEnabled(true);
	updateMarked();
	m_second = 0;
	showTime();
	m_timer.stop();
}

void MainWindow::startTimer()
{
	m_timer.start();
}

void MainWindow::stopTimer()
{
	m_timer.stop();
}

void MainWindow::updateTime()
{
	++m_second;
	showTime();
}

void MainWindow::showTime()
{
	int second = m_second % 60;
	int minute = (m_second / 60) % 60;
	int hour   = m_second / 60 / 60;
	int second2 = second % 10;
	int minute2 = minute % 10;
	int hour2 = hour % 10;
	second = second / 10;
	minute = minute / 10;
	hour = hour / 10;
	m_timeLabel->setText(tr("时间：%0%1:%2%3:%4%5")
		.arg(hour).arg(hour2)
		.arg(minute).arg(minute2)
		.arg(second).arg(second2));
}
