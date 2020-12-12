#include "Rotation.h"
#include "Vector.h"
#include "Renderer.h"
#include <math.h>

	Rotation::Rotation()
	{
		Up_Unit_Vector   = new Vector(0.f, -1.f, 0.f);
		Down_Unit_Vector = new Vector(0.f,  1.f, 0.f);
		
		Array_X_Max = 360;
		Array_Y_Max = 178;
		Center_X_Index = 180;
		Center_Y_Index = 90;
		
		Allocate_Rotation_Unit_Vector_Map();
		Load_Rotation_Unit_Vector_Map();
	}
	
	void Rotation::Allocate_Rotation_Unit_Vector_Map()
	{
		Rotation_Unit_Vector_Map = new Vector**[Array_X_Max];
		
		for(int x_index = 0; x_index < Array_X_Max; x_index++)
		{
			Rotation_Unit_Vector_Map[x_index] = new Vector*[Array_Y_Max];
			
			for(int y_index = 0; y_index < Array_Y_Max; y_index++)
				Rotation_Unit_Vector_Map[x_index][y_index] = NULL;
		}
	}
	
	void Rotation::Load_Rotation_Unit_Vector_Map()
	{
		int y_index = 0;
		int y_rotation_range_min;
		Vector rotated_unit_vector;
		
		for(int i = 0; i < 2; i++)
		{
			if(i == 0){ rotated_unit_vector.Set_Vector(0.f, -1.f,  0.f); y_rotation_range_min = 1; }
			if(i == 1){ rotated_unit_vector.Set_Vector(0.f,  0.f, -1.f); y_rotation_range_min = 0; }
			
			for(int j = y_rotation_range_min; j < 90; j++)
			{
				rotated_unit_vector = Rotate_X(rotated_unit_vector, j);
				
				for(int x_index = 0; x_index < Array_X_Max; x_index++)
				{
					if(i == 1 && (x_index == 0 || x_index == 90 || x_index == 180 || x_index == 270))
					{
						if		(x_index == 0)	Rotation_Unit_Vector_Map[x_index][y_index] = new Vector(-1.f, 0.f,  0.f);
						else if	(x_index == 90)	Rotation_Unit_Vector_Map[x_index][y_index] = new Vector( 0.f, 0.f, -1.f);
						else if	(x_index == 180)Rotation_Unit_Vector_Map[x_index][y_index] = new Vector( 1.f, 0.f,  0.f);
						else if	(x_index == 270)Rotation_Unit_Vector_Map[x_index][y_index] = new Vector( 0.f, 0.f,  1.f);
					}
					else						Rotation_Unit_Vector_Map[x_index][y_index] = new Vector(Rotate_Y(rotated_unit_vector, 270 + x_index));
				}
				
				y_index++;
			}
		}
	}
	
	int Rotation::Confirm_X_Degree(int x_degree)
	{
		if(x_degree < 0)	x_degree += 360;
		if(x_degree > 360)	x_degree  = x_degree - 360;
		
		if(x_degree < 0 || x_degree > 360) Confirm_X_Degree(x_degree);
		
		return x_degree;
	}
	
	int Rotation::Confirm_Y_Degree(int y_degree)
	{
		if(y_degree < 0)	y_degree += 360;
		if(y_degree > 360)	y_degree  = y_degree - 360;
		
		if(y_degree < 0 || y_degree > 360) Confirm_Y_Degree(y_degree);
		
		if(y_degree > 180 && y_degree < 360) y_degree = 180 - (y_degree - 180);
		
		return y_degree;
	}
	
	Vector *Rotation::Get_Unit_Vector(int x_degree, int y_degree)
	{
		x_degree = Confirm_X_Degree(x_degree);
		y_degree = Confirm_Y_Degree(y_degree);
		
		Vector *unit_vector = NULL;
		
		if		(y_degree == 0)		unit_vector = Up_Unit_Vector;
		else if	(y_degree == 180)	unit_vector = Down_Unit_Vector;
		else						unit_vector = Rotation_Unit_Vector_Map[x_degree][--y_degree];
		
		return unit_vector;
	}
	
	Vector Rotation::Rotate_Y(Vector unit_vector, int degree)
	{
		if(degree == 0)
		{
			return unit_vector;
		}
		else
		{
			float radian = ((float)degree * (22.f / 7.f)) / 180.f;
			
			float sin_radian = sin(radian);
			float cos_radian = cos(radian);
			
			float vector_x = unit_vector.Get_X_Component();
			float vector_z = unit_vector.Get_Z_Component();
			
			float x = (vector_x * cos_radian) - (vector_z * sin_radian);
			float z = (vector_z * cos_radian) + (vector_x * sin_radian);
			
			return Vector(x, unit_vector.Get_Y_Component(), z);
		}
	};

	Vector Rotation::Rotate_X(Vector unit_vector, int degree)
	{
		if(degree == 0)
		{
			return unit_vector;
		}
		else
		{
			float radian = ((float)degree * (22.f / 7.f)) / 180.f;
			
			float sin_radian = sin(radian);
			float cos_radian = cos(radian);
			
			float vector_y = unit_vector.Get_Y_Component();
			float vector_z = unit_vector.Get_Z_Component();
			
			float y = (vector_y * cos_radian) - (vector_z * sin_radian);
			float z = (vector_z * cos_radian) + (vector_y * sin_radian);
			
			return Vector(unit_vector.Get_X_Component(), y, z);
		}
	};
	
	Rotation::~Rotation()
	{
		delete Up_Unit_Vector;
		delete Down_Unit_Vector;
		
		for(int x_index = (Array_X_Max - 1); x_index > -1 ; x_index--)
		{
			for(int y_index = (Array_Y_Max - 1); y_index > -1; y_index--)
				delete Rotation_Unit_Vector_Map[x_index][y_index];
				
			delete Rotation_Unit_Vector_Map[x_index];
		}
		delete Rotation_Unit_Vector_Map;
	}