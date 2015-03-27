#include "stdafx.h"
#include <gtest\gtest.h>
#include "RendererSDL.h"
#include "SDL.h"
#include "DeserializeData.h"

using namespace std;

static const RGBA BACKGROUND_COLOR = 255+(255<<8)+(255<<16);
static const char* WINDOW_NAME = "LowPolyCount Raytracer";

RendererSDL::RendererSDL()
:IRenderer(ObjectType::CT_Image)
, m_width(0)
, m_height(0)
, m_frameBuffer(nullptr)
, m_isInitRenderer(false)
{}

RendererSDL::RendererSDL(int inWidth, int inHeight)
: IRenderer(ObjectType::CT_Image)
, m_width(inWidth)
, m_height(inHeight)
, m_frameBuffer(nullptr)
, m_isInitRenderer(false)
{
	Init(m_width, m_height);
}


RendererSDL::~RendererSDL()
{
	if (IsInit())
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		m_screenSurface = nullptr;
	}
}

void RendererSDL::Init(const DeserializeData& data)
{
	const Vector3d& pos = data.m_mapVector.at(DeserializeData::POSITION);
	Init(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void RendererSDL::Init(int inWidth, int inHeight)
{
	m_width = inWidth;
	m_height = inHeight;
}

void RendererSDL::InitRenderer()
{
	//Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		m_window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_screenSurface = SDL_GetWindowSurface(m_window);
			m_frameBuffer = static_cast<RGBA*>(m_screenSurface->pixels);
			for (int i = 0; i < m_width*m_height; ++i)
			{
				m_frameBuffer[i] = BACKGROUND_COLOR;
			}
		}
	}

	m_isInitRenderer = true;
}

void RendererSDL::SetPixel(int inX, int inY, const RGBA& inColor)
{
	if (m_frameBuffer)
	{
		m_frameBuffer[inX*m_width + inY] = inColor;
	}
}

void RendererSDL::Draw()
{
	SDL_UpdateWindowSurface(m_window);
}



TEST(constructor, RendererSDL)
{
	int x = 5;
	int y = 5;
	RendererSDL test1(x, y);

	const RGBA* tt = test1.GetFrameBuffer();

	// @TODO: Figure out better way to test if frame buffer was constructed correctly or not
	/*for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			ASSERT_EQ(BACKGROUND_COLOR, test1.GetFrameBuffer()[i*j]);
		}
	}*/
	
}
