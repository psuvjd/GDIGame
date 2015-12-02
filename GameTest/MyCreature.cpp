#include "StdAfx.h"
#include "MyCreature.h"

CMyCreature::CMyCreature(void)
{
	m_iX = m_iDesX = 0;
	m_iY = m_iDesY = 0;
	m_iState = STAND;
	m_iFaceTo = SOUTH;
	m_dSpeed = 10;
}

CMyCreature::~CMyCreature(void)
{
}

int CMyCreature::GetX(void) const {
	return m_iX;
}

int CMyCreature::GetY(void) const {
	return m_iY;
}

int CMyCreature::GetDesX(void) const {
	return m_iDesX;
}

int CMyCreature::GetDesY(void) const {
	return m_iDesY;
}

void CMyCreature::SetDes(int iX, int iY) {
	m_iDesX = iX;
	m_iDesY = iY;
	double s1 = min(fabs(m_iDesX - m_iX), fabs(m_iDesY - m_iY)) * sqrt(2);
	double s2 = max(fabs(m_iDesX - m_iX), fabs(m_iDesY - m_iY)) - min(fabs(m_iDesX - m_iX), fabs(m_iDesY - m_iY));
	// m_dSpeed = (s1 + s2) / 40;
}

void CMyCreature::Move(int idx) {
	m_iState = WALK;
	if (fabs(m_iX - m_iDesX) > c_dEps && fabs(m_iY - m_iDesY) > c_dEps) {

		int dirX = (m_iDesX - m_iX) < 0 ? -1 : 1;
		double tmp = m_dSpeed * dirX + m_iX;
		if ((tmp - m_iDesX) * (m_iDesX - m_iX) > 0)  tmp = m_iDesX;
		m_iX = tmp;

		int dirY = (m_iDesY - m_iY) < 0 ? -1 : 1;
		tmp = m_dSpeed * dirY + m_iY;
		if ((tmp - m_iDesY) * (m_iDesY - m_iY) > 0)  tmp = m_iDesY;
		m_iY = tmp;

		if (dirX > 0) {
			if (dirY > 0) m_iFaceTo = SOUTHEAST;
			else m_iFaceTo = NORTHEAST;
		}
		else {
			if (dirY > 0) m_iFaceTo = SOUTHWEST;
			else m_iFaceTo = NORTHWEST;
		}
	}
	else if (fabs(m_iX - m_iDesX) > c_dEps) {

		int dirX = (m_iDesX - m_iX) < 0 ? -1 : 1;
		double tmp = m_dSpeed * dirX + m_iX;
		if ((tmp - m_iDesX) * (m_iDesX - m_iX) > 0)  tmp = m_iDesX;
		m_iX = tmp;

		if (dirX > 0) m_iFaceTo = EAST;
		else m_iFaceTo = WEST;
	}
	else if (fabs(m_iY - m_iDesY) > c_dEps) {

		int dirY = (m_iDesY - m_iY) < 0 ? -1 : 1;
		double tmp = m_dSpeed * dirY + m_iY;
		if ((tmp - m_iDesY) * (m_iDesY - m_iY) > 0)  tmp = m_iDesY;
		m_iY = tmp;

		if (dirY > 0) m_iFaceTo = SOUTH;
		else m_iFaceTo = NORTH;
	}
	else m_iState = STAND;
}

int CMyCreature::GetFace(void) const
{
	return m_iFaceTo;
}

int CMyCreature::GetState(void) const
{
	return m_iState;
}
