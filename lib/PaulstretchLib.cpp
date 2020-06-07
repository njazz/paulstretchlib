#include "PaulstretchLib.hpp"

// original:
#include "ProcessedStretch.h"

#include "Player.h"

#include "Control.h"

// yet disabled
// #include "XMLwrapper.h"

#include <array>

#include <future>
#include <thread>
#include <chrono>

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

struct BatchProcessorImplementation {
};

struct PlayerImplementation {
};

struct StretchEngineImplementation {
    std::array<ProcessedStretch*, 2> _pStretchChannels = { (nullptr), (nullptr) };
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

void StretchEngine::SetParameters(const Configuration&) {}
const Configuration StretchEngine::Parameters() const
{
    return Configuration();
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

const Configuration LegacyController::Parameters()
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

PercentRegion LegacyController::RenderRange()
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
    auto t = std::thread([=](){RenderToFile(of);});
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

LegacyRenderTask::LegacyRenderTask(const std::string& in_, const std::string& out_, const PercentRegion& reg_, const Configuration& cfg_)
{
    _ctrl.OpenFile(in_);
    _ctrl.SetParameters(cfg_);
    _ctrl.SetRenderRange(reg_);
}

void LegacyRenderTask::StartRender()
{

    auto task = std::async(std::launch::async, [&] {
        _ctrl.RenderToFile(_output);
    });
}

void LegacyRenderTask::CancelRender()
{
    _ctrl.CancelRender();
}

float LegacyRenderTask::GetRenderPercent()
{
    return _ctrl.GetRenderPercent();
}

}; // namespace
