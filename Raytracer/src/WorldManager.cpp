#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <gtest\gtest.h>
#include "WorldManager.h"
#include "Ray.h"
#include "Deserializer.h"
#include "Factory.h"
#include "DeserializeData.h"
#include "RendererSDL.h"
#include "ErrorObject.h"

using namespace std;

static const RGBA HIT_COLOR = 0;

WorldManager::WorldManager()
:m_objects()
, m_camera(nullptr)
, m_image(nullptr)

{
}

WorldManager::~WorldManager()
{
	delete m_camera;
	delete m_image;

	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		delete *iter;
	}
}

void WorldManager::InitSystems(std::unique_ptr<IFileLoader>& inFileLoader)
{
	m_loader = std::move(inFileLoader);
}

bool WorldManager::Init(const std::string& fileName)
{
	Factory factoryMethod;
	bool noError = true;

	if (!m_loader->LoadFile(fileName))
	{
		return false;
	}

	if (!m_loader->GetDataFromFile())
	{
	}

	const std::vector<DeserializeData>& worldData = m_loader->GetData();
	for (auto iter = worldData.begin(); iter != worldData.end(); ++iter)
	{
		const DeserializeData objData = *iter;
		WorldObject* worldObj = factoryMethod.Create(objData);
		
		switch (worldObj->GetType())
		{
		case WorldObject::WorldType::CT_Camera:
			m_camera = static_cast<Camera*>(worldObj);
			break;
		case WorldObject::WorldType::CT_Image:
			m_image = static_cast<IRenderer*>(worldObj);
			break;
		case WorldObject::WorldType::CT_Error:
			cout << "WorldManager::Init - Error" << endl << static_cast<ErrorObject*>(worldObj)->GetError() << endl;
			noError = false;
			break;
		case WorldObject::WorldType::CT_Unknown:
			cout << "WorldManager::Init - Unknown Type Encountered" << endl;
			noError = false;
			break;
		//TODO: Should probably put all collidableTypes here. 
		default:
			m_objects.push_back(static_cast<CollidableObject*>(worldObj));
			break;
		}
	}

	return noError;
}

void WorldManager::Render(bool createRenderer)
{
	if (createRenderer && m_image)
	{
		m_image->InitRenderer();
	}

	UpdateRays();

	RunThroughSimulation();

	DrawImage();
}

void WorldManager::DrawImage()
{
	if (m_image && m_image->IsInit())
	{
		m_image->Draw();
	}	
}

void WorldManager::RunThroughSimulation()
{
	const int width = m_image->GetWidth();
	const int height = m_image->GetHeight();

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i<width; i++)
		{
			if (FindIfIntersect(m_currentScene[i][j]))
			{
				m_image->SetPixel(i, j, HIT_COLOR);				
			}
		}
	}
}

bool WorldManager::FindIfIntersect(const Ray& testRay)
{
	for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		if ((*i)->IsCollision(testRay))
		{
			return true;
		}
	}

	return false;
}

void WorldManager::UpdateRays()
{
	const int numColumns = m_image->GetWidth();
	const int numRows = m_image->GetHeight();

	m_currentScene.clear();
	m_currentScene.resize(numColumns);
	for (int i = 0; i<numColumns; i++)
	{
		m_currentScene[i].clear();
		m_currentScene[i].resize(numRows);
		for (int j = 0; j < numRows; j++)
		{
			m_currentScene[i][j] = m_camera->CreateRay(i, j, numColumns, numRows);
		}
	}
}