/************************************************************
> File Name: minelogical.cpp
> Author: 庾吉飞
> Mail: yujihui.xidian@gmail.com
> Created Time: 2013年09月30日 星期一 00时29分51秒
************************************************************/

#include "minelogical.h"
#include <cassert>
#include <cstdlib>
#include <ctime>

MineLogical::MineLogical()
{
}

MineLogical::~MineLogical()
{
}

void MineLogical::init(unsigned long width, unsigned long height, unsigned long mineNum)
{
	assert(width * height > mineNum);
	m_width  = width;
	m_height = height;
	m_nMine  = mineNum;
	m_opened = 0;
	m_nMarked = 0;

	makeMineMap();
	makeGridState();
	makeNumMine();
}

bool MineLogical::open(unsigned long x, unsigned long y)
{
	if(x >= m_width || y >= m_height)
		return true;
	if(getState(x, y) != GridStateClose)
		return true;

	setState(x, y, GridStateOpen);
	if(getMine(x, y))
		return false;

	++m_opened;
	if(getNumMine(x, y) == 0)
	{
		open(x + 1, y);
		open(x - 1, y);
		open(x, y + 1);
		open(x, y - 1);
		open(x - 1, y - 1);
		open(x - 1, y + 1);
		open(x + 1, y - 1);
		open(x + 1, y + 1);
	}
	return true;
}

bool MineLogical::mark(unsigned long x, unsigned long y)
{
	if(x >= m_width || y >= m_height)
		return false;

	GridState state = getState(x, y);
	if(state == GridStateMarked)
	{
		setState(x, y, GridStateClose);
		--m_nMarked;
		--m_opened;
	}
	else if(state == GridStateClose)
	{
		if(m_nMarked >= m_nMine)
			return false;
		setState(x, y, GridStateMarked);
		++m_nMarked;
		++m_opened;
		return true;
	}
	return false;
}

unsigned long MineLogical::getDimX() const
{
	return m_width;
}

unsigned long MineLogical::getDimY() const
{
	return m_height;
}

unsigned long MineLogical::getMineNum() const
{
	return m_nMine;
}

unsigned long MineLogical::getMarkedNum() const
{
	return m_nMarked;
}

unsigned long MineLogical::getOpened() const
{
	return m_opened;
}

int MineLogical::getOutlook(unsigned long x, unsigned long y) const
{
	GridState state = getState(x, y);
	if(state == GridStateClose)
	{
		if(getMine(x, y))
			return GRID_MINE_CLOSE;
		return GRID_CLOSE;
	}
	else if(state == GridStateMarked)
	{
		if(getMine(x, y))
			return GRID_MARKED;
		return GRID_ERRMARKED;
	}
	else
	{
		if(getMine(x, y))
			return GRID_MINE_OPEN;
		return getNumMine(x, y);
	}
}

void MineLogical::setMine(unsigned long x, unsigned long y)
{
	assert(x < m_width && y < m_height);
	m_mineMap[y * m_width + x] = true;
}

void MineLogical::setState(unsigned long x, unsigned long y, GridState state)
{
	assert(x < m_width && y < m_height);
	m_gridState[y * m_width + x] = state;
}

void MineLogical::setNumMine(unsigned long x, unsigned long y, int nMine)
{
	assert(x < m_width && y < m_height);
	assert(nMine >= -1 && nMine <= 8);
	m_numMine[y * m_width + x] = nMine;
}

bool MineLogical::getMine(unsigned long x, unsigned long y) const
{
	if(x < m_width && y < m_height)
		return m_mineMap[y * m_width + x];
	return false;
}

MineLogical::GridState MineLogical::getState(unsigned long x, unsigned long y) const
{
	assert(x < m_width && y < m_height);
	return m_gridState[y * m_width + x];
}

int MineLogical::getNumMine(unsigned long x, unsigned long y) const
{
	assert(x < m_width && y < m_height);
	return m_numMine[y * m_width + x];
}

void MineLogical::makeMineMap()
{
	assert(m_width * m_height > m_nMine);

	m_mineMap.clear();
	if(m_mineMap.size() < m_width * m_height)
		m_mineMap.resize(m_width * m_height);
	
	srand(time(0));
	for(unsigned long i = 0; i < m_nMine;)
	{
		unsigned long x = rand() % m_width;
		unsigned long y = rand() % m_height;
		if(!getMine(x, y))
		{
			setMine(x, y);
			++i;
		}
	}
}

void MineLogical::makeGridState()
{
	m_gridState.clear();
	if(m_gridState.size() < m_width * m_height)
		m_gridState.resize(m_width * m_height);

	for(unsigned long i = 0; i < m_width * m_height; ++i)
	{
		m_gridState[i] = GridStateClose;
	}
}

void MineLogical::makeNumMine()
{
	m_numMine.clear();
	if(m_numMine.size() < m_width * m_height)
		m_numMine.resize(m_width * m_height);

	for(unsigned long y = 0; y < m_height; ++y)
	{
		for(unsigned long x = 0; x < m_width; ++x)
		{
			if(getMine(x, y))
				setNumMine(x, y, -1);
			int n = 0;
			n += static_cast<int>(getMine(x - 1, y - 1));
			n += static_cast<int>(getMine(x - 1, y));
			n += static_cast<int>(getMine(x - 1, y + 1));
			n += static_cast<int>(getMine(x, y - 1));
			n += static_cast<int>(getMine(x, y + 1));
			n += static_cast<int>(getMine(x + 1, y - 1));
			n += static_cast<int>(getMine(x + 1, y));
			n += static_cast<int>(getMine(x + 1, y + 1));
			setNumMine(x, y, n);
		}
	}
}

