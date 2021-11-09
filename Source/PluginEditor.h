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

private:
    juce::Random rand;

    void paint(juce::Graphics& g) override;
};

class GLAbletonTestAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    GLAbletonTestAudioProcessorEditor (GLAbletonTestAudioProcessor&);
    ~GLAbletonTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GLAbletonTestAudioProcessor& audioProcessor;
    juce::OpenGLContext glContext;

    juce::OwnedArray<ColourBall> colourBalls;
    juce::Random rand;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GLAbletonTestAudioProcessorEditor)
};
