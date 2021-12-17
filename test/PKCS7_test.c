#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "./../include/PKCS7.h"
#include "PKCS7_test.h"

void demonstrationPaddingOnTestInput(const uint8_t* const testDataExample, const uint16_t dataBitLength, const uint8_t BLOCK_SIZE);
void printDescription(void);

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        printDescription();
        exit(-1);
    }

    testDataSizeSet   testDataSizeInput = atoi(argv[1]);
    paddingBlockSize  blockSizeInput    = atoi(argv[2]) / 8;

    if (blockSizeInput != BLOCK_SIZE_128_BIT && blockSizeInput != BLOCK_SIZE_256_BIT)
    {
        printf(
            "\n"
            "\033[1m \033[31m"
            "\tPadding block size error (check second CLI argument -- arg[2])"
            "\033[0m"
            "\n"
        );
        printDescription();
        exit(-1);
    }

    switch (testDataSizeInput)
    {
    case TEST_24_BIT:
        demonstrationPaddingOnTestInput(testDataExample_24bit,  testDataSizeInput, blockSizeInput);
        break;

    case TEST_32_BIT:
        demonstrationPaddingOnTestInput(testDataExample_32bit,  testDataSizeInput, blockSizeInput);
        break;

    case TEST_64_BIT:
        demonstrationPaddingOnTestInput(testDataExample_64bit,  testDataSizeInput, blockSizeInput);
        break;

    case TEST_128_BIT:
        demonstrationPaddingOnTestInput(testDataExample_128bit, testDataSizeInput, blockSizeInput);
        break;  

    case TEST_192_BIT:
        demonstrationPaddingOnTestInput(testDataExample_192bit, testDataSizeInput, blockSizeInput);
        break;

    case TEST_256_BIT:
        demonstrationPaddingOnTestInput(testDataExample_256bit, testDataSizeInput, blockSizeInput);
        break;  

    case TEST_384_BIT:
        demonstrationPaddingOnTestInput(testDataExample_384bit, testDataSizeInput, blockSizeInput);
        break;

    case TEST_408_BIT:
        demonstrationPaddingOnTestInput(testDataExample_408bit, testDataSizeInput, blockSizeInput);
        break;      

    default:
        printf(
            "\n"
            "\033[1m \033[31m"
            "\tInput data size error (check first CLI argument -- arg[1])"
            "\033[0m"
            "\n"
        );
        printDescription();
        exit(-1);
        break;
    }

    return 0;
}

void demonstrationPaddingOnTestInput(const uint8_t* const testDataExample, const uint16_t dataBitLength, const uint8_t BLOCK_SIZE)
{
    uint8_t  testDataLength = dataBitLength / 8;
    uint8_t* testData       = (uint8_t*) malloc(testDataLength);
    
    memcpy(testData, testDataExample, testDataLength);

    printf("\n************************************\n");
    printf("\nORIGINAL DATA (size is %i bytes):\n\n", testDataLength);
    for (uint8_t i = 0; i < testDataLength; i++)
    {
        printf("%x", testData[i]);
        ((i + 1) % 4 == 0) ? printf("\n") : printf("\t");
    }
    printf("\n\n************************************\n");

    PKCS7_Padding* structWithPaddingResult = addPadding(testData, testDataLength, BLOCK_SIZE); 
    uint8_t*       ptrToPaddingDataResult  = structWithPaddingResult->dataWithPadding;

    printf("\nWITH PADDING (now size is %li bytes):\n\n", structWithPaddingResult->dataLengthWithPadding);
    for (uint16_t i = 0; i < structWithPaddingResult->dataLengthWithPadding; i++)
    {
        printf("%x", *ptrToPaddingDataResult);
        ((i + 1) % 4 == 0) ? printf("\n") : printf("\t");
        ptrToPaddingDataResult++;
    }
    printf("\n************************************\n");

    PKCS7_unPadding* structWithUnpaddingResult = removePadding(structWithPaddingResult->dataWithPadding, 
                                                               structWithPaddingResult->dataLengthWithPadding);

    uint8_t* ptrToUnpaddingDataResult  = structWithUnpaddingResult->dataWithoutPadding;

    printf("\nREMOVE PADDING (size is %li bytes):\n\n", structWithUnpaddingResult->dataLengthWithoutPadding);
    for (uint16_t i = 0; i < structWithUnpaddingResult->dataLengthWithoutPadding; i++)
    {
        printf("%x", *ptrToUnpaddingDataResult);
        ((i + 1) % 4 == 0) ? printf("\n") : printf("\t");
        ptrToUnpaddingDataResult++;
    }
    printf("\n\n************************************\n\n");

    freePaddingResult(structWithPaddingResult);
    freeUnPaddingResult(structWithUnpaddingResult);
    free(testData);
}

void printDescription(void)
{
    printf(
            "\n"
            "\033[1m \033[32m"
            "\tFirst  CLI argument (argv[1]) is size (in bits) of test data input:\n"
            "\t\tUse one of\t{24, 32, 64, 128, 192, 256, 384, 408}\n"
            "\n"
            "\tSecond CLI argument (argv[2]) is size (in bits) of padding block size:\n"
            "\t\tUse one of\t{128, 256}\n"
            "\033[0m"
            "\n\tFor example: PKCS7_test.out 24 128 or PKCS7_test.out 408 256\n"
            "\n"
        );
}