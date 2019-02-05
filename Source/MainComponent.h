/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Timer,
                        public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void play();
    void stop();
    void timerCallback() override;
    void buttonClicked (Button* button) override;

private:
    tracktion_engine::Engine engine { ProjectInfo::projectName };
    tracktion_engine::Edit edit { engine, tracktion_engine::createEmptyEdit(), tracktion_engine::Edit::EditRole::forEditing, nullptr, 0  };
    
    enum class PlayState
    {
        Play,
        Stop
    };
    
    String timeUI { "" };
    PlayState playState { PlayState::Stop };
    TextButton playButton { "Stopped" };
    
    //==============================================================================
    // Your private member variables go here...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
