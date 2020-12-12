class Object;

class Loop
{
private:
	Object		**Object_Array;
	int			  Object_Count;
	
	bool Run_Loop;
	
	unsigned long  Current_Time;
	unsigned long  Previous_Time;
	unsigned short Loop_Interval;
	unsigned short Frame_Rate_Interval;
	unsigned long  Previous_Frame_Rate_Time;
	unsigned short Frame_Rate;
	
	const unsigned char *Keyboard_State_Array;
	
public:
	Loop();
	
	Object			**Get_Object_Array()	{ return Object_Array; };
	int				  Get_Object_Count()	{ return Object_Count; };
	unsigned short	  Get_Loop_Interval()	{ return Loop_Interval; };
	
	void Run();
	void Draw();
	void Update_Loop_Interval();
	void Get_Frame_Rate();
	void Update_Events();
	void Handle_Events();
	
	void Add_Object(Object *object);
	
	~Loop();
};