import paulstretchpy as ps
import bimpy

from tkinter import *
from tkinter.filedialog import askopenfilename

_tk = Tk()
_tk.withdraw()

ctx = bimpy.Context()
ctx.init(1024, 768, "PaulStretch-imgui")

#_test_cfg = ps.Configuration()
_test_player = ps.Player()
_test_batch = ps.BatchProcessor()

_lc = ps.LegacyController()
_parameters = ps.Configuration()

class ViewConfig():
    fileName = None
    configFileName = None
    
    showParameters = False
    renderTask = None

def ranged_slider(name, value, range_info):
    f = bimpy.Float(value)
    ret = None
    rng = (range_info.max-range_info.min)
    spd = .0025*rng if rng>0 else .1
    if bimpy.drag_float("##v_"+name, f, spd,range_info.min, range_info.max):
        ret = ps.ConfigurationInfo.ClampFloat(range_info, f.value)
    bimpy.same_line()
    if bimpy.button("init##b_"+name):
        ret = range_info.initial
    return ret

def edit_autofloat(af, obj_id, range_info):
    ret = False
    
#    f = bimpy.Float(af.staticValue)
#    if bimpy.input_float("##staticValue_"+obj_id+str(id(af.staticValue)),f):
#        af.staticValue = f.value
#        ret = True

    # +str(id(af.staticValue))
    r = ranged_slider(obj_id, af.staticValue, range_info)
    if r != None:
        af.staticValue = r
        ret = True

    # yet disabled:
#    b = bimpy.Bool(af.enableAutomation)
#    if bimpy.checkbox("Auto##_"+obj_id+str(id(af.enableAutomation)),b):
#        print(obj_id)
#        af.enableAutomation = b.value
#        ret = True

    return ret

def edit_config(cfg):
    bimpy.begin("Parameters")
    ret = False

    bimpy.columns(2)
    
    bimpy.text("Stretch")

    bimpy.next_column()
    if edit_autofloat(cfg.stretch,"stretch", ps.ConfigurationInfo.stretch):
        ret = True

    bimpy.next_column()
    bimpy.separator()

    bimpy.text("Window Size")

    bimpy.next_column()

    r = ranged_slider("windowSize",cfg.windowSize, ps.ConfigurationInfo.windowSize)
    if r != None:
        cfg.windowSize = r
        ret = True

    bimpy.next_column()
    bimpy.separator()

    bimpy.text("Onset Sensitivity")

    bimpy.next_column()

    r = ranged_slider("onsetSensitivity",cfg.onsetSensitivity, ps.ConfigurationInfo.onsetSensitivity)
    if r != None:
        cfg.onsetSensitivity = r
        ret = True

    bimpy.next_column()
    bimpy.separator()

    bimpy.separator()

    bimpy.text("Harmonics:")
    #bimpy.separator()
    bimpy.next_column()
    b = bimpy.Bool(cfg.harmonics)
    if bimpy.checkbox("##harmonics",b):
        cfg.harmonics = b.value

    bimpy.next_column()
    bimpy.separator()

    if b.value:
        bimpy.text("Freq")

        bimpy.next_column()

        r = ranged_slider("hFreq",cfg.hFreq, ps.ConfigurationInfo.hFreq)
        if r != None:
            cfg.hFreq = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Bandwidth")

        bimpy.next_column()

        r = ranged_slider("hBandwidth",cfg.hBandwidth, ps.ConfigurationInfo.hBandwidth)
        if r != None:
            cfg.hBandwidth = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Count")
        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.hNumberHarm))

        r = ranged_slider("hNumberHarm",cfg.hNumberHarm, ps.ConfigurationInfo.hNumberHarm)
        if r != None:
            cfg.hNumberHarm = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Gaussian")
        #bimpy.separator()
        bimpy.next_column()

        bimpy.text(str(cfg.hGauss))

#        r = ranged_slider("hGauss",cfg.hGauss, ps.ConfigurationInfo.hGauss)
#        if r != None:
#            cfg.hGauss = r
#            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.separator()

    bimpy.text("Pitch Shift")
    
    
    bimpy.next_column()
    b = bimpy.Bool(cfg.pitchShift)
    if bimpy.checkbox("##pitchShift",b):
        cfg.pitchShift = b.value
    bimpy.next_column()
    bimpy.separator()

    if b.value:
        bimpy.text("Cents")
        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.psCents))

        r = ranged_slider("psCents",cfg.psCents, ps.ConfigurationInfo.psCents)
        if r != None:
            cfg.psCents = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.separator()

    bimpy.text("Freq Shift")
    #bimpy.separator()
    bimpy.next_column()
    b = bimpy.Bool(cfg.freqShift)
    if bimpy.checkbox("##freqShift",b):
        cfg.freqShift = b.value
    bimpy.next_column()
    bimpy.separator()

    if b.value:
        bimpy.text("Freq")
        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.fsFreq))

        r = ranged_slider("fsFreq",cfg.fsFreq, ps.ConfigurationInfo.fsFreq)
        if r != None:
            cfg.fsFreq = r
            ret = True
        
        bimpy.next_column()
        bimpy.separator()

        bimpy.separator()

    bimpy.text("Filter")
    #bimpy.separator()
    bimpy.next_column()
    b = bimpy.Bool(cfg.filter)
    if bimpy.checkbox("##filter",b):
        cfg.filter = b.value
    bimpy.next_column()
    bimpy.separator()

    if b.value:
        bimpy.text("Freq 1")
        #bimpy.separator()
        bimpy.next_column()
        
#        bimpy.text(str(cfg.fFreq1))
        r = ranged_slider("fFreq1",cfg.fFreq1, ps.ConfigurationInfo.fFreq1)
        if r != None:
            cfg.fFreq1 = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Freq 2")


        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.fFreq2))

        r = ranged_slider("fFreq2",cfg.fFreq2, ps.ConfigurationInfo.fFreq2)
        if r != None:
            cfg.fFreq2 = r
            ret = True
        
        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Arbitrary Freq")
        #bimpy.separator()
        bimpy.next_column()
        edit_autofloat(cfg.fFreqArbitrary,"fFreqArbitrary",ps.ConfigurationInfo.fFreqArbitrary)
        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Bandstop")
        #bimpy.separator()
        bimpy.next_column()
        bimpy.text(str(cfg.fBandstop))
        bimpy.next_column()
        bimpy.separator()

        bimpy.separator()

    bimpy.text("Tonal / Noise")
    #bimpy.separator()
    bimpy.next_column()
    b = bimpy.Bool(cfg.tonalNoise)
    if bimpy.checkbox("##tonalNoise",b):
        cfg.tonalNoise = b.value
    #bimpy.text(str(cfg.tonalNoise))
    bimpy.next_column()
    bimpy.separator()

    if b.value:
        bimpy.text("Amount")
        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.tnAmount))
        r = ranged_slider("tnAmount",cfg.tnAmount, ps.ConfigurationInfo.tnAmount)
        if r != None:
            cfg.tnAmount = r
            ret = True
        
        bimpy.next_column()
        bimpy.separator()

        bimpy.text("Bandwidth")
        #bimpy.separator()
        bimpy.next_column()
#        bimpy.text(str(cfg.tnBandwidth))
        r = ranged_slider("tnBandwidth",cfg.tnBandwidth, ps.ConfigurationInfo.tnBandwidth)
        if r != None:
            cfg.tnBandwidth = r
            ret = True

        bimpy.next_column()
        bimpy.separator()

        bimpy.separator()

    bimpy.text("Compress")
    #bimpy.separator()
    bimpy.next_column()
#    bimpy.text(str(cfg.compress))
    b = bimpy.Bool(cfg.compress)
    if bimpy.checkbox("##compress",b):
        cfg.compress = b.value
    bimpy.next_column()
    bimpy.separator()

    bimpy.separator()

    bimpy.text("Binaural")
    #bimpy.separator()
    bimpy.next_column()
    edit_autofloat(cfg.binaural,"binaural",ps.ConfigurationInfo.binaural)
    bimpy.next_column()
    bimpy.separator()
    
    bimpy.end()

    return ret

#def view_single_file(pl):
#    bimpy.begin("Single File")
#
#    if bimpy.button("Open File"):
#        fn = askopenfilename(filetypes=(("WAV/AIFF file", "*.wav;*.aif;*.aiff")))
#        if fn:
#
#    bimpy.button("Open Configuration")
#    bimpy.separator()
#    bimpy.checkbox("Edit Configuration", bimpy.Bool(False))
#    bimpy.separator()
#    bimpy.button("Play")
#    bimpy.same_line()
#    bimpy.slider_float("##seek",bimpy.Float(0),0,1)
#    bimpy.separator()
#    bimpy.slider_float("Start##region_start",bimpy.Float(0),0,1)
#    bimpy.slider_float("End##region_end",bimpy.Float(1),0,1)
#    bimpy.button("Render file")
#    bimpy.end()

def view_legacy_controller(pl):
    bimpy.begin("Single File")
    
    bimpy.text("No file" if not ViewConfig.fileName else ViewConfig.fileName)
    
    if bimpy.button("Open File"):
        fn = askopenfilename(filetypes=( ("WAV files", "*.wav"), ("AIFF files","*.aif") ) )
        if fn:
            _lc.OpenFile(fn)
            ViewConfig.fileName = fn

    bimpy.text("No configuration file" if not ViewConfig.configFileName else ViewConfig.configFileName)

    if bimpy.button("Open Configuration"):
        fn = askopenfilename(filetypes=( ("JSON files", "*.ps.json"), ("All files","*.*") ) )

    if bimpy.button("Save Configuration"):
        pass

    bimpy.separator()

    vcfg = bimpy.Bool(ViewConfig.showParameters)
    if bimpy.checkbox("Edit Configuration", vcfg):
        ViewConfig.showParameters = vcfg.value
    
    bimpy.separator()
    if (not _lc.IsPlaying()):
        if bimpy.button("Play"):
            _lc.Play()
            bimpy.same_line()
    
    if (_lc.IsPlaying()):
        if bimpy.button("Stop"):
            _lc.Stop()

    bimpy.same_line()

    f = bimpy.Float(_lc.GetSeek())
    if bimpy.slider_float("##seek",f,0,1):
        if (not _lc.IsPlaying()):
            _lc.Seek(f.value)
            #bimpy.text(str(_lc.GetSeek()));
    bimpy.separator()
    bimpy.slider_float("Start##region_start",bimpy.Float(0),0,1)
    bimpy.slider_float("End##region_end",bimpy.Float(1),0,1)
    if bimpy.button("Render file (default)"):
        path = os.path.abspath(__file__)
        output_file = os.path.dirname(path)+"/render.wav"
        _lc.RenderToFile(output_file)
#    bimpy.text("render: "+str(_lc.GetRenderPercent()))
#    if bimpy.button("Cancel"):
#        _lc.CancelRender()

#    if bimpy.button("Render async (default)"):
#        path = os.path.abspath(__file__)
#        output_file = os.path.dirname(path)+"/render_async.wav"
#        _lc.RenderToFileAsync(output_file)
#    bimpy.text(str(_lc.GetRenderPercent()))
#    bimpy.button("Cancel Render")
#
#    if bimpy.button("Render Task"):
#        if not ViewConfig.renderTask:
#            path = os.path.abspath(__file__)
#            input_file = os.path.dirname(path)+"/test_file.wav"
#            output_file = os.path.dirname(path)+"/render-task.wav"
#
#            ViewConfig.renderTask = ps.LegacyRenderTask(input_file, output_file, _lc.RenderRange(), _lc.Parameters());
#            ViewConfig.renderTask.StartRender()
#    if ViewConfig.renderTask:
#        bimpy.text(str(ViewConfig.renderTask.GetRenderPercent()))
#        bimpy.button("Cancel Render")
#    bimpy.end()

    #
    if ViewConfig.showParameters:
        #cfg = _lc.Parameters()
        if edit_config(_parameters) == True:
            _lc.SetParameters(_parameters)
            print("edit")
            pass

def view_batch(bp):
    bimpy.begin("Batch")
    bimpy.button("Open files...")
    bimpy.button("Open configurations...")
    bimpy.separator()
    bimpy.text("Regions:")
    bimpy.separator()
    bimpy.button("Render Files")
    bimpy.end()

def test_window():
    view_legacy_controller(_lc)    
    view_batch(_test_batch)

import os
path = os.path.abspath(__file__)
input_file = os.path.dirname(path)+"/test_file.wav"

#_parameters.stretch.staticValue = 2
#_parameters.windowSize = 512

#_lc.OpenFile(input_file)
_lc.OpenFile(input_file)
_lc.SetParameters(_parameters)

while(not ctx.should_close()):
    with ctx:
        test_window()


