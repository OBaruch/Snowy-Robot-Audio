# Intent

> **Retroactive document.** This file was written after the fact, from the code that already existed. It records the intent that the original implementation shows. It is not a design written before the code. See [project-context.md](../project-context.md) for how confident each claim is.

## Why

Give a holiday-themed robot ("Snowy Robot") a voice that can announce how many weeks are left until Christmas, in Spanish, without any external audio hardware beyond a speaker. *(Inferred from the clip vocabulary and the repository name.)*

## What success looks like

1. A controller receives a short text command over serial and speaks the matching Spanish phrase, for example *"Faltan tres semanas para Navidad"*.
2. A bell/jingle sound can be played on its own or before a phrase.
3. All audio is stored in the microcontroller's flash memory, so there is no SD card, file system or network dependency.
4. Clips are chained without gaps that a person would notice, so they sound like one sentence.

## Users and actors

| Actor | Role |
| --- | --- |
| Serial host | Whatever sends the command string (a PC serial monitor, another microcontroller, or a person). What this actually was in the original project is **Unknown**. |
| Listener | Someone near the robot's speaker |

## Non-goals (as observed)

- Calculating the date or the countdown on the device.
- Text-to-speech or free-form speech.
- Recording, streaming or changing audio at runtime.
- Any user interface other than the serial port.

## Constraints

- Microcontroller with a built-in DAC: an ESP32 (**Inferred**), using GPIO 25.
- Flash size limits the audio budget, which leads to 8 kHz / 8-bit mono clips (about 97 KB in total).
- Uses the third-party XT_DAC_Audio library for playback and sequencing.
