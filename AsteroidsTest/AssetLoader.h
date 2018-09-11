#ifndef ASSETLOADER_H_INCLUDED
#define ASSETLOADER_H_INCLUDED

#include <string>
#include <list>
#include <map>

class AssetLoader
{
public:
	AssetLoader();
	~AssetLoader();

	struct Asset
	{
		void *data;
		size_t size;
		std::string groupId;
	};

	void Load(const std::string &filename,
		const std::string &assetId,
		const std::string &groupId);
	bool IsAssetLoading(const std::string &assetId) const;
	bool IsGroupLoading(const std::string &groupId) const;

	void UnloadAsset(const std::string &assetId);
	void UnloadGroup(const std::string &groupId);
	void UnloadAll();

	bool GetAsset(const std::string &assetId, Asset *asset) const;

	void Update();

private:
	AssetLoader(const AssetLoader &);
	void operator=(const AssetLoader &);

	struct PendingAsset
	{
		std::string filename;
		std::string assetId;
		std::string groupId;
	};

	typedef std::list<PendingAsset> PendingAssetList;
	typedef std::map<std::string, Asset> AssetMap;

	void LoadAsset(const PendingAsset &source);
	void DeleteAsset(const AssetMap::iterator &assetIt);

	PendingAssetList pendingAssets_;
	AssetMap loadedAssets_;

};

#endif // ASSETLOADER_H_INCLUDED
