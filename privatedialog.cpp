/************************************************************
> File Name: privatedialog.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月01日 星期二 19时39分58秒
************************************************************/

#include "privatedialog.h"
#include "config.h"
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>

FailedDialog::FailedDialog(QWidget* parent): QDialog(parent)
{
	m_image = new QLabel;
	m_info  = new QLabel(FailedText);
	m_image->setPixmap(QPixmap(tr(":/images/failed.png")));
	m_ok    = new QPushButton(tr("确定"));
	connect(m_ok, SIGNAL(clicked()), this, SLOT(accept()));

	QHBoxLayout* bottom = new QHBoxLayout;
	bottom->addWidget(m_ok);
	setWindowTitle(tr("触雷了"));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_image);
	layout->addWidget(m_info);
	layout->addLayout(bottom);
	setLayout(layout);
	adjustSize();
}

WinDialog::WinDialog(QWidget* parent): QDialog(parent)
{
	m_image = new QLabel;
	m_info  = new QLabel(WinText);
	m_image->setPixmap(QPixmap(tr(":/images/win.png")));
	m_ok    = new QPushButton(tr("确定"));
	connect(m_ok, SIGNAL(clicked()), this, SLOT(accept()));

	QHBoxLayout* bottom = new QHBoxLayout;
	bottom->addWidget(m_ok);
	setWindowTitle(tr("赢了"));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_image);
	layout->addWidget(m_info);
	layout->addLayout(bottom);
	setLayout(layout);
	adjustSize();
}

CustomMineDialog::CustomMineDialog(QWidget* parent): QDialog(parent)
{
	m_hintLabel   = new QLabel(CustomMineHintText);
	m_widthLabel  = new QLabel(CustomMineWidthText);
	m_heightLabel = new QLabel(CustomMineHeightText);
	m_mineLabel   = new QLabel(CustomMineText);
	m_widthBox    = new QSpinBox;
	m_heightBox   = new QSpinBox;
	m_mineBox     = new QSpinBox;
	m_ok          = new QPushButton(tr("开始玩"));
	m_cancel      = new QPushButton(tr("返回"));

	m_widthLabel->setBuddy(m_widthBox);
	m_heightLabel->setBuddy(m_heightBox);
	m_mineLabel->setBuddy(m_mineBox);
	m_widthBox->setRange(GridMinWidth, GridMaxWidth);
	m_widthBox->setValue(DefaultGridWidth);
	m_heightBox->setRange(GridMinHeight, GridMaxHeight);
	m_heightBox->setValue(DefaultGridWidth);
	m_mineBox->setRange(MineNumMin, MineNumMax);
	m_mineBox->setValue(DefaultMineNum);

	connect(m_ok, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_cancel, SIGNAL(clicked()), this, SLOT(reject()));
	connect(m_widthBox, SIGNAL(valueChanged(int)), this, SLOT(onSetWidth(int)));
	connect(m_heightBox, SIGNAL(valueChanged(int)), this, SLOT(onSetHeight(int)));
	connect(m_mineBox, SIGNAL(valueChanged(int)), this, SLOT(onSetMineNum(int)));

	QHBoxLayout* hintLayout = new QHBoxLayout;
	QHBoxLayout* widthLayout = new QHBoxLayout;
	QHBoxLayout* heightLayout = new QHBoxLayout;
	QHBoxLayout* mineLayout = new QHBoxLayout;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QVBoxLayout* mainLayout = new QVBoxLayout;
	
	hintLayout->addWidget(m_hintLabel);
	hintLayout->addStretch();
	widthLayout->addWidget(m_widthLabel);
	widthLayout->addWidget(m_widthBox);
	heightLayout->addWidget(m_heightLabel);
	heightLayout->addWidget(m_heightBox);
	mineLayout->addWidget(m_mineLabel);
	mineLayout->addWidget(m_mineBox);
	buttonLayout->addWidget(m_cancel);
	buttonLayout->addWidget(m_ok);
	mainLayout->addLayout(hintLayout);
	mainLayout->addLayout(widthLayout);
	mainLayout->addLayout(heightLayout);
	mainLayout->addLayout(mineLayout);
	mainLayout->addLayout(buttonLayout);

	setWindowTitle(tr("自定义雷区"));
	setLayout(mainLayout);
	adjustSize();
}

int CustomMineDialog::getMineWidth() const
{
	return m_widthBox->value();
}

int CustomMineDialog::getMineHeight() const
{
	return m_heightBox->value();
}

int CustomMineDialog::getMineNum() const
{
	return m_mineBox->value();
}

void CustomMineDialog::onSetWidth(int w)
{
	int h = m_heightBox->value();
	int m = m_mineBox->value();
	if(m > w * h * MineFillRate)
		m_mineBox->setValue(w * h * MineFillRate);
}

void CustomMineDialog::onSetHeight(int h)
{
	int w = m_widthBox->value();
	int m = m_mineBox->value();
	if(m > w * h * MineFillRate)
		m_mineBox->setValue(w * h * MineFillRate);
}

void CustomMineDialog::onSetMineNum(int n)
{
	int w = m_widthBox->value();
	int h = m_heightBox->value();
	if(n > w * h * MineFillRate)
		m_mineBox->setValue((int)(w * h * MineFillRate));
	else
		m_mineBox->setValue(n);
}
