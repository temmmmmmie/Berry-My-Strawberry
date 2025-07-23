#pragma once
#include "video_reader.h"
#include <gl/GL.h>
class AVideo;
class ASound;
class VideoPlayer
{
	SINGLE(VideoPlayer);
private:
	map<wstring, AVideo*> m_VideoMap;
	map<wstring, ASound*> m_SoundMap;
	AVideo* m_Curvideo = nullptr;

	bool m_loop;
public:
	void AddVideo(const wstring& _key, AVideo* _video) { m_VideoMap.insert(make_pair(_key, _video)); }
	void AddVideoSound(const wstring& _key, ASound* _videosound) { m_SoundMap.insert(make_pair(_key, _videosound)); }
	void Play(const wstring& _key, bool _havesound, bool _repeat);
	void Stop();
	void Render();
};

