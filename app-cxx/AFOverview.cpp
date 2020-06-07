#include "AFOverview.hpp"
#include "audiofile.h"

struct AFOverviewImpl {
    AFfilehandle fileHandle = NULL;
};

#include "audiofile.h"

AFOverview::AFOverview()
{
    _impl = new AFOverviewImpl();
}

AFOverview::AFOverview(const AFOverview& src)
{
    {
        _impl = new AFOverviewImpl();
        *_impl = *src._impl;
    }
}
AFOverview& AFOverview::operator=(const AFOverview& src)
{
    {
        _impl = new AFOverviewImpl();
        *_impl = *src._impl;
    }
    return *this;
}
AFOverview::~AFOverview()
{
    delete _impl;
}

//

void AFOverview::_ReloadData()
{
    //    _data.resize(_dataSize);
    //    for (int i=0;i<_dataSize;i++)
    //        _data[i] = 0.1;

    if (!_impl->fileHandle)
        return;

    // TODO: needs fix!
    if (_scaleFraction == 0) {
        short int* buffer = new short int[_dataSize];

        afReadFrames(_impl->fileHandle, AF_DEFAULT_TRACK, buffer, _dataSize);

        //    _data = std::vector<float>(buffer,buffer+_dataSize);
        _data.resize(_dataSize);

        for (int i = 0; i < _dataSize; i++)
            _data[i] = float(buffer[i]) / 32768.;

        delete[] buffer;
    }

    else {
        _data.resize(_dataSize);
        for (int i = 0; i < _dataSize; i++) {
            AFframecount frame = float(i) / float(_dataSize) * _scaleFraction * _fileSize + ((1.0f-_scaleFraction)*_scrollFraction) * _fileSize;
            if (frame > _fileSize)
                frame = _fileSize;

            short int v = 0;
            afSeekFrame(_impl->fileHandle, AF_DEFAULT_TRACK, frame);
            afReadFrames(_impl->fileHandle, AF_DEFAULT_TRACK, &v, 1);
            _data[i] = float(v) / 32768.;
        }
    }
}

void AFOverview::OpenFile(const std::string fn)
{
    if (_impl->fileHandle)
        afCloseFile(_impl->fileHandle);

    //    auto fs = afNewFileSetup();
    _impl->fileHandle = afOpenFile(fn.c_str(), "r", 0);

    _fileSize = afGetFrameCount(_impl->fileHandle, AF_DEFAULT_TRACK);

    afSetVirtualChannels(_impl->fileHandle, AF_DEFAULT_TRACK, 2);

    _fileSize = afGetFrameCount(_impl->fileHandle, AF_DEFAULT_TRACK);
    //    info.nchannels=afGetVirtualChannels(_impl->fileHandle,AF_DEFAULT_TRACK);
    //    info.samplerate=(int) afGetRate(_impl->fileHandle,AF_DEFAULT_TRACK);
    //    info.currentsample=0;
    //    if (info.samplerate==0) return false;

    afSetVirtualSampleFormat(_impl->fileHandle, AF_DEFAULT_TRACK, AF_SAMPFMT_TWOSCOMP, 16);

    //    afFreeFileSetup(fs);

    _ReloadData();
}

void AFOverview::SetDataSize(const size_t& s)
{
    if (_dataSize == s)
        return;

    _dataSize = s;
    _ReloadData();
}

// 0..1, sample-to-sample .. full file
void AFOverview::SetScaleFraction(const float& f)
{
    _scaleFraction = f;
    if (_scaleFraction < 0)
        _scaleFraction = 0;
    if (_scaleFraction > 1)
        _scaleFraction = 1;

    _ReloadData();
}

void AFOverview::SetScrollFraction(const float& f){
    _scrollFraction = f;
    if (_scrollFraction < 0)
        _scrollFraction = 0;
    if (_scrollFraction > 1)
        _scrollFraction = 1;

    _ReloadData();
}

//
size_t AFOverview::FractionToViewCoord(const float& f)
{
    // TODO:
    if (_scaleFraction == 0)
        return _dataSize * f / 0.00001;
    
    auto ret = _dataSize * (f / _scaleFraction - (1-_scaleFraction)*_scrollFraction);
    if (ret>_dataSize)
        ret = _dataSize;
    if (ret<0)
        ret = 0;
    return ret;
}

float AFOverview::ViewCoordToFraction(const size_t& v)
{
    // TODO:
    return float(v) / _dataSize *( _scaleFraction - (1-_scaleFraction)*_scrollFraction);
}
