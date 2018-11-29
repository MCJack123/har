//
//  Hierarchy.cpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include "Hierarchy.hpp"

namespace HAR {
    void Hierarchy::addFile(std::string name, uint64_t size, uint8_t attributes, char * index) {
        FileEntry file = FileEntry(useHash, index, name, size, attributes);
        files.push_back(file);
    }
    
    FileEntry Hierarchy::removeFile(std::string name) {
        for (std::list<FileEntry>::iterator i = files.begin(); i != files.end(); i++) if (i->name == name) {
            FileEntry retval(*i);
            files.erase(i);
            return retval;
        }
        uint32_t f = INT32_MAX;
        return FileEntry(false, (char*)&f, "invalid", 0, 0);
    }
    
    FileEntry * Hierarchy::getFile(std::string name) {
        for (std::list<FileEntry>::iterator i = files.begin(); i != files.end(); i++) if (i->name == name) return &*i;
        return NULL;
    }
    
    Hierarchy * Hierarchy::operator[](std::string name) {
        FileEntry * e = getFile(name);
        if (e == NULL || !(e->attributes & HAR_ATTRIB_DIRECTORY)) return NULL;
        return e->directories;
    }
    
    DataBuffer Hierarchy::serialize(uint8_t config) {
        DataBuffer retval;
        retval.insert((uint32_t)files.size());
        for (FileEntry e : files) retval.append(e.serialize(config));
        return retval;
    }
    
    Hierarchy::Hierarchy(DataBuffer data, uint8_t config) {
        uint32_t size = data.read<uint32_t>();
        for (int i = 0; i < size; i++) files.push_back(FileEntry((DataBuffer)data, config));
    }
    
    Hierarchy::Hierarchy(DataBuffer& data, uint8_t config, int dummy) {
        uint32_t size = data.read<uint32_t>();
        for (int i = 0; i < size; i++) files.push_back(FileEntry(data, config, 0));
    }
    
    file_list Hierarchy::listFiles() {
        file_list retval;
        for (std::list<FileEntry>::iterator it = files.begin(); it != files.end(); it++) {
            file_listing l(it->name, *it);
            retval.push_back(l);
        }
        assert(retval.size() == files.size());
        return retval;
    }
}
