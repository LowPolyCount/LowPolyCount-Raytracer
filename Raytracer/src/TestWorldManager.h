#pragma once
#include "WorldManager.h"

class IRenderer;
class TestWorldManager :
	public WorldManager
{
public:
	TestWorldManager();
	virtual ~TestWorldManager();
	std::vector<std::shared_ptr<CollidableObject>> TestGetObjects() { return m_objects; }
	std::vector<std::shared_ptr<Light>> TestGetLights() { return m_lights; }
	bool TestLightCollision(const std::shared_ptr<Light> light, const Ray& rayToLight) const { return LightCollision(light, rayToLight); }
	virtual std::shared_ptr<IRenderer> GetImage() { return m_image; }
	std::shared_ptr<Camera> GetCamera() { return m_camera; }
	void TestUpdateRays() { UpdateRays(); }
	const std::vector < std::vector<Ray>>& GetCurrentScene() { return m_currentScene; }
};

