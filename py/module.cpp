
#include <pybind11/pybind11.h>

#include "PaulstretchLib.hpp"

namespace py = pybind11;
using namespace PaulstretchLib;

// extra:

PYBIND11_MODULE(paulstretchpy, m)
{

    py::class_<AbsoluteRegion>(m, "AbsoluteRegion")
        .def(py::init<>())
        .def_readwrite("start", &AbsoluteRegion::start)
        .def_readwrite("end", &AbsoluteRegion::end);

    py::class_<PercentRegion>(m, "PercentRegion")
        .def_readwrite("startFraction", &PercentRegion::startFraction)
        .def_readwrite("endFraction", &PercentRegion::endFraction)
        .def(py::init<>());

    py::enum_<RegionType>(m, "RegionType")
        .value("Percent", RegionType_Percent)
        .value("Absolute", RegionType_Absolute)
        .export_values();

    //

    py::enum_<FFTWindowType>(m, "FFTWindowType")
        .value("FFTWindowType_Rectangular", FFTWindowType_Rectangular)
        .value("FFTWindowType_Hamming", FFTWindowType_Hamming)
        .value("FFTWindowType_Hann", FFTWindowType_Hann)
        .value("FFTWindowType_Blackmann", FFTWindowType_Blackmann)
        .value("FFTWindowType_BlackmannHarris", FFTWindowType_BlackmannHarris)
        .export_values();

    py::enum_<StretchMode>(m, "StretchMode")
        .value("StretchMode_Stretch", StretchMode_Stretch)
        .value("StretchMode_HyperStretch", StretchMode_HyperStretch)
        .value("StretchMode_Shorten", StretchMode_Shorten)
        .export_values();

    //

    py::class_<Region>(m, "Region")
        .def(py::init<>());

    //

    py::class_<BatchProcessor>(m, "BatchProcessor")
        .def(py::init<>())
        .def("OpenFiles", &BatchProcessor::OpenFiles)
        .def("OpenConfigurations", &BatchProcessor::OpenConfigurations)
        .def("SetRegions", &BatchProcessor::SetRegions)
        .def("RenderFiles", &BatchProcessor::RenderFiles);

    py::class_<Player>(m, "Player")
        .def(py::init<>())

        .def("OpenFile", &Player::OpenFile)
        .def("OpenConfiguration", &Player::OpenConfiguration)

        .def("Start", &Player::Start)
        .def("Stop", &Player::Stop)
        .def("Seek", &Player::Seek);

    py::class_<XMLConfigurationCodec>(m, "XMLConfigurationCodec")
        .def(py::init<>())

        .def("ToXMLString", &XMLConfigurationCodec::ToXMLString)
        .def("FromXMLString", &XMLConfigurationCodec::FromXMLString);

    py::class_<ConfigTools>(m, "ConfigTools")
        .def(py::init<>())

        .def("Interpolate", &ConfigTools::Interpolate);

    py::class_<AutomatedFloat>(m, "AutomatedFloat")
        .def(py::init<>())

        .def_readwrite("staticValue", &AutomatedFloat::staticValue)
        .def_readwrite("enableAutomation", &AutomatedFloat::enableAutomation)
        .def_readwrite("points", &AutomatedFloat::points);

    py::class_<RangeInfo>(m, "RangeInfo")
        .def(py::init<float, float, float>())

        .def_readonly("min", &RangeInfo::min)
        .def_readonly("max", &RangeInfo::max)
        .def_readonly("initial", &RangeInfo::initial);

    py::class_<Configuration>(m, "Configuration")
        .def(py::init<>())

        .def_readwrite("stretch", &Configuration::stretch)
        .def_readwrite("windowSize", &Configuration::windowSize)
        .def_readwrite("onsetSensitivity", &Configuration::onsetSensitivity)

        .def_readwrite("windowType", &Configuration::windowType)
        //        .def_readwrite("stretchMode", &Configuration::stretchMode)

        .def_readwrite("harmonics", &Configuration::harmonics)
        .def_readwrite("hFreq", &Configuration::hFreq)
        .def_readwrite("hBandwidth", &Configuration::hBandwidth)
        .def_readwrite("hNumberHarm", &Configuration::hNumberHarm)
        .def_readwrite("hGauss", &Configuration::hGauss)

        .def_readwrite("pitchShift", &Configuration::pitchShift)
        .def_readwrite("psCents", &Configuration::psCents)

        .def_readwrite("freqShift", &Configuration::freqShift)
        .def_readwrite("fsFreq", &Configuration::fsFreq)

        .def_readwrite("octaves", &Configuration::octaves)
        .def_readwrite("oValues", &Configuration::oValues)

        .def_readwrite("filter", &Configuration::filter)
        .def_readwrite("fFreq1", &Configuration::fFreq1)
        .def_readwrite("fFreq2", &Configuration::fFreq2)
        .def_readwrite("fFreqArbitrary", &Configuration::fFreqArbitrary)
        .def_readwrite("fBandstop", &Configuration::fBandstop)
        .def_readwrite("fDamp", &Configuration::fDamp)

        .def_readwrite("tonalNoise", &Configuration::tonalNoise)
        .def_readwrite("tnAmount", &Configuration::tnAmount)
        .def_readwrite("tnBandwidth", &Configuration::tnBandwidth)

        .def_readwrite("spread", &Configuration::spread)
        .def_readwrite("spBandwidth", &Configuration::spBandwidth)

        .def_readwrite("compress", &Configuration::compress)
        .def_readwrite("cmPower", &Configuration::cmPower)

        .def_readwrite("binaural", &Configuration::binaural);

    py::class_<ConfigurationInfo>(m, "ConfigurationInfo")
        //.def(py::init<>())

        .def_readonly_static("stretch", &ConfigurationInfo::stretch)
        .def_readonly_static("windowSize", &ConfigurationInfo::windowSize)
        .def_readonly_static("onsetSensitivity", &ConfigurationInfo::onsetSensitivity)

        .def_readonly_static("hFreq", &ConfigurationInfo::hFreq)
        .def_readonly_static("hBandwidth", &ConfigurationInfo::hBandwidth)
        .def_readonly_static("hNumberHarm", &ConfigurationInfo::hNumberHarm)

        .def_readonly_static("psCents", &ConfigurationInfo::psCents)

        .def_readonly_static("fsFreq", &ConfigurationInfo::fsFreq)

        .def_readonly_static("oValues", &ConfigurationInfo::oValues)

        .def_readonly_static("fFreq1", &ConfigurationInfo::fFreq1)
        .def_readonly_static("fFreq2", &ConfigurationInfo::fFreq2)
        .def_readonly_static("fFreqArbitrary", &ConfigurationInfo::fFreqArbitrary)
        .def_readonly_static("fDamp", &ConfigurationInfo::fDamp)

        .def_readonly_static("tnAmount", &ConfigurationInfo::tnAmount)
        .def_readonly_static("tnBandwidth", &ConfigurationInfo::tnBandwidth)

        .def_readonly_static("spBandwidth", &ConfigurationInfo::spBandwidth)

        .def_readonly_static("cmPower", &ConfigurationInfo::cmPower)

        .def_readonly_static("binaural", &ConfigurationInfo::binaural)

        .def_static("ClampFloat", &ConfigurationInfo::Clamp<float>)
        .def_static("ClampInt", &ConfigurationInfo::Clamp<long>);

    py::class_<StretchEngine>(m, "StretchEngine")
        .def(py::init<>())

        .def("SetParameters", &StretchEngine::SetParameters)
        .def("Parameters", &StretchEngine::Parameters)

        .def("ProcessBuffer", &StretchEngine::ProcessBuffer);

    py::class_<LegacyController>(m, "LegacyController")
        .def(py::init<>())

        .def("Play", &LegacyController::Play)
        .def("Pause", &LegacyController::Pause)
        .def("Stop", &LegacyController::Stop)

        .def("Seek", &LegacyController::Seek)
        .def("GetSeek", &LegacyController::GetSeek)
        .def("IsPlaying", &LegacyController::IsPlaying)

        .def("SetVolume", &LegacyController::SetVolume)
        .def("Volume", &LegacyController::Volume)

        .def("OpenFile", &LegacyController::OpenFile)

        .def("SetParameters", &LegacyController::SetParameters)
        .def("Parameters", &LegacyController::Parameters)

        .def("GetRenderPercent", &LegacyController::GetRenderPercent)
        .def("CancelRender", &LegacyController::CancelRender)

        .def("SetRenderRange", &LegacyController::SetRenderRange)
        .def("RenderRange", &LegacyController::RenderRange)

        .def("RenderToFile", []( LegacyController& obj, const std::string& f) {
        //py::gil_scoped_release release;
        obj.RenderToFile(f); }, py::call_guard<py::gil_scoped_release>())
    
        .def("RenderToFileAsync", []( LegacyController& obj, const std::string& f) {
            //py::gil_scoped_release release;
            obj.RenderToFileAsync(f);
        }, py::call_guard<py::gil_scoped_release>())

        .def("SetOnEndPlayback", &LegacyController::SetOnEndPlayback)
        .def("SetOnFileOpenError", &LegacyController::SetOnFileOpenError)
        .def("SetOnRenderError", &LegacyController::SetOnRenderError);

    py::class_<LegacyRenderTask>(m, "LegacyRenderTask")
        .def(py::init<std::string, std::string, PercentRegion, Configuration>())

        .def("StartRender", &LegacyRenderTask::StartRender)
        .def("CancelRender", &LegacyRenderTask::CancelRender)

        .def("GetRenderPercent", &LegacyRenderTask::GetRenderPercent);
};

;

;

