#include "Vector.h"
#include "Plane.h"
#include "Rotation.h"
#include "Camera.h"
#include "Renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//***************************//
//** Plane Implementations **//
//***************************//


	extern Camera Renderer_Camera;

	Plane::Plane()
	{
		Normal_Rotation_Vector			= new Rotation_Vector();
		Rotation_Vector_Pointer_Count	= 0;
	}
	
	Plane::Plane(Plane *plane)
	{
		Normal_Rotation_Vector			= new Rotation_Vector();
		Rotation_Vector_Pointer_Count	= 0;
		
		Rotation_Vector **rotation_vector_pointer_array = plane->Get_Rotation_Vector_Pointer_Array();
		int rotation_vector_count = plane->Get_Rotation_Vector_Pointer_Count();
		
		for(int i = 0; i < rotation_vector_count; i++) Add_Rotation_Vector_Pointer(new Rotation_Vector(rotation_vector_pointer_array[i]));
	}
	
	Vector Plane::Get_Normal_Vector(){ return Normal_Rotation_Vector->Get_Vector(); };
	
	void Plane::Set_Normal_Rotation_Vector(Rotation_Vector *rotation_vector)
	{
		Normal_Rotation_Vector->Set_Rotation_Vector(rotation_vector);
	}
	
	void Plane::Set_Normal_Rotation_Vector(Rotation_Vector rotation_vector)
	{
		Normal_Rotation_Vector->Set_Rotation_Vector(rotation_vector);
	}
	
	void Plane::Add_Rotation_Vector_Pointer(Rotation_Vector *rotation_vector_pointer)
	{
		Rotation_Vector_Pointer_Count++;
		
		if(Rotation_Vector_Pointer_Count == 1)
			Rotation_Vector_Pointer_Array = (Rotation_Vector**)malloc(Rotation_Vector_Pointer_Count * sizeof(Rotation_Vector*));
		else
			Rotation_Vector_Pointer_Array = (Rotation_Vector**)realloc(Rotation_Vector_Pointer_Array, Rotation_Vector_Pointer_Count * sizeof(Rotation_Vector*));
		
		Rotation_Vector_Pointer_Array[Rotation_Vector_Pointer_Count - 1] = rotation_vector_pointer;
		
		if(Rotation_Vector_Pointer_Count == 3)
		{
			Vector vector_1 = Rotation_Vector_Pointer_Array[0]->Get_Vector();
			Vector vector_2 = Rotation_Vector_Pointer_Array[1]->Get_Vector();
			Vector vector_3 = Rotation_Vector_Pointer_Array[2]->Get_Vector();
			
			Vector vector_4 = (vector_1 - vector_2) ^ (vector_3 - vector_2);
			vector_4.Normalize();
			
			Set_Normal_Rotation_Vector(vector_4.Get_Rotation_Vector());
		}
	}
	
	Vector Plane::Get_Average_Vector()
	{
		Vector average_vector(0, 0, 0);
		
		for(int i = 0; i < Rotation_Vector_Pointer_Count; i++)
			average_vector += Rotation_Vector_Pointer_Array[i]->Get_Vector();
		
		return average_vector / Rotation_Vector_Pointer_Count;
	}
	
	void Plane::Print()
	{
		printf("Plane:\r\n");
		printf("======\r\n");
		
		for(int i = 0; i < Rotation_Vector_Pointer_Count; i++) Rotation_Vector_Pointer_Array[i]->Print();
		
		printf("\r\n");
	}
	
	Orthogonal_Plane *Plane::Get_Orthogonal_Plane()
	{
		Orthogonal_Plane *orthogonal_plane = new Orthogonal_Plane();
		int sceen_x, sceen_y;
		float scale, eye_to_screen_dist;
		
		for(int i = 0; i < Rotation_Vector_Pointer_Count; i++)
		{
			Vector target_vector = Rotation_Vector_Pointer_Array[i]->Get_Vector() - Renderer_Camera.Get_Position_Vector();
			
			eye_to_screen_dist = Renderer_Camera.Get_Eye_to_Screen_Distance();
			scale = eye_to_screen_dist / (eye_to_screen_dist + target_vector.Get_Z_Component());
			
			sceen_x = (int)round(target_vector.Get_X_Component() * scale) + Renderer_Camera.Get_Renderer()->Get_Screen_Origin_X_Offset();
			sceen_y = (int)round(target_vector.Get_Y_Component() * scale) + Renderer_Camera.Get_Renderer()->Get_Screen_Origin_Y_Offset();
			
			orthogonal_plane->Add_Orthogonal_Vector(new Orthogonal_Vector(sceen_x, sceen_y, target_vector.Get_Z_Component()));
		}
		
		return orthogonal_plane;
	}
	
	Plane::~Plane()
	{
		free(Normal_Rotation_Vector);
		
		for(int i = Rotation_Vector_Pointer_Count - 1; i > -1; i--) delete Rotation_Vector_Pointer_Array[i];
		free(Rotation_Vector_Pointer_Array);
	}


//**************************************//
//** Othogonal Plane Implementations ***//
//**************************************//


	Orthogonal_Plane::Orthogonal_Plane()
	{
		Orthogonal_Vector_Array = NULL;
		Orthogonal_Vector_Count = 0;
	}
	
	void Orthogonal_Plane::Add_Orthogonal_Vector(Orthogonal_Vector *orthogonal_vector)
	{
		Orthogonal_Vector_Count++;
		
		if(Orthogonal_Vector_Count == 1)
			Orthogonal_Vector_Array = (Orthogonal_Vector**)malloc(Orthogonal_Vector_Count * sizeof(Orthogonal_Vector*));
		else
			Orthogonal_Vector_Array = (Orthogonal_Vector**)realloc(Orthogonal_Vector_Array, Orthogonal_Vector_Count * sizeof(Orthogonal_Vector*));
		
		Orthogonal_Vector_Array[Orthogonal_Vector_Count - 1] = orthogonal_vector;
	}
	
	Orthogonal_Plane::~Orthogonal_Plane()
	{
		for(int i = Orthogonal_Vector_Count - 1; i > -1; i--) delete Orthogonal_Vector_Array[i];
		if(Orthogonal_Vector_Array) free(Orthogonal_Vector_Array);
	}
