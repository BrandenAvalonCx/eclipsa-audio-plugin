// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "SegmentedToggleButton.h"

#include "components/src/EclipsaColours.h"

STBLookAndFeel::STBLookAndFeel() {
  // Text colours.
  setColour(juce::TextButton::textColourOffId, EclipsaColours::tabTextGrey);
  setColour(juce::TextButton::ColourIds::textColourOnId,
            EclipsaColours::tabTextGrey);

  // Button colours.
  // NOTE: Setting background to BLACK for consistency.
  setColour(juce::TextButton::ColourIds::buttonColourId,
            EclipsaColours::backgroundOffBlack);
  setColour(juce::TextButton::ColourIds::buttonOnColourId,
            EclipsaColours::onButtonGrey);
}

void STBLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& btn,
                                    bool shouldDrawButtonAsHighlighted,
                                    bool shouldDrawButtonAsDown) {
  auto bounds = btn.getLocalBounds();
  // If the button is toggled on, shift text right.
  int offset = 0;
  if (btn.getToggleState()) {
    offset = 10;
  }
  g.drawFittedText(btn.getButtonText(), bounds.getX() + offset, bounds.getY(),
                   bounds.getWidth(), bounds.getHeight(),
                   juce::Justification::centred, 1, 0.2f);
}

void STBLookAndFeel::drawButtonBackground(juce::Graphics& g,
                                          juce::Button& button,
                                          const juce::Colour& backgroundColour,
                                          bool isMouseOverButton,
                                          bool isButtonDown) {
  juce::Colour backColour = backgroundColour;
  if (!button.isToggleable()) {
    backColour = EclipsaColours::ambisonicsFillGrey;
  } else if (isMouseOverButton || button.getToggleState()) {
    backColour = findColour(juce::TextButton::buttonOnColourId);
  }
  g.setColour(backColour);

  // Draw button as rounded if necessary.
  auto buttonBounds = button.getLocalBounds();
  const float kCornerSize = buttonBounds.getHeight() / 2.f;
  const float kStroke = 1.5f;
  // These two constants are to attempt to circumvent JUCE anti-aliasing alg.
  const float kYOffset = 0.24f;
  const float kHOffset = -0.54f;
  bool leftmost = !button.isConnectedOnLeft();
  bool rightmost = !button.isConnectedOnRight();
  if (rightmost) {
    juce::Path path;
    path.addRoundedRectangle(
        buttonBounds.getX() - 1, buttonBounds.getY() + kYOffset,
        buttonBounds.getWidth(), buttonBounds.getHeight() + kHOffset,
        kCornerSize, kCornerSize, false, true, false, true);
    g.fillPath(path);
    g.setColour(button.findColour(juce::TextButton::ColourIds::textColourOnId));
    g.strokePath(path, juce::PathStrokeType(kStroke));

  } else if (leftmost) {
    juce::Path path;
    path.addRoundedRectangle(
        buttonBounds.getX() + 1, buttonBounds.getY() + kYOffset,
        buttonBounds.getWidth(), buttonBounds.getHeight() + kHOffset,
        kCornerSize, kCornerSize, true, false, true, false);
    g.fillPath(path);
    g.setColour(button.findColour(juce::TextButton::ColourIds::textColourOnId));
    g.strokePath(path, juce::PathStrokeType(kStroke));
  } else {
    g.fillRect(buttonBounds);
    g.setColour(button.findColour(juce::TextButton::ColourIds::textColourOnId));
    g.drawRect(buttonBounds, 1.0f);
  }

  // If the button is toggled on draw a checkmark.
  if (button.getToggleState()) {
    g.drawImageWithin(
        IconStore::getInstance().getCheckmarkIcon(), buttonBounds.getX() + 10,
        buttonBounds.getY(), buttonBounds.getWidth(), buttonBounds.getHeight(),
        juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yMid |
            juce::RectanglePlacement::onlyReduceInSize);
  }
}

SegmentedToggleButton::SegmentedToggleButton(
    const std::initializer_list<juce::String>& opts, const bool singularToggle)
    : kSingularToggle_(singularToggle) {
  for (const juce::String& opt : opts) {
    buttons_.emplace_back(std::make_unique<juce::TextButton>(opt, opt));
  }
  configureButtons();
  setLookAndFeel(&lookAndFeel_);
}

void SegmentedToggleButton::paint(juce::Graphics& g) {
  auto bounds = getLocalBounds();
  // Draw buttons.
  int buttonWidth = bounds.getWidth() / buttons_.size();
  for (int i = 0; i < buttons_.size(); ++i) {
    auto buttonBounds = bounds.removeFromLeft(buttonWidth);
    if (i == 0) {
      buttonBounds.removeFromLeft(1);
    } else if (i == buttons_.size() - 1) {
      buttonBounds.removeFromRight(1);
    }
    buttons_[i]->setBounds(buttonBounds);
  }
}

void SegmentedToggleButton::setToggleable(const juce::String& opt,
                                          const bool enable) {
  for (const auto& button : buttons_) {
    if (button->getButtonText() == opt) {
      button->setClickingTogglesState(enable);
    }
  }
}

void SegmentedToggleButton::toggleOn(const juce::String& opt) {
  for (const auto& button : buttons_) {
    if (button->getButtonText() == opt) {
      button->setToggleState(true, true);
    }
  }
}

bool SegmentedToggleButton::getOption(const juce::String& opt) const {
  for (const auto& button : buttons_) {
    if (button->getButtonText() == opt) {
      return button->getToggleState();
    }
  }
}

void SegmentedToggleButton::setOption(const juce::String& opt,
                                      const bool state) {
  for (const auto& button : buttons_) {
    if (button->getButtonText() == opt) {
      button->setToggleState(state, true);
    }
  }
}

std::vector<juce::String> SegmentedToggleButton::getToggled() {
  std::vector<juce::String> selected;
  for (const auto& button : buttons_) {
    if (button->getToggleState()) {
      selected.push_back(button->getButtonText());
    }
  }
  return selected;
}

std::vector<std::pair<juce::String, bool>> SegmentedToggleButton::getState() {
  std::vector<std::pair<juce::String, bool>> state;
  for (const auto& button : buttons_) {
    state.push_back({button->getButtonText(), button->getToggleState()});
  }
  return state;
}

void SegmentedToggleButton::configureButtons() {
  for (const auto& button : buttons_) {
    button->setClickingTogglesState(true);
    button->onClick = [this, &button] { toggleButton(button.get()); };

    // Explicitly record which button edges are connected.
    if (button == buttons_.front()) {
      button->setConnectedEdges(
          juce::Button::ConnectedEdgeFlags::ConnectedOnRight);
    } else if (button == buttons_.back()) {
      button->setConnectedEdges(
          juce::Button::ConnectedEdgeFlags::ConnectedOnLeft);
    } else {
      button->setConnectedEdges(
          juce::Button::ConnectedEdgeFlags::ConnectedOnLeft |
          juce::Button::ConnectedEdgeFlags::ConnectedOnRight);
    }
    addAndMakeVisible(button.get());
  }
}

void SegmentedToggleButton::toggleButton(juce::Button* btn) {
  // Set toggle states if singular toggle.
  if (kSingularToggle_ && btn->getToggleState()) {
    for (const auto& button : buttons_) {
      bool toggleState = button.get() == btn ? true : false;
      button->setToggleState(toggleState, true);
    }
  }
  parentCallback_();
}