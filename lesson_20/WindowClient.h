#pragma once
#include "libsystem/AbstractWindowClient.h"
#include "libsystem/MouseGrabber.h"
#include "libscene/ArrayObject.h"
#include "libscene/Camera.h"
#include "SceneLoader.h"
#include "RenderSystem.h"
#include "PlayerSystem.h"
#include "SadSackSystem.h"
#include "BulletSystem.h"
#include "CollisionSystem.h"
#include "GameState.h"
#include "HeartSystem.h"
#include "RotateSystem.h"
#include <vector>

class CWindowClient
        : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdate(float deltaSeconds) override;
    void OnDraw() override;
    bool OnKeyDown(const SDL_KeyboardEvent &) override;
    bool OnKeyUp(const SDL_KeyboardEvent &) override;
    bool OnMousePress(const SDL_MouseButtonEvent &) override;
    bool OnMouseMotion(const SDL_MouseMotionEvent &) override;
    bool OnMouseUp(const SDL_MouseButtonEvent &) override;

	void LoadModels();
	void SetStartMap();

private:
    // Данный VAO будет объектом по-умолчанию.
    // Его привязка должна произойти до первой привязки VBO.
    //  http://stackoverflow.com/questions/13403807/
    CArrayObject m_defaultVAO;
    anax::World m_world;
    CRenderSystem m_renderSystem;
	CPlayerSystem m_playerSystem;
	CSadSackSystem m_sadSackSystem;
	CBulletSystem m_bulletSystem;
	CCollisionSystem m_collisionSystem;
	CShootSystem m_shootSystem;
	CTrooperSystem m_trooperSystem;
	CGameState m_gameState;
	CHeartSystem m_heartSystem;
	CRotateSystem m_rotateSystem;

	CModelPool m_pool;

    CMouseGrabber m_mouseGrabber;
    CCamera m_camera;
};
