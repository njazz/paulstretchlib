#ifndef PaulstretchLib_hpp
#define PaulstretchLib_hpp

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <array>
#include <mutex>

#include <memory>

//#include "RangedValue.hpp"

// wrapper classes for the original Paulstretch cxx code
namespace PaulstretchLib {

struct AbsoluteRegion;

// ---

struct PercentRegion {
    float startFraction = 0;
    float endFraction = 1;
    
    PercentRegion(){};
    PercentRegion(const float& s, const float& e): startFraction(s), endFraction(e) {}
    
    const AbsoluteRegion ToAbsolute(const float& length);
};

struct AbsoluteRegion {
    float start = 0;
    float end = 0;

    const PercentRegion ToPercent(const float& length);
};

enum RegionType {
    RegionType_Percent,
    RegionType_Absolute
};

//

enum FFTWindowType {
    FFTWindowType_Rectangular,
    FFTWindowType_Hamming,
    FFTWindowType_Hann,
    FFTWindowType_Blackmann,
    FFTWindowType_BlackmannHarris
};

enum StretchMode {
    StretchMode_Stretch,
    StretchMode_HyperStretch,
    StretchMode_Shorten
};

//

struct Region {
    RegionType type;
    PercentRegion percent;
    AbsoluteRegion absolute;
};

///
struct BatchProcessorImplementation;
struct PlayerImplementation;

/// @brief batch processor class. stub/interface example
struct BatchProcessor {
    BatchProcessorImplementation* _impl = nullptr;

    BatchProcessor();
    ~BatchProcessor();

    void OpenFiles(const std::vector<std::string>& names);

    void OpenConfigurations(const std::vector<std::string>& names);

    void SetRegions(const std::vector<Region>& reg);

    void RenderFiles(const std::vector<std::string>& names);
};

struct Configuration;
struct XMLConfigurationCodec {
    std::string ToXMLString(const Configuration&);
    Configuration FromXMLString(const std::string&);
};

struct ConfigTools {
    Configuration Interpolate(const Configuration& a, const Configuration& b, float fraction);
};

struct Player {
    PlayerImplementation* _impl = nullptr;

    Player();
    ~Player();

    void OpenFile(const std::string& name);
    void OpenConfiguration(const Configuration& cfg);

    void Start();
    void Stop();

    void Seek(float seconds);
};

struct AutomatedFloat {
    AutomatedFloat(const float& src = 0)
        : staticValue(src)
    {
    }

    float staticValue = 0.;
    bool enableAutomation = false;
    std::vector<std::pair<float, float> > points;
};

//template <int MIN, int MAX>
//struct AutomatedRangedFloat {
//    RangedFloat<MIN, MAX> staticValue;
//    bool enableAutomation = false;
//
//    std::vector<std::pair<RangedFloat<0, 1>, RangedFloat<MIN, MAX> > > points;
//};

struct RangeInfo {
    float min = 0;
    float max = 0;
    
    float initial = 0;

    constexpr RangeInfo(const float& min_, const float& max_, const float& initial_)
        : min(min_)
        , max(max_), initial(initial_){};
};

struct Configuration {
    AutomatedFloat stretch = AutomatedFloat(8);

    float windowSize = 4096;
    float onsetSensitivity = .5;

    FFTWindowType windowType = FFTWindowType_Rectangular;
//    StretchMode stretchMode = StretchMode_Stretch;

    bool harmonics = false;
    float hFreq = 440;
    float hBandwidth = 0;
    float hNumberHarm = 10;
    bool hGauss = false;

    bool pitchShift = false;
    float psCents = 0;

    bool freqShift = false;
    float fsFreq = 0;

    bool octaves = false;
    std::array<float, 6> oValues = { 0, 0, 1, 0, 0, 0 }; //-2 -1 0 1 1.5 2

    bool filter = false;
    float fFreq1 = 0;
    float fFreq2 = 0;
    AutomatedFloat fFreqArbitrary;
    bool fBandstop = false;
    float fDamp = 0;

    bool tonalNoise = false;
    float tnAmount = 0;
    float tnBandwidth = 0;

    bool spread = false;
    float spBandwidth = 0;

    bool compress = false;
    float cmPower = 1;

    AutomatedFloat binaural;
};

struct ConfigurationInfo {
    static constexpr RangeInfo stretch = RangeInfo(0.01, 10000,8);
    static constexpr RangeInfo windowSize = RangeInfo(512, 2048 * 1024,4096);
    static constexpr RangeInfo onsetSensitivity = RangeInfo(0, 1,.5);

    static constexpr RangeInfo hFreq = RangeInfo(0, 22050,440);
    static constexpr RangeInfo hBandwidth = RangeInfo(0, 1,0);
    static constexpr RangeInfo hNumberHarm = RangeInfo(0, 100,10);

    static constexpr RangeInfo psCents = RangeInfo(-3600, 3600,0);

    static constexpr RangeInfo fsFreq = RangeInfo(-10000, 10000,0);

    static constexpr RangeInfo oValues = RangeInfo(0, 1,0);

    static constexpr RangeInfo fFreq1= RangeInfo(0, 22050,0);
    static constexpr RangeInfo fFreq2 = RangeInfo(0, 22050,22050);
    static constexpr RangeInfo fFreqArbitrary = RangeInfo(0, 22050,0);
    static constexpr RangeInfo fDamp = RangeInfo(0, 1,0);

    static constexpr RangeInfo tnAmount = RangeInfo(0, 1,0);
    static constexpr RangeInfo tnBandwidth = RangeInfo(0, 1,0);

    static constexpr RangeInfo spBandwidth = RangeInfo(0, 1,0);

    static constexpr RangeInfo cmPower = RangeInfo(0, 1,0);

    static constexpr RangeInfo binaural = RangeInfo(0, 100,0);
    
    template<typename T>
    static const T Clamp(const RangeInfo& r, const T& v){
        if (v<r.min) return r.min;
        if (v>r.max) return r.max;
        return v;
    }
};

struct StretchEngineImplementation;

struct StretchEngine {
    StretchEngineImplementation* _impl = nullptr;

    StretchEngine();
    ~StretchEngine();

    void SetParameters(const Configuration&);
    const Configuration Parameters() const;

    void ProcessBuffer(const std::vector<float>&);
};

// original controller wrapper
struct LegacyControllerImplementation;

struct LegacyController {
    using ErrorCallbackFn = std::function<void(const std::string&)>;
    using CallbackFn = std::function<void(void)>;

    LegacyControllerImplementation* _impl = nullptr;

    LegacyController();
    ~LegacyController();

    LegacyController(const LegacyController&);
    LegacyController& operator=(const LegacyController&);

    //
    void Play();
    // bypass removed
    void Pause();
    void Stop();
    // freeze removed
    void Seek(const float& f);  // fraction??
    const float GetSeek(); // fraction 0..1
    
    //
    bool IsPlaying();
    
    void SetVolume(const float&);
    float Volume();

    // legacy file i/o removed (xml library)

    bool OpenFile(const std::string&);

    void SetParameters(const Configuration&);
    const Configuration Parameters();
    
    //
    float GetRenderPercent();
    void CancelRender();
    //

    void SetRenderRange(const PercentRegion&);
    PercentRegion RenderRange();
    
    void RenderToFile(const std::string&);
    void RenderToFileAsync(const std::string&);

    //
    void SetOnEndPlayback(const CallbackFn&);
    void SetOnFileOpenError(const CallbackFn&);
    void SetOnRenderError(const ErrorCallbackFn&);
};

// common for legacy controller and possible other implementation of standard algorithm:
    struct RenderTaskSetup{
        std::string audioFile;
        std::string outputFile;
        PercentRegion region;
        Configuration configuration;
    };
    
// runs legacy controller in separate thread (currently using RenderToFileAsync)
// renamed from LegacyRenderWorker

struct LegacyRenderWorker{
    LegacyController _ctrl;
    std::string _output;
    std::mutex _mutex;
    
    std::mutex _rendering;
    bool _done = false;
    
    // input file, output file, region, cfg
    LegacyRenderWorker(const std::string&, const std::string&, const PercentRegion&, const Configuration&);
    LegacyRenderWorker(const RenderTaskSetup&);
    
    // mutable:
    LegacyRenderWorker();
    void SetTask(const RenderTaskSetup&);
    
    void StartRender();
    void CancelRender();
    
    float GetRenderPercent();
    
    const bool IsDone() ;
    
};

using LegacyRenderWorkerPtr = std::shared_ptr<LegacyRenderWorker>;



struct BatchProcessorLegacyController {
    BatchProcessorLegacyController();
    
    std::vector<std::string> _inputFiles;
    std::vector<std::string> _configurations;
    std::vector<PercentRegion> _regions;
    std::string _outputFolder;
    
    std::vector<RenderTaskSetup> _taskList;
    
    std::vector<LegacyRenderWorkerPtr> _workers;
    size_t _doneCounter = 0;
    
    void _ScheduleTask(const RenderTaskSetup&);
    LegacyRenderWorkerPtr _GetAvailableWorker();
    
    void OpenFiles(const std::vector<std::string>& names);
    void OpenConfigurations(const std::vector<std::string>& names);
    void SetRegions(const std::vector<PercentRegion>& reg);
    void SetOutputFolder(const std::string&);
    
    static std::string MakeOutputFilename(const std::string& file, const std::string& cfg, const PercentRegion& region, const std::string& outFolder);
    
    void RenderBatchAsync();
    void CancelRender();
    
    

    
    size_t GetActiveWorkerCount();
    float GetWorkerRenderPercent(const size_t& idx);
    
    size_t GetTotalTasks();
    size_t GetDoneTasks();
    size_t GetRemainingTasks();
};

};

#endif
