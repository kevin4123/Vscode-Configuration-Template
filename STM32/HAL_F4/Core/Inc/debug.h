#ifndef __DEBUG_H__
#define __DEBUG_H__

// 调试开关：1=打开调试，0=关闭调试
#define DEBUG 1  

#if DEBUG
    #define DEBUG_PRINTF(fmt, ...)  printf("[DEBUG] " fmt "\r\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINTF(fmt, ...)  // 什么都不做
#endif

#endif
