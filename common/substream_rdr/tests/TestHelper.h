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
#include <juce_audio_utils/juce_audio_utils.h>

#include <vector>

inline void populateInput(juce::AudioBuffer<float>& buff) {
  for (int i = 0; i < buff.getNumChannels(); ++i) {
    for (int j = 0; j < buff.getNumSamples(); ++j) {
      buff.setSample(i, j, 1);
    }
  }
}

inline std::vector<float> examineRdrOutput(
    const juce::AudioBuffer<float>& outBuff) {
  std::vector<float> outBuffContents;
  for (int outChIdx = 0; outChIdx < outBuff.getNumChannels(); ++outChIdx) {
    outBuffContents.push_back(*outBuff.getReadPointer(outChIdx));
  }
  return outBuffContents;
}