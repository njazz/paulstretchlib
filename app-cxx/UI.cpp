

#include "UI.hpp"

#include "PaulstretchLib.hpp"
#include "JSONCodec.hpp"

#include "imgui.h"

#include "Optional.hpp"

#include "tinyfiledialogs.h"

#include "imgui_plot.h"

#include "imgui_internal.h"

//#include <fstream>
#include <string>
//#include <iostream>

#include "AFOverview.hpp"

#include "StringUtilities.hpp"

using namespace Core;

struct _UIState {
    std::string filename = "";
    std::string configFilename = "";
    std::string renderFileName = "";

//    Optional<PaulstretchLib::Configuration> cfg = PaulstretchLib::Configuration();

    //bool showParameters = true;

    bool firstRenderOutput = false;
    // renderTask?

    ImGuiID _dockMain;
    ImGuiID _dockLeft;
    ImGuiID _dockRight;

    // batch
    //    std::vector<std::string> inputFiles;
    //    std::vector<std::string> inputConfigurations;
    //    std::vector<PaulstretchLib::PercentRegion> batchRegions;
    //    std::string outputFolder;

    PaulstretchLib::BatchData batch;
    
    //
    const PaulstretchLib::Configuration* parameters = nullptr;
    const PaulstretchLib::PercentRegion* region = nullptr;
};

static _UIState UIState;
static PaulstretchLib::LegacyController _lc;
static ImGuiID dockspaceID = 0;
static ImGui::PlotConfig plotCfg;

static AFOverview overview;

static PaulstretchLib::BatchProcessorLegacyController _batch;

static const char* __windowTypes[5] = { "Rectangular", "Hamming", "Hann", "Blackmann", "BlackmannHarris" };

// ---

inline Optional<std::vector<std::string> > _OpenAudioFiles()
{
    using namespace StringUtilities;

    Optional<std::vector<std::string> > ret;

    std::vector<const char*> flt = { "*.wav", "*.aif*" };

    auto r = tinyfd_openFileDialog(
        "Open audio files", /* NULL or "" */
        NULL, /* NULL or "" */
        2, /* 0 */
        flt.data(), /* NULL | {"*.jpg","*.png"} */
        "Audio files", /* NULL | "image files" */
        1);

    if (r)
        ret = SplitStringWithDelimiter(r, "|");

    return ret;
}

inline Optional<std::vector<std::string> > _OpenConfigFiles()
{
    using namespace StringUtilities;

    Optional<std::vector<std::string> > ret;

    std::vector<const char*> flt = { "*.ps.json" };

    auto r = tinyfd_openFileDialog(
        "Open configuration file", /* NULL or "" */
        NULL, /* NULL or "" */
        1, /* 0 */
        flt.data(), /* NULL | {"*.jpg","*.png"} */
        "paulstretchlib configuration files (JSON)", /* NULL | "image files" */
        0);
    
    if (r)
        ret = SplitStringWithDelimiter(r, "|");
    return ret;
}

inline Optional<std::string> _OpenAudioFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.wav", "*.aif*" };

    auto r = tinyfd_openFileDialog(
        "Open audio file", /* NULL or "" */
        NULL, /* NULL or "" */
        2, /* 0 */
        flt.data(), /* NULL | {"*.jpg","*.png"} */
        "Audio files", /* NULL | "image files" */
        0);

    if (r)
        ret.Set(std::string(r));

    return ret;
}

inline Optional<std::string> _OpenConfigFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.ps.json" };

    auto r = tinyfd_openFileDialog(
        "Open configuration file", /* NULL or "" */
        NULL, /* NULL or "" */
        1, /* 0 */
        flt.data(), /* NULL | {"*.jpg","*.png"} */
        "paulstretchlib configuration files (JSON)", /* NULL | "image files" */
        0);

    if (r)
        ret.Set(std::string(r));

    return ret;
}

inline Optional<std::string> _OpenBatchFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.ps-batch.json" };

    auto r = tinyfd_openFileDialog(
        "Open batch file", /* NULL or "" */
        NULL, /* NULL or "" */
        1, /* 0 */
        flt.data(), /* NULL | {"*.jpg","*.png"} */
        "paulstretchlib batch files (JSON)", /* NULL | "image files" */
        0);

    if (r)
        ret.Set(std::string(r));

    return ret;
}

// ---

inline Optional<std::string> _SaveAudioFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.wav" };

    auto r = tinyfd_saveFileDialog("Save audio file", NULL, 1, flt.data(), "Audio file (WAV)");

    if (r)
        ret.Set(std::string(r));

    return ret;
};

inline Optional<std::string> _SaveConfigFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.ps.json" };

    auto r = tinyfd_saveFileDialog("Save configuration file", NULL, 1, flt.data(), "paulstretchlib configuration file (JSON)");

    if (r)
        ret.Set(std::string(r));

    return ret;
};

inline Optional<std::string> _SaveBatchFile()
{
    Optional<std::string> ret;

    std::vector<const char*> flt = { "*.ps-batch.json" };

    auto r = tinyfd_saveFileDialog("Save batch file", NULL, 1, flt.data(), "paulstretchlib batch file (JSON)");

    if (r)
        ret.Set(std::string(r));

    return ret;
};
// ---

Optional<float> _RangedSlider(const std::string name, const float& value, const PaulstretchLib::RangeInfo& rangeInfo)
{
    Optional<float> ret;

    auto range = rangeInfo.max - rangeInfo.min;
    auto spd = (range > 0) ? .0025 * range : .1;

    float v = value;
    if (ImGui::DragFloat(std::string("##v_" + name).c_str(), &v, rangeInfo.min, rangeInfo.max, spd))

        ret.Set(v);
    ImGui::SameLine();
    if (ImGui::Button(std::string("init##b_" + name).c_str()))

        ret.Set(rangeInfo.initial);

    return ret;
}

Optional<float> _EditAutofloat(PaulstretchLib::AutomatedFloat& af, std::string objId, const PaulstretchLib::RangeInfo& rangeInfo)
{
    Optional<float> ret;

    auto r = _RangedSlider(objId, af.staticValue, rangeInfo);
    if (!r.IsNull()) {
        af.staticValue = r.Get();
        ret = r;
    }

    return ret;
}

void _StringArrayEdit(std::vector<std::string>& obj)
{
    using namespace ImGui;

    int idx = 0;
    int _itemToRemove = -1;

    for (auto& e : obj) {
        Text("%i: %s", idx, e.c_str());
//        Separator();

        if (Button("Del"))
            _itemToRemove = idx;
        SameLine(50);
        if (Button("Replace")) {
            auto v = _OpenAudioFile();
            if (!v.IsNull())
                e = v.Get();
        }
        SameLine(130);
        bool b = false;
        Checkbox("View", &b);

        idx++;

//        Separator();
    }

    if (_itemToRemove != -1) {
        obj.erase(obj.begin() + _itemToRemove);
    }
}

void _ConfigArrayEdit(std::vector<PaulstretchLib::Configuration>& obj)
{
    using namespace ImGui;

    int idx = 0;
    int _itemToRemove = -1;

    for (auto& e : obj) {
        Text("%i", idx);
//        Separator();

        if (Button("Del"))
            _itemToRemove = idx;
        SameLine(50);
        if (Button("Replace")) {
            auto v = _OpenConfigFile();
            if (!v.IsNull())
                e.FromFile(v.Get());// = v.Get();
        }
        SameLine(130);
//        bool b = false;
        
        if (RadioButton(("Edit##"+std::to_string((long)&e)).c_str(), (UIState.parameters == &e))){
            UIState.parameters = &e;
        };
        
        //SameLine();
        if (Button("Write to file"))
        {
            auto v = _SaveConfigFile();
            if (!v.IsNull())
                e.ToFile(v.Get());
        }

        idx++;

//        Separator();
    }

    if (_itemToRemove != -1) {
        UIState.parameters = nullptr;
        obj.erase(obj.begin() + _itemToRemove);
    }
}

void _BatchWindow()
{
    using namespace ImGui;
    using namespace PaulstretchLib;

    Begin("Batch process");

    if (Button("Load batch...")) {
        auto v = _OpenBatchFile();
        if (!v.IsNull()) {
            UIState.batch.FromFile(v.Get());
        }
    }
    SameLine();
    if (Button("Save batch...")) {
        auto v = _SaveBatchFile();
        if (!v.IsNull()) {
            UIState.batch.ToFile(v.Get());
        }
    }
    Separator();Text("");
    Separator();
    
    Text("Audio files:");

    if (Button("Open files...")) {
        auto v = _OpenAudioFiles();
        if (!v.IsNull())
            UIState.batch.inputFiles = v.Get();
    }

    // --- audio files

    if (UIState.batch.inputFiles.size() == 0) {
        Text("No audio files");
    }

    _StringArrayEdit(UIState.batch.inputFiles);

    if (Button("Add audio file ..."))
    {
        auto v = _OpenAudioFile();
        if (!v.IsNull())
        {
            UIState.batch.inputFiles.push_back(v.Get());
        }
    }

    // --- cfg
    
    Separator();
    Text("");
    Separator();
    
    Text("Configurations:");
    
    if (Button("Open configuration files ...")) {
        auto v = _OpenConfigFiles();
        if (!v.IsNull())
        {
            UIState.batch.configurations.clear();
            for (const auto& e : v.Get())
            {
            auto obj = Configuration();
            obj.FromFile(e);
                UIState.batch.configurations.push_back(obj);
                }
            }
    }

    if (UIState.batch.configurations.size() == 0) {
        Text("No configuration files");
    }

    
    _ConfigArrayEdit(UIState.batch.configurations);

    if (Button("Add configuration file ..."))
    {
        auto v = _OpenConfigFile();
        if (!v.IsNull())
        {
            auto obj = Configuration();
            obj.FromFile(v.Get());
                UIState.batch.configurations.push_back(obj);
        }
    }
    
    if (Button("Create configuration ..."))
    {
        UIState.batch.configurations.push_back(Configuration());
    }

    // regions

    Separator();
    Text("");
    Separator();

    Text("Regions:");
    if (UIState.batch.regions.size() == 0) {
        Text("No regions");
    }

    int idx = 0;
    int _itemToRemove = -1;

    for (auto& e : UIState.batch.regions) {
        float range[2];
        range[0] = e.startFraction;
        range[1] = e.endFraction;

        if (DragFloat2("Range", range, 0.005, 0, 1)) {
            e = PercentRegion(range[0], range[1]);
        }

        if (Button("Del"))
            _itemToRemove = idx;

        SameLine(130);
//        bool b = false;
        if (RadioButton(("View##"+std::to_string((long)&e)).c_str(), (UIState.region == &e)))
            {
            UIState.region = &e;
            }

        idx++;
    }

    if (_itemToRemove != -1) {
        UIState.batch.regions.erase(UIState.batch.regions.begin() + _itemToRemove);
    }

    if (Button("Add region"))
        UIState.batch.regions.push_back(PercentRegion(0, 1));

    Separator();
    Text("");
    Separator();

    if (Button("Render Files")) {
        //        _batch.OpenFiles(UIState.inputFiles);
        //        _batch.OpenConfigurations(UIState.inputConfigurations);
        //        _batch.SetRegions(UIState.batchRegions);
        //        _batch.SetOutputFolder(UIState.outputFolder);

        _batch.SetData(UIState.batch);

        _batch.RenderBatchAsync();
    }

    if (_batch.IsRendering()) {
        Separator();
        Text("Processing %i of %i", (int)_batch.GetDoneTasks(), (int)_batch.GetTotalTasks());
        Separator();
        for (int i = 0; i < _batch.GetActiveWorkerCount(); i++) {
            Text("%i %%", int(100 * _batch.GetWorkerRenderPercent(i)));
        };
        Separator();
    }
    End();
}

void _FileWindow()
{
    using namespace ImGui;
    using namespace PaulstretchLib;
    Begin("File");

    Columns(2);
    float fs = overview.ScaleFraction();
    if (SliderFloat("Scale", &fs, 0.01, 1)) {
        overview.SetScaleFraction(fs);
    }
    NextColumn();
    float scroll = overview.ScrollFraction();
    if (SliderFloat("Scroll", &scroll, 0, 1)) {
        overview.SetScrollFraction(scroll);
    }
    NextColumn();
    Columns(1);

    auto ws = ImVec2(GetWindowWidth() * .97, GetWindowHeight() * .87);
    plotCfg.frame_size = ws;

    overview.SetDataSize(1024);
    plotCfg.values.ys = overview.GetData().data();
    
//    if (UIState.region != nullptr){
    auto rng = (UIState.region) ? *UIState.region : PercentRegion();//_lc.RenderRange();

    uint32_t selStart = overview.FractionToViewCoord(rng.startFraction);
    uint32_t selLen = overview.FractionToViewCoord(rng.endFraction) - selStart;
    plotCfg.selection.start = &selStart;
    plotCfg.selection.length = &selLen;
    plotCfg.selection.show = true;

    if (Plot("file:", plotCfg) == PlotStatus::selection_updated && (UIState.region != nullptr)) {
        float nStart = overview.ViewCoordToFraction(selStart);
        float nEnd = overview.ViewCoordToFraction(selLen) + nStart;

        auto r = PaulstretchLib::PercentRegion(nStart, nEnd);

        if (UIState.region == &_lc.RenderRange()){
            _lc.SetRenderRange(r);
            UIState.region = &_lc.RenderRange();
            }
        
        for (auto& e: UIState.batch.regions)
        {
            if (&e == UIState.region)
            {
                e = r;
            }
        }
    }//}
    End();
}

Core::Optional<PaulstretchLib::Configuration> _ConfigurationWindow(const PaulstretchLib::Configuration* cfg_o)
{
    using namespace ImGui;

    bool ret = false;

    Begin("Parameters");

    if (cfg_o == nullptr) {
        Text("No configuration selected");
        End();
        return Core::Optional<PaulstretchLib::Configuration>();
    }

    auto cfg = *cfg_o;//.Get();

    Columns(2);

    Text("Stretch");

    NextColumn();
    if (!_EditAutofloat(cfg.stretch, "stretch", PaulstretchLib::ConfigurationInfo::stretch).IsNull())
        ret = true;

    NextColumn();
    Separator();

    Text("Window Size");

    NextColumn();

    auto r = _RangedSlider("windowSize", cfg.windowSize, PaulstretchLib::ConfigurationInfo::windowSize);
    if (!r.IsNull()) {
        cfg.windowSize = r.Get();
        ret = true;
    }

    NextColumn();
    //    Separator();

    Text("Window Type:");
    NextColumn();

    int wt = (int)cfg.windowType;
    SetNextItemWidth(GetWindowWidth() * .45);
    if (Combo("##window_type", &wt, __windowTypes, 5)) {
        PaulstretchLib::ToFFTWindowType(cfg.windowType, wt);
        ret = true;
    }

    NextColumn();

    Text("Onset Sensitivity");

    NextColumn();

    r = _RangedSlider("onsetSensitivity", cfg.onsetSensitivity, PaulstretchLib::ConfigurationInfo::onsetSensitivity);
    if (!r.IsNull()) {
        cfg.onsetSensitivity = r.Get();
        ret = true;
    }

    NextColumn();
    //    Separator();

    Separator();

    Text("Harmonics:");

    NextColumn();

    if (Checkbox("##harmonics", &cfg.harmonics)) {
        ret = true;
    }

    NextColumn();
    //    Separator();

    if (cfg.harmonics) {
        Text("Freq");

        NextColumn();

        r = _RangedSlider("hFreq", cfg.hFreq, PaulstretchLib::ConfigurationInfo::hFreq);
        if (!r.IsNull()) {
            cfg.hFreq = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Bandwidth");

        NextColumn();

        r = _RangedSlider("hBandwidth", cfg.hBandwidth, PaulstretchLib::ConfigurationInfo::hBandwidth);
        if (!r.IsNull()) {
            cfg.hBandwidth = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Count");

        NextColumn();

        r = _RangedSlider("hNumberHarm", cfg.hNumberHarm, PaulstretchLib::ConfigurationInfo::hNumberHarm);
        if (!r.IsNull()) {
            cfg.hNumberHarm = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Gaussian");

        NextColumn();

        if (Checkbox("##hGauss", &cfg.hGauss))
            ret = true;

        NextColumn();
        //        Separator();

        //        Separator();
    }

    Separator();

    Text("Octaves:");

    NextColumn();

    if (Checkbox("##octaves", &cfg.octaves)) {
        ret = true;
    }

    if (cfg.octaves) {
        float f = cfg.oValues[0];
        if (SliderFloat("-2##oct0", &f, 0, 1)) {
            cfg.oValues[0] = f;
            ret = true;
        }

        f = cfg.oValues[1];
        if (SliderFloat("-1##oct1", &f, 0, 1)) {
            cfg.oValues[1] = f;
            ret = true;
        }

        f = cfg.oValues[2];
        if (SliderFloat("0##oct2", &f, 0, 1)) {
            cfg.oValues[2] = f;
            ret = true;
        }

        f = cfg.oValues[3];
        if (SliderFloat("1##oct3", &f, 0, 1)) {
            cfg.oValues[3] = f;
            ret = true;
        }

        f = cfg.oValues[4];
        if (SliderFloat("1.5##oct4", &f, 0, 1)) {
            cfg.oValues[4] = f;
            ret = true;
        }

        f = cfg.oValues[5];
        if (SliderFloat("2##oct5", &f, 0, 1)) {
            cfg.oValues[5] = f;
            ret = true;
        }
    }

    NextColumn();
    Separator();

    Text("Pitch Shift:");

    NextColumn();

    if (Checkbox("##pitchShift", &cfg.pitchShift)) {
        ret = true;
    }

    NextColumn();

    if (cfg.pitchShift) {
        Text("Cents");

        NextColumn();

        r = _RangedSlider("psCents", cfg.psCents, PaulstretchLib::ConfigurationInfo::psCents);
        if (!r.IsNull()) {
            cfg.psCents = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        //        Separator();
    }
    Separator();

    Text("Freq Shift:");

    NextColumn();

    if (Checkbox("##freqShift", &cfg.freqShift)) {
        ret = true;
    }

    NextColumn();
    //    Separator();

    if (cfg.freqShift) {
        Text("Freq");

        NextColumn();

        r = _RangedSlider("fsFreq", cfg.fsFreq, PaulstretchLib::ConfigurationInfo::fsFreq);
        if (!r.IsNull()) {
            cfg.fsFreq = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        //        Separator();
    }
    Separator();

    Text("Filter:");

    NextColumn();

    if (Checkbox("##filter", &cfg.filter)) {
        ret = true;
    }

    NextColumn();
    //    Separator();

    if (cfg.filter) {
        Text("Freq 1");

        NextColumn();

        r = _RangedSlider("fFreq1", cfg.fFreq1, PaulstretchLib::ConfigurationInfo::fFreq1);
        if (!r.IsNull()) {
            cfg.fFreq1 = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Freq 2");

        NextColumn();

        r = _RangedSlider("fFreq2", cfg.fFreq2, PaulstretchLib::ConfigurationInfo::fFreq2);
        if (!r.IsNull()) {
            cfg.fFreq2 = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Arbitrary Freq");

        NextColumn();
        if (!_EditAutofloat(cfg.fFreqArbitrary, "fFreqArbitrary", PaulstretchLib::ConfigurationInfo::fFreqArbitrary).IsNull())
            ret = true;
        NextColumn();
        //        Separator();

        Text("Bandstop");

        NextColumn();

        if (Checkbox("##fBandstop", &cfg.fBandstop)) {
            ret = true;
        };

        NextColumn();
        //        Separator();

        //        Separator();
    }
    Separator();

    Text("Tonal / Noise:");

    NextColumn();

    if (Checkbox("##tonalNoise", &cfg.tonalNoise)) {
        ret = true;
    }

    NextColumn();
    //    Separator();

    if (cfg.tonalNoise) {
        Text("Amount");

        NextColumn();

        r = _RangedSlider("tnAmount", cfg.tnAmount, PaulstretchLib::ConfigurationInfo::tnAmount);
        if (!r.IsNull()) {
            cfg.tnAmount = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        Text("Bandwidth");

        NextColumn();

        r = _RangedSlider("tnBandwidth", cfg.tnBandwidth, PaulstretchLib::ConfigurationInfo::tnBandwidth);
        if (!r.IsNull()) {
            cfg.tnBandwidth = r.Get();
            ret = true;
        }

        NextColumn();
        //        Separator();

        //        Separator();
    }
    Separator();

    Text("Compress");

    NextColumn();

    if (Checkbox("##compress", &cfg.compress)) {
        ret = true;
    }

    NextColumn();
    Separator();

    //    Separator();

    Text("Binaural");
    NextColumn();

    if (!_EditAutofloat(cfg.binaural, "binaural", PaulstretchLib::ConfigurationInfo::binaural).IsNull())
        ret = true;

    NextColumn();
    Separator();

    End();

//    if (ret)
//        *cfg_o = (cfg);

//    return ret;
    
    return (ret) ? Core::Optional<PaulstretchLib::Configuration>(cfg) : Core::Optional<PaulstretchLib::Configuration>();
}

void _LegacyControllerWindow()
{
    using namespace ImGui;

    SetNextWindowSize(ImVec2(250, 400));

    Begin("Single file");

    Text("%s", (UIState.filename.compare("") == 0 ? "No file" : UIState.filename.c_str()));
    bool f_b = true;
    RadioButton("View file", f_b);

    if (Button("Open file...")) {
        auto f = _OpenAudioFile();
        if (!f.IsNull()) {
            UIState.filename = f.Get();
            _lc.OpenFile(f.Get());
            overview.OpenFile(f.Get());
        }
    }
    Separator();

    Text("%s", (UIState.configFilename.compare("") == 0 ? "No configuration file" : UIState.configFilename.c_str()));

    if (Button("Open configuration file...")) {
        auto r = _OpenConfigFile();
        if (!r.IsNull()) {

            // TODO: try
            // TODO: move to lib

            //
            //            std::string s;
            //            std::ifstream in1(r.Get());
            //            in1 >> s;
            //            in1.close();
            //
            //            // auto s = PaulstretchLib::JSONStringFromConfiguration(UIState.cfg.Get());
            //            UIState.cfg = PaulstretchLib::FromJSONString(s);
//            UIState.cfg.Get().ToFile(r.Get());
            
            _lc.Parameters().ToFile(r.Get());
        }
    }

    if (Button("Save configuration file...")) {
        auto r = _SaveConfigFile();
        if (!r.IsNull()) {
            //            auto s = PaulstretchLib::JSONStringFromConfiguration(UIState.cfg.Get());
            //            //
            //            std::ofstream out1(r.Get());
            //            out1 << s;
            //            out1.close();
            //
//            UIState.cfg.GetRef().FromFile(r.Get());
            
            auto p = PaulstretchLib:: Configuration();
            p.FromFile(r.Get());
            _lc.SetParameters(p);
        }
    }

    Separator();
    
//    bool bb = true;
    if (RadioButton("Edit Configuration", (UIState.parameters == &_lc.Parameters())))
        UIState.parameters = &_lc.Parameters();
    Separator();

    if (!_lc.IsPlaying()) {
        if (Button("Play"))
            _lc.Play();
    }

    if (_lc.IsPlaying()) {
        if (Button("Stop"))
            _lc.Stop();
    }
    SameLine();

    auto f = _lc.GetSeek();
    if (SliderFloat("##seek", &f, 0, 1)) {
        //if (!_lc.IsPlaying())
        _lc.Seek(f);
    }

    Separator();
    Text("Quick render:");
    if (Button("Render all to file...")) {
        auto r = _SaveAudioFile();
        if (!r.IsNull()) {
            auto fn = UIState.renderFileName;
            UIState.renderFileName = r.Get();
            _lc.SetRenderRange(PaulstretchLib::PercentRegion(0, 1));
            _lc.RenderToFileAsync(UIState.renderFileName);
            UIState.renderFileName = fn;
        }
    }

    Separator();

    Text("%s", (UIState.renderFileName.compare("") == 0 ? "No output file" : UIState.renderFileName.c_str()));

    if (Button("Select output file ...")) {
        auto r = _SaveAudioFile();
        if (!r.IsNull()) {
            UIState.renderFileName = r.Get();
            UIState.firstRenderOutput = true;
        }
    }

    auto rr = _lc.RenderRange();
    float range[2];
    range[0] = rr.startFraction;
    range[1] = rr.endFraction;

    Separator();

    //bool r_b = true;
    if (RadioButton("Set range", (UIState.region == &_lc.RenderRange())))
        {
            UIState.region = &_lc.RenderRange();
        }

    if (DragFloat2("Range", range, 0.005, 0, 1)) {
        _lc.SetRenderRange(PaulstretchLib::PercentRegion(range[0], range[1]));
    }

    if (Button("Select all")) {
        _lc.SetRenderRange(PaulstretchLib::PercentRegion(0, 1));
    }

    Separator();

    if (UIState.firstRenderOutput) {
        Text("Not rendered");
    }

    if (UIState.renderFileName.compare(""))
        if (Button("Render")) {
            UIState.firstRenderOutput = false;
            _lc.RenderToFileAsync(UIState.renderFileName);
        }

    if (_lc.GetRenderPercent() >= 0) {
        Text("Render: %i", int(_lc.GetRenderPercent()));
        if (Button("Cancel render"))
            _lc.CancelRender();
    }

    End();
}

void PaulstretchUI()
{
    using namespace ImGui;
    using namespace PaulstretchLib;

    ImGui::StyleColorsLight();

    std::vector<float> test_vec;
    for (int i = 0; i < 1024; i++)
        test_vec.push_back(0);

    plotCfg.values.ys = test_vec.data();
    plotCfg.values.count = test_vec.size();

    plotCfg.grid_x.show = true;
    plotCfg.grid_y.show = true;

    plotCfg.scale.max = 1;
    plotCfg.scale.min = -1;

    //plotCfg.frame_size = ImVec2(400, 300);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    //

    ImGui::Begin("Dock", nullptr, window_flags);

    dockspaceID = ImGui::GetID("DockSpace");

    if (ImGui::DockBuilderGetNode(dockspaceID) == NULL) {

        ImGui::DockBuilderRemoveNode(dockspaceID); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspaceID, ImVec2(800, 600));

        UIState._dockMain = dockspaceID; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        UIState._dockLeft = ImGui::DockBuilderSplitNode(UIState._dockMain, ImGuiDir_Left, 0.20f, NULL, &UIState._dockMain);
        UIState._dockRight = ImGui::DockBuilderSplitNode(UIState._dockMain, ImGuiDir_Right, 0.45f, NULL, &UIState._dockMain);

        ImGui::DockBuilderDockWindow("Batch process", UIState._dockLeft);
        ImGui::DockBuilderDockWindow("Single file", UIState._dockLeft);

        ImGui::DockBuilderDockWindow("File", UIState._dockMain);
        ImGui::DockBuilderDockWindow("Parameters", UIState._dockRight);
        ImGui::DockBuilderFinish(dockspaceID);
    }

    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);

    End();

    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    // ---
    ImGui::SetNextWindowDockID(UIState._dockLeft, ImGuiCond_FirstUseEver);
    _BatchWindow();

    ImGui::SetNextWindowDockID(UIState._dockLeft, ImGuiCond_FirstUseEver);
    _LegacyControllerWindow();

    if (UIState.parameters != nullptr) {
//        UIState.cfg = *UIState.parameters;
        ImGui::SetNextWindowDockID(UIState._dockRight, ImGuiCond_FirstUseEver);
    } else {
        UIState.parameters = nullptr;//cfg.SetNull();
    }

//    if (UIState.parameters == &_lc.Parameters()){
    auto r = _ConfigurationWindow(UIState.parameters);
    if (!r.IsNull()) {
        if (UIState.parameters == &_lc.Parameters()){
        _lc.SetParameters(r.Get());
        UIState.parameters = &_lc.Parameters();
        }
        
        for (auto& e: UIState.batch.configurations)
        {
            if (&e == UIState.parameters)
            {
                e = r.Get();
                UIState.parameters = &e;
            }
        }
        //UIState.cfg = _lc.Parameters();
    }//}

    ImGui::SetNextWindowDockID(UIState._dockMain, ImGuiCond_FirstUseEver);
    _FileWindow();
};

;
