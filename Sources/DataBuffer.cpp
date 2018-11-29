//
//  DataBuffer.cpp
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include "DataBuffer.hpp"

namespace HAR {
    template<typename T>
    void DataBuffer::insert(T value) {
        for (int i = 0; i < sizeof(T); i++) bytes.push_back(((char*)&value)[i]);
    }
    
    void DataBuffer::insert(char * buf, uint64_t size) {
        for (uint64_t i = 0; i < size; i++) bytes.push_back(buf[i]);
    }
    
    void DataBuffer::insert(const char * buf, uint64_t size) {
        for (uint64_t i = 0; i < size; i++) bytes.push_back(buf[i]);
    }
    
    void DataBuffer::insert(std::string str) {
        this->insert(str.c_str(), str.size());
        bytes.push_back((uint8_t)0);
    }
    
    void DataBuffer::append(DataBuffer buf) {
        while (buf.bytes.size() > 0) {
            bytes.push_back(buf.bytes.front());
            buf.bytes.pop_front();
        }
    }
    
    data_buf_t DataBuffer::buffer() {
        data_buf_t buf;
        buf.size = bytes.size();
        buf.data = (uint8_t*)malloc(buf.size);
        std::list<uint8_t> temp(bytes);
        for (uint64_t i = 0; i < buf.size; i++) {
            buf.data[i] = temp.front();
            temp.pop_front();
        }
        return buf;
    }
    
    template<typename T>
    T DataBuffer::read() {
        if (sizeof(T) > bytes.size()) throw std::bad_exception();
        T retval = 0;
        for (int i = 0; i < sizeof(T); i++) {
            ((uint8_t*)&retval)[i] = bytes.front();
            bytes.pop_front();
        }
        return retval;
    }
    
    template<>
    std::string DataBuffer::read<std::string>() {
        std::string retval = "";
        for (char c = read<char>(); c != '\0'; c = read<char>()) retval.push_back(c);
        return retval;
    }
    
    uint8_t * DataBuffer::read(uint64_t size) {
        if (size > bytes.size()) throw std::bad_exception();
        uint8_t * retval = (uint8_t*)malloc(size);
        for (uint64_t i = 0; i < size; i++) {
            retval[i] = bytes.front();
            bytes.pop_front();
        }
        return retval;
    }
    
    uint64_t DataBuffer::size() {
        return bytes.size();
    }
    
    template uint8_t DataBuffer::read<uint8_t>();
    template uint32_t DataBuffer::read<uint32_t>();
    template uint64_t DataBuffer::read<uint64_t>();
    template void DataBuffer::insert(uint8_t);
    template void DataBuffer::insert(uint32_t);
    template void DataBuffer::insert(uint64_t);
}
