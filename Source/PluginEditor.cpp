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

void ColourBall::paintGl (Graphics& g)
{
    Rectangle<float> area(areaX.get(), areaY.get(), areaW.get(), areaH.get());
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
    glContext.setSwapInterval(1);
    glContext.attachTo(*this);

    for (int b = 0; b < 100; b++)
    {
        auto ball = colourBalls.add(new ColourBall());
    }
    setSize (400, 300);
    startTimerHz(30);
}

GLAbletonTestAudioProcessorEditor::~GLAbletonTestAudioProcessorEditor()
{
    const ScopedLock lock(exitLock);
}

void GLAbletonTestAudioProcessorEditor::timerCallback()
{
    for (auto& b : colourBalls)
    {
        auto randX = getWidth() * rand.nextFloat();
        auto randY = getHeight() * rand.nextFloat();
        b->areaX.set(randX);
        b->areaY.set(randY);
        b->areaW.set(20);
        b->areaH.set(20);
    }
}

void GLAbletonTestAudioProcessorEditor::renderOpenGL()
{
    const ScopedLock lock(exitLock);
    std::unique_ptr<LowLevelGraphicsContext> glRenderer(createOpenGLGraphicsContext(glContext, getWidth(), getHeight()));
    Graphics g (*glRenderer);
    g.fillAll(Colours::black);
    for (auto& b : colourBalls)
    {
        Graphics::ScopedSaveState save(g); 
        g.addTransform(AffineTransform().translated(b->areaX.get(), b->areaY.get()));
        b->paintGl(g);
    }
       
}

//==============================================================================
void GLAbletonTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
  // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void GLAbletonTestAudioProcessorEditor::resized()
{



}