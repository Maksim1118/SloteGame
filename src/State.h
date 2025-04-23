#pragma once

class State
{
public:
	virtual ~State() = default;
	virtual void update(float diff) = 0;
	virtual bool exit() = 0;
};