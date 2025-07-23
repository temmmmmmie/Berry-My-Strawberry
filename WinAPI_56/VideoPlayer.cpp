#include "pch.h"
#include "VideoPlayer.h"

#include "Engine.h"
#include "TimeMgr.h"

#include "AVideo.h"
#include "ASound.h"
#include <chrono>
#include <thread>

void VideoPlayer::Stop()
{
    if (m_Curvideo) {
        glDeleteTextures(1, &m_Curvideo->GetVideoTex());
        video_reader_close(&m_Curvideo->GetVideoReader());
        m_Curvideo = nullptr;
    }
}
void VideoPlayer::Play(const wstring& _key, bool _havesound, bool _repeat)
{
    m_Curvideo = m_VideoMap.find(_key)->second;
    if (_havesound) {
        ASound* pBGM = m_SoundMap.find(_key)->second;
        if (pBGM) {
            pBGM->SetVolume(100);
            pBGM->Play(false);
        }
    }
    m_loop = _repeat;
    m_Curvideo->Load(m_Curvideo->GetFilePath());
}
VideoPlayer::VideoPlayer() {};
VideoPlayer::~VideoPlayer() {
    map<wstring, ASound*>::iterator iter = m_SoundMap.begin();
    for (; iter != m_SoundMap.end(); ++iter)
    {
        delete iter->second;
    }
};

void VideoPlayer::Render()
{
    if (m_Curvideo == nullptr) return;
    static auto playback_start_time = chrono::steady_clock::now();
    Vec2 resol = Engine::GetInst()->GetResolution();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up orphographic projection

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Engine::GetInst()->GetResolution().x, Engine::GetInst()->GetResolution().y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glColor4f(1, 1, 1, 1.0f);

    auto vr_state = m_Curvideo->GetVideoReader();
    // Read a new frame and load it into texture
    int64_t pts;
    if (!video_reader_read_frame(&vr_state, m_Curvideo->Getframedata(), &pts)) {
        if (m_loop) {
            video_reader_seek_frame(&vr_state, 0);
            playback_start_time = chrono::steady_clock::now();
        }
        else
        {
            glDeleteTextures(1, &m_Curvideo->GetVideoTex());
            m_Curvideo = nullptr;
            video_reader_close(&vr_state);
            return;
        }
    }
    double pt_in_seconds = pts * (double)vr_state.time_base.num / (double)vr_state.time_base.den;
     //현재 경과 시간 계산
    auto now = chrono::steady_clock::now();
    chrono::duration<double> elapsed = now - playback_start_time;

    // 프레임 시간보다 남았다면 대기
    if (pt_in_seconds > elapsed.count()) {
        this_thread::sleep_for(chrono::duration<double>(pt_in_seconds - elapsed.count()));
    }

    glBindTexture(GL_TEXTURE_2D, m_Curvideo->GetVideoTex());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, vr_state.width, vr_state.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Curvideo->Getframedata());

    // Render whatever you want
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Curvideo->GetVideoTex());
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2i(0, 0);
    glTexCoord2d(1, 0); glVertex2i(resol.x, 0);
    glTexCoord2d(1, 1); glVertex2i(resol.x, resol.y);
    glTexCoord2d(0, 1); glVertex2i(0, resol.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
