#pragma once

#include "stdafx.h"
#include <anax/World.hpp>
#include <boost/filesystem/path.hpp>
#include "libscene/AssetLoader.h"
#include <utility>

class CSceneLoader
{
public:
    CSceneLoader(anax::World &world);

    // Загружает SkyBox из заданного атласа (PLIST + изображение).
    void LoadSkybox(const boost::filesystem::path &path);

private:
    anax::World &m_world;
    CAssetLoader m_assetLoader;
};


class CModelPool
{
public:
	CModelPool() = default;
	CModelPool(const std::map<std::string, std::string> &absPaths);
	void AddModel(const std::pair<std::string, std::string> &absPath);
	CStaticModel3DPtr GetModel(const std::string &modelName) const;

protected:
	

private:
	std::map<std::string, CStaticModel3DPtr> m_modelsCache;
	CAssetLoader m_assetLoader;
};

