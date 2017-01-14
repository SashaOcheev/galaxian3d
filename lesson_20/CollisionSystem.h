#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "TimeController.h"
#include "SceneLoader.h"

class CCollisionSystem
	: public anax::System<anax::Requires<CTransformComponent, CBulletComponent>>
{
public:
	CCollisionSystem() = default;

	void Update(anax::World &world);
};
