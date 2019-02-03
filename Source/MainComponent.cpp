/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    playButton.setToggleState(false, NotificationType::dontSendNotification);
    playButton.onClick = [this]() { play(); };
    addAndMakeVisible(playButton);
    
    stopButton.setToggleState(true, NotificationType::dontSendNotification);
    stopButton.onClick = [this]() { stop(); };
    addAndMakeVisible(stopButton);
    
    setSize (200, 200);
    setAudioChannels (2, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::play()
{
    if (playState == PlayState::Stop)
    {
        playState = PlayState::Play;
        edit.getTransport().play(false);
        Timer::startTimer (100);
    }
}

void MainComponent::stop()
{
    if (playState == PlayState::Play)
    {
        playState = PlayState::Stop;
        edit.getTransport().stop(true, false);
        Timer::stopTimer();
    }
}

void MainComponent::timerCallback()
{
    DBG("Time: " << edit.getTransport().getCurrentPosition());
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    FlexBox flexbox { FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::center };
    
    flexbox.items.add(FlexItem(100, 100, playButton));
    flexbox.items.add(FlexItem(100, 100, stopButton));
    
    flexbox.performLayout(bounds);
    
}
