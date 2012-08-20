/* 
 * File:   main.cpp
 * Author: Dennis Roberts
 *
 * A simple program for extracting phylogenetic trees from tree files.
 */

#include <cstdlib>

#include "boost/program_options.hpp"

#include "tree_info.h"
#include "tree_parser.h"

using namespace std;

namespace po = boost::program_options;

// Static function declarations.
static void describe_options();

// The supported program options.
static po::options_description desc("Allowed options");

/**
 * Attempts to parse the standard input as a trees file.  The format is specified using the -f command-line option.
 */
int main(int argc, char** argv) {
    
    // Parse the command-line options.
    describe_options();
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    // Display the help if we're supposed to.
    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }
    
    // Validate the command-line options.
    if (!vm.count("format")) {
        cerr << "required option, --format, missing" << endl;
        cerr << desc << endl;
        return 1;
    }
	return 0;
}

/**
 * Describes the command-line options accepted by the program.
 */
static void describe_options() {
    desc.add_options()
            ("help,h", "display the help message")
            ("format,f", po::value<string>(), "specify the format of the input data")
            ;
}
