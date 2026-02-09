/**
************************************************************
* @file         ringbuffer.h
* @brief        Loop buffer processing
* @author       Gizwits
* @date         2022-09-14
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#ifndef _GIZWITS_RING_BUFFER_H
#define _GIZWITS_RING_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RB_INDEX(num, idx) ( (idx) >= (num) ? (idx) - (num) : (idx) )

#define min(a, b) (a)<=(b)?(a):(b)                   ///< Calculate the minimum value

#pragma pack(1)
typedef struct {
    size_t rbCapacity;
    size_t  rbReadIndex;
    size_t  rbWriteIndex;
    uint8_t  *rbBuff;
}rb_t;
#pragma pack()

int8_t rbCreate(rb_t* rb);
int8_t rbDelete(rb_t* rb);
int32_t rbCapacity(rb_t *rb);
int32_t rbWriteIndicator(rb_t *rb);
int32_t rbReadIndicator(rb_t *rb);
int32_t rbCanRead(rb_t *rb);
int32_t rbCanWrite(rb_t *rb);
int32_t rbRead(rb_t *rb, void *data, size_t count);
int32_t rbWrite(rb_t *rb, const void *data, size_t count);

#ifdef __cplusplus
}
#endif
	
#endif
