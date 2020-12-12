#include "Vector.h"
#include "Rotation.h"
#include <math.h>

extern Rotation Rotate;


//****************************//
//** Vector Implementations **//
//****************************//


	Vector::Vector(){}
	
	Vector::Vector(float x_component, float y_component, float z_component)
	{
		X_Component = x_component;
		Y_Component = y_component;
		Z_Component = z_component;
	}
	
	Vector::Vector(Vector *vector)
	{
		X_Component = vector->Get_X_Component();
		Y_Component = vector->Get_Y_Component();
		Z_Component = vector->Get_Z_Component();
	}
	
	void Vector::Set_Vector(float x_component, float y_component, float z_component)
	{
		X_Component = x_component;
		Y_Component = y_component;
		Z_Component = z_component;
	}
	void Vector::Set_Vector(Vector *vector)
	{ 
		X_Component = vector->Get_X_Component();
		Y_Component = vector->Get_Y_Component();
		Z_Component = vector->Get_Z_Component();
	}
	void Vector::Set_Vector(Vector vector)
	{ 
		X_Component = vector.Get_X_Component();
		Y_Component = vector.Get_Y_Component();
		Z_Component = vector.Get_Z_Component();
	}
	
	float Vector::Get_Magnitude(){ return sqrt((X_Component * X_Component) + (Y_Component * Y_Component) + (Z_Component * Z_Component)); }
	
	void Vector::Normalize()
	{
		float magnitude = Get_Magnitude();
		
		X_Component /= magnitude;
		Y_Component /= magnitude;
		Z_Component /= magnitude;
	}
	
	Rotation_Vector Vector::Get_Rotation_Vector()
	{
		float	delta_x				= 0.f;
		float	delta_y				= 0.f;
		float	delta_z				= 0.f;
		float	delta_sum			= 999.9f;
		int		closest_x_degree	= -1;
		int		closest_y_degree	= -1;
		Vector target_vector(X_Component, Y_Component, Z_Component);
		target_vector.Normalize();
		
		for(int x_degree = 0; x_degree < 360; x_degree++)
		{
			for(int y_degree = 0; y_degree < 181; y_degree++)
			{
				Vector unit_vector(Rotate.Get_Unit_Vector(x_degree, y_degree));
				
				float delta_x_temp		= target_vector.Get_X_Component() - unit_vector.Get_X_Component();
				float delta_y_temp		= target_vector.Get_Y_Component() - unit_vector.Get_Y_Component();
				float delta_z_temp		= target_vector.Get_Z_Component() - unit_vector.Get_Z_Component();
				float delta_sum_temp	= fabs(delta_x_temp) + fabs(delta_y_temp) + fabs(delta_z_temp);
				
				if(delta_sum_temp < delta_sum)
				{
					delta_x				= delta_x_temp;
					delta_y				= delta_y_temp;
					delta_z				= delta_z_temp;
					delta_sum			= delta_sum_temp;
					closest_x_degree	= x_degree;
					closest_y_degree	= y_degree;
				}
			}
		}
		
		printf("closest_x_degree: %d\r\n", closest_x_degree);
		printf("closest_y_degree: %d\r\n", closest_y_degree);
		printf("Get_Magnitude():  %f\r\n", Get_Magnitude());
		printf("delta_x: %f\r\n", delta_x);
		printf("delta_y: %f\r\n", delta_y);
		printf("delta_z: %f\r\n", delta_z);
		printf("\r\n");
		
		return Rotation_Vector(closest_x_degree, closest_y_degree, Get_Magnitude(), delta_x, delta_y, delta_z);
	}
	
	Vector Vector::operator +(Vector vector)
	{
		return Vector(X_Component + vector.Get_X_Component(), Y_Component + vector.Get_Y_Component(), Z_Component + vector.Get_Z_Component());
	}
	
	void Vector::operator +=(Vector vector)
	{
		X_Component += vector.Get_X_Component();
		Y_Component += vector.Get_Y_Component();
		Z_Component += vector.Get_Z_Component();
	}
	
	Vector Vector::operator -(Vector vector)
	{
		return Vector(X_Component - vector.Get_X_Component(), Y_Component - vector.Get_Y_Component(), Z_Component - vector.Get_Z_Component());
	}
	
	void Vector::operator -=(Vector vector)
	{
		X_Component -= vector.Get_X_Component();
		Y_Component -= vector.Get_Y_Component();
		Z_Component -= vector.Get_Z_Component();
	}
	
	Vector Vector::operator *(float scalar)
	{
		return Vector(X_Component * scalar, Y_Component * scalar, Z_Component * scalar);
	}
	
	void Vector::operator *=(float scalar)
	{
		X_Component *= scalar; 
		Y_Component *= scalar;
		Z_Component *= scalar;
	}
	
	Vector Vector::operator /(float scalar)
	{
		return Vector(X_Component / scalar, Y_Component / scalar, Z_Component / scalar);
	}
	
	void Vector::operator /=(float scalar)
	{
		X_Component /= scalar; 
		Y_Component /= scalar;
		Z_Component /= scalar;
	}
	
	Vector Vector::operator ^(Vector vector)
	{
		return Vector((Y_Component * vector.Get_Z_Component()) - (Z_Component * vector.Get_Y_Component()),
					  (Z_Component * vector.Get_X_Component()) - (X_Component * vector.Get_Z_Component()),
					  (X_Component * vector.Get_Y_Component()) - (Y_Component * vector.Get_X_Component()));
	}
	
	void Vector::operator ^=(Vector vector)
	{
		X_Component = (Y_Component * vector.Get_Z_Component()) - (Z_Component * vector.Get_Y_Component());
		Y_Component = (Z_Component * vector.Get_X_Component()) - (X_Component * vector.Get_Z_Component());
		Z_Component = (X_Component * vector.Get_Y_Component()) - (Y_Component * vector.Get_X_Component());
	}
	
	float Vector::operator %(Vector vector)
	{
		return (X_Component * vector.Get_X_Component()) + (Y_Component * vector.Get_Y_Component()) + (Z_Component * vector.Get_Z_Component());
	}
	
	bool Vector::operator ==(Vector vector)
	{
		bool result = false;
		
		if(X_Component == vector.Get_X_Component() && Y_Component == vector.Get_Y_Component() && Z_Component == vector.Get_Z_Component()) result = true;
		
		return result;
	}
	
	Vector::~Vector(){}


//*************************************//
//** Rotation Vector Implementations **//
//*************************************//


	Rotation_Vector::Rotation_Vector()
	{
		X_Degree	= NULL;
		Y_Degree	= NULL;
		Magnitude	= 1;
		
		Set_X_Component(0.f);
		Set_Y_Component(0.f);
		Set_Z_Component(0.f);
	}
	
	Rotation_Vector::Rotation_Vector(int x_degree, int y_degree)
	{
		X_Degree	= x_degree;
		Y_Degree	= y_degree;
		Magnitude	= 1;
		
		Set_X_Component(0.f);
		Set_Y_Component(0.f);
		Set_Z_Component(0.f);
	}
	
	Rotation_Vector::Rotation_Vector(int x_degree, int y_degree, float magnitude, float x_component, float y_component, float z_component)
	{
		X_Degree	= x_degree;
		Y_Degree	= y_degree;
		Magnitude	= magnitude;
		
		Set_X_Component(x_component);
		Set_Y_Component(y_component);
		Set_Z_Component(z_component);
	}
	
	Rotation_Vector::Rotation_Vector(Rotation_Vector *rotation_vector)
	{
		X_Degree	= rotation_vector->Get_X_Degree();
		Y_Degree	= rotation_vector->Get_Y_Degree();
		Magnitude	= rotation_vector->Get_Magnitude();
		
		Set_X_Component(rotation_vector->Get_X_Component());
		Set_Y_Component(rotation_vector->Get_Y_Component());
		Set_Z_Component(rotation_vector->Get_Z_Component());
	}
	
	void Rotation_Vector::Set_Rotation_Vector(int x_degree, int y_degree, float magnitude, float x_component, float y_component, float z_component)
	{
		X_Degree	= x_degree;
		Y_Degree	= y_degree;
		Magnitude	= magnitude;
		
		Set_X_Component(x_component);
		Set_Y_Component(y_component);
		Set_Z_Component(z_component);
	}
	
	void Rotation_Vector::Set_Rotation_Vector(Rotation_Vector rotation_vector)
	{
		X_Degree	= rotation_vector.Get_X_Degree();
		Y_Degree	= rotation_vector.Get_Y_Degree();
		Magnitude	= rotation_vector.Get_Magnitude();
		
		Set_X_Component(rotation_vector.Get_X_Component());
		Set_Y_Component(rotation_vector.Get_Y_Component());
		Set_Z_Component(rotation_vector.Get_Z_Component());
	}
	
	Vector Rotation_Vector::Get_Vector()
	{
		Vector unit_vector = Rotate.Get_Unit_Vector(X_Degree, Y_Degree);
		
		unit_vector.Set_X_Component(unit_vector.Get_X_Component() + Get_X_Component());
		unit_vector.Set_Y_Component(unit_vector.Get_Y_Component() + Get_Y_Component());
		unit_vector.Set_Z_Component(unit_vector.Get_Z_Component() + Get_Z_Component());
		
		unit_vector *= Magnitude;
		
		return unit_vector;
	}
	
	bool Rotation_Vector::operator ==(Rotation_Vector rotation_vector)
	{
		bool result = false;
		
		if(Get_X_Component()	== rotation_vector.Get_X_Component() &&
		   Get_Y_Component()	== rotation_vector.Get_Y_Component() &&
		   Get_Z_Component()	== rotation_vector.Get_Z_Component() &&
		   X_Degree				== rotation_vector.Get_X_Degree() &&
		   Y_Degree				== rotation_vector.Get_Y_Degree() &&
		   Magnitude			== rotation_vector.Get_Magnitude())
			result = true;
		
		return result;
	}
	
	Rotation_Vector::~Rotation_Vector(){}


//***************************************//
//** Orthogonal Vector Implementations **//
//***************************************//


	Orthogonal_Vector::Orthogonal_Vector(int screen_x, int screen_y, float z_component)
	{
		Screen_X	= screen_x;
		Screen_Y	= screen_y;
		Z_Component	= z_component;
	}
