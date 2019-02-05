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
    playButton.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::limegreen);
    playButton.onClick = [this]() { play(); };
    playButton.addListener(this);
    addAndMakeVisible(playButton);

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
        playButton.setToggleState(true, NotificationType::dontSendNotification);
        playButton.setButtonText("Playing");
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
        playButton.setToggleState(false, NotificationType::dontSendNotification);
        playButton.setButtonText("Stopped");
        Timer::stopTimer();
    }
}

void MainComponent::timerCallback()
{
    timeUI = static_cast<String>(edit.getTransport().getCurrentPosition());
    //DBG("Time: " << edit.getTransport().getCurrentPosition());
    repaint();
}

void MainComponent::buttonClicked (Button* button)
{
   if (button == &playButton)
   {
       if (playState == PlayState::Play)
       {
           playButton.onClick = [&]() { stop(); };
       }
       else
       {
           playButton.onClick = [&]() { play(); };
       }
   }
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
    Rectangle<int> timeUIBounds { 50, 10, 100, 20 };
    
    g.fillAll(Colours::black);
    g.setFont(15.0f);
    g.setColour(Colours::white);
    g.drawText(timeUI, timeUIBounds, Justification::centred);
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    FlexBox flexbox { FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::center, FlexBox::AlignItems::center, FlexBox::JustifyContent::center };
    
    flexbox.items.add(FlexItem(100, 100, playButton));
    flexbox.performLayout(bounds);
}
