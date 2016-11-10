#include <string>
#include <vector>

struct WavetableRow;

class Loader {
public:
  std::vector<WavetableRow> load(std::string filename);

private:
  int parseValue(std::string line, int start, int length);
};
