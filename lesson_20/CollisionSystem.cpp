#include "stdafx.h"
#include "CollisionSystem.h"

using namespace std;
using namespace glm;


bool IsIntersects(CTransformComponent &transform1, CTransformComponent &transform2)
{
	return abs(transform1.m_position.z - transform2.m_position.z) < 0.5f
		&& abs(transform1.m_position.x - transform2.m_position.x) < 2.f;
}


void CCollisionSystem::Update(anax::World & world)
{
	auto entities = world.getEntities();

	for (auto &enemy : entities)
	{
		if (enemy.hasComponent<CEnemyComponent>())
		{
			for (auto &myFriend : entities)
			{
				if (myFriend.hasComponent<CFriendComponent>())
				{
					if (IsIntersects(enemy.getComponent<CTransformComponent>(), myFriend.getComponent<CTransformComponent>()))
					{
						unsigned &life1 = enemy.getComponent<CTransformComponent>().life;
						unsigned &life2 = myFriend.getComponent<CTransformComponent>().life;
						life1 -= 1;
						life2 -= 1;
						if (life1 <= 0)
						{
							enemy.kill();
						}

						if (life2 <= 0)
						{
							myFriend.kill();
						}
					}
				}
			}
		}
	}
}
