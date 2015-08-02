#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <limits>
#include <gtest\gtest.h>
#include "WorldManager.h"
#include "LpcMath.h"
#include "IFileLoader.h"
#include "Ray.h"
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
		shared_ptr<Object> worldObj = factoryMethod.Create(objData);
		
		switch (worldObj->GetType())
		{
		case Object::ObjectType::CT_Camera:
			m_camera = tr1::static_pointer_cast<Camera>(worldObj);
			break;
		case Object::ObjectType::CT_Image:
			m_image = tr1::static_pointer_cast<IRenderer>(worldObj);
			break;
		case Object::ObjectType::CT_Light:
			m_lights.push_back(tr1::static_pointer_cast<Light>(worldObj));
			break;
		case Object::ObjectType::CT_Error:
			cout << "WorldManager::Init - Error" << endl << tr1::static_pointer_cast<ErrorObject>(worldObj)->GetError() << endl;
			noError = false;
			break;
		case Object::ObjectType::CT_Unknown:
			cout << "WorldManager::Init - Unknown Type Encountered" << endl;
			noError = false;
			break;
		//TODO: Should probably put all collidableTypes here. 
		default:
			m_objects.push_back(tr1::static_pointer_cast<CollidableObject>(worldObj));
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
	//@todo with height are actually reversed.  
	m_image->LockForDrawing();
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i<width; i++)
		{
			RGBA hitColor = FindIfIntersect(m_currentScene[i][j]);
			m_image->SetPixel(i, j, hitColor);
		}
	}

	for (int j = 290; j < 300; j++)
	{
		for (int i = 300; i<301; i++)
		{
			RGBA hitColor = FindIfIntersect(m_currentScene[i][j]);
			m_image->SetPixel(i, j, hitColor);
		}
	}
	m_image->UnlockAfterDrawing();
}

struct IntersectionRecord
{
	const Ray*				m_rayHit;
	std::shared_ptr<const CollidableObject> m_objectHit;
	Vector3d				m_pointOfIntersect;
	double					m_distance;
};



RGBA WorldManager::FindIfIntersect(const Ray& testRay)
{
	std::vector<IntersectionRecord> hitsDetected;
	for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		Vector3d pointOfIntersect;
		if (LpcMath::IsCollision(testRay, (**i), pointOfIntersect))
		{
			IntersectionRecord hitInfo;
			hitInfo.m_rayHit = &testRay;
			hitInfo.m_objectHit = *i;
			hitInfo.m_pointOfIntersect = pointOfIntersect;
			hitInfo.m_distance = ((*i)->GetPosition() - testRay.GetPosition()).length();
			hitsDetected.push_back(hitInfo);
		}
	}

	if (hitsDetected.size() > 0)
	{
		IntersectionRecord closestHit;
		closestHit.m_distance = std::numeric_limits<double>::max();

		for (auto i = hitsDetected.begin(); i != hitsDetected.end(); ++i)
		{
			if ((*i).m_distance >= 0 && (*i).m_distance < closestHit.m_distance)
			{
				closestHit = *i;
			}
		}
		
		std::vector<const std::shared_ptr<Light>> hitLights;

		// from here, now go find out how many lights this hits
		for (auto i = m_lights.begin(); i != m_lights.end(); ++i)
		{
			// build ray to light
			Vector3d dirToLight((*i)->GetPosition() - closestHit.m_pointOfIntersect);
			dirToLight.NormalizeVector();
			Ray rayToLight;
			rayToLight.Init(closestHit.m_pointOfIntersect, dirToLight);
			// move ray a bit off the intersect point
			rayToLight.MoveByDelta(0.001);
			// test collision
			if (LightCollision(*i, rayToLight))
			{
				//IntersectionRecordLight lightHitRecord;
				//lightHitRecord.m_light = *i;
				//lightHitRecord.m_rayHit = rayToLight;
				// pass, add to list
				hitLights.push_back(*i);
			}
		}

		// ok, send in list of lights hit to material for processing
		return closestHit.m_objectHit->CalculateMaterialHit(testRay, closestHit.m_pointOfIntersect, hitLights).ToRGBA();
		return closestHit.m_objectHit->GetMaterial().GetColor().ToRGBA();
	}

	return COLOR_BLACK;
}

bool WorldManager::LightCollision(const shared_ptr<Light> light, const Ray& rayToLight) const
{
	std::vector<IntersectionRecord> hitsDetected;
	for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		Vector3d pointOfIntersect;
		if (LpcMath::IsCollision(rayToLight, (**i), pointOfIntersect))
		{
			IntersectionRecord hitInfo;
			hitInfo.m_rayHit = &rayToLight;
			hitInfo.m_objectHit = *i;
			hitInfo.m_pointOfIntersect = pointOfIntersect;
			hitInfo.m_distance = ((*i)->GetPosition() - rayToLight.GetPosition()).length();
			hitsDetected.push_back(hitInfo);
		}
	}

	if (hitsDetected.size() > 0)
	{
		IntersectionRecord closestHit;
		closestHit.m_distance = std::numeric_limits<double>::max();

		for (auto i = hitsDetected.begin(); i != hitsDetected.end(); ++i)
		{
			if ((*i).m_distance >= 0 && (*i).m_distance < closestHit.m_distance)
			{
				closestHit = *i;
			}
		}

		if (closestHit.m_distance <= (rayToLight.GetPosition() - light->GetPosition()).length())
		{
			return false;
		}
	}

	return true;
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