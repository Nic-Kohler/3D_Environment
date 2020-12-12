class Loop;
class Object;
class Vector;
class Rotation_Vector;
class Renderer;

class Camera
{
private:
	Renderer		*Render;
	int				 Screen_Width;
	int				 Screen_Height;
	int				 View_Frustum_Depth;
	float			 Eye_to_Screen_Distance;
	Object			*View_Frustum;
	Rotation_Vector	*Forward_Vector;
	Rotation_Vector	*Left_Vector;
	Vector			*Position_Vector;
	
	float Forward_Velocity;
	float Sidestep_Velocity;
	
public:
	Camera();
	
	Renderer   *Get_Renderer()				{ return Render; }
	int			Get_Screen_Width()			{ return Screen_Width; };
	int			Get_Screen_Height()			{ return Screen_Height; };
	int			Get_View_Frustum_Depth()	{ return View_Frustum_Depth; };
	float		Get_Eye_to_Screen_Distance(){ return Eye_to_Screen_Distance; }
	float		Get_Forward_Velocity()		{ return Forward_Velocity; };
	float		Get_Sidestep_Velocity()		{ return Sidestep_Velocity; }
	
	Object			*Get_View_Frustum()		{ return View_Frustum; };
	Rotation_Vector	*Get_Forward_Vector()	{ return Forward_Vector; };
	Rotation_Vector	*Get_Left_Vector()		{ return Left_Vector; };
	Vector			*Get_Position_Vector()	{ return Position_Vector; };
	
	void Translate(Vector translation_vector);
	Object Find_Visible_Planes(Object **object_array, int object_count, bool is_transparent);
	void Clear_Renderer();
	
	~Camera();
};