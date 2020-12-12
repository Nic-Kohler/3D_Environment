#include <stdio.h>

class Rotation_Vector;

class Vector
{
private:
	float X_Component;
	float Y_Component;
	float Z_Component;

public:
	Vector();
	Vector(float x_component, float y_component, float z_component);
	Vector(Vector *vector);
	
	void Set_X_Component(float x_component){ X_Component = x_component; };
	void Set_Y_Component(float y_component){ Y_Component = y_component; };
	void Set_Z_Component(float z_component){ Z_Component = z_component; };
	
	void Set_Vector(float x_component, float y_component, float z_component);
	void Set_Vector(Vector *vector);
	void Set_Vector(Vector vector);
	
	float Get_X_Component(){ return X_Component; };
	float Get_Y_Component(){ return Y_Component; };
	float Get_Z_Component(){ return Z_Component; };
	
	float			Get_Magnitude();
	void			Normalize();
	Rotation_Vector Get_Rotation_Vector();
	
	Vector	operator  +(Vector unit_vector);
	void	operator +=(Vector unit_vector);
	Vector	operator  -(Vector unit_vector);
	void	operator -=(Vector unit_vector);
	Vector	operator  *(float scalar);
	void	operator *=(float scalar);
	Vector	operator  /(float scalar);
	void	operator /=(float scalar);
	Vector	operator  ^(Vector unit_vector); //Cross Product
	void	operator ^=(Vector unit_vector);
	float	operator  %(Vector unit_vector); //Dot Product
	bool	operator ==(Vector unit_vector);
	
	void Print(){ printf("Vector - X:\t%f, Y:\t%f, Z:\t%f\r\n\r\n", X_Component, Y_Component, Z_Component); };
	
	~Vector();
};

class Rotation_Vector:public Vector
{
private:
	int		X_Degree;
	int		Y_Degree;
	float	Magnitude;
	
public:
	Rotation_Vector();
	Rotation_Vector(int x_degree, int y_degree);
	Rotation_Vector(int x_degree, int y_degree, float magnitude, float x_component, float y_component, float z_component);
	Rotation_Vector(Rotation_Vector *rotation_vector);
	
	int 	Get_X_Degree()	{ return X_Degree; };
	int 	Get_Y_Degree()	{ return Y_Degree; };
	float 	Get_Magnitude()	{ return Magnitude; };
	
	void Set_X_Degree	(int x_degree)		{ X_Degree = x_degree; };
	void Set_Y_Degree	(int y_degree)		{ Y_Degree = y_degree; };
	void Set_Magnitude	(float magnitude)	{ Magnitude = magnitude; };
	
	void	Set_Rotation_Vector(int x_degree, int y_degree, float magnitude, float x_component, float y_component, float z_component);
	void	Set_Rotation_Vector(Rotation_Vector rotation_vector);
	Vector	Get_Vector();
	
	bool operator ==(Rotation_Vector rotation_vector);
	
	void Print()
	{
		printf("Rotation Vector - X_Degree:\t%d, Y_Degree:\t%d, Magnitude:\t%f\r\n", X_Degree, Y_Degree, Magnitude);
		printf("Vector - X_Component:\t%f, Y_Component:\t%f, Z_Component:\t%f\r\n\r\n", Get_X_Component(), Get_Y_Component(), Get_Z_Component());
	}
	
	~Rotation_Vector();
};

class Orthogonal_Vector
{
private:
	int Screen_X;
	int Screen_Y;
	float Z_Component;
	
public:
	Orthogonal_Vector(){};
	Orthogonal_Vector(int screen_x, int screen_y, float z_component);
	
	int		Get_Screen_X()		{ return Screen_X; }
	int		Get_Screen_Y()		{ return Screen_Y; }
	float	Get_Z_Component()	{ return Z_Component; }
	
	~Orthogonal_Vector(){};
};