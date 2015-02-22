#pragma once

struct DeserializeData;
class WorldObject
{
public:
	enum WorldType
	{
		// types that can collide with each other
		CT_Sphere = 0,
		CT_Point,
		CT_Ray,
		CT_Plane,
		CT_InfinitePlane,

		// other types of objects
		CT_Image,
		CT_Camera,
		CT_Error,
		CT_Unknown
	};

	explicit WorldObject(WorldType inType);
	virtual ~WorldObject();
	virtual void Init(const DeserializeData& data) = 0;
	inline WorldType GetType() const { return m_type; }
private:
	WorldType m_type;
};

