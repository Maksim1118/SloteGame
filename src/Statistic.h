#pragma once

class Statistic
{
public:
	void setBet(int bet);
	void setBalance(int balance);
	void addWin(int win);

	int getBet() const;
	int getWin() const;
	int getBalance() const;

private:
	struct Stats
	{
		int Bet;
		int Win;
		int Balance;
		Stats() : Bet(0), Win(0), Balance(0) {}
	};
	Stats m_Statistic;
};