

#include "UI.hpp"

#include "PaulstretchLib.hpp"
#include "JSONCodec.hpp"

#include "imgui.h"

#include "Optional.hpp"

#include "tinyfiledialogs.h"

#include "imgui_plot.h"

#include "imgui_internal.h"

#include <fstream>
#include <string>
#include <iostream>

#include "AFOverview.hpp"

#include "StringUtilities.hpp"

using namespace Core;

struct _UIState {
    std::string filename = "";
    std::string configFilename = "";
    std::string renderFileName = "";

    Optional<PaulstretchLib::Configuration> cfg = PaulstretchLib::Configuration();

    bool showParameters = false;

    bool firstRenderOutput = false;
    // renderTask?

    ImGuiID _dockMain;
    ImGuiID _dockLeft;
    ImGuiID _dockRight;

    // batch
    std::vector<std::string> inputFiles;
    std::vector<std::string> inputConfigurations;
    std::vector<PaulstretchLib::PercentRegion> batchRegions;
    std::string outputFolder;
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

    auto r = tinyfd_saveFileDialog("Save paulstretchlib configuration file", NULL, 1, flt.data(), "paulstretchlib configuration file (JSON)");

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

void _BatchWindow()
{
    using namespace ImGui;
    using namespace PaulstretchLib;

    Begin("Batch process");
    if (Button("Open files...")) {
        auto v = _OpenAudioFiles();
        if (!v.IsNull())
            UIState.inputFiles = v.Get();
    }
    // --- audio files
    Separator();
    if (UIState.inputFiles.size() == 0) {
        Text("No audio files");
    }
    
    
    for (const auto& e : UIState.inputFiles) {
        Text("%s", e.c_str());
        Separator();
        Button("Del");
        SameLine(50);
        Button("Replace");
        SameLine(130);
        bool b = false;
        Checkbox("View", &b);
    }

    Separator();

    if (Button("Open configurations...")) {
        auto v = _OpenConfigFiles();
        if (!v.IsNull())
            UIState.inputConfigurations = v.Get();
    }

    // --- cfg

    Separator();
    if (UIState.inputConfigurations.size() == 0) {
        Text("No configuration files");
    }
    for (const auto& e : UIState.inputConfigurations) {
        Text("%s", e.c_str());
        Separator();
        Button("Del");
        SameLine(50);
        Button("Replace");
        SameLine(130);
        bool b = false;
        Checkbox("Edit", &b);
    }

    Separator();
    Text("Regions:");
    if (UIState.batchRegions.size() == 0) {
        Text("No regions");
    }
    
    for (auto& e : UIState.batchRegions) {
        float range[2];
        range[0] = e.startFraction;
        range[1] = e.endFraction;

        if (DragFloat2("Range", range, 0.005, 0, 1)) {
            e = PercentRegion(range[0], range[1]);
        }

        Button("Del");
        SameLine(50);
        bool b = false;
        Checkbox("View", &b);
        Separator();
    }
    if (Button("Add region"))
        UIState.batchRegions.push_back(PercentRegion(0, 1));

    Separator();
    if (Button("Render Files"))
    {
        _batch.OpenFiles(UIState.inputFiles);
        _batch.OpenConfigurations(UIState.inputConfigurations);
        _batch.SetRegions(UIState.batchRegions);
        _batch.SetOutputFolder(UIState.outputFolder);

        _batch.RenderBatchAsync();
    }
    
    if (_batch.IsRendering())
    {
        Separator();
        Text("Processing %i of %i", (int)_batch.GetDoneTasks(), (int)_batch.GetTotalTasks());
        Separator();
        for (int i=0;i<_batch.GetActiveWorkerCount();i++)
        {
            Text("%i %%", int(100*_batch.GetWorkerRenderPercent(i)));
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

    auto rng = _lc.RenderRange();

    uint32_t selStart = overview.FractionToViewCoord(rng.startFraction);
    uint32_t selLen = overview.FractionToViewCoord(rng.endFraction) - selStart;
    plotCfg.selection.start = &selStart;
    plotCfg.selection.length = &selLen;
    plotCfg.selection.show = true;

    if (Plot("file:", plotCfg) == PlotStatus::selection_updated) {
        float nStart = overview.ViewCoordToFraction(selStart);
        float nEnd = overview.ViewCoordToFraction(selLen) + nStart;

        auto r = PaulstretchLib::PercentRegion(nStart, nEnd);

        _lc.SetRenderRange(r);
    }
    End();
}

bool _ConfigurationWindow(Optional<PaulstretchLib::Configuration>& cfg_o)
{
    using namespace ImGui;

    bool ret = false;

    Begin("Parameters");

    if (cfg_o.IsNull()) {
        Text("No configuration selected");
        End();
        return false;
    }

    auto cfg = cfg_o.Get();

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
    if (Combo("##window_type", &wt, __windowTypes, 5))
    {
         PaulstretchLib::ToFFTWindowType(cfg.windowType ,wt);
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
        if (SliderFloat("-1##oct0", &f, 0, 1)) {
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

    if (ret)
        cfg_o.Set(cfg);

    return ret;
}

void _LegacyControllerWindow()
{
    using namespace ImGui;

    SetNextWindowSize(ImVec2(250, 400));

    Begin("Single file");

    Text("%s", (UIState.filename.compare("") == 0 ? "No file" : UIState.filename.c_str()));
    bool f_b = true;
    Checkbox("View file", &f_b);
    
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
            std::string s;
            std::ifstream in1(r.Get());
            in1 >> s;
            in1.close();

            // auto s = PaulstretchLib::JSONStringFromConfiguration(UIState.cfg.Get());
            UIState.cfg = PaulstretchLib::FromJSONString(s);
        }
    }

    if (Button("Save configuration file...")) {
        auto r = _SaveConfigFile();
        if (!r.IsNull()) {
            auto s = PaulstretchLib::JSONStringFromConfiguration(UIState.cfg.Get());
            //
            std::ofstream out1(r.Get());
            out1 << s;
            out1.close();
        }
    }

    Separator();

    Checkbox("Edit Configuration", &UIState.showParameters);

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
    
    bool r_b = true;
    Checkbox("Set range", &r_b);

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

    if (UIState.showParameters) {
        UIState.cfg = _lc.Parameters();
        ImGui::SetNextWindowDockID(UIState._dockRight, ImGuiCond_FirstUseEver);
    } else {
        UIState.cfg.SetNull();
    }

    auto r = _ConfigurationWindow(UIState.cfg);
    if (r && !UIState.cfg.IsNull()) {
        _lc.SetParameters(UIState.cfg.Get());
        //UIState.cfg = _lc.Parameters();
    }

    ImGui::SetNextWindowDockID(UIState._dockMain, ImGuiCond_FirstUseEver);
    _FileWindow();
};

;
