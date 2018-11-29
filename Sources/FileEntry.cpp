//
//  FileEntry.cpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include "FileEntry.hpp"
#include "Hierarchy.hpp"

namespace HAR {
    FileEntry::FileEntry(bool useHas, char * inde, std::string nam, uint64_t siz, uint8_t attrib) : useHash(useHas), name(nam), size(siz), attributes(attrib) {
        if (attrib & HAR_ATTRIB_DIRECTORY) directories = new Hierarchy(useHas);
        if (useHas) {
            index = (char*)malloc(32);
            memcpy(index, inde, 32);
        } else {
            index = (char*)malloc(4);
            memcpy(index, inde, 4);
        }
    }
    
    FileEntry::FileEntry(DataBuffer data, uint8_t config) {
        if (config & HAR_TYPE_INDEX_HASH) index = (char*)data.read(32);
        else {
            index = (char*)malloc(4);
            ((uint32_t*)index)[0] = data.read<uint32_t>();
        }
        name = data.read<std::string>();
        attributes = data.read<uint8_t>();
        if (attributes & HAR_ATTRIB_DIRECTORY) directories = new Hierarchy(data, config);
    }
    
    FileEntry::FileEntry(DataBuffer& data, uint8_t config, int dummy) {
        if (config & HAR_TYPE_INDEX_HASH) index = (char*)data.read(32);
        else {
            index = (char*)malloc(4);
            ((uint32_t*)index)[0] = data.read<uint32_t>();
        }
        name = data.read<std::string>();
        attributes = data.read<uint8_t>();
        if (attributes & HAR_ATTRIB_DIRECTORY) directories = new Hierarchy(data, config, 0);
    }
    
    DataBuffer FileEntry::serialize(uint8_t config) {
        DataBuffer retval;
        if (config & HAR_TYPE_INDEX_HASH) retval.insert(index, 32);
        else retval.insert(((uint32_t*)index)[0]);
        retval.insert(name);
        retval.insert(attributes);
        if (attributes & HAR_ATTRIB_DIRECTORY) retval.append(directories->serialize(config));
        return retval;
    }
}
