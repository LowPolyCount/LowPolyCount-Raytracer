#include "stdafx.h"
#include <gtest\gtest.h>
//#include <render\SDL_sysrender.h>
#include "RendererSDL.h"
#include "SDL.h"
#include "DeserializeData.h"

using namespace std;

//static const RGBA BACKGROUND_COLOR = 255+(255<<8)+(255<<16);
static const RGBA BACKGROUND_COLOR = 255+(255<<8)+(255<<16) + (0 << 24);
//static const RGBA BACKGROUND_COLOR = 125 + (125 << 8) + (125 << 16);
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
, m_texture(nullptr)
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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		m_window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer == NULL)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}

		Uint32 rmask = 0, gmask = 0, bmask = 0, amask = 0;
		//SDL_MasksToPixelFormatEnum(SDL_PIXELFORMAT_BGR888, rmask, gmask, bmask, amask);
		SDL_MasksToPixelFormatEnum(SDL_PIXELFORMAT_BGRA4444, rmask, gmask, bmask, amask);
		//m_screenSurface = SDL_GetWindowSurface(m_window);
		//m_screenSurface = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
			/*0x00FF0000,
			0x000000FF,
			0x0000FF00,

			0xFF000000);*/
		m_screenSurface = SDL_CreateRGBSurface(0, m_width, m_height, 32, rmask, gmask, bmask, amask);
			/*0x00FF0000,
			0x0000FF00,
			0x000000FF,
			0xFF000000);*/
		if (m_screenSurface == NULL)
		{
			printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}

		if (m_screenSurface->w != m_width || m_screenSurface->h != m_height)
		{
			m_width = m_screenSurface->w;
			m_height = m_screenSurface->h;
			cout << "Error while Initalizing:" << SDL_GetError() << endl;
			cout << "SDL was not able to create a screen surface as big as you requested. Displaying " << m_width << "x" << m_height << endl;
			SDL_ClearError();
		}


		//m_texture = SDL_CreateTextureFromSurface(m_renderer, m_screenSurface);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
		if (m_texture == NULL)
		{
			printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}

		LockForDrawing();

		const int totalPixels = m_width*m_height;
		for (int i = 0; i < totalPixels; ++i)
		{
			m_frameBuffer[i] = BACKGROUND_COLOR;
		}

		UnlockAfterDrawing();
	}

	m_isInitRenderer = true;
}

void RendererSDL::LockForDrawing()
{
	void* pixels = nullptr;

	if (SDL_LockTexture(m_texture, &m_screenSurface->clip_rect, &pixels, &m_screenSurface->pitch) != 0)
	{
		cout << "Error on Locking Texture: " << SDL_GetError() << endl;
		SDL_ClearError();
		return;
	}

	// @todo: framebuffer should remain unchanged after lock/unlock, but we update it here anyway for when it's used in Draw()
	m_frameBuffer = static_cast<RGBA*>(pixels);

}

void RendererSDL::UnlockAfterDrawing()
{
	SDL_UnlockTexture(m_texture);
}

void RendererSDL::Draw()
{
	if (SDL_UpdateTexture(m_texture, NULL, m_frameBuffer, m_screenSurface->pitch) != 0)
	{
		cout << "Error on Updating Texture: " << SDL_GetError() << endl;
		SDL_ClearError();
	}

	if (SDL_RenderClear(m_renderer) != 0)
	{
		cout << "Error on Render Clear: " << SDL_GetError() << endl;
		SDL_ClearError();
	}
	if (SDL_RenderCopy(m_renderer, m_texture, NULL, NULL))
	{
		cout << "Error on Render Copy: " << SDL_GetError() << endl;
		SDL_ClearError();
	}
	SDL_RenderPresent(m_renderer);

	m_frameBuffer = nullptr;
}

void RendererSDL::SetPixel(int inX, int inY, const RGBA& inColor)
{
	if (m_frameBuffer)
	{
		
		if (inX >= m_width && inY >= m_height)
		{
			cout << "ERROR tried to hit outside of framebuffer:" << inX << ":" << inY << endl;
			return;
		}

		m_frameBuffer[(inX*m_width + inY)] = inColor;
	}
}



TEST(constructor, RendererSDL)
{
	const int x = 5;
	const int y = 5;
	RendererSDL test1(x, y);
	test1.InitRenderer();
	const RGBA* tt = test1.GetFrameBuffer();
	
	// make sure bg color was used
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			ASSERT_EQ(BACKGROUND_COLOR, test1.GetFrameBuffer()[i*j]);
		}
	}
	
}
