#include "stdafx.h"
#include "GameState.h"

using namespace std;
using namespace glm;

void CreateWin(anax::World &m_world, const CModelPool &m_pool)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("win"));
	AddTransform(body, glm::vec3(1.f), glm::vec3(0.f, 2.f, 5.f), { 1.57f, 3.14f, 0.f });
	AddRotate(body, glm::vec3(0, 0, 0.025));
	body.activate();
}

void CreateLose(anax::World &m_world, const CModelPool &m_pool)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("lose"));
	AddTransform(body, glm::vec3(1.f), glm::vec3(0.f, 2.f, 5.f), { 1.57f, 3.14f, 0.f });
	AddRotate(body, glm::vec3(0, 0, 0.025));
	body.activate();
}

void CGameState::Update(anax::World & world, CModelPool &pool)
{
	if (state != State::GOINGON)
	{
		return;
	}
	auto entities = world.getEntities();
	bool hasEnemy = false;
	bool hasFriend = false;

	for (auto entity : entities)
	{
		if (entity.hasComponent<CEnemyComponent>())
		{
			hasEnemy = true;
		}
		if (entity.hasComponent<CFriendComponent>())
		{
			hasFriend = true;
		}
	}

	if (!hasEnemy)
	{
		state = State::WIN;
		CreateWin(world, pool);
		return;
	}
	if (!hasFriend)
	{
		state = State::LOSE;
		CreateLose(world, pool);
		return;
	}
}

State CGameState::GetState() const
{
	return state;
}
