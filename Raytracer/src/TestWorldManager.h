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
	virtual IRenderer* GetImage() { return m_image; }
	Camera* GetCamera() { return m_camera; }
	const std::vector < std::vector<Ray>>& GetCurrentScene() { return m_currentScene; }
};

