/************************************************************
> File Name: minelogical.h
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年09月30日 星期一 00时02分18秒
************************************************************/

#ifndef __FILE_MINE_LOGICAL_H__
#define __FILE_MINE_LOGICAL_H__

#include <vector>

#define GRID_MINE_CLOSE -5
#define GRID_MINE_OPEN  -4
#define GRID_CLOSE      -3
#define GRID_ERRMARKED  -2
#define GRID_MARKED     -1

class MineLogical
{
public:
	enum GridState{GridStateClose, GridStateOpen, GridStateMarked};

public:
	MineLogical();
	~MineLogical();
	void init(unsigned long width, unsigned long height, unsigned long mineNum);
	bool open(unsigned long x, unsigned long y);
	bool mark(unsigned long x, unsigned long y);
	unsigned long getDimX() const;
	unsigned long getDimY() const;
	unsigned long getMineNum() const;
	int getNumMine(unsigned long x, unsigned long y) const;
	unsigned long getMarkedNum() const;
	unsigned long getOpened() const;
	int getOutlook(unsigned long x, unsigned long y) const; //绘制代码用以获取某个栅格的外观：或闭或已标记或周边地雷数等

private:
	MineLogical(const MineLogical&);
	MineLogical& operator=(const MineLogical&);
	void setMine(unsigned long x, unsigned long y);
	void setState(unsigned long x, unsigned long y, GridState state);
	void setNumMine(unsigned long x, unsigned long y, int nMine);
	bool getMine(unsigned long x, unsigned long y) const;
	GridState getState(unsigned long x, unsigned long y) const;
	void makeMineMap();
	void makeGridState();
	void makeNumMine();

private:
	unsigned long m_width;
	unsigned long m_height;
	unsigned long m_nMine;
	unsigned long m_nMarked;
	unsigned long m_opened;
	std::vector<bool> m_mineMap;
	std::vector<GridState> m_gridState;
	std::vector<unsigned int> m_numMine;
};

#endif
