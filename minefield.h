/************************************************************
> File Name: minefield.h
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年09月30日 星期一 05时24分57秒
************************************************************/
#ifndef __FILE_MINE_FIELD__
#define __FILE_MINE_FIELD__

#include "minelogical.h"
#include "config.h"
#include <QWidget>
#include <QSize>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QRect>
#include <vector>

class MineField: public QWidget
{
	Q_OBJECT
public:
	enum GameState{GameStateUnstart, GameStateStarted, GameStatePause, GameStateFailed, GameStateWin};

public:
	MineField(QWidget* parent = NULL);
	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	void  init(unsigned long width, unsigned long height, unsigned long nMine);
	GameState getState() const;
	bool running() const;
	const MineLogical& getDocument() const;

public slots:
	void pause();
	void restart();
	void start();
	void stop();

signals:
	void gameStart();
	void gameMark();
	void gamePause();
	void gameRestart();
	void gameStop();
	void gameReady();

protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	MineField(const MineField&);
	MineField& operator=(const MineField&);
	void drawGameUnstart(QPaintEvent* event);
	void drawGameStarted(QPaintEvent* event);
	void drawGamePause(QPaintEvent* event);
	void drawGameFailed(QPaintEvent* event);
	void mousePressUnstart(QMouseEvent* event);
	void mousePressStarted(QMouseEvent* event);
	void rebuildCreateRect(QResizeEvent* event);
	void rebuildMineRect(QResizeEvent* event);
	QRect getHintTextRect(QResizeEvent* event) const;

private:
	MineLogical m_mineLogical;
	GameState   m_gameState;
	int         m_currentGrid;
	QRect       m_createRect[4];
	std::vector<QRect> m_mineRect;
	bool		m_running;
};

#endif
