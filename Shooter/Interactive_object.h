#pragma once
#include "link.h"
struct object
{
	int type;
	int ID;
};
enum object_states{ON,OFF};
class Interactive_object
{
protected:
	std::string bitmap;
private:
	std::vector<int> IDs_of_nothing;
public:
	int button_to_interact_with;
	bool active;
	int connections;
	std::vector<object> affected_object;
	int PosX;
	int PosY;
	bool exists;
	int of_object;
	int of_ID;
	void remove_connection(int which);
	void send_state();
	void object_draw();
	void set_up(int x,int y, int ID,int object,int button=0);
	void add_affected_objects(int type,int ID);
	void remove();
	Interactive_object(void);
	~Interactive_object(void);
};

