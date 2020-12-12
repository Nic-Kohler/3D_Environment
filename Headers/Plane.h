class Vector;
class Rotation_Vector;
class Orthogonal_Vector;
class Orthogonal_Plane;

class Plane
{
private:
	Rotation_Vector	**Rotation_Vector_Pointer_Array;
	Rotation_Vector	 *Normal_Rotation_Vector;
	int				  Rotation_Vector_Pointer_Count;
	
public:
	Plane();
	Plane(Plane *plane);
	
	Rotation_Vector	**Get_Rotation_Vector_Pointer_Array()	{ return Rotation_Vector_Pointer_Array; };
	int				  Get_Rotation_Vector_Pointer_Count()	{ return Rotation_Vector_Pointer_Count; };
	Rotation_Vector	 *Get_Normal_Rotation_Vector()			{ return Normal_Rotation_Vector; };
	Vector			  Get_Normal_Vector();
	
	void	Set_Normal_Rotation_Vector(Rotation_Vector *rotation_vector);
	void	Set_Normal_Rotation_Vector(Rotation_Vector rotation_vector);
	int		Get_Vector_Index(Vector *vector);
	void	Add_Rotation_Vector_Pointer(Rotation_Vector *rotation_vector);
	Vector	Get_Average_Vector();
	void	Print();
	
	Orthogonal_Plane *Get_Orthogonal_Plane();
	
	~Plane();
};

class Orthogonal_Plane
{
private:
	Orthogonal_Vector	**Orthogonal_Vector_Array;
	int					  Orthogonal_Vector_Count;
	
public:
	Orthogonal_Plane();
	
	Orthogonal_Vector	**Get_Orthogonal_Vector_Array()	{ return Orthogonal_Vector_Array; };
	int					  Get_Orthogonal_Vector_Count()	{ return Orthogonal_Vector_Count; };
	
	void Add_Orthogonal_Vector(Orthogonal_Vector *orthogonal_vector);
	
	~Orthogonal_Plane();
};