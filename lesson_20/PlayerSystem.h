#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "SceneLoader.h"

void CreatePlayer(anax::World &m_world, const CModelPool &m_pool);

class CPlayerSystem
	: public anax::System<anax::Requires<CTransformComponent, CControlComponent, CCanShootComponent, CFriendComponent>>
{
public:

	void Update(float deltaSec, anax::World &m_world, const CModelPool &m_pool);

	bool OnKeyDown(const SDL_KeyboardEvent &event);
	bool OnKeyUp(const SDL_KeyboardEvent &event);


private:
	std::set<unsigned> m_keysPressed;
	float m_lastShootTime = 0.f;
};