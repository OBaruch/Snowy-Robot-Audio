# Specification

> **Retroactive document.** This spec describes the behavior **as implemented** in [`src/audio/audio.ino`](../../src/audio/audio.ino) and [`src/audio/SoundData.h`](../../src/audio/SoundData.h). Anything the code does not show is marked *Inferred* or *Unknown*. Known gaps are listed at the end rather than fixed.

## 1. System overview

A single Arduino sketch that plays sequences of embedded WAV clips through a DAC pin when it receives command characters over a serial port.

## 2. Interfaces

### 2.1 Serial input

| Property | Value | Status |
| --- | --- | --- |
| Baud rate | 115200 | Confirmed |
| Framing | Whatever `Serial.readString()` collects before the serial timeout (default 1 s) | Confirmed (library behavior) |
| Encoding | ASCII, one character per token | Confirmed |

### 2.2 Command alphabet

| Token | Clip |
| --- | --- |
| `b` | bells |
| `n` | navidad |
| `f` | faltan |
| `p` | para |
| `s` | semanas |
| `1`–`5` | una, dos, tres, cuatro, cinco |

Any other character is **ignored silently**.

### 2.3 Serial output

After playback starts, the received string is printed back unchanged, with `println`.

### 2.4 Audio output

| Property | Value | Status |
| --- | --- | --- |
| Pin | GPIO 25 (DAC) | Confirmed |
| Timer | 0 | Inferred meaning of the constructor argument |
| Sample format | PCM, mono, 8,000 Hz, 8-bit unsigned | Confirmed from the WAV headers |

## 3. Functional requirements (as implemented)

| ID | Requirement | Implemented in |
| --- | --- | --- |
| FR-1 | The system shall start serial communication at 115200 baud on boot. | `setup()` |
| FR-2 | The system shall call the audio buffer refill routine on every main-loop pass. | `loop()` → `DacAudio.FillBuffer()` |
| FR-3 | When serial data is available, the system shall read it as one string. | `loop()` |
| FR-4 | For each received string, the system shall clear the current playlist. | `PlayNumber()` → `RemoveAllPlayItems()` |
| FR-5 | For each character in the string, in order, the system shall append the mapped clip to the playlist. | `AddNumberToSequence()` |
| FR-6 | The system shall start playback of the playlist. | `DacAudio.Play(&Sequence)` |
| FR-7 | The system shall echo the received string over serial. | `Serial.println(Number)` |
| FR-8 | Unknown characters shall not add clips or cause errors. | `switch` with no `default` |

## 4. Data

Ten embedded WAV files. Sizes and durations are listed in [code-overview.md](../code-overview.md#sounddatah).

## 5. Acceptance scenarios (inferred)

| Given | When the host sends | Then the speaker plays |
| --- | --- | --- |
| Device idle | `b` | Bell sound (~6 s) |
| Device idle | `f3spn` | "Faltan tres semanas para Navidad" |
| Device idle | `bf5spn` | Bells, then "Faltan cinco semanas para Navidad" |
| Device idle | `xyz` | Nothing (empty sequence); `xyz` is echoed |
| Clip playing | Any new command | The playlist is replaced. How the library handles an in-progress clip is **Unknown**. |

## 6. Known gaps (not fixed, by design)

See [possible-improvements.md](../possible-improvements.md). In short: `readString()` blocks the buffer refill, `cinco_wav` is non-const, there is no singular "semana" clip, and the external library version is not pinned.
