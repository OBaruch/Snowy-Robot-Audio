# Project Context

This document reconstructs the context of **Snowy-Robot-Audio** from the evidence available in the repository. Every statement is labeled:

- **Confirmed**: backed directly by files, code or git metadata.
- **Inferred**: a reasonable deduction from the available files that cannot be fully verified.
- **Unknown**: the repository does not provide enough information to determine this.

## Evidence inventory

The original repository had **no** PDFs, Word documents, slides, images, diagrams, notebooks, datasets, READMEs or configuration files. The only sources of context are:

| Source | What it provides |
| --- | --- |
| `audio.ino` (now `src/audio/audio.ino`) | Program logic, library in use, serial protocol, trailing comments that map characters to clips |
| `SoundData.h` (now `src/audio/SoundData.h`) | Ten WAV files stored as C byte arrays; the array names are Spanish words |
| `LICENSE` | MIT License, `Copyright (c) 2021 Baruch Lopez` |
| Git history | Two commits by Baruch Lopez on 2021-02-20 (UTC-6): `Initial commit` and `Add files via upload` (GitHub web upload) |
| GitHub metadata | Repository name `Snowy-Robot-Audio`, created 2021-02-21 UTC, no description, primary language detected as C |

## Project origin

**Project origin: Unknown.**

- There is no course name, university, assignment statement, rubric or report in the repository, so there is **no evidence** that this was an academic project.
- The small scope, the holiday theme and the name "Snowy Robot" suggest a personal or hobby build (**Inferred**), but nothing in the repository confirms it.

## What the project does

| Aspect | Status | Detail |
| --- | --- | --- |
| Plays pre-recorded voice/sound clips through a DAC pin | Confirmed | `XT_DAC_Audio_Class DacAudio(25,0);` and `DacAudio.Play(&Sequence);` |
| Clips are chosen by characters received over serial | Confirmed | `Serial.readString()` → `PlayNumber()` → `AddNumberToSequence()` |
| Serial speed is 115200 baud | Confirmed | `Serial.begin(115200);` |
| Clips are 8 kHz, 8-bit, mono PCM WAV | Confirmed | Parsed from the RIFF headers inside `SoundData.h` |
| Target microcontroller is an **ESP32** | Inferred | The XT_DAC_Audio library targets the ESP32 built-in DAC, and GPIO 25 is one of the two ESP32 DAC pins |
| The second constructor argument (`0`) selects a hardware timer | Inferred | Based on the public XT_DAC_Audio API; the library is not included in the repository |
| A speaker or amplifier was connected to GPIO 25 | Inferred | Needed to hear the DAC output; no wiring information exists |

## Theme and purpose

The clip names are Spanish words:

| Array | Word | English |
| --- | --- | --- |
| `bells_wav` | *(bells)* | A ~6 s sound clip, probably a bell/jingle sound effect (**Inferred** from the name and length) |
| `navidad_wav` | navidad | Christmas |
| `faltan_wav` | faltan | "there are ... left" |
| `para_wav` | para | until / for |
| `semanas_wav` | semanas | weeks |
| `una_wav`, `dos_wav`, `tres_wav`, `cuatro_wav`, `cinco_wav` | una ... cinco | one ... five |

Together these words form the Spanish phrase **"Faltan _N_ semanas para Navidad"** ("_N_ weeks left until Christmas"), with _N_ from one to five.

- **Inferred:** the project was a talking Christmas countdown for a holiday-themed robot, possibly a snowman ("Snowy"). The device (or a person, or another controller) sends a short command such as `f3spn` over serial and the robot speaks the sentence.
- **Unknown:** what the rest of "Snowy Robot" was (a physical robot, a decoration, a larger system), what sent the serial commands, and whether other firmware or hardware belonged to the same project.

## Timeline

| Date | Event | Status |
| --- | --- | --- |
| 2021-02-20 | Files uploaded to GitHub through the web interface | Confirmed |
| Before 2021-02-20 | Development of the sketch | Inferred (the upload date is after Christmas 2020, which suggests the code was written for the 2020 holiday season and archived afterwards; this cannot be confirmed) |
| Later | Repository reorganized and documented; source code left unchanged | Confirmed (this reorganization) |

## Scope and limitations

- **In scope:** a single firmware sketch that plays and chains audio clips on command.
- **Not present:** hardware schematics, bill of materials, photos, recordings of the original audio, the XT_DAC_Audio library, build configuration, or any code that decides *which* countdown number to say. The number is chosen entirely by whatever sends the serial command.

## Contradictions and open questions

- The singular clip is named `una` (feminine "one", which agrees with *semana*), but only a plural `semanas` clip exists. "Faltan una semanas" would be ungrammatical. Whether a singular form was ever planned is **Unknown**.
- `una_wav` and `dos_wav` have exactly the same size (3,463 bytes) but different content. This looks like a coincidence or trimming to a common length; the reason is **Unknown**.
- `cinco_wav` is declared without `const`, unlike the other nine arrays. Whether this was deliberate is **Unknown**. Its technical effect is described in [possible-improvements.md](possible-improvements.md).
