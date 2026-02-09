/**
************************************************************
* @file         ringbuffer.c
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
#include "ringBuffer.h"
#include "common.h"

int8_t ICACHE_FLASH_ATTR rbCreate(rb_t* rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    rb->rbReadIndex = 0;
    rb->rbWriteIndex = 0;
    return 0;
}

int8_t ICACHE_FLASH_ATTR rbDelete(rb_t* rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    rb->rbBuff = NULL;
    rb->rbReadIndex = 0;
    rb->rbWriteIndex = 0;
    rb->rbCapacity = 0;
		return 0;
}

int32_t ICACHE_FLASH_ATTR rbCapacity(rb_t *rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    return rb->rbCapacity;
}

int32_t ICACHE_FLASH_ATTR rbWriteIndicator(rb_t *rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    if (rb->rbWriteIndex >= rb->rbCapacity )
    {
      return rb->rbWriteIndex - rb->rbCapacity;
    }
    
    return rb->rbWriteIndex;
}

int32_t ICACHE_FLASH_ATTR rbReadIndicator(rb_t *rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    if (rb->rbReadIndex >= rb->rbCapacity )
    {
      return rb->rbReadIndex - rb->rbCapacity;
    }
    
    return rb->rbReadIndex;
}

int32_t ICACHE_FLASH_ATTR rbCanRead(rb_t *rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    if (rb->rbWriteIndex == rb->rbReadIndex)
    {
        return 0;
    }

    if (rb->rbReadIndex < rb->rbWriteIndex)
    {
        return rb->rbWriteIndex - rb->rbReadIndex;
    }

    return 2 * rbCapacity(rb) - (rb->rbReadIndex - rb->rbWriteIndex);;
}

int32_t ICACHE_FLASH_ATTR rbCanWrite(rb_t *rb)
{
    if(NULL == rb)
    {
        return -1;
    }

    return rbCapacity(rb) - rbCanRead(rb);
}

int32_t ICACHE_FLASH_ATTR rbRead(rb_t *rb, void *data, size_t count)
{
    int32_t copySz = 0;

    if(NULL == rb||(NULL == data))
    {
        return -1;
    }

    if (rb->rbReadIndex < rb->rbWriteIndex)
    {
        copySz = min(count, rbCanRead(rb));
        memcpy(data,&rb->rbBuff[rbReadIndicator(rb)], copySz);
        rb->rbReadIndex += copySz;
        return copySz;
    }
    else
    {
        if (count < (2 * rbCapacity(rb) - rb->rbReadIndex))
        {
            copySz = count;
            memcpy(data, &rb->rbBuff[rbReadIndicator(rb)], copySz);
            rb->rbReadIndex += copySz;
            return copySz;
        }
        else
        {
            copySz = 2 * rbCapacity(rb) - rb->rbReadIndex;
            memcpy(data, &rb->rbBuff[rbReadIndicator(rb)], copySz);
            rb->rbReadIndex = 0;
            copySz += rbRead(rb, (char*)data+copySz, count-copySz);
            return copySz;
        }
    }
}

int32_t ICACHE_FLASH_ATTR rbWrite(rb_t *rb, const void *data, size_t count)
{
    int32_t tailAvailSz = 0;

    if((NULL == rb)||(NULL == data))
    {
        return -1;
    }
    if (count > rbCanWrite(rb))
    {
        return -2;
    }

    if (rb->rbWriteIndex >= rb->rbReadIndex)
    {
      tailAvailSz = 2 * rbCapacity(rb) - rb->rbWriteIndex;    
      if (tailAvailSz >= count)
      {
          memcpy(&rb->rbBuff[rbWriteIndicator(rb)], data, count);
          rb->rbWriteIndex += count;
          if (rb->rbWriteIndex >= 2 * rbCapacity(rb))
          {
              rb->rbWriteIndex = 0;
          }
          return count;
      }
      else
      {
          memcpy(&rb->rbBuff[rbWriteIndicator(rb)], data, tailAvailSz);
          rb->rbWriteIndex = 0;

          return tailAvailSz + rbWrite(rb, (char*)data+tailAvailSz, count-tailAvailSz);
      }
    }
    else
    {
        memcpy(&rb->rbBuff[rbWriteIndicator(rb)], data, count);
        rb->rbWriteIndex += count;

        return count;
    }
}
