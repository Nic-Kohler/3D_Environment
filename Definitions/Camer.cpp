#include "Loop.h"
#include "Camera.h"
#include "Renderer.h"
#include "Object.h"
#include "Plane.h"
#include "Vector.h"
#include <stdlib.h> 

	Camera::Camera()
	{
		Render = new Renderer();
		
		Screen_Width		= 1280;
		Screen_Height		= 720;
		View_Frustum_Depth	= 10000;
		Forward_Velocity	= 0.1f / 1000.f;
		Sidestep_Velocity	= Forward_Velocity;
		
		View_Frustum		= new Object();
		Forward_Vector		= new Rotation_Vector( 90, 270);
		Left_Vector			= new Rotation_Vector(  0,  90);
		Position_Vector		= new Vector(0.f, 0.f, -Eye_to_Screen_Distance);
		
		Eye_to_Screen_Distance = View_Frustum->Create_View_Frustum(Screen_Width, Screen_Height, 30.f, 10000.f);
	}
	
	void Camera::Translate(Vector translation_vector)
	{
		Vector position_vector(*Position_Vector + translation_vector);
		
		delete Position_Vector;
		Position_Vector = new Vector(position_vector);
		
		View_Frustum->Translate(translation_vector);
	}
	
	Object Camera::Find_Visible_Planes(Object **object_array, int object_count, bool is_transparent)
	{
		Object object;
		
		for(int i = 0; i < object_count; i++)
		{
			Plane **plane_array = object_array[i]->Get_Plane_Array();
			int		plane_count = object_array[i]->Get_Plane_Count();
			
			for(int j = 0; j < plane_count; j++)
			{
				Vector	plane_normal_vector(plane_array[j]->Get_Normal_Vector());
				float	plane_is_facing_camera = Forward_Vector->Get_Vector() % plane_array[j]->Get_Normal_Vector();
				if(is_transparent) plane_is_facing_camera = 1.f;
				
				if(plane_is_facing_camera > 0)
				{
					bool vector_is_not_included = true;
					
					Rotation_Vector	**rotation_vector_pointer_array = plane_array[j]->Get_Rotation_Vector_Pointer_Array();
					int				  rotation_vector_pointer_count = plane_array[j]->Get_Rotation_Vector_Pointer_Count();
					
					for(int k = 0; k < rotation_vector_pointer_count && vector_is_not_included; k++)
						if(View_Frustum->Vector_Is_Contained(rotation_vector_pointer_array[k]->Get_Vector()))
							object.Add_Plane(plane_array[j]);
				}
			}
		}
		
		return object;
	}
	
	void Camera::Clear_Renderer()
	{
		Render->Clear();
	}
	
	Camera::~Camera()
	{
		delete View_Frustum;
		
		delete Forward_Vector;
		delete Left_Vector;
		delete Position_Vector;
		
		delete Render;
	}