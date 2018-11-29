//
//  main.cpp
//  har-test
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <Archive.hpp>
#define ERROR {\
std::cerr << "Usage: " << argv[0] << " <x|c|l> <archive> [directory|files...]\n";\
return 1;\
}
#ifdef __WIN32__
#include <windows.h>
#define mkdir(dir, mode) _mkdir(dir)
#else
#include <sys/stat.h>
#endif

std::ofstream out;

void extract(HAR::Archive ar, HAR::Hierarchy h, std::string path) {
    HAR::file_list list = h.listFiles();
    for (HAR::file_listing l : list) {
        if (l.second.attributes & HAR_ATTRIB_DIRECTORY) {
            mkdir((path + "/" + l.first).c_str(), 0777);
            extract(ar, *l.second.directories, path + "/" + l.first);
        } else {
            out.open((path + "/" + l.first).c_str());
            HAR::File * f = ar.readFile(l.second.index);
            assert(f != NULL);
            out.write((char*)f->data, f->size);
            out.close();
        }
    }
}

void list(HAR::Hierarchy h, std::string path) {
    HAR::file_list listt = h.listFiles();
    for (HAR::file_listing l : listt) {
        if (l.second.attributes & HAR_ATTRIB_DIRECTORY) {
            list(*l.second.directories, path + "/" + l.first);
        } else {
            std::cout << path << "/" << l.first << "\n";
        }
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 3) ERROR
    if (argv[1][0] == 'x') {
        std::ifstream in;
        in.open(argv[2], std::ios::ate);
        if (in.bad()) {
            std::cerr << "Could not open " << argv[2] << "\n";
            return 2;
        }
        uint64_t size = in.tellg();
        in.seekg(0);
        if (in.tellg() != 0) {
            std::cerr << "Could not read entire file: " << argv[2] << "\n";
            return 3;
        }
        uint8_t * data = (uint8_t*)malloc(size);
        in.read((char*)data, size);
        if (in.tellg() != size) {
            std::cerr << "Could not read entire file: " << argv[2] << "\n";
            return 3;
        }
        in.close();
        HAR::DataBuffer buf;
        buf.insert((char*)data, size);
        //std::cout << size;
        HAR::Archive har(buf);
        std::string basePath = ".";
        if (argc > 3) basePath = std::string(argv[3]);
        extract(har, har.entries, basePath);
    } else if (argv[1][0] == 'c') {
        if (argc < 4) ERROR
        HAR::Archive har;
        std::ifstream in;
        for (int i = 3; i < argc; i++) {
            in.open(argv[i], std::ios::ate);
            if (in.bad()) {
                std::cerr << "Could not open " << argv[i] << "\n";
                return 2;
            }
            uint64_t size = in.tellg();
            in.seekg(0);
            if (in.tellg() != 0) {
                std::cerr << "Could not read entire file: " << argv[i] << "\n";
                return 3;
            }
            uint8_t * data = (uint8_t*)malloc(size);
            in.read((char*)data, size);
            if (in.tellg() != size) {
                std::cerr << "Could not read entire file: " << argv[i] << "\n";
                return 3;
            }
            in.close();
            har.addFile(argv[i], data, size, 0);
        }
        std::ofstream out(argv[2]);
        HAR::data_buf_t data = har.serialize().buffer();
        out.write((char*)data.data, data.size);
        out.close();
    } else if (argv[1][0] == 'l') {
        std::ifstream in;
        in.open(argv[2], std::ios::ate);
        if (in.bad()) {
            std::cerr << "Could not open " << argv[2] << "\n";
            return 2;
        }
        uint64_t size = in.tellg();
        in.seekg(0);
        if (in.tellg() != 0) {
            std::cerr << "Could not read entire file: " << argv[2] << "\n";
            return 3;
        }
        uint8_t * data = (uint8_t*)malloc(size);
        in.read((char*)data, size);
        if (in.tellg() != size) {
            std::cerr << "Could not read entire file: " << argv[2] << "\n";
            return 3;
        }
        in.close();
        HAR::DataBuffer buf;
        buf.insert((char*)data, size);
        //std::cout << size;
        HAR::Archive har(buf);
        list(har.entries, "");
    } else ERROR
    return 0;
}
