#include "pch.h"
#include "video_reader.h"

// av_err2str returns a temporary array. This doesn't work in gcc.
// This function can be used as a replacement for av_err2str.
static const char* av_make_error(int errnum) {
    static char str[AV_ERROR_MAX_STRING_SIZE];
    memset(str, 0, sizeof(str));
    return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
}


bool video_reader_open(VideoReaderState* state, wstring filename) {
    // Unpack members of state
    auto& width = state->width;
    auto& height = state->height;
    auto& time_base = state->time_base;
    auto& av_format_ctx = state->av_format_ctx;
    auto& av_codec_ctx = state->av_codec_ctx;
    auto& video_stream_index = state->video_stream_index;
    auto& av_frame = state->av_frame;
    auto& av_packet = state->av_packet;

    // Open the file using libavformat
    av_format_ctx = avformat_alloc_context();
    if (!av_format_ctx) {
        printf("Couldn't created AVFormatContext\n");
        return false;
    }
    wstring buffer = filename;
    char str[256];
    WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), -1, str, 256, NULL, NULL);
    if (avformat_open_input(&av_format_ctx, str, NULL, NULL) != 0) {
        printf("Couldn't open video file\n");
        return false;
    }

    // Find the first valid video stream inside the file
    video_stream_index = -1;
    AVCodecParameters* av_codec_params = nullptr;
    AVCodec* av_codec = nullptr;
    for (int i = 0; i < av_format_ctx->nb_streams; ++i) {
        av_codec_params = av_format_ctx->streams[i]->codecpar;
        av_codec = const_cast<AVCodec*>(avcodec_find_decoder(av_codec_params->codec_id));
        if (!av_codec) {
            continue;
        }
        if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            width = av_codec_params->width;
            height = av_codec_params->height;
            time_base = av_format_ctx->streams[i]->time_base;
            break;
        }
    }
    if (video_stream_index == -1) {
        printf("Couldn't find valid video stream inside file\n");
        return false;
    }

    // Set up a codec context for the decoder
    av_codec_ctx = avcodec_alloc_context3(av_codec);
    if (!av_codec_ctx) {
        printf("Couldn't create AVCodecContext\n");
        return false;
    }
    if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
        printf("Couldn't initialize AVCodecContext\n");
        return false;
    }
    if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
        printf("Couldn't open codec\n");
        return false;
    }

    av_frame = av_frame_alloc();
    if (!av_frame) {
        printf("Couldn't allocate AVFrame\n");
        return false;
    }
    av_packet = av_packet_alloc();
    if (!av_packet) {
        printf("Couldn't allocate AVPacket\n");
        return false;
    }

    return true;
}

bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer, int64_t* pts) {
    auto& width = state->width;
    auto& height = state->height;
    auto& av_format_ctx = state->av_format_ctx;
    auto& av_codec_ctx = state->av_codec_ctx;
    auto& video_stream_index = state->video_stream_index;
    auto& av_frame = state->av_frame;
    auto& av_packet = state->av_packet;
    auto& sws_scaler_ctx = state->sws_scaler_ctx;

    int response;

    // �������� �д� ����
    while (av_read_frame(av_format_ctx, av_packet) >= 0) {
        if (av_packet->stream_index != video_stream_index) {
            av_packet_unref(av_packet);
            continue;
        }

        response = avcodec_send_packet(av_codec_ctx, av_packet);
        av_packet_unref(av_packet); // �̰� �׻� ȣ��

        if (response < 0) {
            printf("Failed to decode packet: %s\n", av_make_error(response));
            return false;
        }

        response = avcodec_receive_frame(av_codec_ctx, av_frame);
        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
            continue;
        }
        else if (response < 0) {
            printf("Failed to receive frame: %s\n", av_make_error(response));
            return false;
        }

        // ���������� �������� ���� ���
        *pts = av_frame->pts;

        // �����Ϸ� �ʱ�ȭ (���� 1ȸ)
        if (!sws_scaler_ctx) {
            auto source_pix_fmt = av_codec_ctx->pix_fmt;
            switch (av_codec_ctx->pix_fmt) {
            case AV_PIX_FMT_YUVJ420P: source_pix_fmt = AV_PIX_FMT_YUV420P; break;
            case AV_PIX_FMT_YUVJ422P: source_pix_fmt = AV_PIX_FMT_YUV422P; break;
            case AV_PIX_FMT_YUVJ444P: source_pix_fmt = AV_PIX_FMT_YUV444P; break;
            case AV_PIX_FMT_YUVJ440P: source_pix_fmt = AV_PIX_FMT_YUV440P; break;
            default: break;
            }

            sws_scaler_ctx = sws_getContext(width, height, source_pix_fmt,
                width, height, AV_PIX_FMT_RGB0,
                SWS_BILINEAR, nullptr, nullptr, nullptr);
            if (!sws_scaler_ctx) {
                printf("Failed to initialize sws scaler\n");
                return false;
            }
        }

        uint8_t* dest[4] = { frame_buffer, nullptr, nullptr, nullptr };
        int dest_linesize[4] = { width * 4, 0, 0, 0 };
        sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize,
            0, height, dest, dest_linesize);

        sws_freeContext(sws_scaler_ctx);
        return true; // ���� ������ ��ȯ
    }

    // ���⿡ �����ϸ� av_read_frame() == EOF
    return false;
}


bool video_reader_seek_frame(VideoReaderState* state, int64_t ts) {
    
    // Unpack members of state
    auto& av_format_ctx = state->av_format_ctx;
    auto& av_codec_ctx = state->av_codec_ctx;
    auto& video_stream_index = state->video_stream_index;
    auto& av_packet = state->av_packet;
    auto& av_frame = state->av_frame;
    
    av_seek_frame(av_format_ctx, video_stream_index, ts, AVSEEK_FLAG_BACKWARD);
    avcodec_flush_buffers(av_codec_ctx);

    // av_seek_frame takes effect after one frame, so I'm decoding one here
    // so that the next call to video_reader_read_frame() will give the correct
    // frame
    int response;
    while (av_read_frame(av_format_ctx, av_packet) >= 0) {
        if (av_packet->stream_index != video_stream_index) {
            av_packet_unref(av_packet);
            continue;
        }

        response = avcodec_send_packet(av_codec_ctx, av_packet);
        if (response < 0) {
            printf("Failed to decode packet: %s\n", av_make_error(response));
            return false;
        }

        response = avcodec_receive_frame(av_codec_ctx, av_frame);
        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
            av_packet_unref(av_packet);
            continue;
        } else if (response < 0) {
            printf("Failed to decode packet: %s\n", av_make_error(response));
            return false;
        }

        av_packet_unref(av_packet);
        break;
    }
    return true;
}

void video_reader_close(VideoReaderState* state) {
    avformat_close_input(&state->av_format_ctx);
    avformat_free_context(state->av_format_ctx);
    av_frame_free(&state->av_frame);
    av_packet_free(&state->av_packet);
    avcodec_free_context(&state->av_codec_ctx);
}
