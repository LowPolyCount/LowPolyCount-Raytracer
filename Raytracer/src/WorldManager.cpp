#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <limits>
#include <gtest\gtest.h>
#include "WorldManager.h"
#include "LpcMath.h"
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
		Object* worldObj = factoryMethod.Create(objData);
		
		switch (worldObj->GetType())
		{
		case Object::ObjectType::CT_Camera:
			m_camera = static_cast<Camera*>(worldObj);
			break;
		case Object::ObjectType::CT_Image:
			m_image = static_cast<IRenderer*>(worldObj);
			break;
		case Object::ObjectType::CT_Error:
			cout << "WorldManager::Init - Error" << endl << static_cast<ErrorObject*>(worldObj)->GetError() << endl;
			noError = false;
			break;
		case Object::ObjectType::CT_Unknown:
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
			RGBA hitColor = FindIfIntersect(m_currentScene[i][j]);
			m_image->SetPixel(i, j, hitColor);
		}
	}
}

struct HitInformaionStruct
{
	RGBA m_hitMaterial;
	double m_distance;
};

RGBA WorldManager::FindIfIntersect(const Ray& testRay)
{
	std::vector<HitInformaionStruct> hitsDetected;
	Vector3d pointOfIntersect;
	for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		if (LpcMath::IsCollision(testRay, (**i), pointOfIntersect))
		{
			HitInformaionStruct hitInfo;
			hitInfo.m_hitMaterial = (*i)->GetLastMaterialHit();
			hitInfo.m_distance = ((*i)->GetPosition() - testRay.GetPosition()).length();
			hitsDetected.push_back(hitInfo);
		}
	}

	if (hitsDetected.size() > 0)
	{
		HitInformaionStruct closestHit;
		closestHit.m_hitMaterial = COLOR_WHITE;
		closestHit.m_distance = std::numeric_limits<double>::max();

		for (auto i = hitsDetected.begin(); i != hitsDetected.end(); ++i)
		{
			if ((*i).m_distance >= 0 && (*i).m_distance < closestHit.m_distance)
			{
				closestHit = *i;
			}
		}

		return closestHit.m_hitMaterial;
	}

	return COLOR_WHITE;
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