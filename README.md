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
 - Click on SEND ALL to get the patches you've imported on your hardware

## How to setup the SDK (for environment devlopment)
You can find all the informations you need on the logue SDK official Github (https://github.com/korginc/logue-sdk). Here are some other links that may help you to setup the environment : 
- (https://www.youtube.com/watch?v=ouGBnYXUT40)
- (https://korgnts1beginnersguide.wordpress.com/setting-up-the-development-environment/)

## License

This project is under CC BY-NC-ND 4.0 license (Attribution-NonCommercial-NoDerivatives 4.0 International). See LICENSE file.
<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.
