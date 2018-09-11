#ifndef ASSETMANAGER_HPP_INCLUDED
#define ASSETMANAGER_HPP_INCLUDED

#include "AssetManager.h"

template <typename ASSET>
AssetManager<ASSET>::AssetManager()
{
}

template <typename ASSET>
AssetManager<ASSET>::~AssetManager()
{
	for (AssetMap::iterator assetIt = assets_.begin(), end = assets_.end();
		assetIt != end;
		++assetIt)
	{
		ASSET::Destroy(assetIt->second);
	}
}

template <typename ASSET>
ASSET *AssetManager<ASSET>::Create(const std::string &assetId,
	const typename ASSET::CreateParams *params)
{
	ASSET *asset = 0;
	AssetMap::const_iterator existingAsset = assets_.find(assetId);
	if (existingAsset == assets_.end())
	{
		asset = ASSET::Create(params);
		assets_[assetId] = asset;
	}
	return asset;
}

template <typename ASSET>
ASSET *AssetManager<ASSET>::Get(const std::string &assetId) const
{
	ASSET *asset = 0;
	AssetMap::const_iterator existingAsset = assets_.find(assetId);
	if (existingAsset != assets_.end())
	{
		asset = existingAsset->second;
	}
	return asset;
}

template <typename ASSET>
void AssetManager<ASSET>::Destroy(const std::string &assetId)
{
	AssetMap::iterator existingAsset = assets_.find(assetId);
	if (existingAsset != assets_.end())
	{
		assets_.erase(existingAsset->second);
	}
}

#endif // ASSETMANAGER_HPP_INCLUDED
