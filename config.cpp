/************************************************************
> File Name: config.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月02日 星期三 21时37分15秒
************************************************************/

#include "config.h"
#include <QObject>
#include <cstdio>

unsigned long DefaultGridWidth = 8;
unsigned long DefaultGridHeight = 8;
unsigned long DefaultMineNum = 10;

QString HintTextFamily;
QString GridTextFamily;
QString MineTextFamily;
QString PauseTextFamily;
QString HintText;
QString GridTextSmall;
QString GridTextMedium;
QString GridTextLarge;
QString GridTextCustom;
QString PauseText;
QString FailedText;
QString WinText;
QString CustomMineHintText;
QString CustomMineWidthText;
QString CustomMineHeightText;
QString CustomMineText;

void loadString()
{
	HintTextFamily = QObject::tr("宋体");
	GridTextFamily = QObject::tr("宋体");
	MineTextFamily = QObject::tr("Times New Roman");
	PauseTextFamily = QObject::tr("宋体");
	HintText = QObject::tr("设置雷区大小：");
	GridTextSmall = QObject::tr("8 x 8\n10个雷");
	GridTextMedium = QObject::tr("16 x 16\n40个雷");
	GridTextLarge = QObject::tr("30 x 16\n99个雷");
	GridTextCustom = QObject::tr("?\n自定义");
	PauseText = QObject::tr("暂停");
	FailedText = QObject::tr("Bang! 触雷了！");
	WinText = QObject::tr("啊哈，恭喜通过！");
	CustomMineHintText = QObject::tr("自定义雷区大小：");
	CustomMineWidthText = QObject::tr("水平大小：");
	CustomMineHeightText = QObject::tr("垂直大小：");
	CustomMineText = QObject::tr("地雷数量：");
}

void readConfigure(const char* name)
{
	loadString();
	FILE* fp = fopen(name, "r");
	if(fp == NULL)
		return;
	fscanf(fp, "%lu %lu %lu", &DefaultGridWidth, &DefaultGridHeight, &DefaultMineNum);
	fclose(fp);
}

void writeConfigure(const char* name)
{
	FILE* fp = fopen(name, "w");
	if(fp == NULL)
		return;
	fprintf(fp, "%lu %lu %lu  ", DefaultGridWidth, DefaultGridHeight, DefaultMineNum);
	fclose(fp);
}
