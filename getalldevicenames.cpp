#include <fstream>
#include <sstream>
#include <limits>
#include <iostream>

//Overwrites standart IO template
std::istream& skip_line(std::istream& in) {
  return in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

int main (int argc, const char* argv[]) {
  std::ifstream partitions("/proc/partitions", std::ios::binary);
  if (!partitions.is_open()) {
    return false;
  }
  std::string line;
  std::string dev_name;
  std::stringstream ss;
  std::size_t pos = 0;

  partitions >> skip_line;
  partitions >> skip_line;
  ss << partitions.rdbuf();
  while (std::getline(ss, line, '\n')) {
    if ((pos = line.find("sd")) != std::string::npos || (pos = line.find("hd")) != std::string::npos) {
      dev_name = line.substr(pos, (line.length() - 1));
      if (dev_name.length() == 3) {
        std::cerr << dev_name << '\n'; // do what you want with device name
      }
    }
  }
  return 0;
}
