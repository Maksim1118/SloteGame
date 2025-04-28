#pragma once

#include <vector>

class Combination
{
public:
	Combination(std::vector<int>& combination, int winAmount);
	std::vector<int> getCombination() const;
	int getWinAmount() const;
protected:
	std::vector<int> m_Combination;
	int m_WinAmount;
};
