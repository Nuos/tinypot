//����������
//˽�д�ǰ�»���
//���������»���
//ͨ����ʹ�ù���������ͨ����������д

#pragma once

#include "Engine.h"
#include "Config.h"

//���ܲ���ȫ

class BigPotBase
{
protected:
    Engine* engine_;
    Config* config_;
public:
    BigPotBase();
    ~BigPotBase() {};

    //void setFilePath(char *s) { BigPotString::setFilePath(s); }
    //static bool fileExist(const string& filename);
    //void safedelete(void* p){ if (p) delete p; p = nullptr; };
};

