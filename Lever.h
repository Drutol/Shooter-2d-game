#pragma once
#include "Interactive_object.h"
class Lever : public Interactive_object
{
private:
	int state;
	std::string object_name;
public:
	void apply_new_state();
	Lever(void);
	~Lever(void);
};

