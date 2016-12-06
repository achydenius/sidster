#include "renderer.h"
#include "loader.h"
#include <cstdio>
#include <vector>

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: sidster [wavetable-file] [output-file]\n");
    return 0;
  }

  char* wavetableFilename = argv[1];
  char* outputFilename = argv[2];
  char* format = strrchr(wavetableFilename, '.');

  Loader loader;
  std::vector<WavetableRow> steps;
  if (!strcmp(format, ".yml")) {
    steps = loader.loadFromYaml(wavetableFilename);
  } else {
    steps = loader.loadFromTxt(wavetableFilename);
  }

  printf("Loaded %lu wavetable rows from %s\n", steps.size(), wavetableFilename);

  short* buffer = 0;
  Renderer renderer;
  int totalSamples = renderer.render(steps, buffer);
  printf("Rendered %d samples\n", totalSamples);

  FILE* fp;
  fp = fopen(outputFilename, "wb");
  int writtenSamples = fwrite(buffer, 2, totalSamples, fp);
  fclose(fp);
  printf("Wrote %d samples to %s\n", writtenSamples, outputFilename);
}
