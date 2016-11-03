class SID;

struct WavetableRow {
  static const int EMPTY = -1;
  int freq;
  short waveform;
  int adsr;
  short pulse;
};

class Renderer {
  static const int sampleRate = 44100;
  static const int palClockFreq = 985248;
  static const int stepFreq = 50;
  static const int cyclesPerSample = palClockFreq / sampleRate;
  static const int cyclesPerStep = palClockFreq / stepFreq;

  SID* sid;

public:
  Renderer();
  ~Renderer();

  int render(WavetableRow* rows, int rowCount, int sampleDuration, short* &buffer);

private:
  void writeRegisters(WavetableRow* row);
};
