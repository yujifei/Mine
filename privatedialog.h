/************************************************************
> File Name: privatedialog.h
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年10月01日 星期二 19时18分02秒
************************************************************/

#ifndef __FILE_PRIVATE_DIALOG__
#define __FILE_PRIVATE_DIALOG__

#include <QDialog>

class QWidget;
class QLabel;
class QSpinBox;
class QPushButton;

class FailedDialog: public QDialog
{
	Q_OBJECT
public:
	FailedDialog(QWidget* parent = NULL);

private:
	QLabel* m_image;
	QLabel* m_info;
	QPushButton* m_ok;
};

class WinDialog: public QDialog
{
	Q_OBJECT
public:
	WinDialog(QWidget* parent = NULL);

private:
	QLabel* m_image;
	QLabel* m_info;
	QPushButton* m_ok;
};

class CustomMineDialog: public QDialog
{
	Q_OBJECT
public:
	CustomMineDialog(QWidget* parent = NULL);
	int getMineWidth() const;
	int getMineHeight() const;
	int getMineNum() const;

private slots:
	void onSetWidth(int w);
	void onSetHeight(int h);
	void onSetMineNum(int n);

private:
	QLabel* m_hintLabel;
	QLabel* m_widthLabel;
	QLabel* m_heightLabel;
	QLabel* m_mineLabel;
	QSpinBox* m_widthBox;
	QSpinBox* m_heightBox;
	QSpinBox* m_mineBox;
	QPushButton* m_ok;
	QPushButton* m_cancel;
};

#endif
