class Vector;
class Rotation_Vector;
class Renderer;

class Rotation
{
private:
	Vector	  *Up_Unit_Vector;
	Vector	  *Down_Unit_Vector;
	Vector	***Rotation_Unit_Vector_Map;
	
	int Array_X_Max;
	int Array_Y_Max;
	int Center_X_Index;
	int Center_Y_Index;
	
	
public:
	Rotation();
	
	void Allocate_Rotation_Unit_Vector_Map();
	void Load_Rotation_Unit_Vector_Map();
	void Draw_Rotation_Unit_Vector_Map(Renderer *renderer);
	
	int Confirm_X_Degree(int x_degree);
	int Confirm_Y_Degree(int y_degree);
	
	Vector Rotate_X(Vector vector, int degree);
	Vector Rotate_Y(Vector vector, int degree);
	
	Vector *Get_Unit_Vector(int x_degree, int y_degree);
	
	~Rotation();
};