#include <string>
#include <vector>

struct WavetableRow;

class Loader {
public:
  std::vector<WavetableRow> loadFromTxt(std::string filename);
  std::vector<WavetableRow> loadFromYaml(std::string filename);

private:
  int parseValue(std::string line, int start, int length);
};
