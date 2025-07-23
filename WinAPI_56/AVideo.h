#pragma once
#include "Asset.h"
#include "video_reader.h"

#include <GL/gl.h>
class AVideo:
	public Asset
{
private :
	VideoReaderState vr_state;
	GLuint Video_Tex;
	uint8_t* frame_data;

	wstring Filepath;
public:
	VideoReaderState& GetVideoReader() { return vr_state; }
	wstring& GetFilePath() { return Filepath; }
	uint8_t* Getframedata() { return frame_data; }
	GLuint& GetVideoTex() { return Video_Tex; }
	virtual int Load(const wstring& _FilePath) override;
private:
	AVideo();
	virtual ~AVideo();
	friend class AssetMgr;
};

