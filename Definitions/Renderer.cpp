#include "Renderer.h"
#include "Rotation.h"
#include "Camera.h"
#include "Object.h"
#include "Plane.h"
#include "Vector.h"
#include "Color.h"

#include <SDL.h>
#include <stdio.h>
#include <math.h>

extern Camera Renderer_Camera;

	Renderer::Renderer()
	{
		Orthogonal_Plane_Array = NULL;
		Orthogonal_Plane_Count = 0;

		Screen_Origin_X_Offset = Renderer_Camera.Get_Screen_Width() / 2;
		Screen_Origin_Y_Offset = Renderer_Camera.Get_Screen_Height() / 2;

		Initialize_SDL();
	}

	void Renderer::Add_Orthogonal_Plane(Orthogonal_Plane *orthogonal_plane)
	{
		Orthogonal_Plane_Count++;

		if(Orthogonal_Plane_Count == 1)
			Orthogonal_Plane_Array = (Orthogonal_Plane**)malloc(Orthogonal_Plane_Count * sizeof(Orthogonal_Plane*));
		else
			Orthogonal_Plane_Array = (Orthogonal_Plane**)realloc(Orthogonal_Plane_Array, Orthogonal_Plane_Count * sizeof(Orthogonal_Plane*));

		Orthogonal_Plane_Array[Orthogonal_Plane_Count - 1] = orthogonal_plane;
	}

	void Renderer::Initialize_SDL()
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
			printf("SDL could not initialize! SDL_Error: %s\r\n", SDL_GetError());
		else
		{
			Window = SDL_CreateWindow("3D Stuff",
									  SDL_WINDOWPOS_UNDEFINED,
									  SDL_WINDOWPOS_UNDEFINED,
									  Renderer_Camera.Get_Screen_Width(),
									  Renderer_Camera.Get_Screen_Height(),
									  SDL_WINDOW_SHOWN);

			if(Window == NULL)
				printf("SDL Window could not be created! SDL_Error: %s\r\n", SDL_GetError());
			else
			{
				printf("SDL Window created.\r\n");

				//Create Renderer
				Window_Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

				if(Window_Renderer == NULL)
					printf("SDL Renderer could not be created! SDL_Error: %s\r\n", SDL_GetError());
				else
				{
					printf("SDL Renderer created.\r\n");

					SDL_SetRenderDrawColor(Window_Renderer, 32, 32, 32, 255);
					SDL_RenderClear(Window_Renderer);
					SDL_RenderPresent(Window_Renderer);
				}
			}
		}

		printf("\r\n");
	}

	void Renderer::Draw_Object(Object *object, int int_color)
	{
		int plane_count = object->Get_Plane_Count();

		for(int i = 0; i < plane_count; i++)
			Draw_Orthogonal_Plane(object->Get_Plane_Array()[i]->Get_Orthogonal_Plane(), int_color);
	}

	void Renderer::Draw_Orthogonal_Plane(Orthogonal_Plane *orthogonal_plane, int int_color)
	{
		Color color(int_color);
		SDL_SetRenderDrawColor(Window_Renderer, color.Get_Red_Int(), color.Get_Green_Int(), color.Get_Blue_Int(), SDL_ALPHA_OPAQUE);

		int x_start, x_end, y_start, y_end;
		int vector_count = orthogonal_plane->Get_Orthogonal_Vector_Count();

		for(int i = 0; i < vector_count; i++)
		{
			x_start = orthogonal_plane->Get_Orthogonal_Vector_Array()[i]->Get_Screen_X();
			y_start = orthogonal_plane->Get_Orthogonal_Vector_Array()[i]->Get_Screen_Y();

			if(i < (vector_count - 1))
			{
				x_end = orthogonal_plane->Get_Orthogonal_Vector_Array()[i + 1]->Get_Screen_X();
				y_end = orthogonal_plane->Get_Orthogonal_Vector_Array()[i + 1]->Get_Screen_Y();
			}
			else
			{
				x_end = orthogonal_plane->Get_Orthogonal_Vector_Array()[0]->Get_Screen_X();
				y_end = orthogonal_plane->Get_Orthogonal_Vector_Array()[0]->Get_Screen_X();
			}

			SDL_RenderDrawLine(Window_Renderer, x_start, y_start, x_end, y_end);
		}
	}

	void Renderer::Draw_Vector(Vector *vector, int int_color)
	{
		Color color(int_color);
		SDL_SetRenderDrawColor(Window_Renderer, color.Get_Red_Int(), color.Get_Green_Int(), color.Get_Blue_Int(), SDL_ALPHA_OPAQUE);

		int x_end, y_end;
		float scale, eye_to_screen_dist;

		eye_to_screen_dist = Renderer_Camera.Get_Eye_to_Screen_Distance();
		scale = eye_to_screen_dist / (eye_to_screen_dist + vector->Get_Z_Component());

		x_end = (int)round(vector->Get_X_Component() * scale);
		y_end = (int)round(vector->Get_Y_Component() * scale);

		SDL_RenderDrawLine(Window_Renderer, 0	  + Screen_Origin_X_Offset, 0	  + Screen_Origin_Y_Offset,
											x_end + Screen_Origin_X_Offset, y_end + Screen_Origin_Y_Offset);
	}

	void Renderer::Update()
	{
		SDL_RenderPresent(Window_Renderer);
	}

	void Renderer::Clear()
	{
		SDL_SetRenderDrawColor(Window_Renderer, 32, 32, 32, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Window_Renderer);

		if(Orthogonal_Plane_Array)
		{
			for(int i = Orthogonal_Plane_Count - 1; i > -1; i--) delete Orthogonal_Plane_Array[i];
			free(Orthogonal_Plane_Array);

			Orthogonal_Plane_Array = NULL;
			Orthogonal_Plane_Count = 0;
		}
	}

	void Renderer::Delay(int time){ SDL_Delay(time); }

	Renderer::~Renderer()
	{
		for(int i = Orthogonal_Plane_Count - 1; i > -1; i--) delete Orthogonal_Plane_Array[i];
		if(Orthogonal_Plane_Array) free(Orthogonal_Plane_Array);

		SDL_DestroyRenderer(Window_Renderer);
		SDL_DestroyWindow(Window);
		SDL_Quit();
	}
