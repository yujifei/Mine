/************************************************************
> File Name: config.h
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月02日 星期三 19时37分00秒
************************************************************/
#ifndef __FILL_CONFIG__
#define __FILL_CONFIG__

#include <QSize>
#include <QRect>
#include <QColor>
#include <QObject>

const QSize DefaultSize(800, 600);
const QSize MinimumSize(200, 200);

extern unsigned long DefaultGridWidth;
extern unsigned long DefaultGridHeight;
extern unsigned long DefaultMineNum;

const unsigned long HintTextWidth = 1;
const unsigned long GridStrokeWidth = 1;
const unsigned long GridTextSmallPixel = 20;
const unsigned long GridTextMediumPixel = 20;
const unsigned long GridTextLargePixel = 20;
const unsigned long GridTextCustomPixel = 20;
const unsigned long PauseTextPixel = 80;
const unsigned long GridTextSmallWidth = 3;
const unsigned long GridTextMediumWidth = 3;
const unsigned long GridTextLargeWidth = 3;
const unsigned long GridTextCustomWidth = 3;
const unsigned long MineTextWidth = 2;
const unsigned long PauseTextWidth = 10;
const unsigned long GridWidthSmall = 8;
const unsigned long GridHeightSmall = 8;
const unsigned long MineNumSmall = 10;
const unsigned long GridWidthMedium = 16;
const unsigned long GridHeightMedium = 16;
const unsigned long MineNumMedium = 40;
const unsigned long GridWidthLarge = 30;
const unsigned long GridHeightLarge = 16;
const unsigned long MineNumLarge = 99;
const unsigned long MarginTop = 2;
const unsigned long MarginBottom = 2;
const unsigned long MarginLeft = 2;
const unsigned long MarginRight = 2;
const unsigned long HintTextMarginTop = 0;
const unsigned long HintTextMarginBottom = 2;
const unsigned long HintTextRectHeight = 20;
const unsigned long HintTextPixel = 15;
const unsigned long MinGridSize = 10;
const unsigned long GridMinWidth = 4;
const unsigned long GridMaxWidth = 50;
const unsigned long GridMinHeight = 4;
const unsigned long GridMaxHeight = 50;
const unsigned long MineNumMin = 6;
const unsigned long MineNumMax = 1000;
const float MineFillRate = 0.4;

const QColor HintTextColor(0, 0, 0);
const QColor GridForegroundColor(245, 245, 245);
const QColor GridForegroundColorLight(250, 250, 250);
const QColor MineForegroundColor(235, 235, 235);
const QColor MineBackgroundColor(128, 128, 128);
const QColor GridStrokeColor(136, 136, 136);
const QColor GridTextSmallColor(255, 0, 0);
const QColor GridTextMediumColor(0, 255, 0);
const QColor GridTextLargeColor(0, 0, 255);
const QColor GridTextCustomColor(255, 0, 255);
const QColor MineTextColor[] =
{
	QColor(255, 0, 0),    QColor(0, 255, 0),     QColor(0, 0, 255),        QColor(255, 255, 0),
	QColor(255, 0, 255), QColor(0, 255, 255), QColor(255, 255, 255), QColor(0, 0, 0)
};
const QColor PauseBackgroundColor(112, 112, 112);
const QColor PauseTextColor(240, 240, 240);

extern QString HintTextFamily;
extern QString GridTextFamily;
extern QString MineTextFamily;
extern QString PauseTextFamily;
extern QString HintText;
extern QString GridTextSmall;
extern QString GridTextMedium;
extern QString GridTextLarge;
extern QString GridTextCustom;
extern QString PauseText;
extern QString FailedText;
extern QString WinText;
extern QString CustomMineHintText;
extern QString CustomMineWidthText;
extern QString CustomMineHeightText;
extern QString CustomMineText;

void readConfigure(const char* name);
void writeConfigure(const char* name);
#endif
