#pragma once
#include "Dynamic_Object.h"
#include "Artificial_Inteligence.h"
class NPC :public Dynamic_Object,public Artificial_Inteligence
{
public:
	NPC(void);
	~NPC(void);
};

