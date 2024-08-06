# HarmonicVoyage
An artistic journey through sound and math, visualized in code.

# Jingle Bells Synth

## Advanced Audio Synthesis and Visualization Project

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![License](https://img.shields.io/badge/license-BSD--3--Clause-blue.svg)

### Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [System Requirements](#system-requirements)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Technical Details](#technical-details)
7. [Architecture](#architecture)
8. [Performance Optimization](#performance-optimization)
9. [Future Enhancements](#future-enhancements)
10. [Contributing](#contributing)
11. [License](#license)

---

### Introduction

Jingle Bells Synth is a state-of-the-art audio synthesis and visualization project that demonstrates advanced techniques in digital signal processing, real-time audio generation, and graphical rendering. This project synthesizes the "Jingle Bells" melody using various waveforms and applies envelope shaping, while simultaneously providing a high-performance, real-time spectral analysis visualization.

---

### Features

- **Advanced Waveform Synthesis**: Generates sine, square, triangle, and sawtooth waves with high precision.
- **ADSR Envelope Shaping**: Applies attack, decay, sustain, and release envelopes to each note for realistic sound shaping.
- **Real-time Spectral Analysis**: Performs fast Fourier transform (FFT) based spectral analysis on the audio output.
- **High-performance Visualization**: Utilizes GPU-accelerated rendering for smooth, real-time spectrum visualization.
- **Optimized Audio Processing**: Employs efficient algorithms for minimal CPU usage and low-latency output.

---

### System Requirements

- **OS**: Debian-based Linux distribution (Ubuntu 20.04 LTS or later recommended)
- **CPU**: x86_64 architecture, 2.0 GHz dual-core or better
- **RAM**: 4 GB minimum, 8 GB recommended
- **GPU**: OpenGL 3.3 compatible graphics card
- **Audio**: ALSA-compatible audio device
- **Development Tools**: GCC 9.3.0 or later, Make 4.2.1 or later

---

### Installation

1. **Clone the repository:**
    - `git clone https://github.com/yezzfusl/HarmonicVoyage.git`
    - `cd HarmonicVoyage`
    
2. **Install dependencies:**
    - `sudo apt-get update`
    - `sudo apt-get install gcc make libsdl2-dev libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev`

3. **Install Raylib:**
    - `git clone https://github.com/raysan5/raylib.git`
    - `sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev`
    - `cd raylib/src/`
    - `make PLATFORM=PLATFORM_DESKTOP # To make the static version.`
    - `sudo make install # Static version.`

4. **Build the project:**
    - `cd HarmonicVoyage/build`
    - `make clean && make`

---

### Usage

- Run the executable from the build directory:
    - `./jingle_bells_synth`

- The application will start playing the Jingle Bells melody and display the real-time spectral analysis. Close the window to exit the program.

---

### Technical Details

#### Audio Synthesis

- **Sample Rate**: 44.1 kHz
- **Bit Depth**: 16-bit signed integer
- **Waveforms**: Sine, Square, Triangle, Sawtooth
- **Envelope**: ADSR (Attack, Decay, Sustain, Release)

#### Spectral Analysis

- **FFT Size**: 2048 samples
- **Window Function**: Hann window
- **Frequency Resolution**: ~21.5 Hz
- **Time Resolution**: ~46.4 ms

#### Visualization

- **Rendering Engine**: Raylib
- **Color Space**: HSV for spectrum visualization
- **Frame Rate**: 60 FPS (V-Sync enabled)
- **Resolution**: 800x450 pixels

---

### Architecture

The project follows a modular architecture with the following key components:

1. **Sound Generator**: Responsible for waveform synthesis and ADSR envelope application.
2. **Fourier Transform**: Performs real-time FFT for spectral analysis.
3. **Visualizer**: Handles rendering of the spectral data using Raylib.
4. **Main Controller**: Orchestrates audio playback and visualization updates.

---

### Performance Optimization

- **SIMD Vectorization**: Utilizes SSE/AVX instructions for parallel audio processing.
- **Cache-friendly Algorithms**: Optimized data structures and memory access patterns for improved cache utilization.
- **GPU Acceleration**: Offloads visualization rendering to the GPU for reduced CPU load.
- **Lock-free Audio Buffer**: Implements a custom lock-free ring buffer for low-latency audio output.

---

### Future Enhancements

1. Implement real-time parameter adjustment for waveforms and ADSR envelopes.
2. Add support for MIDI input for live performance capabilities.
3. Integrate a reverb engine for enhanced audio output.
4. Implement a more sophisticated spectral analysis using the STFT (Short-Time Fourier Transform) method.
5. Develop a user interface for dynamic control of synthesis parameters.

---

### Contributing

We welcome contributions to the Jingle Bells Synth project. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes with clear, descriptive commit messages.
4. Push your branch and submit a pull request.

Please ensure your code adheres to the existing style conventions and includes appropriate test coverage.

---

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

For more information, please contact the project maintainer at maintainer@yezzfusl.me
