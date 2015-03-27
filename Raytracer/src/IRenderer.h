#pragma once
#include "Object.h"
#include "RaytracerTypes.h"

struct DeserializeData;
class IRenderer: public Object
{
public:
	IRenderer(ObjectType inType) :Object(inType) {}
	~IRenderer(){}

	virtual bool IsInit() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual const RGBA* GetFrameBuffer() const = 0;

	virtual void Init(const DeserializeData& data) = 0;
	virtual void Init(int inX, int inY) = 0;
	virtual void InitRenderer() = 0;

	virtual void SetPixel(int inX, int inY, const RGBA& inColor) = 0;
	virtual void Draw() = 0;
};

