#include "Loop.h"
#include "Camera.h"
#include "Renderer.h"
#include "Vector.h"
#include "Object.h"
#include <time.h>
#include <stdio.h>

#include <math.h>

extern Camera Renderer_Camera;

	Loop::Loop()
	{
		Object_Count = 0;

		Run_Loop = true;

		Loop_Interval = 0;
		Frame_Rate_Interval = (unsigned short)round(1000.f / 60.f);
		Frame_Rate = 0;
	}

	void Loop::Run()
	{
		//Add_Object(new Object());
		//Object_Array[Object_Count - 1]->Create_Cube(100, Vector(0.f, 0.f, 110.f));

		Previous_Time = clock();
		Previous_Frame_Rate_Time = Previous_Time;

		while(Run_Loop)
		{
			Update_Events();
			Update_Loop_Interval();
			Handle_Events();

			if(Loop_Interval >= Frame_Rate_Interval)
			{
				Previous_Time = Current_Time;
				Get_Frame_Rate();

				Draw();
			}
		}
	}

	void Loop::Draw()
	{
		Renderer_Camera.Clear_Renderer();

		//Object visible_planes = Renderer_Camera.Find_Visible_Planes(Object_Array, Object_Count, true);
		//Renderer_Camera.Get_Renderer()->Draw_Object(&visible_planes, 0x3333FF);

		/////////////////////////////////////////////




		/////////////////////////////////////////////

		Renderer_Camera.Get_Renderer()->Update();
	}

	void Loop::Update_Events()
	{
		SDL_PumpEvents();
		Keyboard_State_Array = SDL_GetKeyboardState(NULL);
	}

	void Loop::Update_Loop_Interval()
	{
		Current_Time  = clock();
		Loop_Interval = Current_Time - Previous_Time;
	}

	void Loop::Get_Frame_Rate()
	{
		if(Current_Time >= (Previous_Frame_Rate_Time + 1000))
		{
			printf("Frame Rate: %dfps\r\n", Frame_Rate);

			Frame_Rate = 0;
			Previous_Frame_Rate_Time = Current_Time;
		}
		else Frame_Rate++;
	}

	void Loop::Handle_Events()
	{
		if(Keyboard_State_Array[SDL_SCANCODE_ESCAPE]) Run_Loop = false;

		if((Keyboard_State_Array[SDL_SCANCODE_W] ||
			Keyboard_State_Array[SDL_SCANCODE_S] ||
			Keyboard_State_Array[SDL_SCANCODE_A] ||
			Keyboard_State_Array[SDL_SCANCODE_D])
		   && Run_Loop)
		{
			Vector foreward_vector(Renderer_Camera.Get_Forward_Vector()->Get_Vector());
			Vector left_vector(Renderer_Camera.Get_Left_Vector()->Get_Vector());

			Vector translation_vector(0.f, 0.f, 0.f);

			if(Keyboard_State_Array[SDL_SCANCODE_W]) translation_vector += Vector(foreward_vector	*  (Loop_Interval * Renderer_Camera.Get_Forward_Velocity()));
			if(Keyboard_State_Array[SDL_SCANCODE_S]) translation_vector += Vector(foreward_vector	* -(Loop_Interval * Renderer_Camera.Get_Forward_Velocity()));
			if(Keyboard_State_Array[SDL_SCANCODE_A]) translation_vector += Vector(left_vector		*  (Loop_Interval * Renderer_Camera.Get_Sidestep_Velocity()));
			if(Keyboard_State_Array[SDL_SCANCODE_D]) translation_vector += Vector(left_vector		* -(Loop_Interval * Renderer_Camera.Get_Sidestep_Velocity()));

			Renderer_Camera.Translate(translation_vector);
		}
	}

	void Loop::Add_Object(Object *object)
	{
		Object_Count++;

		if(Object_Count == 1)
			Object_Array = (Object**)malloc(Object_Count * sizeof(Object*));
		else
			Object_Array = (Object**)realloc(Object_Array, Object_Count * sizeof(Object*));

		Object_Array[Object_Count - 1] = object;
	}

	Loop::~Loop()
	{
		for(int i = (Object_Count - 1); i > -1; i--)
			delete Object_Array[i];

		if(Object_Count) free(Object_Array);
	}
