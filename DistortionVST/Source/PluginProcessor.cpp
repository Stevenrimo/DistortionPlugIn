/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionVstAudioProcessor::DistortionVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	//contrusctor for state of audio
	state = new AudioProcessorValueTreeState(*this, nullptr);

	//paramenters for constructor on Drive Knob
	state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr);
	//paramenters for constructor on range knob
	state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.f, 3000.f, 0.0001), 1.0, nullptr, nullptr);
	//paramenters for constructor on blend Knob
	state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr);
	//paramenters for constructor on volume Knob
	state->createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.f, 3.f, 0.0001), 1.0, nullptr, nullptr);

	//Stores value tree states in memory for drive knob
	state->state = ValueTree("drive");
	//Stores value tree states in memory for range knob
	state->state = ValueTree("range");
	//Stores value tree states in memory for blend knob
	state->state = ValueTree("blend");
	//Stores value tree states in memory for volume knob
	state->state = ValueTree("volume");
}

DistortionVstAudioProcessor::~DistortionVstAudioProcessor()
{
}

//==============================================================================
const String DistortionVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVstAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionVstAudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortionVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionVstAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

	// gets the paramter value for the drive
	float drive = *state->getRawParameterValue("drive");
	// gets the paramter value for the range
	float range = *state->getRawParameterValue("range");
	// gets the paramter value for the blend
	float blend = *state->getRawParameterValue("blend");
	// gets the paramter value for the volume
	float volume = *state->getRawParameterValue("volume");


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
		for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
			//saves the clean signal to memory
			float cleanSig = *channelData;

			//sets channel data to the drive times the range
			*channelData *= drive * range;

			// Formula for clipping the drive of audio 
			// a = 2/Pi * arctan(input) (smooth and never equals 1)
			// b = a * blend
			// c = b + cleansignal * percent of blend / 2 (gets average)
			// d = c * volume (makes it loud boi)
			*channelData = (((((2.f / float_Pi) * atan(*channelData)) * blend) + (cleanSig * (1.f - blend))) / 2.f) * volume;

			//points to next point of channel data
			channelData++;

		}
		
    }
}

// Function to get State of Audio 
AudioProcessorValueTreeState& DistortionVstAudioProcessor::getState() {
	return *state;
}

//==============================================================================
bool DistortionVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionVstAudioProcessor::createEditor()
{
    return new DistortionVstAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Method to store parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	MemoryOutputStream stream(destData, false);
	state->state.writeToStream(stream);
}

void DistortionVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	//checks if the value tree is valid
	if (tree.isValid()) {
		state->state = tree;
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionVstAudioProcessor();
}
