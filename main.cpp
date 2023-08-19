#include "src/InputReader.h"
#include "src/Mesh.h"
#include "src/PostProcessing.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <gmsh.h>

int main(int argc, char* argv[]) {
  
    std::string inputFileName = "input.txt"; // Default input file name

    // Parse command-line arguments
    if (argc >= 3 && std::string(argv[1]) == "-i") {  // -i <Input file name.txt>
        inputFileName = argv[2];
    } else { // we must at least provide an input file name for the code to run
        std::cout << "Usage: " << argv[0] << " -i <input_file.txt>" << std::endl;
        return 1;
    }

    // Read the input file 
    InputReader reader(inputFileName); 
    if (reader.readFile()) {
        reader.printMaterialProperties();
    } else {
        return 1;
    }

    Mesh mesh(reader);
    mesh.getHexahedralElements();

    PostProcessing psp(reader,mesh);
    //psp.convertHexMshToVtk();

    return 0;
}