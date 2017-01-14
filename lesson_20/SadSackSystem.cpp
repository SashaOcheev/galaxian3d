#include "stdafx.h"
#include "SadSackSystem.h"
#include "BulletSystem.h"

#include <cstdlib>

using namespace std;

void CreateSadSack(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &pos)
{
	auto body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("sadsack"));
	AddTransform(body, glm::vec3(1.f), pos, { 1.57f, 3.14f, 3.14f });
	AddEnemy(body);
	AddSadSack(body);
	body.activate();
}

void CreateShoot(anax::World & m_world, const CModelPool & m_pool, const glm::vec3 & pos)
{
	auto body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("shoot"));
	AddTransform(body, glm::vec3(1.f), pos, { 1.57f, 3.14f, 3.14f });
	AddEnemy(body);
	AddShootEnemy(body);
	body.activate();
}

void CreateTrooper(anax::World & m_world, const CModelPool & m_pool)
{
	auto body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("trooper"));
	AddTransform(body, glm::vec3(1.f), glm::vec3(std::rand() % 18 - 9.f, 0.f, -20.f), { 1.57f, 3.14f, 3.14f });
	CTransformComponent& transform = body.getComponent<CTransformComponent>();
	AddEnemy(body);
	AddTrooper(body, 0.1f, 0.1f, 3.f, transform.m_position.x);
	CTrooperComponent& trooper = body.getComponent<CTrooperComponent>();
	body.activate();
}


void RedirectX(CTransformComponent& transform, float &m_velocity)
{
	//without explicit > and < it does not work correct
	if (transform.m_position.x > FLANK_BOUND)
	{
		m_velocity = -abs(m_velocity);
	}
	else if (transform.m_position.x < -FLANK_BOUND)
	{
		m_velocity = abs(m_velocity);
	}
}


void CSadSackSystem::Update(float deltaSec)
{
	auto entities = getEntities();
	for (auto &entity : entities) {
		RedirectX(entity.getComponent<CTransformComponent>(), m_velocity);
	}
	
	for (auto &entity : entities) {
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		transform.m_position.x += m_velocity;
	}
}

void CShootSystem::Update(float deltaSec, anax::World &world, CModelPool &pool)
{
	auto entities = getEntities();
	for (auto &entity : entities) {
		RedirectX(entity.getComponent<CTransformComponent>(), m_velocity);
	}

	for (auto &entity : entities) {
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		transform.m_position.x += m_velocity;
		if (float(std::rand()) / RAND_MAX <= m_shootChance)
		{
			CreateEnemyBullet(world, pool, transform.m_position);
		}
	}
}

void CTrooperSystem::Update(float deltaSec, anax::World & world, CModelPool & pool)
{
	auto entities = getEntities();
	for (auto &entity : entities) {
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		CTrooperComponent& trooper = entity.getComponent<CTrooperComponent>();
		if (abs(transform.m_position.x - trooper.start_x) > trooper.interval_x)
		{
			trooper.velocity_x = -trooper.velocity_x;
		}
		transform.m_position += glm::vec3(trooper.velocity_x, 0.f, trooper.velocity_z);

		if (transform.m_position.z > 15.f)
		{
			entity.kill();
		}

		if (float(std::rand()) / RAND_MAX <= 1.f / 450.f)
		{
			CreateEnemyBullet(world, pool, transform.m_position);
		}
	}

	if (float(std::rand()) / RAND_MAX <= 1.f / 450.f)
	{
		CreateTrooper(world, pool);
	}
}
