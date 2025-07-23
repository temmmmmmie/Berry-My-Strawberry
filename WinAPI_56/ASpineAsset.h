#pragma once
#include "Asset.h"
#include "spine/spine.h"

using namespace spine;
class ASpineAsset:
	public Asset
{
private:
	Atlas* m_atlas;
	SkeletonData* m_skeletonData;
	AnimationStateData* m_animationStateData;
	virtual int Load(const wstring& _FilePath) override { return 0; }
public:
	GET_SET(Atlas*, atlas);
	GET_SET(SkeletonData*, skeletonData);
	GET_SET(AnimationStateData*, animationStateData);
	int Load_(const String& _filepath);
private:
	ASpineAsset();
	virtual ~ASpineAsset();
	friend class AssetMgr;

};

