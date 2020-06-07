
#include "JSONCodec.hpp"

#include "json.hpp"

using json = nlohmann::json;

namespace PaulstretchLib {

AutomatedFloat _AFFromJSON(const json& j)
{
    auto ret = AutomatedFloat();

    return ret;
};

json _JSONFromAF(const AutomatedFloat& a)
{
    return json::object();
};

// TODO:
FFTWindowType _WTFromJSON(const json& j)
{
    return FFTWindowType_Rectangular;
}

// TODO:
json _JSONFromWT(const FFTWindowType& t)
{
    return "FFTWindowType_Rectangular";
}

Configuration FromJSONString(const std::string& src)
{
    Configuration ret;

    // TODO: try
    auto j = json::parse(src);

    ret.stretch = _AFFromJSON(j["stretch"]);
    ret.windowSize = j["windowSize"];
    ret.onsetSensitivity = j["onsetSensitivity"];

    //!
    ret.windowType = _WTFromJSON(j["windowType"]);

    ret.harmonics = j["harmonics"];
    ret.hFreq = j["hFreq"];
    ret.hBandwidth = j["hBandwidth"];
    ret.hNumberHarm = j["hNumberHarm"];
    ret.hGauss = j["hGauss"];

    ret.pitchShift = j["pitchShift"];
    ret.psCents = j["psCents"];

    ret.freqShift = j["freqShift"];
    ret.fsFreq = j["fsFreq"];

    ret.octaves = j["octaves"];
    ret.oValues = j["oValues"];

    ret.filter = j["filter"];
    ret.fFreq1 = j["fFreq1"];
    ret.fFreq2 = j["fFreq2"];
    ret.fFreqArbitrary = _AFFromJSON(j["fFreqArbitrary"]);
    ret.fBandstop = j["fBandstop"];
    ret.fDamp = j["fDamp"];

    ret.tonalNoise = j["tonalNoise"];
    ret.tnAmount = j["tnAmount"];
    ret.tnBandwidth = j["tnBandwidth"];

    ret.spread = j["spread"];
    ret.spBandwidth = j["spBandwidth"];

    ret.compress = j["compress"];
    ret.cmPower = j["cmPower"];

    ret.binaural = _AFFromJSON(j["binaural"]);

    // TODO: fix ranges

    return ret;
}
std::string JSONStringFromConfiguration(const Configuration& src)
{
    json j;

    j["stretch"] = _JSONFromAF(src.stretch);
    j["windowSize"] = src.windowSize;
    j["onsetSensitivity"] = src.onsetSensitivity;

    j["windowType"] = _JSONFromWT(src.windowType);

    j["harmonics"] = src.harmonics;
    j["hFreq"] = src.hFreq;
    j["hBandwidth"] = src.hBandwidth;
    j["hNumberHarm"] = src.hNumberHarm;
    j["hGauss"] = src.hGauss;

    j["pitchShift"] = src.pitchShift;
    j["psCents"] = src.psCents;

    j["freqShift"] = src.freqShift;
    j["fsFreq"] = src.fsFreq;

    j["octaves"] = src.octaves;
    j["oValues"] = src.oValues;

    j["filter"] = src.filter;
    j["fFreq1"] = src.fFreq1;
    j["fFreq2"] = src.fFreq2;
    j["fFreqArbitrary"] = _JSONFromAF(src.fFreqArbitrary);
    j["fBandstop"] = src.fBandstop;
    j["fDamp"] = src.fDamp;

    j["tonalNoise"] = src.tonalNoise;
    j["tnAmount"] = src.tnAmount;
    j["tnBandwidth"] = src.tnBandwidth;

    j["spread"] = src.spread;
    j["spBandwidth"] = src.spBandwidth;

    j["compress"] = src.compress;
    j["cmPower"] = src.cmPower;

    j["binaural"] = _JSONFromAF(src.binaural);

    return j.dump(4);
}
};
