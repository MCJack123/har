//
//  Archive.hpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef Archive_hpp
#define Archive_hpp

#include "File.hpp"
#include "FileEntry.hpp"
#include "Hierarchy.hpp"

namespace HAR {
    class Archive {
        std::vector<File> files;
    public:
        uint8_t config;
        Hierarchy entries;
        Archive(uint8_t config = 0);
        Archive(DataBuffer data);
        DataBuffer serialize();
        bool addFile(std::string path, uint8_t * data, uint64_t size, uint8_t attrib);
        file_list listDir(std::string path);
        FileEntry * getFile(std::string path);
        File * readFile(char index[32]);
    };
}

#endif /* Archive_hpp */
