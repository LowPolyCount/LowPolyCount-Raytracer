#pragma once
#include "WorldManager.h"

class IRenderer;
class TestWorldManager :
	public WorldManager
{
public:
	TestWorldManager();
	virtual ~TestWorldManager();
	std::vector<CollidableObject*> TestGetObjects() { return m_objects; }
	std::vector<Light*> TestGetLights() { return m_lights; }
	bool TestLightCollision(const Light* light, const Ray& rayToLight) const { return LightCollision(light, rayToLight); }
	virtual IRenderer* GetImage() { return m_image; }
	Camera* GetCamera() { return m_camera; }
	void TestUpdateRays() { UpdateRays(); }
	const std::vector < std::vector<Ray>>& GetCurrentScene() { return m_currentScene; }
};

