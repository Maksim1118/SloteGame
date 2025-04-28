#include "Statistic.h"

void Statistic::setBet(int bet)
{
	m_Statistic.Bet = bet;
}

void Statistic::setBalance(int balance)
{
	m_Statistic.Balance = balance;
}

void Statistic::addWin(int win)
{
	m_Statistic.Win += win;
}

int Statistic::getBet() const
{
	return m_Statistic.Bet;
}

int Statistic::getWin() const
{
	return m_Statistic.Win;
}

int Statistic::getBalance() const
{
	return m_Statistic.Balance;
}