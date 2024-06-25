//#pragma once
//#include "Object/NetObject.hpp"
//
//class Projectile : public NetObject
//{
//	friend class TurretPlant;
//	USE_POOL(Projectile)
//public:
//	Projectile(uint64 id, const std::shared_ptr<class GameMap> map, const std::shared_ptr<NetObject> target);
//protected:
//	void BeginPlay() override;
//	void Tick() override;
//private:
//	Vector2DF m_targetPos;
//	std::weak_ptr<class GameMap> m_map;
//	std::weak_ptr<NetObject> m_targetObject;
//};
//
