//
//  types.h
//  har
//
//  Created by Homework User on 11/28/18.
//  Copyright © 2018 JackMacWindows. All rights reserved.
//

#ifndef har_types_h
#define har_types_h

#define HAR_TYPE_INDEX_NUMBER 0x00
#define HAR_TYPE_INDEX_HASH 0x01
#define HAR_TYPE_UNENCRYPTED 0x00
#define HAR_TYPE_ENCRYPTED 0x02
#define HAR_TYPE_RAW 0x00
#define HAR_TYPE_ARCHIVED 0x04

#define HAR_MAGIC ((uint32_t*)"HAR@")[0]

#define HAR_ATTRIB_RDONLY 0x01
#define HAR_ATTRIB_HIDDEN 0x02
#define HAR_ATTRIB_SYSTEM 0x04
#define HAR_ATTRIB_ARCHIVE 0x20
#define HAR_ATTRIB_DIRECTORY 0x10

#include "DataBuffer.hpp"

#endif /* har_types_h */
