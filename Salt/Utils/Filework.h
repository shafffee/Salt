#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include "Logging.h"

namespace salt::Utils {

    //read_file
    inline std::string read_file(const std::string& file_path) {
        // Open the file in binary mode to preserve all characters
        std::ifstream file(file_path, std::ios::binary);

        // Check if the file was successfully opened
        if (!file.is_open()) {
            salt::Logging::Error("Can not open file "+ file_path+ " to read");
        }

        // Read the entire file content using stream iterators
        return std::string(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        );
    }
}