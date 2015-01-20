#pragma once
#include <vector>
#include "Vector3d.h"
#include "WorldObject.h"
#include "IRenderer.h"
#include "RaytracerTypes.h"


struct SDL_Window;
struct SDL_Surface;
class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	RendererSDL(int inX, int inY);
	virtual ~RendererSDL();

	virtual inline bool IsInit() const { return m_isInitRenderer; }
	virtual inline int GetWidth() const { return m_width; }
	virtual inline int GetHeight() const { return m_height; }
	virtual inline const RGBA* GetFrameBuffer() const { return m_frameBuffer; }

	virtual void Init(const DeserializeData& data);
	virtual void Init(int inX, int inY);
	virtual void InitRenderer();

	virtual void SetPixel(int inX, int inY, const RGBA& inColor);
	virtual void Draw();
private:
	void CreateRenderer();
	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
	RGBA* m_frameBuffer;
	int m_width;
	int m_height;
	bool m_isInitRenderer;
};

