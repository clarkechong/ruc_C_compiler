#pragma once

#include <iostream>
#include <unistd.h>

struct CommandLineArguments
{
    std::string compile_source_path;
    std::string compile_output_path;
};

CommandLineArguments ParseCommandLineArgs(int argc, char **argv);

/*
    all this does is parse the command line ./bin/c_compiler -S [source-file.c] -o [dest-file.s] for the source and output paths
    irrelevant to actual compiler functionality
*/
