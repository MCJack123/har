//
//  FileEntry.hpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef FileEntry_hpp
#define FileEntry_hpp

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>
#include "types.h"

namespace HAR {
    class Hierarchy;
    class FileEntry {
        bool useHash;
    public:
        char * index;
        std::string name;
        uint64_t size;
        uint8_t attributes;
        Hierarchy * directories;
        
        DataBuffer serialize(uint8_t config);
        FileEntry(DataBuffer data, uint8_t config);
        FileEntry(DataBuffer& data, uint8_t config, int dummy);
        FileEntry(bool useHas, char * inde, std::string nam, uint64_t siz, uint8_t attrib);
    };
    
    typedef std::pair<std::string, FileEntry> file_listing;
    typedef std::vector<file_listing> file_list;
}

#endif /* FileEntry_hpp */
