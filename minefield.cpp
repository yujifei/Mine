/************************************************************
> File Name: minefield.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年09月30日 星期一 05时25分31秒
************************************************************/

#include "minefield.h"
#include "privatedialog.h"
#include <QPainter>
#include <cassert>

MineField::MineField(QWidget* parent)
	:QWidget(parent)
	,m_mineLogical()
	,m_gameState(GameStateUnstart)
	,m_currentGrid(-1)
{
	rebuildCreateRect(NULL);
	getHintTextRect(NULL);
	setMouseTracking(true);
}

QSize MineField::sizeHint() const
{
	return DefaultSize;
}

QSize MineField::minimumSizeHint() const
{
	return MinimumSize;
}

void MineField::init(unsigned long width, unsigned long height, unsigned long nMine)
{
	m_mineLogical.init(width, height, nMine);
	m_mineRect.clear();
	if(m_mineRect.size() < width * height)
		m_mineRect.resize(width * height);
	
	rebuildMineRect(NULL);
	m_gameState = GameStateStarted;
	m_running = false;
	update();
	emit gameReady();
}

void MineField::pause()
{
	if(m_gameState != GameStateStarted || !m_running)
		return;
	m_gameState = GameStatePause;
	update();
	emit gamePause();
}

void MineField::restart()
{
	if(m_gameState != GameStatePause)
		return;
	m_gameState = GameStateStarted;
	update();
	emit gameRestart();
}

void MineField::start()
{
	if(m_gameState != GameStateUnstart)
		return;
	init(DefaultGridWidth, DefaultGridHeight, DefaultMineNum);
}

void MineField::stop()
{
	m_gameState = GameStateUnstart;
	update();
}

MineField::GameState MineField::getState() const
{
	return m_gameState;
}

const MineLogical& MineField::getDocument() const
{
	return m_mineLogical;
}

bool MineField::running() const
{
	return m_running;
}

void MineField::paintEvent(QPaintEvent* event)
{
	switch(m_gameState)
	{
	case GameStateUnstart:
		drawGameUnstart(event);
		break;
	case GameStateStarted:
		drawGameStarted(event);
		break;
	case GameStatePause:
		drawGamePause(event);
		break;
	case GameStateFailed:
		drawGameFailed(event);
		break;
	default:
		QWidget::paintEvent(event);
	}
}

void MineField::resizeEvent(QResizeEvent* event)
{
	rebuildCreateRect(event);
	getHintTextRect(event);
	rebuildMineRect(event);
	QWidget::resizeEvent(event);
	update();
}

void MineField::mousePressEvent(QMouseEvent* event)
{
	if(m_gameState == GameStateUnstart)
		mousePressUnstart(event);
	else if(m_gameState == GameStateStarted)
		mousePressStarted(event);
	else
		QWidget::mousePressEvent(event);
	update();
}

void MineField::mouseMoveEvent(QMouseEvent* event)
{
	if(m_gameState == GameStateUnstart)
	{
		m_currentGrid = -1;
		if(m_createRect[0].contains(event->pos()))
			m_currentGrid = 0;
		else if(m_createRect[1].contains(event->pos()))
			m_currentGrid = 1;
		else if(m_createRect[2].contains(event->pos()))
			m_currentGrid = 2;
		else if(m_createRect[3].contains(event->pos()))
			m_currentGrid = 3;
	}
	QWidget::mouseMoveEvent(event);
	update();
}

void MineField::drawGameUnstart(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen(HintTextColor, HintTextWidth);

	QFont font;
	font.setFamily(HintTextFamily);
	font.setPixelSize(HintTextPixel);

	QTextOption textOption;
	textOption.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

	painter.setPen(pen);
	painter.setFont(font);

	painter.drawText(getHintTextRect(NULL), HintText, textOption);
	painter.fillRect(m_createRect[0], GridForegroundColor);
	painter.fillRect(m_createRect[1], GridForegroundColor);
	painter.fillRect(m_createRect[2], GridForegroundColor);
	painter.fillRect(m_createRect[3], GridForegroundColor);
	
	if(m_currentGrid != -1)
	{
		assert(m_currentGrid >= 0 && m_currentGrid < 4);
		painter.fillRect(m_createRect[m_currentGrid], GridForegroundColorLight);
	}
	
	pen.setColor(GridStrokeColor);
	pen.setWidth(GridStrokeWidth);
	painter.setPen(pen);
	painter.drawRect(m_createRect[0]);
	painter.drawRect(m_createRect[1]);
	painter.drawRect(m_createRect[2]);
	painter.drawRect(m_createRect[3]);

	font.setFamily(GridTextFamily);
	textOption.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

	font.setPixelSize(GridTextSmallPixel);
	pen.setColor(GridTextSmallColor);
	pen.setWidth(GridTextSmallWidth);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(m_createRect[0], GridTextSmall, textOption);
	
	font.setPixelSize(GridTextMediumPixel);
	pen.setColor(GridTextMediumColor);
	pen.setWidth(GridTextMediumWidth);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(m_createRect[1], GridTextMedium, textOption);
	
	font.setPixelSize(GridTextLargePixel);
	pen.setColor(GridTextLargeColor);
	pen.setWidth(GridTextLargeWidth);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(m_createRect[2], GridTextLarge, textOption);
	
	font.setPixelSize(GridTextCustomPixel);
	pen.setColor(GridTextCustomColor);
	pen.setWidth(GridTextCustomWidth);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(m_createRect[3], GridTextCustom, textOption);
}

void MineField::drawGameStarted(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;

	QFont font;
	font.setFamily(MineTextFamily);
	font.setPixelSize(m_mineRect[0].width());
	QTextOption textOption;
	textOption.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	painter.setFont(font);

	for(unsigned long y = 0; y < m_mineLogical.getDimY(); ++y)
	{
		for(unsigned long x = 0; x < m_mineLogical.getDimX(); ++x)
		{
			int outlook = m_mineLogical.getOutlook(x, y);
			assert(outlook >= 0 || outlook == GRID_MINE_CLOSE || outlook == GRID_CLOSE || outlook == GRID_MARKED || outlook == GRID_ERRMARKED);
			QRect curRect = m_mineRect[y * m_mineLogical.getDimX() + x];
			switch(outlook)
			{
			case GRID_MINE_CLOSE:
			case GRID_CLOSE:
			case GRID_MARKED:
			case GRID_ERRMARKED:
				painter.fillRect(curRect, MineForegroundColor);
				if(outlook == GRID_MARKED || outlook == GRID_ERRMARKED)
					painter.drawPixmap(curRect, QPixmap(tr(":/images/flag.svg")));
				break;
				
			default:
				painter.fillRect(curRect, MineBackgroundColor);
				if(outlook > 0)
				{
					pen.setColor(MineTextColor[outlook - 1]);
					pen.setWidth(MineTextWidth);
					painter.setPen(pen);
					painter.drawText(curRect, QString::number(outlook), textOption);
				}
				break;
			}

			pen.setColor(GridStrokeColor);
			pen.setWidth(GridStrokeWidth);
			painter.setPen(pen);
			painter.drawRect(curRect);
		}
	}
}

void MineField::drawGamePause(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(), PauseBackgroundColor);

	QPen pen(PauseTextColor, PauseTextWidth);
	QFont font;
	font.setFamily(PauseTextFamily);
	font.setPixelSize(PauseTextPixel);
	QTextOption textOption;
	textOption.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	painter.setPen(pen);
	painter.setFont(font);

	painter.drawText(rect(), PauseText, textOption);
}

void MineField::drawGameFailed(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;

	QFont font;
	font.setFamily(MineTextFamily);
	font.setPixelSize(m_mineRect[0].width());
	QTextOption textOption;
	textOption.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	painter.setFont(font);

	for(unsigned long y = 0; y < m_mineLogical.getDimY(); ++y)
	{
		for(unsigned long x = 0; x < m_mineLogical.getDimX(); ++x)
		{
			int outlook = m_mineLogical.getOutlook(x, y);
			assert(outlook >= GRID_MINE_CLOSE && outlook < 9);
			QRect curRect = m_mineRect[y * m_mineLogical.getDimX() + x];
			painter.fillRect(curRect, MineForegroundColor);
			
			switch(outlook)
			{
			case GRID_MINE_CLOSE:
				painter.drawPixmap(curRect, QPixmap(tr(":/images/mine.png")));
				break;
			case GRID_MARKED:
				painter.drawPixmap(curRect, QPixmap(tr(":/images/flag.svg")));
				break;
			case GRID_ERRMARKED:
				painter.drawPixmap(curRect, QPixmap(tr(":/images/errflag.svg")));
				break;
			default:
				painter.fillRect(curRect, MineBackgroundColor);
				if(outlook == GRID_MINE_OPEN)
				{
					painter.drawPixmap(curRect, QPixmap(tr(":/images/bang.svg")));
				}
				else if(m_mineLogical.getNumMine(x, y) > 0)
				{
					pen.setColor(MineTextColor[m_mineLogical.getNumMine(x, y) - 1]);
					pen.setWidth(MineTextWidth);
					painter.setPen(pen);
					painter.drawText(curRect, QString::number(m_mineLogical.getNumMine(x, y)), textOption);
				}
				break;
			}

			pen.setColor(GridStrokeColor);
			pen.setWidth(GridStrokeWidth);
			painter.setPen(pen);
			painter.drawRect(curRect);
		}
	}
}

void MineField::mousePressUnstart(QMouseEvent* event)
{
	unsigned long x = (event->pos().x() - m_createRect[0].x()) / m_createRect[0].width();
	unsigned long y = (event->pos().y() - m_createRect[0].y()) / m_createRect[0].height();
	unsigned long index = y * 2 + x;
	bool ok = false;

	switch(index)
	{
	case 0:
		DefaultGridWidth  = GridWidthSmall;
		DefaultGridHeight = GridHeightSmall;
		DefaultMineNum    = MineNumSmall;
		ok = true;
		break;
	case 1:
		DefaultGridWidth  = GridWidthMedium;
		DefaultGridHeight = GridHeightMedium;
		DefaultMineNum    = MineNumMedium;
		ok = true;
		break;
	case 2:
		DefaultGridWidth  = GridWidthLarge;
		DefaultGridHeight = GridHeightLarge;
		DefaultMineNum    = MineNumLarge;
		ok = true;
		break;
	case 3:
	{	
		CustomMineDialog customDialog;
		if(customDialog.exec())
		{
			DefaultGridWidth  = customDialog.getMineWidth();
			DefaultGridHeight = customDialog.getMineHeight();
			DefaultMineNum    = customDialog.getMineNum();
			ok = true;
		}
		break;
	}
	default:
		assert(false);
	}
	if(ok)
		init(DefaultGridWidth, DefaultGridHeight, DefaultMineNum);
}

void MineField::mousePressStarted(QMouseEvent* event)
{
	unsigned long x = (event->pos().x() - m_mineRect[0].x()) / m_mineRect[0].width();
	unsigned long y = (event->pos().y() - m_mineRect[0].y()) / m_mineRect[0].height();
	if(x >= m_mineLogical.getDimX() || y >= m_mineLogical.getDimY())
		return;

	if(!m_running)
	{
		m_running = true;
		emit gameStart();
	}

	if(event->button() == Qt::RightButton)
	{
		m_mineLogical.mark(x, y);
		emit gameMark();
	}
	else if(event->button() == Qt::LeftButton)
	{
		if(!m_mineLogical.open(x, y))
		{
			m_gameState = GameStateFailed;
			emit gameStop();
			update();
			FailedDialog failedDialog;
			failedDialog.exec();
			init(DefaultGridWidth, DefaultGridHeight, DefaultMineNum);
		}
	}
	if(m_mineLogical.getOpened() == m_mineLogical.getDimX() * m_mineLogical.getDimY())
	{
		emit gameStop();
		WinDialog winDialog;
		winDialog.exec();
		init(DefaultGridWidth, DefaultGridHeight, DefaultMineNum);
	}
}

void MineField::rebuildCreateRect(QResizeEvent* event)
{
	QSize winSize(rect().width(), rect().height());
	if(event != NULL)
		winSize = event->size();

	unsigned long realHeight = winSize.height() - MarginTop - HintTextMarginTop - HintTextRectHeight 
					 - HintTextMarginBottom - MarginBottom;
	unsigned long realWidth  = winSize.width() - MarginLeft - MarginRight;

	unsigned long gridSize = qMin(realHeight / 2, realWidth / 2);
	unsigned long totalGridSize = gridSize * 2;
	unsigned long top = (realHeight - totalGridSize) / 2 + MarginTop + HintTextMarginTop 
			  + HintTextRectHeight + HintTextMarginBottom;
	unsigned long left = (realWidth - totalGridSize) / 2 + MarginLeft;

	m_createRect[0] = QRect(left, top, gridSize, gridSize);
	m_createRect[1] = QRect(left + gridSize, top, gridSize, gridSize);
	m_createRect[2] = QRect(left, top + gridSize, gridSize, gridSize);
	m_createRect[3] = QRect(left + gridSize, top + gridSize, gridSize, gridSize);

}

void MineField::rebuildMineRect(QResizeEvent* event)
{
	if(m_mineLogical.getDimX() == 0 || m_mineLogical.getDimY() == 0)
		return;
	QSize winSize(rect().width(), rect().height());
	if(event != NULL)
		winSize = event->size();

	unsigned long realHeight = winSize.height() - MarginTop - MarginBottom;
	unsigned long realWidth  = winSize.width() - MarginLeft - MarginRight;
	unsigned long gridSize = qMin(realHeight / m_mineLogical.getDimY(), realWidth / m_mineLogical.getDimX());
	if(gridSize < MinGridSize)
		gridSize = MinGridSize;

	realHeight = gridSize * m_mineLogical.getDimY();
	realWidth  = gridSize * m_mineLogical.getDimX();
	unsigned long top  = (winSize.height() - realHeight) / 2;
	unsigned long left = (winSize.width() - realWidth) / 2;

	for(unsigned long y = 0; y < m_mineLogical.getDimY(); ++y)
	{
		for(unsigned long x = 0; x < m_mineLogical.getDimX(); ++x)
		{
			m_mineRect[y * m_mineLogical.getDimX() + x] = 
				QRect(left + x * gridSize, top + y * gridSize, gridSize, gridSize);
		}
	}
}

QRect MineField::getHintTextRect(QResizeEvent* event) const
{
	return QRect(m_createRect[0].x(), MarginTop, m_createRect[0].width() * 2, HintTextRectHeight);
}
