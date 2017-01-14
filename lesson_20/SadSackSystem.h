#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "SceneLoader.h"


void CreateSadSack(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &pos);
void CreateShoot(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &pos);
void CreateTrooper(anax::World & m_world, const CModelPool & m_pool);


class CSadSackSystem
	: public anax::System<anax::Requires<CTransformComponent, CEnemyComponent, CSadSackComponent>>
{
public:
	CSadSackSystem() = default;

	void Update(float deltaSec);

private:
	float m_velocity = 0.1f;
};


class CShootSystem
	: public anax::System<anax::Requires<CTransformComponent, CEnemyComponent, CShootEnemyComponent>>
{
public:
	void Update(float deltaSec, anax::World &world, CModelPool &pool);

private:
	float m_velocity = 0.1f;
	float m_shootChance = 1.f / 900.f;
};


class CTrooperSystem
	: public anax::System<anax::Requires<CTransformComponent, CEnemyComponent, CTrooperComponent>>
{
public:
	void Update(float deltaSec, anax::World &world, CModelPool &pool);
};