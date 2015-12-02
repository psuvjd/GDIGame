#include "stdafx.h"
#include "MyAnimal.h"

CMyAnimal::CMyAnimal()
{
	m_iX = m_iDesX = CreateX();
	m_iY = m_iDesY = CreateY();
	m_iType = rand() % TYPE_MAX;
	m_dSpeed = rand() % 5 + 2;
	m_iTimer = 0;
	m_iStop = rand() % 4 + 1;
}

CMyAnimal::CMyAnimal(int nX, int nY): CMyCreature()
{
	m_iX = m_iDesX = nX;
	m_iY = m_iDesY = nY;
	m_iType = rand() % TYPE_MAX;
	m_dSpeed = rand() % 5 + 2;
	m_iTimer = 0;
	m_iStop = rand() % 4 + 1;
}

int CMyAnimal::GetType(void) const
{
	return m_iType;
}

int CMyAnimal::CreateX(void) const
{
	int tmpX = rand();
	int toX = max((min(640 - 80, tmpX % 641) - 35), 0);
	return toX;
}

int CMyAnimal::CreateY(void) const
{
	int tmpY = rand();
	int toY = max((min(480 - 80, tmpY % 480) - 35), 0);
	return toY;
}

void CMyAnimal::AI(int nFrequency)
{
	if (m_iState == STAND) {
		m_iTimer++;
		if (m_iTimer >= m_iStop * 1000 / nFrequency) {
			m_iTimer = 0;
			SetDes(CreateX(), CreateY());
		}
	}
	Move(0);
}


CMyAnimal::~CMyAnimal()
{
}
