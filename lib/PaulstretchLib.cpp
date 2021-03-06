#include "PaulstretchLib.hpp"

// original:
#include "ProcessedStretch.h"

#include "Player.h"

#include "Control.h"

#include "LiteControl.h"

// yet disabled
// #include "XMLwrapper.h"

#include <array>

#include <future>
#include <thread>
#include <chrono>

#include "StringUtilities.hpp"

#include "JSONCodec.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "TextFileIO.hpp"

// ---
namespace PaulstretchLib {

constexpr RangeInfo ConfigurationInfo::stretch;
constexpr RangeInfo ConfigurationInfo::windowSize;
constexpr RangeInfo ConfigurationInfo::onsetSensitivity;

constexpr RangeInfo ConfigurationInfo::hFreq;
constexpr RangeInfo ConfigurationInfo::hBandwidth;
constexpr RangeInfo ConfigurationInfo::hNumberHarm;

constexpr RangeInfo ConfigurationInfo::psCents;

constexpr RangeInfo ConfigurationInfo::fsFreq;

constexpr RangeInfo ConfigurationInfo::oValues;

constexpr RangeInfo ConfigurationInfo::fFreq1;
constexpr RangeInfo ConfigurationInfo::fFreq2;
constexpr RangeInfo ConfigurationInfo::fFreqArbitrary;
constexpr RangeInfo ConfigurationInfo::fDamp;

constexpr RangeInfo ConfigurationInfo::tnAmount;
constexpr RangeInfo ConfigurationInfo::tnBandwidth;

constexpr RangeInfo ConfigurationInfo::spBandwidth;

constexpr RangeInfo ConfigurationInfo::cmPower;

constexpr RangeInfo ConfigurationInfo::binaural;

// ---

const std::string ToString(const FFTWindowType& v)
{
    switch (v) {
    case FFTWindowType_Rectangular:
        return "Rectangular";
    case FFTWindowType_Hamming:
        return "Hamming";
    case FFTWindowType_Hann:
        return "Hann";
    case FFTWindowType_Blackmann:
        return "Blackmann";
    case FFTWindowType_BlackmannHarris:
        return "BlackmannHarris";
    }
}

const bool ToFFTWindowType(FFTWindowType& obj, const std::string src)
{
    if (!src.compare("Rectangular")) {
        obj = FFTWindowType_Rectangular;
        return true;
    }
    if (!src.compare("Hamming")) {
        obj = FFTWindowType_Hamming;
        return true;
    }
    if (!src.compare("Hann")) {
        obj = FFTWindowType_Hann;
        return true;
    }
    if (!src.compare("Blackmann")) {
        obj = FFTWindowType_Blackmann;
        return true;
    }
    if (!src.compare("BlackmannHarris")) {
        obj = FFTWindowType_BlackmannHarris;
        return true;
    }
    return false;
}

const bool ToFFTWindowType(FFTWindowType& obj, const int& v)
{
    if (v >= 0 && v < 5) {
        obj = (FFTWindowType)v;
        return true;
    }
    return false;
};

// ---

struct BatchProcessorImplementation {
};

struct PlayerImplementation {
};

struct StretchEngineImplementation {
    std::array<ProcessedStretch*, 2> _pStretchChannels = { (nullptr), (nullptr) };
    Configuration _parameters;
};

// ---

const AbsoluteRegion PercentRegion::ToAbsolute(const float& length)
{
    AbsoluteRegion ret;
    return ret;
}

const PercentRegion AbsoluteRegion::ToPercent(const float& length)
{
    PercentRegion ret;
    return ret;
}

// ---
BatchProcessor::BatchProcessor()
{
    _impl = new BatchProcessorImplementation();
}

BatchProcessor::~BatchProcessor()
{
    delete _impl;
}
void BatchProcessor::OpenFiles(const std::vector<std::string>& names) {}

void BatchProcessor::OpenConfigurations(const std::vector<std::string>& names) {}

void BatchProcessor::SetRegions(const std::vector<Region>& reg) {}

void BatchProcessor::RenderFiles(const std::vector<std::string>& names) {}

// ---

std::string XMLConfigurationCodec::ToXMLString(const Configuration&) { return ""; }
Configuration XMLConfigurationCodec::FromXMLString(const std::string&) { return Configuration(); }

// ---

Configuration ConfigTools::Interpolate(const Configuration& a, const Configuration& b, float fraction)
{
    return Configuration();
}

// ---

void Configuration::ToFile(const std::string& f) const
{

    auto s = JSONStringCodec::ToJSONString(*this);
    TextFileIO::ToFile(f, s);
}

bool Configuration::FromFile(const std::string& f)
{
    auto s = TextFileIO::FromFile(f);
    return JSONStringCodec::FromJSONString(*this, s);
}

// ---
// convert

ProcessParameters ToPParameters(const Configuration& c)
{
    auto ret = ProcessParameters();

    ret.pitch_shift.enabled = c.pitchShift;
    ret.pitch_shift.cents = c.psCents;

    ret.octave.enabled = c.octaves;
    ret.octave.om2 = c.oValues[0];
    ret.octave.om1 = c.oValues[1];
    ret.octave.o0 = c.oValues[2];
    ret.octave.o1 = c.oValues[3];
    ret.octave.o15 = c.oValues[4];
    ret.octave.o2 = c.oValues[5];

    ret.freq_shift.enabled = c.freqShift;
    ret.freq_shift.Hz = c.fsFreq;

    ret.compressor.enabled = c.compress;
    ret.compressor.power = c.cmPower;

    ret.filter.enabled = c.filter;
    ret.filter.low = c.fFreq1;
    ret.filter.high = c.fFreq2;
    ret.filter.stop = c.fBandstop;
    ret.filter.hdamp = c.fDamp;

    ret.harmonics.enabled = c.harmonics;
    ret.harmonics.freq = c.hFreq;
    ret.harmonics.bandwidth = c.hBandwidth;
    ret.harmonics.nharmonics = c.hNumberHarm;
    ret.harmonics.gauss = c.hGauss;

    ret.spread.enabled = c.spread;
    ret.spread.bandwidth = c.spBandwidth;

    ret.tonal_vs_noise.enabled = c.tonalNoise;
    ret.tonal_vs_noise.preserve = c.tnAmount;
    ret.tonal_vs_noise.bandwidth = c.tnBandwidth;

    // todo: convert filter to FreeEdit
    // todo: convert stretch to FreeEdit

    return ret;
}

BinauralBeatsParameters ToBBParameters(const Configuration& c)
{
    auto ret = BinauralBeatsParameters();

    // todo: convert bb to FreeEdit;

    return ret;
};

Configuration FromPParameters(const ProcessParameters& p)
{
    return Configuration();
}

FFTWindow FromFFTWType(const FFTWindowType t)
{
    if (t == FFTWindowType_Rectangular)
        return W_RECTANGULAR;

    return W_RECTANGULAR;
}

// ---
Player::Player()
{
    _impl = new PlayerImplementation();
}

Player::~Player()
{
    delete _impl;
}

void Player::OpenFile(const std::string& name) {}
void Player::OpenConfiguration(const Configuration& cfg) {}

void Player::Start() {}
void Player::Stop() {}

void Player::Seek(float seconds) {}

// ---

StretchEngine::StretchEngine()
{
    _impl = new StretchEngineImplementation();
}
StretchEngine::~StretchEngine()
{
    delete _impl;
}

void StretchEngine::SetParameters(const Configuration&c) {
    _impl->_parameters = c;
}
const Configuration& StretchEngine::Parameters() const
{
    return _impl->_parameters;
}

void StretchEngine::ProcessBuffer(const std::vector<float>&) {}

// ---

struct LegacyControllerImplementation {
    Control _legacyControl;

    std::string _inputFilename;
    float _volume = 1;
    Configuration _cfg;
    PercentRegion _range;

    LegacyController::CallbackFn _onEndPlayback = []() {};
    LegacyController::CallbackFn _onFileOpenError = []() {};
    LegacyController::ErrorCallbackFn _onRenderError = [](const std::string&) {};
};

LegacyController::LegacyController()
{
    _impl = new LegacyControllerImplementation();

    SetParameters(_impl->_cfg);
}
LegacyController::~LegacyController()
{
    delete _impl;
}

LegacyController::LegacyController(const LegacyController& src)
{
    _impl = new LegacyControllerImplementation();

    *_impl = *src._impl;
};

LegacyController& LegacyController::operator=(const LegacyController& src)
{
    if (&src != this) {
        _impl = new LegacyControllerImplementation();

        *_impl = *src._impl;
    }
    return *this;
}

//
void LegacyController::Play()
{
    _impl->_legacyControl.startplay(false);
}
void LegacyController::Pause()
{
    _impl->_legacyControl.pauseplay();
}
void LegacyController::Stop()
{
    _impl->_legacyControl.stopplay();
}

//

void LegacyController::Seek(const float& f)
{
    _impl->_legacyControl.set_seek_pos(f);
}
const float LegacyController::GetSeek()
{
    return _impl->_legacyControl.get_seek_pos();
}

bool LegacyController::IsPlaying()
{
    return _impl->_legacyControl.playing();
}

void LegacyController::SetVolume(const float& v)
{
    _impl->_legacyControl.set_volume(v);
}
float LegacyController::Volume()
{
    return _impl->_volume;
}

// legacy file i/o removed (xml library)

bool LegacyController::OpenFile(const std::string& fn)
{
    _impl->_inputFilename = fn;
    auto ret = _impl->_legacyControl.set_input_filename(fn, FILE_WAV);
    if (!ret)
        _impl->_onFileOpenError();

    return ret;
}

void LegacyController::SetParameters(const Configuration& cfg)
{
    _impl->_cfg = cfg;

    auto stretch_v = ConfigurationInfo::Clamp(ConfigurationInfo::stretch, _impl->_cfg.stretch.staticValue);
    auto windowSize_v = ConfigurationInfo::Clamp(ConfigurationInfo::windowSize, _impl->_cfg.windowSize);
    auto onset_v = ConfigurationInfo::Clamp(ConfigurationInfo::onsetSensitivity, _impl->_cfg.onsetSensitivity);

    _impl->_legacyControl.set_stretch_direct_controls(stretch_v, windowSize_v, onset_v);

    _impl->_legacyControl.update_player_stretch();

    _impl->_legacyControl.set_window_type(FromFFTWType(_impl->_cfg.windowType));

    _impl->_legacyControl.ppar = ToPParameters(_impl->_cfg);
    _impl->_legacyControl.bbpar = ToBBParameters(_impl->_cfg);
    _impl->_legacyControl.update_process_parameters();
};

const Configuration& LegacyController::Parameters()
{
    return _impl->_cfg;
}

//

float LegacyController::GetRenderPercent()
{
    return _impl->_legacyControl.info.render_percent;
}
void LegacyController::CancelRender()
{
    _impl->_legacyControl.info.cancel_render = true;
}

//

void LegacyController::SetRenderRange(const PercentRegion& r)
{
    _impl->_range = r;
}

const PercentRegion& LegacyController::RenderRange()
{
    return _impl->_range;
}

void LegacyController::RenderToFile(const std::string& of)
{
    _impl->_legacyControl.info.cancel_render = false;

    auto err = _impl->_legacyControl.Render(_impl->_inputFilename, of, FILE_WAV, FILE_WAV, _impl->_range.startFraction, _impl->_range.endFraction);
    if (err.size())
        _impl->_onRenderError(err);
}

void LegacyController::RenderToFileAsync(const std::string& of)
{
    auto t = std::thread([=]() { RenderToFile(of); });
    t.detach();
}

//

void LegacyController::SetOnEndPlayback(const CallbackFn& fn)
{
    _impl->_onEndPlayback = fn;
}
void LegacyController::SetOnFileOpenError(const CallbackFn& fn)
{
    _impl->_onFileOpenError = fn;
}
void LegacyController::SetOnRenderError(const ErrorCallbackFn& fn)
{
    _impl->_onRenderError = fn;
}

// ---

// duplicate:

struct LegacyRenderControllerImplementation {
    LiteControl _legacyControl;

    std::string _inputFilename;
    float _volume = 1;
    Configuration _cfg;
    PercentRegion _range;

    LegacyRenderController::CallbackFn _onFileOpenError = []() {};
    LegacyRenderController::ErrorCallbackFn _onRenderError = [](const std::string&) {};
};

LegacyRenderController::LegacyRenderController()
{
    _impl = new LegacyRenderControllerImplementation();

    SetParameters(_impl->_cfg);
}
LegacyRenderController::~LegacyRenderController()
{
    delete _impl;
}

LegacyRenderController::LegacyRenderController(const LegacyRenderController& src)
{
    _impl = new LegacyRenderControllerImplementation();

    *_impl = *src._impl;
};

LegacyRenderController& LegacyRenderController::operator=(const LegacyRenderController& src)
{
    if (&src != this) {
        _impl = new LegacyRenderControllerImplementation();

        *_impl = *src._impl;
    }
    return *this;
}

bool LegacyRenderController::OpenFile(const std::string& fn)
{
    _impl->_inputFilename = fn;
    auto ret = _impl->_legacyControl.set_input_filename(fn, FILE_WAV);
    if (!ret)
        _impl->_onFileOpenError();

    return ret;
}

void LegacyRenderController::SetParameters(const Configuration& cfg)
{
    _impl->_cfg = cfg;

    auto stretch_v = ConfigurationInfo::Clamp(ConfigurationInfo::stretch, _impl->_cfg.stretch.staticValue);
    auto windowSize_v = ConfigurationInfo::Clamp(ConfigurationInfo::windowSize, _impl->_cfg.windowSize);
    auto onset_v = ConfigurationInfo::Clamp(ConfigurationInfo::onsetSensitivity, _impl->_cfg.onsetSensitivity);

    _impl->_legacyControl.set_stretch_direct_controls(stretch_v, windowSize_v, onset_v);

    _impl->_legacyControl.set_window_type(FromFFTWType(_impl->_cfg.windowType));

    _impl->_legacyControl.ppar = ToPParameters(_impl->_cfg);
    _impl->_legacyControl.bbpar = ToBBParameters(_impl->_cfg);
    
};

const Configuration LegacyRenderController::Parameters()
{
    return _impl->_cfg;
}

//

float LegacyRenderController::GetRenderPercent()
{
    return _impl->_legacyControl.info.render_percent;
}
void LegacyRenderController::CancelRender()
{
    _impl->_legacyControl.info.cancel_render = true;
}

//

void LegacyRenderController::SetRenderRange(const PercentRegion& r)
{
    _impl->_range = r;
}

PercentRegion LegacyRenderController::RenderRange()
{
    return _impl->_range;
}

void LegacyRenderController::RenderToFile(const std::string& of)
{
    _impl->_legacyControl.info.cancel_render = false;

    auto err = _impl->_legacyControl.Render(_impl->_inputFilename, of, FILE_WAV, FILE_WAV, _impl->_range.startFraction, _impl->_range.endFraction);
    if (err.size())
        _impl->_onRenderError(err);
}

void LegacyRenderController::RenderToFileAsync(const std::string& of)
{
    auto t = std::thread([=]() { RenderToFile(of); });
    t.detach();
}

//

void LegacyRenderController::SetOnFileOpenError(const CallbackFn& fn)
{
    _impl->_onFileOpenError = fn;
}
void LegacyRenderController::SetOnRenderError(const ErrorCallbackFn& fn)
{
    _impl->_onRenderError = fn;
}

// ---

LegacyRenderWorker::LegacyRenderWorker(const std::string& in_, const std::string& out_, const PercentRegion& reg_, const Configuration& cfg_)
{
    _ctrl.OpenFile(in_);
    _ctrl.SetParameters(cfg_);
    _ctrl.SetRenderRange(reg_);
    _output = out_;
    _done = false;
}

LegacyRenderWorker::LegacyRenderWorker(const RenderTaskSetup& s)
{
    //    SetTask(s);
    _ctrl.OpenFile(s.audioFile);
    _ctrl.SetParameters(s.configuration);
    _ctrl.SetRenderRange(s.region);
    _output = s.outputFile;
    _done = false;
}

// mutable:

void LegacyRenderWorker::SetTask(const RenderTaskSetup& s)
{
    _mutex.lock();
    _rendering.lock();

    _ctrl.OpenFile(s.audioFile);
    _ctrl.SetParameters(s.configuration);
    _ctrl.SetRenderRange(s.region);
    _output = s.outputFile;
    
    _done = false;

    _rendering.unlock();
    _mutex.unlock();
}

LegacyRenderWorker::LegacyRenderWorker()
{
    _done = true;
}

void LegacyRenderWorker::StartRender()
{
    if (_done)
        return;
    
    auto onStartRender = [&]() {
        _mutex.lock();
        _rendering.lock();
        _mutex.unlock();
    };

    auto onTaskDone = [&]() {
        _mutex.lock();
        _done = true;
        _rendering.unlock();
        _mutex.unlock();
    };

    auto t = std::thread([=]() {
        onStartRender();
        _ctrl.RenderToFile(_output);
        onTaskDone();
    });

    t.detach();
}

const bool LegacyRenderWorker::IsDone()
{
    bool ret;
    _mutex.lock();
    ret = _done;
    _mutex.unlock();
    return ret;
}

void LegacyRenderWorker::CancelRender()
{
    if (_done)
        return;
    _ctrl.CancelRender();
}

float LegacyRenderWorker::GetRenderPercent()
{
    return _ctrl.GetRenderPercent();
}

// ---

void BatchProcessorLegacyController::_ScheduleTask(const RenderTaskSetup& t)
{
    bool wait = true;
    while (wait) {
        auto w = _GetAvailableWorker();
        if (w != nullptr)
        {
            printf("schedule task: %s\n", t.outputFile.c_str());
            w->SetTask(t);
            w->StartRender();
        }
        wait = (w == nullptr);
    }
    printf("schedule task: done\n");
}
LegacyRenderWorkerPtr BatchProcessorLegacyController::_GetAvailableWorker()
{
    for (auto& e : _workers)
        if (e->IsDone())
            return e;

    return nullptr;
}

//
BatchProcessorLegacyController::BatchProcessorLegacyController()
{
    for (int i = 0; i < std::thread::hardware_concurrency(); i++)
        _workers.push_back(std::make_shared<LegacyRenderWorker>());
}

void BatchProcessorLegacyController::SetData(const BatchData& data)
{
    _data = data;
    _UpdateTaskList();
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

std::string BatchProcessorLegacyController::MakeOutputFilename(const std::string& file, const std::string& cfg, const PercentRegion& region, const std::string& outFolder)
{
    // TODO
    using namespace StringUtilities;

    auto lf = SplitStringWithDelimiter(file, ".");
    lf.pop_back();
    auto ln = JoinStringsWithDelimiter(lf, ".");

    auto cfgName = GetFileName(cfg);

    std::string regionName = "FULL";

    if ((region.startFraction > 0) || (region.endFraction < 1))
        // TODO:
        regionName = "PART_"+to_string_with_precision(region.startFraction)+"_"+to_string_with_precision(region.endFraction);

    return ln + "_" + cfgName + "_" + regionName + ".wav";
}

void BatchProcessorLegacyController::_UpdateTaskList()
{
    _taskList.data.clear();
    
    printf("update task list\n");
    
    int idx = 0;
    for (const auto& infile : _data.inputFiles) {
        printf("input file %s\n", infile.c_str());
        for (const auto& incfg : _data.configurations) {
            printf("cfg %i\n", idx);
            for (const auto& inreg : _data.regions) {
                printf("region %f %f\n", inreg.startFraction, inreg.endFraction);
                RenderTaskSetup setup;
                setup.audioFile = infile;
                std::string incfgName = "cfg"+std::to_string(idx);
                idx++;
                setup.outputFile = MakeOutputFilename(infile, incfgName, inreg, _data.outputFolder);
                setup.region = inreg;
                setup.configuration = incfg;//Configuration(); // TODO: load from file: incfg;
                _taskList.data.push_back(setup);
                
                printf("added task\n");
            }
        }
    }
}

void BatchProcessorLegacyController::RenderBatchAsync()
{
    printf("render batch\n");
    // extra:
    _UpdateTaskList();

    _doneCounter = 0;
    _isRendering = true;

    // ---
    for (auto& e : _taskList.data) {
        printf("task:\n");
        printf("file %s\n", e.audioFile.c_str());
        
        _ScheduleTask(e);
        _doneCounter++;
    }
}

void BatchProcessorLegacyController::CancelRender()
{
    for (auto& e : _workers)
        e->CancelRender();
}

size_t BatchProcessorLegacyController::GetActiveWorkerCount() { return _workers.size(); }
float BatchProcessorLegacyController::GetWorkerRenderPercent(const size_t& idx)
{
    if (idx >= _workers.size())
        return 0.;

    return _workers[idx]->GetRenderPercent();
}

size_t BatchProcessorLegacyController::GetTotalTasks() { return _taskList.data.size(); }
size_t BatchProcessorLegacyController::GetDoneTasks() { return _doneCounter; }
size_t BatchProcessorLegacyController::GetRemainingTasks() { return _taskList.data.size() - _doneCounter; }

// ---

void BatchData::ToFile(const std::string& f)
{

    auto s = JSONStringCodec::ToJSONString(*this);
    TextFileIO::ToFile(f, s);

}
bool BatchData::FromFile(const std::string& f)
{

    auto s = TextFileIO::FromFile(f);
    return JSONStringCodec::FromJSONString(*this, s);
}
}; // namespace
