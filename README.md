# Snowy-Robot-Audio

Firmware for a talking Christmas-countdown voice. An Arduino sketch plays Spanish voice clips stored in flash, such as *"Faltan tres semanas para Navidad"* ("Three weeks left until Christmas"), through a microcontroller's DAC when it receives short commands over serial.

> **Original implementation.** This repository keeps the project as it was originally implemented. The source code has deliberately not been refactored or modernized, so it keeps its historical context and original development approach.

## Project Overview

| | |
| --- | --- |
| **Type** | Embedded firmware (Arduino sketch) |
| **Author** | Baruch Lopez |
| **Date** | Uploaded 2021-02-20 |
| **Language** | Arduino C++ |
| **Size** | 1 sketch + 1 embedded-audio header (10 clips, ~12 s of audio) |
| **License** | [MIT](LICENSE) |

## Project Context

**Project origin: Unknown.** The repository has no course, assignment or report material, so there is no evidence that this was an academic project. The holiday theme, the small scope and the name "Snowy Robot" suggest a personal or hobby build for a Christmas-themed robot, but this is *inferred*, not confirmed. The full evidence review is in [docs/project-context.md](docs/project-context.md).

## Problem Statement

Give a small robot a voice that announces how many weeks are left until Christmas, using only the microcontroller's built-in DAC and flash memory: no SD card, no audio module and no network.

## Objective

Assemble spoken Spanish sentences from a small vocabulary of pre-recorded clips, choosing and ordering them with a simple one-character-per-word serial protocol.

## Repository Structure

```
.
├── README.md
├── LICENSE
├── src/
│   └── audio/                   # Arduino sketch folder (name must match the .ino)
│       ├── audio.ino            # Original sketch (unchanged)
│       └── SoundData.h          # Original embedded WAV clips (unchanged)
└── docs/
    ├── project-context.md       # Recovered context: Confirmed / Inferred / Unknown
    ├── code-overview.md         # How the code works, protocol, audio data tables
    ├── possible-improvements.md # Observations only, not applied
    └── sdlc/
        ├── intent.md            # Why the project exists (retroactive)
        ├── spec.md              # Behavior as implemented (retroactive)
        └── plan.md              # Reconstructed build plan + reorganization plan
```

## Original Implementation

Both files in `src/audio/` are the original files from the first upload, with identical bytes. They were only **moved** into an Arduino-compatible sketch folder. Their logic, style, names, comments and quirks are left as they were. Observations about the code are kept separately in [docs/possible-improvements.md](docs/possible-improvements.md).

## Technologies

| Technology | Status |
| --- | --- |
| Arduino (C++ sketch, `.ino`) | Confirmed |
| XT_DAC_Audio library (by XTronical) (`XT_DAC_Audio_Class`, `XT_Wav_Class`, `XT_Sequence_Class`) | Confirmed by the include and class names; library **not included**, version unknown |
| ESP32 microcontroller (built-in DAC on GPIO 25) | Inferred |
| 8 kHz / 8-bit / mono PCM WAV embedded as C arrays | Confirmed |

## How It Works

1. `setup()` opens serial at **115200 baud**.
2. `loop()` keeps the DAC buffer filled and waits for serial input.
3. Each received character is mapped to a clip and appended to a playlist (`XT_Sequence_Class`).
4. The playlist is played through **GPIO 25**, and the command is echoed back over serial.

### Command characters

| Char | Clip | | Char | Clip |
| --- | --- | --- | --- | --- |
| `b` | bells | | `1` | una (one) |
| `n` | Navidad (Christmas) | | `2` | dos (two) |
| `f` | Faltan (there are ... left) | | `3` | tres (three) |
| `p` | para (until) | | `4` | cuatro (four) |
| `s` | semanas (weeks) | | `5` | cinco (five) |

Example: `bf3spn` → bells + *"Faltan tres semanas para Navidad."*

Function details, a sequence diagram and a per-clip size and duration table are in [docs/code-overview.md](docs/code-overview.md).

## Inputs and Outputs

| Input | Output |
| --- | --- |
| ASCII command string over serial (115200 baud) | Analog audio on GPIO 25 (to an amplifier or speaker, inferred) and the command echoed over serial |

## Running the Project

These steps are **inferred** from the code. The original build setup was not recorded.

1. Install the Arduino IDE with ESP32 board support.
2. Install the XT_DAC_Audio library (not included here; the exact version used originally is unknown).
3. Open `src/audio/audio.ino`, select an ESP32 board and upload.
4. Connect an amplifier or speaker to **GPIO 25** and GND.
5. Open the serial monitor at **115200 baud** and send a command such as `f3spn`.

## Documentation

- [Project context](docs/project-context.md): origin, evidence and open questions
- [Code overview](docs/code-overview.md): functions, protocol, data and diagrams
- [Possible improvements](docs/possible-improvements.md): observations, not applied
- [Intent](docs/sdlc/intent.md) · [Spec](docs/sdlc/spec.md) · [Plan](docs/sdlc/plan.md): retroactive SDLC documents

## Historical Note

This repository was later reorganized and documented to make it easier to read and to preserve the historical context of the original project. The original source code remains unchanged.
