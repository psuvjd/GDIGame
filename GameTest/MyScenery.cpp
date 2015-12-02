#include "stdafx.h"
#include "MyScenery.h"


CMyScenery::CMyScenery()
{
}

CMyScenery::CMyScenery(int nX, int nY, int nID)
{
	m_iX = nX;
	m_iY = nY;
	m_iID = nID % ScePicAmount;
}

int CMyScenery::GetX(void) const
{
	return m_iX;
}

int CMyScenery::GetY(void) const
{
	return m_iY;
}

int CMyScenery::GetID(void) const
{
	return m_iID;
}

void CMyScenery::SetX(int nX)
{
	m_iX = nX;
}

void CMyScenery::SetY(int nY)
{
	m_iY = nY;
}

void CMyScenery::SetID(int nID)
{
	m_iID = nID % ScePicAmount;
}

bool CMyScenery::operator<(const CMyScenery & rhs) const
{
	return m_iY < rhs.m_iY;
}

CMyScenery::~CMyScenery()
{
}
