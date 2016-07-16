#include "BigPotSubtitleFactory.h"


BigPotSubtitleFactory::BigPotSubtitleFactory()
{
    _ext.push_back("ass");
    _ext.push_back("ssa");
    _ext.push_back("srt");
    _ext.push_back("txt");
}

BigPotSubtitleFactory::~BigPotSubtitleFactory()
{
}

BigPotSubtitle* BigPotSubtitleFactory::createSubtitle(const std::string& filename)
{
    BigPotSubtitle* ret = nullptr;
    auto ext = toLowerCase(getFileExt(filename));
    if (ext == "ass" || ext == "ssa")
    { ret = new BigPotSubtitleAss; }
    else if (ext == "srt" || ext == "txt")
    { ret = new BigPotSubtitleSrt; }
    if (ret)
    {
        //ret->init();
        ret->openSubtitle(filename);
    }
    else
    {
        ret = new BigPotSubtitle;
    }
    return ret;
}

std::string BigPotSubtitleFactory::lookForSubtitle(const std::string& filename)
{
    std::string str = "";
    bool b = false;
    //���Ĭ������
    for (auto& ext : _ext)
    {
        str = changeFileExt(filename, ext);
        if (fileExist(str))
        {
            return str;
        }
    }
    str = fingFileWithMainName(filename);
    if (!isSubtitle(str))
    { str = ""; }
    return str;
}


bool BigPotSubtitleFactory::tryOpenSubtitle(const std::string& filename)
{
    bool b = false;
    return b;
}

bool BigPotSubtitleFactory::isSubtitle(const std::string& filename)
{
    auto ext = getFileExt(filename);
    ext = toLowerCase(ext);
    //transform(ext.begin(), ext.end(), ext.begin(), tolower);
    bool b = false;
    for (auto& e : _ext)
    {
        if (e == ext)
        {
            b = true;
            break;
        }
    }
    return b;
}