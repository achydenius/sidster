#include "renderer.h"
#include "loader.h"
#include <cstdio>
#include <vector>

int main() {
  Loader loader;
  std::vector<WavetableRow> steps = loader.load("instrument.txt");

  short* buffer = 0;
  Renderer renderer;
  int totalSamples = renderer.render(steps, 750, buffer);

  FILE* fp;
  fp = fopen("output.raw", "wb");
  fwrite(buffer, 2, totalSamples, fp);
  fclose(fp);
}
