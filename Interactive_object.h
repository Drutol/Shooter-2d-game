#pragma once
#include "link.h"
struct object
{
	int type;
	int ID;
};
enum states{ON,OFF};
class Interactive_object
{
protected:
	std::string bitmap;
private:
	int connections;
	bool active;
	object *affected_object;
	void create_array_of_affected_objects(int how_many);
public:
	int PosX;
	int PosY;
	bool exists;
	void send_state();
	void object_draw();
	void set_up(int how_many_connections,int x,int y,int object_type);
	void add_affected_objects(int type,int ID);
	Interactive_object(void);
	~Interactive_object(void);
};

