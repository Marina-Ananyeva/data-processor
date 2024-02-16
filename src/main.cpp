#include <execution>
#include <iostream>
#include <memory>
#include <string>

#include "common.h"
#include "log_duration.h"
#include "solution.h"

int main(int argc, char* argv[]) 
{
    try {
        LOG_DURATION("Process_time");
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
        solution->process(std::execution::seq);     // последовательная обработка
        //solution->process(std::execution::par);   // параллельная обработка
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}