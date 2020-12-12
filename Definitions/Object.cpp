#include "Object.h"
#include "Plane.h"
#include "Vector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

	Object::Object()
	{
		Average_Vector			= NULL;
		Rotation_Vector_Array	= NULL;
		Plane_Array				= NULL;
		Rotation_Vector_Count	= 0;
		Plane_Count				= 0;
	}
	
	Object::Object(Object *object)
	{
		Average_Vector			= NULL;
		Rotation_Vector_Array	= NULL;
		Plane_Array				= NULL;
		Rotation_Vector_Count	= 0;
		Plane_Count				= 0;
		
		Rotation_Vector	**rotation_vector_array	= object->Get_Rotation_Vector_Array();
		int				  rotation_vector_count	= object->Get_Rotation_Vector_Count();
		Plane			**plane_array			= object->Get_Plane_Array();
		int				  plane_count			= object->Get_Plane_Count();
		
		for(int i = 0; i < rotation_vector_count; i++)
			Add_Rotation_Vector(new Rotation_Vector(rotation_vector_array[i]));
		
		for(int i = 0; i < plane_count; i++)
		{
			Add_Plane(new Plane());
			Rotation_Vector	**rotation_vector_pointer_array	= plane_array[i]->Get_Rotation_Vector_Pointer_Array();
			int				  rotation_vector_pointer_count	= plane_array[i]->Get_Rotation_Vector_Pointer_Count();
			
			for(int j = 0; j < rotation_vector_pointer_count; j++)
				Plane_Array[Plane_Count - 1]->Add_Rotation_Vector_Pointer(rotation_vector_pointer_array[j]);
		}
		
		Confrim_Plane_Normals();
		Set_Average_Vector();
	}
	
	void Object::Add_Rotation_Vector(Rotation_Vector *rotation_vector)
	{
		Rotation_Vector_Count++;
		
		if(Rotation_Vector_Count == 1)
			Rotation_Vector_Array = (Rotation_Vector**)malloc(Rotation_Vector_Count * sizeof(Rotation_Vector*));
		else
			Rotation_Vector_Array = (Rotation_Vector**)realloc(Rotation_Vector_Array, Rotation_Vector_Count * sizeof(Rotation_Vector*));
		
		Rotation_Vector_Array[Rotation_Vector_Count - 1] = rotation_vector;
	}
	
	void Object::Add_Plane(Plane *plane)
	{
		Plane_Count++;
		
		if(Plane_Count == 1)
			Plane_Array = (Plane**)malloc(Plane_Count * sizeof(Plane*));
		else
			Plane_Array = (Plane**)realloc(Plane_Array, Plane_Count * sizeof(Plane*));
			
		Plane_Array[Plane_Count - 1] = plane;
		
		if(Plane_Count == 3)
		{
			Vector average_vector(0, 0, 0);
			
			for(int i = 0; i < 3; i++)
				average_vector += Plane_Array[i]->Get_Average_Vector();
			
			Average_Vector = new Vector(average_vector / 3);
		}
	}
	
	void Object::Set_Average_Vector()
	{
		Vector average_vector(0, 0, 0);
		
		for(int i = 0; i < Plane_Count; i++)
			average_vector += Plane_Array[i]->Get_Average_Vector();
		
		delete Average_Vector;
		Average_Vector = new Vector(average_vector / Plane_Count);
	}
	
	void Object::Confrim_Plane_Normals()
	{
		Set_Average_Vector();
		
		for(int i = 0; i < Plane_Count; i++)
		{
			Vector normal_vector = Plane_Array[i]->Get_Normal_Rotation_Vector()->Get_Vector();
			Vector plane_average_vector(Plane_Array[i]->Get_Average_Vector());
			Vector object_average_vector(Average_Vector);
			
			if((normal_vector % (plane_average_vector - object_average_vector)) < 0)
			{
				normal_vector *= -1;
				
				Plane_Array[i]->Set_Normal_Rotation_Vector(normal_vector.Get_Rotation_Vector());
			}
		}
	}
	
	void Object::Reverse_Plane_Normals()
	{
		for(int i = 0; i < Plane_Count; i++)
		{
			Vector normal_vector = Plane_Array[i]->Get_Normal_Rotation_Vector()->Get_Vector();
			
			normal_vector *= -1;
			
			Plane_Array[i]->Set_Normal_Rotation_Vector(normal_vector.Get_Rotation_Vector());
		}
	}
	
	void Object::Create_Cube(int radius, Vector position_vector)
	{
		Vector vector_1(position_vector.Get_X_Component() - radius, position_vector.Get_Y_Component() - radius, position_vector.Get_Z_Component() - radius);
		Vector vector_2(position_vector.Get_X_Component() + radius, position_vector.Get_Y_Component() - radius, position_vector.Get_Z_Component() - radius);
		Vector vector_3(position_vector.Get_X_Component() + radius, position_vector.Get_Y_Component() + radius, position_vector.Get_Z_Component() - radius);
		Vector vector_4(position_vector.Get_X_Component() - radius, position_vector.Get_Y_Component() + radius, position_vector.Get_Z_Component() - radius);
		Vector vector_5(position_vector.Get_X_Component() - radius, position_vector.Get_Y_Component() - radius, position_vector.Get_Z_Component() + radius);
		Vector vector_6(position_vector.Get_X_Component() + radius, position_vector.Get_Y_Component() - radius, position_vector.Get_Z_Component() + radius);
		Vector vector_7(position_vector.Get_X_Component() + radius, position_vector.Get_Y_Component() + radius, position_vector.Get_Z_Component() + radius);
		Vector vector_8(position_vector.Get_X_Component() - radius, position_vector.Get_Y_Component() + radius, position_vector.Get_Z_Component() + radius);
		
		Add_Rotation_Vector(new Rotation_Vector(vector_1.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_2.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_3.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_4.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_5.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_6.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_7.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_8.Get_Rotation_Vector()));
		
		for(int i = 0; i < 6; i++) Add_Plane(new Plane());
		
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		
		Set_Average_Vector();
		Confrim_Plane_Normals();
	}
	
	float Object::Create_View_Frustum(int screen_width, int screen_height, float y_frustum_flare_degree, float view_field_depth)
	{
		float half_screen_width			= (float)screen_height / 2.f;
		float half_screen_height		= (float)screen_height / 2.f;
		float x_frustum_flare_degree	= y_frustum_flare_degree * ((float)screen_width / (float)screen_height);
		
		float x_remaining_angle_degree = 180.f - (90.f + x_frustum_flare_degree);
		float y_remaining_angle_degree = 180.f - (90.f + y_frustum_flare_degree);
		float x_remaining_angle_radian = (x_remaining_angle_degree * (22.f / 7.f)) / 180.f;
		float y_remaining_angle_radian = (y_remaining_angle_degree * (22.f / 7.f)) / 180.f;
		
		float delta_x = (view_field_depth / sin(x_remaining_angle_radian)) * sin(x_frustum_flare_degree);
		float delta_y = (view_field_depth / sin(y_remaining_angle_radian)) * sin(y_frustum_flare_degree);
		
		float back_plane_width  = half_screen_width  + delta_x;
		float back_plane_height = half_screen_height + delta_y;
		
		float eye_to_screen_dist = view_field_depth * (half_screen_height / delta_y);
		
		Vector vector_1(-half_screen_width, -half_screen_height, 0);
		Vector vector_2( half_screen_width, -half_screen_height, 0);
		Vector vector_3( half_screen_width,  half_screen_height, 0);
		Vector vector_4(-half_screen_width,  half_screen_height, 0);
		Vector vector_5(-back_plane_width,  -back_plane_height,  view_field_depth);
		Vector vector_6( back_plane_width,  -back_plane_height,  view_field_depth);
		Vector vector_7( back_plane_width,   back_plane_height,  view_field_depth);
		Vector vector_8(-back_plane_width,   back_plane_height,  view_field_depth);
		
		Add_Rotation_Vector(new Rotation_Vector(vector_1.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_2.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_3.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_4.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_5.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_6.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_7.Get_Rotation_Vector()));
		Add_Rotation_Vector(new Rotation_Vector(vector_8.Get_Rotation_Vector()));
		
		for(int i = 0; i < 6; i++) Add_Plane(new Plane());
		
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		Plane_Array[0]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[1]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		Plane_Array[2]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[0]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[4]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[3]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[1]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[5]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[4]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[3]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[7]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[6]);
		Plane_Array[5]->Add_Rotation_Vector_Pointer(Rotation_Vector_Array[2]);
		
		Set_Average_Vector();
		Confrim_Plane_Normals();
		
		return eye_to_screen_dist;
	}
	
	void Object::Translate(Vector translation_vector)
	{
		for(int i = 0; i < Rotation_Vector_Count; i++)
		{
			Vector vector_1 = Rotation_Vector_Array[i]->Get_Vector();
			vector_1 += translation_vector;
			
			Rotation_Vector_Array[i]->Set_Vector(vector_1.Get_Rotation_Vector());
		}
	}
	
	void Object::Scale(float scalar)
	{
		for(int i = 0; i < Rotation_Vector_Count; i++)
		{
			Vector vector_1 = Rotation_Vector_Array[i]->Get_Vector();
			vector_1 *= scalar;
			
			Rotation_Vector_Array[i]->Set_Vector(vector_1);
		}
	}
	
	bool Object::Vector_Is_Contained(Vector vector_ptr)
	{
		bool	is_contained = true;
		Vector	target_vector(*Get_Average_Vector() - vector_ptr);
		
		for(int i = 0; i < Plane_Count && is_contained; i++)
			if((target_vector % Plane_Array[i]->Get_Normal_Vector()) <= 0) is_contained = false;
		
		return is_contained;
	}
	
	Object::~Object()
	{
		delete Average_Vector;
		
		for(int i = Rotation_Vector_Count - 1; i > -1; i--) delete Rotation_Vector_Array[i];
		free(Rotation_Vector_Array);
		for(int i = Plane_Count - 1; i > -1; i--) delete Plane_Array[i];
		free(Plane_Array);
	}

