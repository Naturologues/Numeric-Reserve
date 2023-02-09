# Numeric-Reserve # 1
We provide here our numeric patches inspired by everyday sounds for the Korg Nutekt NTS-1 and Minilogue xd digital synthesizers. 
You’ll find information about the code used in the logue SDK, the maxMSP / PureData patches used for the prototype sounds.

## Features
- 4 Oscillators inspired by daily sounds, available for the NTS-1 and the Minilogue xd
- User Manuals for each oscillator
- The Source Code of each oscillator
- The equivalent of our oscillators translated into patches for MaxMSP and Max for Live

## Parameters
 
| Oscillator     | Description                                             | Parameter A                      | Parameter B                                       |
| :------------: | :-----------------------------------------------------: | :------------------------------: | :-----------------------------------------------: |
| Bells          | Additive synthesis oscillator with amplitude modulation | Modulation depth                 | Modulation speed                                  |
| Wind           | Subtractive synthesis oscillator with resonant filters  | Resonance amplitude on the pitch | Wind movements                                    |
| Crickets       | Filter source model oscillator                          | Resonance frequency control      | Shape and speed of the pulse train                |
| Clock          | Impulse additive synthesis oscillator                   | Pulse velocity                   | Pulse pitch frequencies (Random attribution)      |

## How to install
 - Install and launch the NTS-1 digital librarian (https://www.korg.com/us/support/download/software/0/832/4424/) (or the Minilogue xd librarian [https://www.korg.com/us/support/download/software/0/811/4222/])
 - Connect your NTS-1 to computer
 - Make sure to select the correct MIDI In and MIDI Out ports in the librarian preferences
 - Go to FILE -> IMPORT USER UNIT
 - Import the .ntkdigunit file (or the .mnlgxdunit if you're using the Minilogue xd)
