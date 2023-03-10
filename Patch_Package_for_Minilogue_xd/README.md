# Caution !

The Minilogue xd patches are not yet fully functional, and are distributed on an experimental basis. For the time being we now know that these problems occur systematically :

- The Bells patch seems to saturate when 3 or 4 voices are used in polyphony.
- The shape and shift + shape knobs of the Bells patch seems to degrade the sound depending on their settings.
- The Wind and the Crickets patches seems to bug the Minilogue xd, so that the sound wave display screen lags, and the sound does not stop even after changing the synthesizer preset. Be careful using them.

We distribute our patches insofar as certain people would be interested in carrying out their development ; but in the same way as Korg, we do not consider ourselves responsible for any material damage whatsoever. In general, be careful when using a third-party patch.

Note that the ADSR envelope and all the options of the Korg synthesizer can always be used to adjust the sound of the patch to your use.


# Bells

Bells is an additive synthesis oscillator, with an amplitude and frequencies modulation options.
Use the knob Shape to adjust the modulation depth, and the knob Shift+Shape to adjust the modulation speed.
However, no sound variation will be audible if the knob Shift+Shape is set on 0. When the knob Shape is greater than 0, you can play adjust the modulation flutter with knob Shape+Shift.

You may hear some saturation depending on the values of the two parameters ; in that event, moving one of the knob may fix the problem.

# Wind

Wind is a subtractive synthesis oscillator wich works with five resonant filters, that move randomly on the spectrum.
Use the knob Shape to adjust the range of motion of the wind, and the knob Shape+Shift to adjust the pitch resonance of the exact key you're playing. When Shape is set on 0, the random motion and the range of movement of the wind is maximal, while if set to 1, the wind will turn out not to move at all. The variation of the knob can take a while to take effect, because the wind will finish his initial motion before move on to the next move.
Knob Shape+Shift can be used to switch from an atmospheric synthesizer to a melodic synthesizer easily.

# Crickets

Crickets is a filter source model oscillator that can simulate insect sounds. 
Use the knob A to adjust the pitch resonance, wich works more or less like a KBD slide, and knob Shape+Shift to adjust both the shape and the speed of the pulse.
In initial configuration (Shape to 0, Shape+Shift to 0), the patch will sound like a cricket. Know that if the knob A is set to 0, any key on the keyboard will play the same note.

# Clock

Clock is an impulse additive synthesis oscillator. 
Use the knob Shape to adjust the pulse velocity, and the knob Shape+Shift to randomly attribute pitch frequencies to pulse.
When the knob Shape is setup to 0, the rate of the pulse is of 60 ms, while if the knob is setup to 1, the pulse rate will be of 2000 ms.
Moving the knob Shape+Shift at high speed while the Shape parameter is at high rate can sound like water and produce some interesting results.
The key pressed on the keyboard has no influence on the sound of the synthesizer.
