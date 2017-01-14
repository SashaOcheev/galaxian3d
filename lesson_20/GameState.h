#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "TimeController.h"
#include "SceneLoader.h"

void CreateWin(anax::World &m_world, const CModelPool &m_pool);
void CreateLose(anax::World &m_world, const CModelPool &m_pool);

enum class State
{
	WIN,
	LOSE,
	GOINGON
};

class CGameState
	: public anax::System<anax::Requires<CTransformComponent>>
{
public:
	CGameState() = default;

	void Update(anax::World &world, CModelPool &pool);
	State GetState() const;

private:
	State state = State::GOINGON;
};


void CreateHeart(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position);