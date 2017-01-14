#include "stdafx.h"
#include "SceneLoader.h"
#include "json/json.hpp"
#include "Components.h"
#include <fstream>

using namespace nlohmann;
using namespace boost::filesystem;
using glm::vec3;

CSceneLoader::CSceneLoader(anax::World &world)
    : m_world(world)
{
}


void CSceneLoader::LoadSkybox(const boost::filesystem::path &path)
{
    CTexture2DAtlas atlas(path, m_assetLoader);
    std::vector<CFloatRect> rects;
    rects.resize(static_cast<unsigned>(CubeFace::NumFaces));
    rects[static_cast<unsigned>(CubeFace::Back)] = atlas.GetFrameRect("stars_bk.jpg");
	rects[static_cast<unsigned>(CubeFace::Front)] = atlas.GetFrameRect("stars_fr.jpg");
	rects[static_cast<unsigned>(CubeFace::Left)] = atlas.GetFrameRect("stars_lf.jpg");
	rects[static_cast<unsigned>(CubeFace::Right)] = atlas.GetFrameRect("stars_rt.jpg");
	rects[static_cast<unsigned>(CubeFace::Top)] = atlas.GetFrameRect("stars_up.jpg");
	rects[static_cast<unsigned>(CubeFace::Bottom)] = atlas.GetFrameRect("stars_dn.jpg");


    const CStaticGeometry cube = CTesselator::TesselateSkybox(rects);

    auto pModel = std::make_shared<CStaticModel3D>();
    pModel->m_pGeometry = cube.m_pGeometry;
    pModel->m_meshes.emplace_back();
    pModel->m_meshes.back().m_layout = cube.m_layout;
    pModel->m_materials.emplace_back();
    pModel->m_materials.back().pEmissive = atlas.GetTexture();

    anax::Entity skybox = m_world.createEntity();
    auto &mesh = skybox.addComponent<CMeshComponent>();
    mesh.m_category = CMeshComponent::Environment;
    mesh.m_pModel = pModel;
    skybox.addComponent<CTransformComponent>();
    skybox.activate();
}


CModelPool::CModelPool(const std::map<std::string, std::string>& absPaths)
{
	for (auto &path : absPaths)
	{
		AddModel(path);
	}
}

CStaticModel3DPtr CModelPool::GetModel(const std::string & modelName) const
{
	return m_modelsCache.at(modelName);
}

void CModelPool::AddModel(const std::pair<std::string, std::string> &absPath)
{
	CStaticModelLoader model(m_assetLoader);
	auto pModel = model.Load(absPath.second);
	m_modelsCache[absPath.first] = pModel;
}

