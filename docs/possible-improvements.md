# Possible Improvements

> **None of these changes have been applied.** The source code in `src/` is preserved exactly as originally written so that it keeps its historical context. This list only records observations a reader of the code today might make.

## Observations about the original code

| # | Observation | Location | Possible impact |
| --- | --- | --- | --- |
| 1 | `Serial.readString()` blocks until the serial timeout expires (1 s by default). `FillBuffer()` is not called during that wait. | `loop()` | Audio that is already playing may stutter or stop while a command is being read. |
| 2 | `cinco_wav` is declared `unsigned char` instead of `const unsigned char`. | `SoundData.h` | On an ESP32 a non-const array is copied into RAM (about 6 KB) instead of staying in flash. |
| 3 | `SoundData.h` has no include guard (`#pragma once` or `#ifndef`). | `SoundData.h` | Including it twice would cause redefinition errors. |
| 4 | Serial input is echoed with `Serial.println(Number)`, including any trailing line-ending characters. | `PlayNumber()` | Cosmetic only: blank lines on the serial monitor. |
| 5 | There is only a plural `semanas` clip. | Audio set | "Faltan una semanas" is ungrammatical; a singular `semana` / `falta` pair would be needed for N = 1. |
| 6 | The countdown number is not calculated on the device. | Whole sketch | An RTC/NTP-based date calculation could let the robot pick N on its own. |
| 7 | Function names `PlayNumber` / `AddNumberToSequence` and the parameter name `Number` date from number-only playback, but the input now also contains words. | `audio.ino` | Readability only. |
| 8 | Audio is 8 kHz / 8-bit. | `SoundData.h` | Low fidelity, but a reasonable size trade-off for flash storage. |
| 9 | The XT_DAC_Audio library and its version are not recorded or vendored. | Repository | Reproducing the build depends on finding a compatible library release. |
| 10 | The original WAV source files are not kept, only the generated C arrays. | Repository | Editing or re-recording clips requires extracting them from the header first. |

## Possible repository-level additions

These are **optional** and were deliberately left out to avoid adding infrastructure the original project never had:

- A small, separate script that extracts the WAV clips from `SoundData.h` for listening. This would live outside `src/` and would not touch the original files.
- A wiring note or photo, if the original hardware still exists.
- Recording the exact XT_DAC_Audio release once someone confirms which one compiles the sketch.
