//
//  File.hpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdint.h>
#include <vector>
#include "types.h"
#include "picosha2.h"

namespace HAR {
    class File {
    public:
        char hash[32];
        uint64_t size;
        uint8_t * data;
        
        File(uint8_t * dat, uint64_t siz);
        DataBuffer serialize(uint8_t config);
        File(DataBuffer data, uint8_t config);
        File(DataBuffer& data, uint8_t config, int dummy);
    };
}

#endif /* File_hpp */
