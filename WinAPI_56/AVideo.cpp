#include "pch.h"
#include "AVideo.h"

#include "Engine.h"
#include "TimeMgr.h"
#include <malloc.h>

AVideo::AVideo()
{
}

AVideo::~AVideo()
{
   if(frame_data != nullptr) _aligned_free(frame_data);

}

int AVideo::Load(const wstring& _FilePath)
{
	if(video_reader_open(&vr_state, _FilePath) == 0) return E_FAIL;
    // Generate texture
    glGenTextures(1, &Video_Tex);
    glBindTexture(GL_TEXTURE_2D, Video_Tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Allocate frame buffer
    constexpr int ALIGNMENT = 128;
    const int frame_width = vr_state.width;
    const int frame_height = vr_state.height;
    frame_data = (uint8_t*)_aligned_malloc(frame_width * frame_height * 4, ALIGNMENT);
    if (frame_data == NULL) {
        printf("Couldn't allocate frame buffer\n");
        return E_FAIL;
    }
    Filepath = _FilePath;
    return S_OK;
}
