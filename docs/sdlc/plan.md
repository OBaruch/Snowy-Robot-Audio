# Plan

> **Retroactive document.** This file has two parts:
> 1. **Original build plan (reconstructed):** the steps the existing code shows were taken. The order is inferred.
> 2. **Repository modernization plan:** the documentation-only work actually done later, which **did not change the source code**.

## Part 1: Original build plan (reconstructed)

| Step | Work | Evidence |
| --- | --- | --- |
| 1 | Choose an ESP32 and the XT_DAC_Audio library to play audio through the built-in DAC | `#include "XT_DAC_Audio.h"`, `DacAudio(25,0)` |
| 2 | Record or source the Spanish words and a bell sound | Clip names in `SoundData.h` |
| 3 | Convert each clip to 8 kHz / 8-bit mono WAV | WAV headers |
| 4 | Convert the WAVs to C byte arrays and collect them in `SoundData.h` | Header format |
| 5 | Wrap each array in an `XT_Wav_Class` and assign it a command character | Globals and comments in `audio.ino` |
| 6 | Build the serial command parser that chains clips with `XT_Sequence_Class` | `PlayNumber()`, `AddNumberToSequence()` |
| 7 | Test from a serial monitor and upload the files to GitHub (2021-02-20) | Echo in `PlayNumber()`; git history |

## Part 2: Repository modernization plan (executed)

**Guiding rule:** modernize the repository, not the project. The files in `src/` must stay byte-identical to the originals.

| # | Task | Status |
| --- | --- | --- |
| 1 | Inventory every file and git/GitHub metadata; recover context | Done |
| 2 | Parse the embedded WAV headers to confirm audio format and durations | Done |
| 3 | Move `audio.ino` and `SoundData.h` into `src/audio/`, an Arduino-valid sketch folder, with `git mv` and no content change | Done (SHA-256 checksums verified before and after) |
| 4 | Write `docs/project-context.md` with Confirmed / Inferred / Unknown labels | Done |
| 5 | Write `docs/code-overview.md` covering functions, protocol, data tables and diagrams | Done |
| 6 | Write `docs/possible-improvements.md` with observations only, clearly not applied | Done |
| 7 | Write the retroactive `docs/sdlc/intent.md`, `spec.md` and this `plan.md` | Done |
| 8 | Write `README.md` and a minimal `.gitignore` | Done |
| 9 | Open a pull request for review | Done |

### Deliberately not done

- No changes to code, formatting, line endings or dependencies.
- No CI, Docker, linters, test frameworks, package managers or build tooling.
- No `architecture.md`: two files do not justify a separate architecture document. The relationships are covered in the code overview.
- No `assignment.md`: there is no evidence that this was coursework.

### Verification

```bash
# Contents of the original files must match the initial upload (commit 4ad59ab)
git diff 4ad59ab -M --stat -- audio.ino SoundData.h src/audio/
sha256sum src/audio/audio.ino src/audio/SoundData.h
# ef7172976cd3b8ce2ac6c8a182ef7b5aa5917f10b272faa5e99559abc2eec5a7  src/audio/audio.ino
# 386e238712e222402ea385686429ef645aa65efd44a40e20c4a9cab1fde4cff5  src/audio/SoundData.h
```
