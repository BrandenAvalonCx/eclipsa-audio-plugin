/*
 * Copyright 2025 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <components/components.h>

#include "AudioElementPluginProcessor.h"
#include "components/src/SelectionBox.h"
#include "components/src/SliderButton.h"
#include "components/src/TitledTextBox.h"
#include "data_repository/implementation/AudioElementSpatialLayoutRepository.h"
#include "screens/PositionSelectionScreen.h"
#include "screens/RoomViewScreen.h"
#include "screens/TrackMonitorScreen.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
 public:
  CustomLookAndFeel();

  void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                            const juce::Colour& backgroundColour,
                            bool isMouseOverButton, bool isButtonDown) override;
};

//==============================================================================
class AudioElementPluginEditor final : public juce::AudioProcessorEditor,
                                       public AudioElementPluginListener {
 public:
  explicit AudioElementPluginEditor(AudioElementPluginProcessor& p);
  ~AudioElementPluginEditor() override;

  void audioElementsUpdated() override;

  //==============================================================================
  void setAudioElementSelection();

  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  RoomLayout layout_;
  CustomLookAndFeel customLookAndFeel_;
  bool panningAvailable_;

  juce::Label titleLabel_;
  juce::Label panningControlsLabel_;
  SliderButton panningControls_;
  juce::Component* currentScreen_;

  AudioElementSpatialLayoutRepository* audioElementSpatialLayoutRepository_;
  AudioElementPluginSyncClient* syncClient_;

  PositionSelectionScreen positionSelectionScreen_;
  RoomViewScreen roomViewScreen_;
  TrackMonitorScreen trackMonitorScreen_;

  TitledTextBox trackNameTextBox_;
  TitledTextBox outputModeTypeLabel_;
  SelectionBox audioElementSelectionBox_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioElementPluginEditor)
};
