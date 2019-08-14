//
//  FileStream.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef FileStream_h
#define FileStream_h

#include "Using.hpp"

#include <fstream>
#include <sstream>

namespace FileStream {
    
    /* takes a file path and returns the file's contents in a string */
    static inline string readFile(const string filePath) {
        
        std::ifstream fileStream;
        fileStream.open(filePath);
        if(!fileStream) {
            cout << "file " << filePath << " does not exist" << endl;
        }
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        fileStream.close();
        
        string fileContent = buffer.str();
        return fileContent;
    }
}

#endif /* FileStream_h */
