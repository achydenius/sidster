# SIDster

SIDster is a [SID](https://en.wikipedia.org/wiki/MOS_Technology_SID) wavetable sample writer. It can be used to render Commodore 64 -like sounding audio samples.

## Installation

Build and install [ReSID](http://www.zimmers.net/anonftp/pub/cbm/crossplatform/emulators/resid/index.html) first as it's used for harware emulation. Then build the application with `make`.

## Usage

Run the application with `./sidster [wavetable-file] [output-file] [sample-duration-ms]`.

Generated file is a 16-bit/44.1KHz raw mono audio file that is stored as signed little-endian data.

Files can be played back for example with [SoX](http://sox.sourceforge.net/): `play -t raw -r 44.1k -e signed -b 16 -c 1 output.raw`.

## Wavetable file format

Wavetables are defined as plain text files. A wavetable file consists of rows that define a set of hexadecimal values that are written consecutively to SID registers with an interval of 20 milliseconds. The values map directly to [SID registers](http://www.waitingforfriday.com/index.php/Commodore_SID_6581_Datasheet) and are separated by two spaces. A single wavetable row consists of:

* Frequency (2 bytes)
* Voice control (1 byte)
* Envelope (2 bytes)
* Pulse width (3 nibbles)
* Filter cutoff (2 bytes)
* Filter resonance & toggle filter (1 nibble)
* Filter mode (1 nibble)
