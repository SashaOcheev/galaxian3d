#include "stdafx.h"
#include "WindowClient.h"
#include "includes/opengl-common.hpp"
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;

namespace
{
const vec3 CAMERA_EYE = { 0, 16, 8 };
const vec3 CAMERA_AT = {0, 0, 0};
const vec3 CAMERA_UP = {0, 1, 0};
const vec4 SUNLIGHT_DIRECTION = {0, -1, 0, 0};
const vec4 WHITE_RGBA = {1, 1, 1, 1};
const vec4 FADED_WHITE_RGBA = {0.3f, 0.3f, 0.3f, 1.0f};
const char SKYBOX_PLIST[] = "res/static_scene/skybox.plist";

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

glm::mat4 MakeProjectionMatrix(const glm::ivec2 &size)
{
    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;

    return glm::perspective(fieldOfView, aspect, zNear, zFar);
}
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
    , m_defaultVAO(CArrayObject::do_bind_tag())
    , m_mouseGrabber(window)
    , m_camera(CAMERA_EYE, CAMERA_AT, CAMERA_UP)
{
    const vec4 BLACK_RGBA = {0, 0, 0, 1};
    const float CAM_SPEED = 20;

    window.SetBackgroundColor(BLACK_RGBA);
    SetupOpenGLState();

    m_camera.SetMoveSpeed(CAM_SPEED);
    m_renderSystem.SetupLight0(SUNLIGHT_DIRECTION, WHITE_RGBA, FADED_WHITE_RGBA);

    CSceneLoader loader(m_world);
	
	LoadModels();
	SetStartMap();

    loader.LoadSkybox(SKYBOX_PLIST);

    // Добавляем систему, отвечающую за рендеринг планет.
    m_world.addSystem(m_renderSystem);
	m_world.addSystem(m_playerSystem);
	m_world.addSystem(m_sadSackSystem);
	m_world.addSystem(m_bulletSystem);
	m_world.addSystem(m_collisionSystem);
	m_world.addSystem(m_shootSystem);
	m_world.addSystem(m_trooperSystem);
	m_world.addSystem(m_gameState);
	m_world.addSystem(m_heartSystem);
	m_world.addSystem(m_rotateSystem);
	

    // После активации новых сущностей или деактивации,
    //  а при добавления новых систем следует
    //  вызывать refresh() у мира.
    m_world.refresh();
}

void CWindowClient::OnUpdate(float deltaSeconds)
{
	m_gameState.Update(m_world, m_pool);
	m_rotateSystem.Update();
	if (m_gameState.GetState() == State::GOINGON)
	{
		m_playerSystem.Update(deltaSeconds, m_world, m_pool);
		m_sadSackSystem.Update(deltaSeconds);
		m_bulletSystem.Update(deltaSeconds);
		m_collisionSystem.Update(m_world);
		m_shootSystem.Update(deltaSeconds, m_world, m_pool);
		m_trooperSystem.Update(deltaSeconds, m_world, m_pool);
		m_heartSystem.Update(deltaSeconds, m_world);
	}

	m_world.refresh();
}

void CWindowClient::OnDraw()
{
    const glm::ivec2 windowSize = GetWindow().GetWindowSize();

    const mat4 view = m_camera.GetViewMat4();
    const mat4 proj = MakeProjectionMatrix(windowSize);

    glViewport(0, 0, windowSize.x, windowSize.y);
    m_renderSystem.Render(view, proj);
}

bool CWindowClient::OnKeyDown(const SDL_KeyboardEvent &event)
{
	m_playerSystem.OnKeyDown(event);
    return m_camera.OnKeyDown(event);
}

bool CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_playerSystem.OnKeyUp(event);
    return m_camera.OnKeyUp(event);
}

bool CWindowClient::OnMousePress(const SDL_MouseButtonEvent &event)
{
    return m_camera.OnMousePress(event);
}

bool CWindowClient::OnMouseMotion(const SDL_MouseMotionEvent &event)
{
    return m_mouseGrabber.OnMouseMotion(event)
            || m_camera.OnMouseMotion(event);
}

bool CWindowClient::OnMouseUp(const SDL_MouseButtonEvent &event)
{
    return m_camera.OnMouseUp(event);
}

void CWindowClient::LoadModels()
{
	m_pool.AddModel(std::make_pair<std::string, std::string>("player", "res/static_scene/Drone/Drone.dae"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("bullet", "res/static_scene/AIM120D.dae"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("shoot", "res/static_scene/Drone/Drone.dae"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("sadsack", "res/static_scene/Drone/Drone.dae"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("trooper", "res/static_scene/Drone/Drone.dae"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("heart", "res/static_scene/HEART/Human Heart.obj"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("win", "res/static_scene/WIN/cup.obj"));
	m_pool.AddModel(std::make_pair<std::string, std::string>("lose", "res/static_scene/LOSE/skull.3ds"));
}

void CWindowClient::SetStartMap()
{
	CreatePlayer(m_world, m_pool);

	int i = -1;
	for (; i > 4 * -3; i -= 3)
	{
		for (int j = -12; j < -12 + 5 * 6; j += 6)
		{
			CreateSadSack(m_world, m_pool, glm::vec3(j, 0, i));
		}
	}


	for (; i > 6 * -3; i -= 3)
	{
		for (int j = -12; j < -12 + 5 * 6; j += 6)
		{
			CreateShoot(m_world, m_pool, glm::vec3(j, 0, i));
		}
	}

	CreateHeart(m_world, m_pool, glm::vec3(6, 1, 9.3f));
	CreateHeart(m_world, m_pool, glm::vec3(8, 1, 9.3f));
	CreateHeart(m_world, m_pool, glm::vec3(10, 1, 9.3f));

	
}
