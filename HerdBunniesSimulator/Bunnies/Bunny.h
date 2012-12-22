#pragma once

#include "IBunny.h"

class Bunny : public IBunny
{
public:
	Bunny(void);
	~Bunny(void);

	float GetHealth() const;

protected:
	float m_health;
};

