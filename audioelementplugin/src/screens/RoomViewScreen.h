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

#include "../AudioElementPluginProcessor.h"
#include "components/components.h"
#include "data_repository/implementation/AudioElementSpatialLayoutRepository.h"
#include "data_structures/src/AudioElementParameterTree.h"

class RoomViewScreen : public juce::Component,
                       public juce::ValueTree::Listener,
                       juce::Timer {
 public:
  RoomViewScreen(
      AudioElementPluginSyncClient* syncClient,
      AudioElementSpatialLayoutRepository* audioElementSpatialLayoutRepo,
      AudioElementParameterTree* tree, const SpeakerMonitorData& repos);

  ~RoomViewScreen();

  void paint(juce::Graphics& g) override;
  void updateSpeakerSetup(const Speakers::AudioElementSpeakerLayout& layout) {
    room_->setSpeakers(layout);
  }

 private:
  void elevationChangeCallback();
  void timerCallback() override;
  void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged,
                                const juce::Identifier& property) override;

  AudioElementPluginSyncClient* syncClient_;
  AudioElementSpatialLayoutRepository* audioElementSpatialLayoutRepository_;
  AudioElementParameterTree* parameterTree_;
  std::unique_ptr<AudioElementPluginRearView> room_;
  SegmentedToggleImageButton selRoomElevation_;
  std::function<void()> onRoomElevationChange_;
  const SpeakerMonitorData& spkrData_;
};