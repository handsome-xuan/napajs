#include "settings-parser.h"

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include <iostream>

using namespace boost::program_options;
using namespace napa;

static bool Parse(const std::vector<std::string>& args, Settings& settings) {
    // All parsing options should be added here.
    options_description desc;
    desc.add_options()
        ("cores", value(&settings.cores), "number of cores")
        ("loggingProvider", value(&settings.loggingProvider), "logging provider")
        ("metricProvider", value(&settings.metricProvider), "metric provider")
        ("v8Flags", value(&settings.v8Flags)->multitoken(), "v8 flags")
        ("initV8", value(&settings.initV8), "specify whether v8 should be initialized")
        ("maxOldSpaceSize", value(&settings.maxOldSpaceSize), "max old space size in MB")
        ("maxSemiSpaceSize", value(&settings.maxSemiSpaceSize), "max semi space size in MB")
        ("maxExecutableSize", value(&settings.maxExecutableSize), "max executable size in MB")
        ("maxStackSize", value(&settings.maxStackSize), "max isolate stack size in bytes");

    try {
        variables_map vm;
        store(command_line_parser(args).options(desc).run(), vm);
        notify(vm);
    } catch (std::exception& ex) {
        std::cerr << "Failed to parse settings. Error: " << ex.what() << std::endl;
        return false;
    }

    // TODO @asib: here is where we need to verify settings values are valid, i.e. cores is greater then 0.

    return true;
}

bool settings_parser::ParseFromString(const std::string& str, Settings& settings) {
    std::vector<std::string> args;

    try {
        boost::split(args, str, boost::is_any_of("\t "), boost::token_compress_on);
    } catch (std::exception& ex) {
        std::cerr << "Failed to split input string [" << str << "] error: " << ex.what() << std::endl;
        return false;
    }

    return Parse(args, settings);
}

bool settings_parser::ParseFromConsole(int argc, char* argv[], Settings& settings) {
    std::vector<std::string> args;

    for (auto i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    return Parse(args, settings);
}