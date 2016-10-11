//
// Created by ye on 16-8-30.
//

#ifndef ENCODER_CENCODER_H
#define ENCODER_CENCODER_H

#include <stdio.h>
extern "C"
{
#include </usr/local/ffmpeg/include/libavutil/opt.h>
#include </usr/local/ffmpeg/include/libavcodec/avcodec.h>
#include </usr/local/ffmpeg/include/libavformat/avformat.h>
};

#include <stdio.h>
#include <string>
using namespace std;
class CEncoder
{
public:
    CEncoder(int width,int height,const string outfile):in_w(width),in_h(height){
        this->out_file=new char[100];
        strcpy(this->out_file,outfile.c_str());
    }
    int encodeYuv(uint8_t* picture_buf);
    int flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index);

    int init();
    int endCode();

private:
    int in_w;
    int in_h;                              //Input data's width and height
    int count=0;


    AVFormatContext* pFormatCtx;
    AVOutputFormat* fmt;
    AVStream* video_st;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;
    AVPacket pkt;
    AVFrame* pFrame;

    char* out_file ;
};


#endif //ENCODER_CENCODER_H
