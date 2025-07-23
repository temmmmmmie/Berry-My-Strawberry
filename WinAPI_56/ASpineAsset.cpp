#include "pch.h"
#include "ASpineAsset.h"
#include "SpineTextureLoader.h"

using namespace spine;
int ASpineAsset::Load_(const String& _filepath)
{
    SpineTextureLoader* loader = new SpineTextureLoader();
    String Buffer = {};
    Buffer.append(_filepath);
    Buffer.append(".atlas");
    m_atlas = new Atlas(Buffer, loader);
    if (m_atlas ->getPages().size() == 0) {
        printf("Failed to load atlas");
        delete m_atlas;
        return E_FAIL;
    }

    // Load the skeleton data
    SkeletonJson json(m_atlas);
    Buffer = {};
    Buffer.append(_filepath);
    Buffer.append(".json");
    m_skeletonData = json.readSkeletonDataFile(Buffer);
    if (!m_skeletonData) {
        printf("Failed to load skeleton data");
        delete m_atlas;
        return E_FAIL;
    }

    // Setup mix times
    m_animationStateData = new spine::AnimationStateData(m_skeletonData);
    m_animationStateData->setDefaultMix(0.1f);
    return S_OK;
}

ASpineAsset::ASpineAsset():
    m_atlas(nullptr), m_animationStateData(nullptr), m_skeletonData(nullptr)
{
}

ASpineAsset::~ASpineAsset()
{
    delete m_atlas;
    delete m_skeletonData;
    delete m_animationStateData;
}
