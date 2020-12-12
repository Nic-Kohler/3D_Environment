class Vector;
class Rotation_Vector;
class Plane;

class Object
{
private:
	Vector			 *Average_Vector;
	Rotation_Vector	**Rotation_Vector_Array;
	Plane			**Plane_Array;
	int				  Rotation_Vector_Count;
	int				  Plane_Count;
	
public:
	Object();
	Object(Object *object);
	
	Vector			 *Get_Average_Vector()			{ return Average_Vector; };
	Rotation_Vector	**Get_Rotation_Vector_Array()	{ return Rotation_Vector_Array; };
	Plane			**Get_Plane_Array()				{ return Plane_Array; };
	int				  Get_Rotation_Vector_Count()	{ return Rotation_Vector_Count; };
	int				  Get_Plane_Count()				{ return Plane_Count; };
	
	void Add_Rotation_Vector(Rotation_Vector *rotation_vector);
	void Add_Plane(Plane *plane);
	void Set_Average_Vector();
	void Confrim_Plane_Normals();
	void Reverse_Plane_Normals();
	void Create_Cube(int radius, Vector position_vector);
	float Create_View_Frustum(int screen_width, int screen_height, float y_frustum_flare_degree, float view_field_depth);
	void Translate(Vector translation_vector);
	void Scale(float scalar);
	bool Vector_Is_Contained(Vector vector_ptr);
	
	~Object();
};