//
//  DataBuffer.hpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef DataBuffer_hpp
#define DataBuffer_hpp

#include <stdint.h>
#include <list>
#include <string>

namespace HAR {
    typedef struct {
        uint64_t size;
        uint8_t * data;
    } data_buf_t;
    
    class DataBuffer {
        std::list<uint8_t> bytes;
    public:
        template<typename T>
        void insert(T value);
        void insert(char * buf, uint64_t size);
        void insert(const char * buf, uint64_t size);
        void insert(std::string str);
        template<typename T>
        T read();
        uint8_t * read(uint64_t size);
        void append(DataBuffer buf);
        data_buf_t buffer();
        uint64_t size();
    };
}

#endif /* DataBuffer_hpp */
