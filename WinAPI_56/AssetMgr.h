#pragma once


class ATexture;
class ASprite;
class AFlipbook;
class AVideo;
class ASound;
class AssetMgr
{
	SINGLE(AssetMgr);
private:
	map<wstring, ATexture*>		m_mapTex;
	map<wstring, ASprite*>		m_mapSprite;
	map<wstring, AFlipbook*>	m_mapFlipbook;
	map<wstring, AVideo*>	m_mapVideo;
	map<wstring, ASound*>		m_mapSound;

	IDirectSound8* m_SoundDevice;	// 사운드 카드 제어	
	ASound* m_BGM;			// 배경음으로 지정된 사운드
public:
	void Init();
	void RegisterToBGM(ASound* _BGM);

	ATexture* FindTexture(const wstring& _Key);
	ATexture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	ATexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);

	AVideo* FindVideo(const wstring& _Key);
	AVideo* LoadVideo(const wstring& _Key, const wstring& _RelativePathWOExtension, const wstring& _vidformet);
	
	ASprite* FindSprite(const wstring& _Key);
	ASprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	int AddSprite(const wstring& _Key, ASprite* _Sprite);

	AFlipbook* FindFlipbook(const wstring& _Key);
	AFlipbook* LoadFlipbook(const wstring& _Key, const wstring& _RelativePath);
	int AddFlipbook(const wstring& _Key, AFlipbook* _Sprite);

	ASound* FindSound(const wstring& _Key);
	ASound* LoadSound(const wstring& _Key, const wstring& _RelativePath);

	IDirectSound8* GetSoundDevice() { return m_SoundDevice; }

private:
	void LoadInitAsset();
	void CreateSpriteAndFlipbook(ATexture* _Atlas, const wstring& _Key, Vec2 _LeftTop, Vec2 _Slice, int _Count);
};

