#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"
#include <filesystem>
#include <string>
#include <vector>

std::vector<std::string> split_string(const std::string &str,
                                      const std::string &delim) {
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos)
      pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty())
      tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length());
  return tokens;
}

std::string basename(std::string filename) {
  return filename.substr(filename.find_last_of("/\\") + 1);
}

namespace fs = std::filesystem;

int fail(int code = 10) {
  std::cout << "Error " << std::to_string(code)
            << " Occured... Press Enter to exit...";
  return code;
}

int main(int argc, char *argv[]) {
  try {
    srand(time(NULL));
    if (argc != 2) {
      std::cerr << "[ERROR]: Too few or too many arguments: "
                << std::to_string(argc) << std::endl;
      return fail(1);
    }

    std::vector<std::string> file = split_string(basename(argv[1]), ".");
    std::vector<std::string> szs = split_string(file.at(1), "x");
    std::vector<int> sz = {atoi(szs.at(0).c_str()), atoi(szs.at(1).c_str())};

    std::vector<unsigned char> rgbaData(sz.at(0) * sz.at(1) *
                                        4); // Ensure correct size
    int index = 0;

    for (int i = 0; i < sz.at(0) * sz.at(1); i++) {
      rgbaData[index++] = rand() % 255; // R
      rgbaData[index++] = rand() % 255; // G
      rgbaData[index++] = rand() % 255; // B
      rgbaData[index++] = 255;          // A
    }

    try {
      fs::remove(argv[1]);
    } catch (const fs::filesystem_error &e) {
      std::cerr << "[ERROR]: Error deleting file: " << e.what() << std::endl;
      fail(2);
    }

    fs::path finalpath = (file.at(0) + "." + file.at(2));
    // Save the image as PNG
    if (!stbi_write_png(finalpath.string().c_str(), sz.at(0), sz.at(1), 4,
                        rgbaData.data(), sz.at(0) * 4)) {
      return fail(3);
    }

    return EXIT_SUCCESS;
  } catch (const std::exception &e) {
    std::cerr << "[ERROR]: " << e.what() << std::endl;
    return fail(4);
  }
}
