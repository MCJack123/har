//
//  Hierarchy.hpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef Hierarchy_hpp
#define Hierarchy_hpp

#include <list>
#include <string>
#include <stdint.h>
#include "types.h"
#include "FileEntry.hpp"

namespace HAR {
    class Hierarchy {
        bool useHash = false;
        std::list<FileEntry> files;
    public:
        Hierarchy(bool useHas) : useHash(useHas) {}
        void addFile(std::string name, uint64_t size, uint8_t attributes, char * index);
        FileEntry removeFile(std::string name);
        FileEntry * getFile(std::string name);
        file_list listFiles();
        Hierarchy * operator[](std::string name);
        DataBuffer serialize(uint8_t config);
        Hierarchy(DataBuffer data, uint8_t config);
        Hierarchy(DataBuffer& data, uint8_t config, int dummy);
    };
}

#endif /* Hierarchy_hpp */
