#pragma once
#include <vector>
#include <string>
#include <memory>
#include "CollidableObject.h"
#include "Camera.h"



class IRenderer;
class IFileLoader;
class WorldManager
{
public:
	WorldManager();
	virtual ~WorldManager();
	void InitSystems(std::unique_ptr<IFileLoader>& inFileLoader);
	bool Init(const std::string& fileName);
	void Render(bool createRenderer);
	inline const IRenderer* const GetImage() { return m_image; }
protected:
	typedef std::vector<std::unique_ptr<CollidableObject>> VectorOfObjectPtr;
	void UpdateRays();
	void RunThroughSimulation();
	RGBA FindIfIntersect(const Ray& testRay);
	void DrawImage();
	std::vector<CollidableObject*>	m_objects;
	std::vector<std::vector<Ray>>	m_currentScene;
	std::unique_ptr<IFileLoader>	m_loader;
	Camera*			m_camera;
	IRenderer*		m_image;
	//std::unique_ptr<Camera*>		m_camera;
	//std::unique_ptr<IRenderer*>		m_image;
};

