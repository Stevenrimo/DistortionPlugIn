/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionVstAudioProcessorEditor::DistortionVstAudioProcessorEditor (DistortionVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	// Creates a visable roatary slider which appears as a Drive Knob with no textbox
	addAndMakeVisible(driveKnob = new Slider("Drive"));
	driveKnob->setSliderStyle(Slider::Rotary);
	driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	// Creates a visable roatary slider which appears as a Range Knob with no textbox
	addAndMakeVisible(rangeKnob = new Slider("Range"));
	rangeKnob->setSliderStyle(Slider::Rotary);
	rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	// Creates a visable roatary slider which appears as a Blend Knob with no textbox
	addAndMakeVisible(blendKnob = new Slider("Blend"));
	blendKnob->setSliderStyle(Slider::Rotary);
	blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	// Creates a visable roatary slider which appears as a Volume Knob with no textbox
	addAndMakeVisible(volumeKnob = new Slider("Volume"));
	volumeKnob->setSliderStyle(Slider::Rotary);
	volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	//links the state of audio to drive knob
	driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(),"drive",*driveKnob);
	//links the state of audio to range knob
	rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);
	//links the state of audio to blend knob
	blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
	//links the state of audio to volume knob
	volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeKnob);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
}

DistortionVstAudioProcessorEditor::~DistortionVstAudioProcessorEditor()
{
}

//==============================================================================
void DistortionVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);

	//adds text to each button
	g.drawText("Drive", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred,false);
	g.drawText("Range", ((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
	g.drawText("Blend", ((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
	g.drawText("Volume", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
}

void DistortionVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	// sets postion of drive knob
	driveKnob->setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	// sets postion of range knob
	rangeKnob->setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	// sets postion of blend knob
	blendKnob->setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	// sets postion of volume knob
	volumeKnob->setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
}
