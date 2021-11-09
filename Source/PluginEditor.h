/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/


class ColourBall : public juce::Component
{
public:
    ColourBall();
    void paintGl (Graphics& g) ;
    void resized() override;

    CriticalSection glVarLock;

private:
    juce::Random rand;

    
    Rectangle<float> area;


   
};

class GLAbletonTestAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer, public juce::OpenGLRenderer
{
public:
    GLAbletonTestAudioProcessorEditor (GLAbletonTestAudioProcessor&);
    ~GLAbletonTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::OpenGLContext glContext;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GLAbletonTestAudioProcessor& audioProcessor;

    void newOpenGLContextCreated() override {}
    void  	openGLContextClosing() override {}
    void            renderOpenGL() override;
    

    juce::OwnedArray<ColourBall> colourBalls;
    juce::Random rand;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GLAbletonTestAudioProcessorEditor)
};
