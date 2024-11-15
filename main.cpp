#include <iostream>
#include "include/BitmapPlusPlus.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

std::vector<std::string> split_string(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
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

std::string basename(std::string filename)
{
    return filename.substr(filename.find_last_of("/\\") + 1);
}

namespace fs = std::filesystem;

bool file_exists(const fs::path &path)
{
    return fs::exists(path) && fs::is_regular_file(path);
}

int main(int argc, char *argv[])
{
    try
    {
        std::cout << "[INFO]: Creating New Image from " << argv[1] << std::endl;
        if (argc != 2)
        {
            std::cerr << "[ERROR]: Too few or too many arguments: " << std::to_string(argc) << std::endl;
            return EXIT_FAILURE;
        }
        if (!file_exists(argv[1]))
        {
            std::cerr << "[ERROR]: File does not exist: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<std::string> file = split_string(basename(argv[1]), ".");
        std::vector<std::string> szs = split_string(file.at(1), "x");
        std::vector<int> sz = {atoi(szs.at(0).c_str()), atoi(szs.at(1).c_str())};
        std::cout << "[INFO]: File: " << file.at(0) << "." << file.at(2) << " at size: " << file.at(1) << std::endl;

        bmp::Bitmap image(sz.at(0), sz.at(1));
        image.clear(bmp::Black);

        std::vector<unsigned char> rgbaData(sz.at(0) * sz.at(1) * 4); // Ensure correct size
        int index = 0;

        for (bmp::Pixel &pixel : image)
        {
            rgbaData[index++] = pixel.r; // R
            rgbaData[index++] = pixel.g; // G
            rgbaData[index++] = pixel.b; // B
            rgbaData[index++] = 0;       // A
        }

        try
        {
            fs::remove(argv[1]);
            std::cout << "[INFO]: File deleted successfully" << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "[ERROR]: Error deleting file: " << e.what() << std::endl;
        }

        fs::path finalpath = (file.at(0) + "." + file.at(2));
        // Save the image as PNG
        if (!stbi_write_png(finalpath.string().c_str(),
                            sz.at(0), sz.at(1), 4, rgbaData.data(),
                            sz.at(0) * 4))
        {
            throw std::runtime_error("[ERROR]: Failed to write PNG image");
        }

        std::cout << "[INFO]: File saved successfully!" << std::endl;

        return EXIT_SUCCESS;
    }
    catch (const bmp::Exception &e)
    {
        std::cerr << "[BMP ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
