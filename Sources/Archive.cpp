//
//  Archive.cpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include "Archive.hpp"
#include <sstream>
#include <algorithm>

std::vector<std::string> strsplit(std::string s, char delim) {
    std::vector<std::string> retval;
    std::string temp;
    std::stringstream ss(s);
    while (std::getline(ss, temp, delim))
        retval.push_back(temp);
    return retval;
}

namespace HAR {
    Archive::Archive(uint8_t config) : entries(config & HAR_TYPE_INDEX_HASH), config(config) {}
    
    Archive::Archive(DataBuffer data) : entries(false) /*temporary value*/ {
        assert(this != NULL);
        uint32_t magic = data.read<uint32_t>();
        config = (((char*)&magic)[3] - 1) & 0x07;
        assert(this != NULL);
        assert(&data != NULL);
        data.read<uint64_t>();
        uint32_t file_count = data.read<uint32_t>();
        for (; file_count > 0; file_count--)
        files.push_back(File(data, config, 0));
        entries = Hierarchy(data, config, 0);
    }
    
    DataBuffer Archive::serialize() {
        DataBuffer retval;
        retval.insert<uint32_t>((HAR_MAGIC | ((config + 1) << 24)));
        uint64_t file_size = 4;
        for (File f : files) file_size += 36 + f.size;
        DataBuffer hier_buf = entries.serialize(config);
        file_size += hier_buf.size();
        retval.insert(file_size);
        retval.insert((uint32_t)files.size());
        for (File f : files) retval.append(f.serialize(config));
        retval.append(hier_buf);
        return retval;
    }
    
    bool Archive::addFile(std::string path, uint8_t * data, uint64_t size, uint8_t attrib) {
        std::vector<std::string> tokens = strsplit(path, '/');
        std::vector<unsigned char> hash_tmp(picosha2::k_digest_size);
        picosha2::hash256(data, data + size, hash_tmp);
        char * index;
        if (config & HAR_TYPE_INDEX_HASH) index = (char*)malloc(32);
        else index = (char*)malloc(4);
        bool found = false;
        uint32_t i = 0;
        for (File f : files) {
            if (std::vector<unsigned char>((unsigned char *)f.hash, (unsigned char *)f.hash + 32) == hash_tmp) {
                found = true;
                if (config & HAR_TYPE_INDEX_HASH) index = f.hash;
                else index = (char*)&i;
                break;
            }
            i++;
        }
        if (!found) {
            files.push_back(File(data, size));
            if (config & HAR_TYPE_INDEX_HASH) index = (char*)&hash_tmp[0];
            else {
                uint32_t size = (uint32_t)files.size() - 1;
                index = (char*)&size;
            }
        }
        Hierarchy * p = &entries;
        for (i = 0; i < tokens.size() - 1; i++) {
            p = (*p)[tokens[i]];
            if (p == NULL) return false;
        }
        p->addFile(tokens[i], size, attrib, index);
        return true;
    }
    
    FileEntry * Archive::getFile(std::string path) {
        std::vector<std::string> tokens = strsplit(path, '/');
        Hierarchy * p = &entries;
        uint32_t i;
        for (i = 0; i < tokens.size() - 1; i++) {
            p = (*p)[tokens[i]];
            if (p == NULL) return NULL;
        }
        return p->getFile(tokens[i]);
    }
    
    File * Archive::readFile(char index[32]) {
        if (config & HAR_TYPE_INDEX_HASH) {
            for (uint32_t i = 0; i < files.size(); i++)
                if (std::equal(files[i].hash, files[i].hash + 32, index))
                    return &files[i];
        } else {
            uint32_t i = ((uint32_t*)index)[0];
            if (files.size() > i) return &files[i];
        }
        return NULL;
    }
    
    file_list Archive::listDir(std::string path) {
        std::vector<std::string> tokens = strsplit(path, '/');
        Hierarchy * p = &entries;
        uint32_t i;
        for (i = 0; i < tokens.size(); i++) {
            p = (*p)[tokens[i]];
            if (p == NULL) return file_list();
        }
        return p->listFiles();
    }
}
