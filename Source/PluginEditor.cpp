/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

ColourBall::ColourBall()
{

}

void ColourBall::paint (Graphics& g)
{
    const auto area = getLocalBounds().toFloat();
    juce::ColourGradient gradient(juce::Colour((juce::uint8)rand.nextInt(255), (juce::uint8)rand.nextInt(255), (juce::uint8)rand.nextInt(255)),
        area.getCentreX(), area.getCentreY(),
        juce::Colour((juce::uint8)rand.nextInt(255), (juce::uint8)rand.nextInt(255), (juce::uint8)rand.nextInt(255)),
        area.getTopLeft().getX(), area.getTopLeft().getY(),
        true);
    g.setGradientFill(gradient);
    g.fillEllipse(area);
}



//==============================================================================
GLAbletonTestAudioProcessorEditor::GLAbletonTestAudioProcessorEditor (GLAbletonTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    glContext.setRenderer(this);
    glContext.setContinuousRepainting(true);

    for (int b = 0; b < 5; b++)
    {
        auto ball = colourBalls.add(new ColourBall());
        addAndMakeVisible(ball);
        ball->setSize (20, 20);
    }
    setSize (400, 300);
    startTimerHz(30);
}

GLAbletonTestAudioProcessorEditor::~GLAbletonTestAudioProcessorEditor()
{
}

void GLAbletonTestAudioProcessorEditor::timerCallback()
{
    for (auto& b : colourBalls)
    {
        auto randX = getWidth() * rand.nextFloat();
        auto randY = getHeight() * rand.nextFloat();
        b->setCentrePosition(randX, randY);
    }
}

void GLAbletonTestAudioProcessorEditor::renderOpenGL()
{
    std::unique_ptr<LowLevelGraphicsContext> glRenderer(createOpenGLGraphicsContext(glContext, getWidth(), getHeight()));
    Graphics g(*glRenderer);

    for (auto b : colourBalls)
        b->paint(g);
}

//==============================================================================
void GLAbletonTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void GLAbletonTestAudioProcessorEditor::resized()
{

}
