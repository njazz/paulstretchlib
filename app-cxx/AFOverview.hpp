#include <string>
#include <vector>

struct AFOverviewImpl;

struct AFOverview {
    size_t _dataSize = 512;
    
    float _scaleFraction = 1.;
    float _scrollFraction = 0.; // scroll = _scrollFraction 0..1 * (1-_scaleFraction)
    
    std::vector<float> _data;
    size_t _fileSize = 0;
    
    AFOverviewImpl* _impl = nullptr;
    
    AFOverview();
    AFOverview(const AFOverview&);
    AFOverview& operator=(const AFOverview&);
    ~AFOverview();
    
    void _ReloadData();
    
    void OpenFile(const std::string fn);
    
    void SetDataSize(const size_t& s);
    
    const std::vector<float>& GetData() { return _data;};
    
    // 0..1, sample-to-sample .. full file
    void SetScaleFraction(const float& f);
    const float ScaleFraction() { return _scaleFraction; }
    
    void SetScrollFraction(const float& f);
    const float ScrollFraction() { return _scrollFraction; }
    
    
    //
    // 0..1 of file length to (pixel) x coordinate
    size_t FractionToViewCoord(const float& f);
    // and reverse
    float ViewCoordToFraction(const size_t& v);
};
