
#include "JSONCodec.hpp"

#include "json.hpp"

using json = nlohmann::json;

namespace PaulstretchLib {

AutomatedFloat _AFFromJSON(const json& j)
{
    auto ret = AutomatedFloat();
    
    ret.staticValue = j["static_value"];

    return ret;
};

json _JSONFromAF(const AutomatedFloat& a)
{
    auto j = json::object();
    
    j["static_value"] = a.staticValue;
    
    return j;
};

// TODO: error check
FFTWindowType _WTFromJSON(const json& j)
{
    std::string str = j.get<std::string>();
    
    if (str.compare(ToString(FFTWindowType_Hann)) == 0)
        return FFTWindowType_Hann;
    if (str.compare(ToString(FFTWindowType_Hamming)) == 0)
        return FFTWindowType_Hamming;
    if (str.compare(ToString(FFTWindowType_Blackmann)) == 0)
        return FFTWindowType_Blackmann;
    if (str.compare(ToString(FFTWindowType_BlackmannHarris)) == 0)
        return FFTWindowType_BlackmannHarris;
    
    return FFTWindowType_Rectangular;
}

// TODO:
json _JSONFromWT(const FFTWindowType& t)
{
    return ToString(t);
}

// ---

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

// new:

bool JSONStringCodec:: FromJSONString(Configuration& ret, const std::string& src)
{
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

    return true;
}

std::string JSONStringCodec:: ToJSONString(const Configuration& src)
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

// ---

json _JSONFromPercentRegionVec(const std::vector<PercentRegion>& vec)
{
    // todo:
    json j = json::array();
    
    for (const auto& e: vec)
    {
        json jj = json::object();
        
        jj["start"] = e.startFraction;
        jj["end"] = e.endFraction;
        
        j.push_back(jj);
    }
    
    return j;
}

const std::vector<PercentRegion> _PercentRegionVecFromJSON(const json& j)
{
    std::vector<PercentRegion> ret;
    
    json::array_t arr = j;
    for (const auto& e: arr)
    {
        PercentRegion p;
        
        p.startFraction = e["start"];
        p.endFraction = e["end"];
        
        ret.push_back(p);
    }
    
    return ret;
}

bool JSONStringCodec:: FromJSONString(BatchData& d, const std::string& src){
    // todo: try
    auto ret = json::parse(src);
    
    d.configurationFiles = ret["configurations"].get<std::vector<std::string>>();
    d.inputFiles = ret["input_files"].get<std::vector<std::string>>();
    d.regions = _PercentRegionVecFromJSON(ret["regions"]);
    d.outputFolder = ret["output_folder"];
    return false;
}

std::string JSONStringCodec:: ToJSONString(const BatchData& obj)
{
    json j;
    
    j["configurations"] = obj.configurationFiles;
    j["input_files"] = obj.inputFiles;
    j["output_folder"] = obj.outputFolder;
    j["regions"] = _JSONFromPercentRegionVec(obj.regions);
    
    return j.dump(4);
}

};
