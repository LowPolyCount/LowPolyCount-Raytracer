#pragma once
#include <vector>
#include <string>
#include <memory>
#include "CollidableObject.h"
#include "Camera.h"
#include "Light.h"


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
	inline const std::shared_ptr<IRenderer> GetImage() const { return m_image; }
protected:
	typedef std::vector<std::unique_ptr<CollidableObject>> VectorOfObjectPtr;
	void UpdateRays();
	void RunThroughSimulation();
	RGBA FindIfIntersect(const Ray& testRay);
	bool LightCollision(const std::shared_ptr<Light> light, const Ray& rayToLight) const;
	void DrawImage();
	std::vector<std::shared_ptr<CollidableObject>>		m_objects;
	std::vector<std::vector<Ray>>		m_currentScene;
	std::unique_ptr<IFileLoader>		m_loader;
	std::vector<std::shared_ptr<Light>>	m_lights;
	std::shared_ptr<Camera>				m_camera;
	std::shared_ptr<IRenderer>			m_image;
};

