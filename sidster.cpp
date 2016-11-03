#include "renderer.h"
#include <cstdio>

int main() {
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

  short* buffer = 0;
  Renderer renderer;
  int totalSamples = renderer.render(steps, totalSteps, 750, buffer);

  FILE* fp;
  fp = fopen("output.raw", "wb");
  fwrite(buffer, 2, totalSamples, fp);
  fclose(fp);
}
