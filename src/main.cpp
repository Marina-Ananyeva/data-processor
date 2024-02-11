#include <iostream>
#include <memory>
#include <string>

#include "common.h"
#include "solution.h"

int main(int argc, char* argv[]) 
{
    try {
        std::string inputFileName = "../data/input.txt";
        std::string configFileName = "../data/settings.json";
        std::string outputFileName = "../data/output.txt";
        if (argc > 1) {
            outputFileName = argv[1];
        }
        if (argc > 2) {
            configFileName = argv[2];
        }
        if (argc > 3) {
            outputFileName = argv[3];
        }
        std::unique_ptr<Solution> solution = std::make_unique<Solution>(DataFiles(configFileName
                                                                        , inputFileName
                                                                        , outputFileName));
        solution->process();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}