#include "AssetLoader.h"
#include <Windows.h>

AssetLoader::AssetLoader()
{
}

AssetLoader::~AssetLoader()
{
	UnloadAll();
}

void AssetLoader::Load(const std::string &filename,
	const std::string &assetId,
	const std::string &groupId)
{
	PendingAsset queuedAsset;
	queuedAsset.filename = filename;
	queuedAsset.assetId = assetId;
	queuedAsset.groupId = groupId;
	pendingAssets_.push_back(queuedAsset);
}

bool AssetLoader::IsAssetLoading(const std::string &assetId) const
{
	for (PendingAssetList::const_iterator pendingIt = pendingAssets_.begin(),
		end = pendingAssets_.end();
		pendingIt != end;
		++pendingIt)
	{
		if (pendingIt->assetId == assetId)
		{
			return true;
		}
	}

	return false;
}

bool AssetLoader::IsGroupLoading(const std::string &groupId) const
{
	for (PendingAssetList::const_iterator pendingIt = pendingAssets_.begin(),
		end = pendingAssets_.end();
		pendingIt != end;
		++pendingIt)
	{
		if (pendingIt->groupId == groupId)
		{
			return true;
		}
	}

	return false;
}

void AssetLoader::UnloadAsset(const std::string &assetId)
{
	AssetMap::iterator assetIt = loadedAssets_.find(assetId);
	if (assetIt != loadedAssets_.end())
	{
		DeleteAsset(assetIt);
	}
}

void AssetLoader::UnloadGroup(const std::string &groupId)
{
	std::list<AssetMap::iterator> assets;

	for (AssetMap::iterator assetIt = loadedAssets_.begin(),
		end = loadedAssets_.end();
		assetIt != end;
		++assetIt)
	{
		if (assetIt->second.groupId == groupId)
		{
			assets.push_back(assetIt);
		}
	}

	for (std::list<AssetMap::iterator>::iterator assetIt = assets.begin(),
		end = assets.end();
		assetIt != end;
		++assetIt)
	{
		DeleteAsset(*assetIt);
	}
}

void AssetLoader::UnloadAll()
{
	for (AssetMap::iterator assetIt = loadedAssets_.begin(),
		end = loadedAssets_.end();
		assetIt != end;
		++assetIt)
	{
		free(assetIt->second.data);
	}
}

bool AssetLoader::GetAsset(const std::string &assetId, Asset *asset) const
{
	AssetMap::const_iterator assetIt = loadedAssets_.find(assetId);
	if (assetIt == loadedAssets_.end())
	{
		asset->data = 0;
		asset->size = 0;
		asset->groupId = "";
		return false;
	}

	*asset = assetIt->second;
	return true;
}

void AssetLoader::Update()
{
	if (pendingAssets_.empty())
		return;

	PendingAsset assetToLoad = pendingAssets_.front();
	pendingAssets_.pop_front();
	LoadAsset(assetToLoad);
}

void AssetLoader::LoadAsset(const PendingAsset &source)
{
	HANDLE file = CreateFile(source.filename.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0);
	if (file == INVALID_HANDLE_VALUE)
		return;

	BY_HANDLE_FILE_INFORMATION fileInfo;
	ZeroMemory(&fileInfo, sizeof(fileInfo));
	GetFileInformationByHandle(file, &fileInfo);

	Asset loadedAsset;
	loadedAsset.size = fileInfo.nFileSizeLow;
	loadedAsset.data = malloc(loadedAsset.size);

	DWORD bytesRead = 0;
	BOOL fileRead = ReadFile(file,
		loadedAsset.data,
		loadedAsset.size,
		&bytesRead,
		0);
	if (fileRead && (bytesRead == loadedAsset.size))
	{
		loadedAssets_.insert(std::make_pair(source.assetId,
			loadedAsset));
	}

	CloseHandle(file);
}

void AssetLoader::DeleteAsset(const AssetMap::iterator &assetIt)
{
	free(assetIt->second.data);
	loadedAssets_.erase(assetIt);
}
