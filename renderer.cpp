#include "renderer.h"
#include <sid.h>

Renderer::Renderer() {
  sid = new SID();
  sid->set_chip_model(MOS6581);
  sid->reset();
  sid->write(0x18, 0xf);
  sid->write(0x17, 0);
  sid->write(0x5, 0);
  sid->write(0x6, 0);

  // Clock two steps for avoiding popping sound in the beginning of the sample
  for (int i = 0; i < cyclesPerStep * 2; i++) {
    sid->clock();
  }
}

Renderer::~Renderer() {
  delete sid;
}

int Renderer::render(std::vector<WavetableRow> rows, short* &buffer) {
  const int totalCycles = cyclesPerStep * rows.size();
  const int totalSamples = totalCycles / cyclesPerSample;

  buffer = new short[totalSamples];

  // TODO: Improve accuracy of the timing calculations
  int cycles = 0;
  int samples = 0;
  int row = 0;
  while (cycles < totalCycles) {
    if (cycles % cyclesPerStep == 0) {
      if (row < rows.size()) {
        writeRegisters(&rows[row]);
        row++;
      }
    }

    if (cycles % cyclesPerSample == 0) {
      buffer[samples] = (short)sid->output();
      samples++;
    }

    sid->clock();
    cycles++;
  }

  return totalSamples;
}

void Renderer::writeRegisters(WavetableRow* row) {
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

  if (row->cutoff != WavetableRow::EMPTY) {
    sid->write(0x15, row->cutoff & 0xff);
    sid->write(0x16, (row->cutoff & 0xff00) >> 8);
  }

  if (row->resonance != WavetableRow::EMPTY) {
    sid->write(0x17, row->resonance);
  }

  if (row->mode != WavetableRow::EMPTY) {
    sid->write(0x18, (row->mode << 4) | 0xf);
  }
}
