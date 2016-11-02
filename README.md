# SIDster

SIDster is a [SID](https://en.wikipedia.org/wiki/MOS_Technology_SID) wavetable sample writer.

[ReSID](https://en.wikipedia.org/wiki/ReSID) library is used for hardware emulation.

Generated samples can be played for example with [SoX](http://sox.sourceforge.net/): `play -t raw -r 44.1k -e signed -b 16 -c 1 output.raw`.
