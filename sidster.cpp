#include <sid.h>
#include <cstdio>

struct WavetableRow {
  static const int EMPTY = -1;
  int freq;
  short waveform;
  int adsr;
  short pulse;
};

void writeRegisters(SID* sid, WavetableRow* row) {
  if (row->freq != WavetableRow::EMPTY) {
    sid->write(0, row->freq & 0xff);
    sid->write(1, (row->freq & 0xff00) >> 8);
  }

  if (row->pulse != WavetableRow::EMPTY) {
    sid->write(2, row->pulse & 0xff);
    sid->write(3, (row->pulse & 0xff00) >> 8);
  }

  if (row->waveform != WavetableRow::EMPTY) {
    sid->write(4, row->waveform);
  }

  if (row->adsr != WavetableRow::EMPTY) {
    sid->write(5, (row->adsr & 0xff00) >> 8);
    sid->write(6, row->adsr & 0xff);
  }
}

int main() {
  SID* sid = new SID();
  sid->set_chip_model(MOS6581);
  sid->reset();
  sid->write(0x18, 0xf);
  sid->write(0x17, 0);
  sid->write(0x5, 0);
  sid->write(0x6, 0);

  const int sampleRate = 44100;
  const int palClockFreq = 985248;
  const int stepFreq = 50;
  const int sampleLength = 750;

  const int cyclesPerSample = palClockFreq / sampleRate;
  const int cyclesPerStep = palClockFreq / stepFreq;
  const int totalCycles = cyclesPerSample * sampleRate * sampleLength / 1000;
  const int totalSamples = totalCycles / cyclesPerSample;

  WavetableRow steps[] = {
    { 0x02A3, 0x11, 0x08D9, 0x800 },
    { 0x2D00, 0x81,     -1,    -1 },
    { 0x0D00, 0x41,     -1,    -1 },
    { 0x0C00, 0x40,     -1,    -1 },
    { 0x2D00, 0x80,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    { 0x0D00, 0x40,     -1,    -1 },
    { 0x0C00,   -1,     -1,    -1 },
    { 0x2D00, 0x80,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    { 0x0D00, 0x40,     -1,    -1 },
    { 0x0C00,   -1,     -1,    -1 },
    { 0x2D00, 0x80,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    { 0x0D00, 0x40,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    {     -1,   -1,     -1,    -1 },
    {     -1, 0x10,     -1,    -1 }
  };
  const int totalSteps = 19;

  short* buffer = new short[totalSamples];

  // Clock two steps for avoiding popping sound in the beginning of the sample
  for (int i = 0; i < cyclesPerStep * 2; i++) {
    sid->clock();
  }

  // TODO: Improve accuracy of the timing calculations
  int cycles = 0;
  int samples = 0;
  int step = 0;
  while (cycles < totalCycles) {
    if (cycles % cyclesPerStep == 0) {
      if (step < totalSteps) {
        writeRegisters(sid, &steps[step]);
        step++;
      }
    }

    if (cycles % cyclesPerSample == 0) {
      buffer[samples] = (short)sid->output();
      samples++;
    }

    sid->clock();
    cycles++;
  }

  FILE* fp;
  fp = fopen("output.raw", "wb");
  fwrite(buffer, 2, totalSamples, fp);
  fclose(fp);
}
