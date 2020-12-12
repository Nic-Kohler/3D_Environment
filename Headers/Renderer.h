class SDL_Window;
class SDL_Renderer;
class Rotation;
class Camera;
class Object;
class Plane;
class Vector;
class Orthogonal_Plane;

class Renderer
{
private:
	SDL_Window		*Window;
	SDL_Renderer	*Window_Renderer;
	
	int Screen_Origin_X_Offset;
	int Screen_Origin_Y_Offset;
	
	Orthogonal_Plane **Orthogonal_Plane_Array;
	int				   Orthogonal_Plane_Count;
	
public:
	Renderer();
	
	int Get_Screen_Origin_X_Offset(){ return Screen_Origin_X_Offset; }
	int Get_Screen_Origin_Y_Offset(){ return Screen_Origin_Y_Offset; }
	
	Orthogonal_Plane **Get_Orthogonal_Plane_Array()		{ return Orthogonal_Plane_Array; };
	int				   Get_Orthogonal_Plane_Count()		{ return Orthogonal_Plane_Count; };
	Orthogonal_Plane  *Get_Orthogonal_Plane(int index)	{ return Orthogonal_Plane_Array[index]; }
	void			   Add_Orthogonal_Plane(Orthogonal_Plane *orthogonal_plane);
	
	void Initialize_SDL();
	void Draw_Object(Object *object, int int_color);
	void Draw_Orthogonal_Plane(Orthogonal_Plane *orthogonal_plane, int int_color);
	void Draw_Vector(Vector *vector, int int_color);
	void Update();
	void Clear();
	void Delay(int time);
	
	~Renderer();
};