#include "Combination.h"

Combination::Combination(std::vector<int>& combination, int winAmount)
	:m_Combination(combination), m_WinAmount(winAmount)
{
}

std::vector<int> Combination::getCombination() const
{
	return m_Combination;
}

int Combination::getWinAmount() const
{
	return m_WinAmount;
}
