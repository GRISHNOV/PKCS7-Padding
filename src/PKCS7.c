#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./../include/PKCS7.h"

PKCS7_Padding* addPadding(const void* const data, const unsigned int dataLength, const unsigned char BLOCK_SIZE)
{
    if (0 == BLOCK_SIZE)
    {
        puts("ERROR: block size value must be 0 < BLOCK_SIZE < 256");
        exit(-1);
    }
    
    PKCS7_Padding* paddingResult = (PKCS7_Padding*) malloc(sizeof(PKCS7_Padding));
    if (NULL == paddingResult)
    {
        perror("problem with PKCS7_Padding* paddingResult");    /* if memory allocation failed */
        exit(-1);
    }

    unsigned char paddingBytesAmount     = BLOCK_SIZE - (dataLength % BLOCK_SIZE);  /* number of bytes to be appended */
    paddingResult->valueOfByteForPadding = paddingBytesAmount;                      /* according to the PKCS7 */
    paddingResult->dataLengthWithPadding = dataLength + paddingBytesAmount;         /* size of the final result */
    
    unsigned char* dataWithPadding = (unsigned char*) malloc(paddingResult->dataLengthWithPadding);
    if (NULL == paddingResult)
    {
        perror("problem with unsigned char* dataWithPadding");  /* if memory allocation failed */
        exit(-1);
    }
    
    memcpy(dataWithPadding, data, dataLength);      /* copying the original data for further adding padding */
    for (int i = 0; i < paddingBytesAmount; i++)
    {
        dataWithPadding[dataLength + i] = paddingResult->valueOfByteForPadding;   /* adding padding bytes */
    }
    paddingResult->dataWithPadding = dataWithPadding;

    return paddingResult;
}

PKCS7_unPadding* removePadding(const void* const data, const unsigned int dataLength)
{
    PKCS7_unPadding* unpaddingResult = (PKCS7_unPadding*) malloc(sizeof(PKCS7_unPadding));
    if (NULL == unpaddingResult)
    {
        perror("problem with PKCS7_Padding* unpaddingResult");  /* if memory allocation failed */
        exit(-1);
    }
    
    unsigned char paddingBytesAmount            = *((unsigned char *)(data + dataLength - 1));  /* last byte contains length of data to be deleted */
    unpaddingResult->valueOfRemovedByteFromData = paddingBytesAmount;                           /* according to the PKCS7 */
    unpaddingResult->dataLengthWithoutPadding   = dataLength - paddingBytesAmount;              /* size of the final result */

    unsigned char* dataWithoutPadding = (unsigned char*) malloc(unpaddingResult->dataLengthWithoutPadding);
    if (NULL == dataWithoutPadding)
    {
        perror("problem with unsigned char* dataWithoutPadding");   /* if memory allocation failed */
        exit(-1);
    }

    memcpy(dataWithoutPadding, data, unpaddingResult->dataLengthWithoutPadding);    /* taking data without bytes containing the padding value */
    unpaddingResult->dataWithoutPadding = dataWithoutPadding;

    return unpaddingResult;
}