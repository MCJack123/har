//
//  File.cpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include "File.hpp"

namespace HAR {
    File::File(uint8_t * dat, uint64_t siz) {
        data = dat;
        size = siz;
        std::vector<unsigned char> hash_tmp(picosha2::k_digest_size);
        picosha2::hash256(data, data + size, hash_tmp);
        for (int i = 0; i < 32; i++) hash[i] = (char)hash_tmp[i];
    }
    
    DataBuffer File::serialize(uint8_t config) {
        DataBuffer retval;
        retval.insert(hash, 32);
        retval.insert(size);
        retval.insert((char*)data, size);
        return retval;
    }
    
    File::File(DataBuffer data, uint8_t config) {
        char * hasharr = (char*)data.read(32);
        for (int i = 0; i < 32; i++) hash[i] = hasharr[i];
        free(hasharr);
        size = data.read<uint64_t>();
        this->data = data.read(size);
    }
    
    File::File(DataBuffer& data, uint8_t config, int dummy) {
        char * hasharr = (char*)data.read(32);
        for (int i = 0; i < 32; i++) hash[i] = hasharr[i];
        free(hasharr);
        size = data.read<uint64_t>();
        this->data = data.read(size);
    }
}
