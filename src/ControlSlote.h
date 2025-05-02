#pragma once

struct ControlSlote
{
	bool isRunning;
	bool startSlote;
	bool stopSlote;
	ControlSlote() : isRunning(false), startSlote(false), stopSlote(false) {};
};
