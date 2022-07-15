# Loopty Loop
<img src="https://user-images.githubusercontent.com/67290936/179236412-1db42e19-7469-4bf0-9322-2515665f2194.png" alt="screenshot" width="500"/>

## Overview
Loopty Loop is a desktop audio looping sampler built as a Computer Science project in a three-person team. It supports both live recording and file uploading for up to four tracks, and allows for realtime adjustment of various track parameters. It is built for Windows using the [JUCE framework](https://juce.com/).

This repository is a fork of the original repository used during development, with no changes besides this README.

## Controls
1. To add audio to a track, first check the "Arm" checkbox for the desired track.
2. Then, you may either click the red record button to start recording from audio input. Or, click "Load Track" to select an audio file.
3. You can start / stop playback using the play button (green) or the stop button (black).
4. Volume can be adjusted using the sliders in the bottom right.
5. The "Pan" knob controls a track's L/R pan, while the "Slip" knob adds offset to the beginning of a track.
6. The "Rev" checkbox will reverse a track in realtime.
7. The "Mute" checkbox will silence a track, and the "Solo" checkbox will silence all other tracks.
8. The default audio input device can be adjusted under "Audio Settings."

## Build Instructions
1. Ensure you have JUCE [installed on your machine](https://juce.com/get-juce), and Visual Studio 2019 or later with MSVC (C++ compiler).
2. Download this repository to your machine.
3. Open `Loopy Loop.juicer` in the root directory using Projucer, which should have come with the JUCE installation.
4. Inside Projucer, click the Visual Studio button near the top of the window to load the project into Visual Studio.
5. Inside Visual Studio, you can use "Build -> Build Solution" to compile the .exe for the program.
