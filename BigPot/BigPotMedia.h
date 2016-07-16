#pragma once

#include "BigPotBase.h"
#include "BigPotStream.h"
#include "BigPotStreamAudio.h"
#include "BigPotStreamVideo.h"
#include "BigPotStreamSubtitle.h"
#include "BigPotString.h"

//#include "BigPotSubtitle.h"


class BigPotMedia : public BigPotBase
{
public:
    BigPotMedia();
    virtual ~BigPotMedia();
private:
    BigPotStreamVideo* _streamVideo = nullptr;
    BigPotStreamAudio* _streamAudio = nullptr;
    BigPotStreamSubtitle* _streamSubtitle = nullptr;
    int _extAudioFrame = 1; //�����ѹһ֡��Ƶ����ʱ��Ƶ�ߴ�ܴ󣬿��ܵ�����Ƶ�������
private:
    int _count = 0;
    int _totalTime = 0;
    int _lastdts = 0;
    int _timebase = 0;
    bool _seeking = false;
public:
    BigPotStreamVideo* getVideo() { return _streamVideo; };
    BigPotStreamAudio* getAudio() { return _streamAudio; };
    int decodeFrame();
    int openFile(const std::string& filename);
    int getAudioTime();
    int getVideoTime();
    int seekTime(int time, int direct = 1, int reset = 0);
    int seekPos(double pos, int direct = 1, int reset = 0);
    int showVideoFrame(int time);
    int getTotalTime() { return _totalTime; }
    int getTime();
    void destroy();
    bool isMedia();
    void setPause(bool pause);
};

