<h1 align="center">PKCS7-Padding</h1>

Implementation of PKCS7 padding in C. It can be used to pre-prepare data before block cipher using (for example, AES).

# Algorithm description

   PKCS7 is described in [RFC 5652](https://tools.ietf.org/html/rfc5652#section-6.3).
    
   Some content-encryption algorithms assume the input length is a
   multiple of k octets, where k is greater than one.  For such
   algorithms, the input shall be padded at the trailing end with
   k-(lth mod k) octets all having value k-(lth mod k), where lth is
   the length of the input.  In other words, the input is padded at
   the trailing end with one of the following strings:

                     01 -- if lth mod k = k-1
                  02 02 -- if lth mod k = k-2
                      .
                      .
                      .
            k k ... k k -- if lth mod k = 0

   The padding can be removed unambiguously since all input is padded,
   including input values that are already a multiple of the block size,
   and no padding string is a suffix of another.  This padding method is
   well defined if and only if k is less than 256.

# Quick start

Download this repository and go to directory with project.

```
git clone https://github.com/GRISHNOV/PKCS7-Padding.git
cd PKCS7-Padding
```

Run the project build using the make utility.

```
make
```

Now the `build` folder contains the `PKCS7.o` object file. Use it together with the `PKCS7.h` header file from `include` folder to work with PKCS7 padding in your project.

For PKCS7 padding, use this function with appropriate structure:

```C
/* 
    A pointer to this structure is returned from the function addPadding().
    The structure contains result of adding PKCS7 padding.
*/
typedef struct {
    void*    dataWithPadding;        /* result of adding padding to the data */
    uint64_t dataLengthWithPadding;  /* length of the result */
    uint8_t  valueOfByteForPadding;  /* used for padding byte value */
} PKCS7_Padding; 

/* 
    Applies PKCS7 padding to data.
    Your data at the provided address does not change. A copy is created, to which the adding padding is applied.
    WARNING: use only 0 < BLOCK_SIZE < 256
*/
PKCS7_Padding* addPadding(const void* const data, const uint64_t dataLength, const uint8_t BLOCK_SIZE);
```

For PKCS7 unpadding, use this function with appropriate structure:

```C
/* 
    A pointer to this structure is returned from the function removePadding().
    The structure contains result of removing PKCS7 padding.
*/
typedef struct {
    void*    dataWithoutPadding;         /* result of remove padding from data */
    uint64_t dataLengthWithoutPadding;   /* length of the result */
    uint8_t  valueOfRemovedByteFromData; /* value of byte that was used for padding */
} PKCS7_unPadding;                              

/* 
    Remove PKCS7 padding from data.
    Your data at the provided address does not change. A copy is created, to which the removing padding is applied.
*/
PKCS7_unPadding* removePadding(const void* const data, const uint64_t dataLength);
```

Also note the `paddingBlockSize` constants from the `PKCS7.h` file, which can be used to pass to addPadding() as the third parameter. For convenience, you can set your own `BLOCK_SIZE_CUSTOM_VALUE` value to this enum:

```C
/* 
    Examples of commonly used block sizes for data padding.
    WARNING: block size for PKCS7 padding can be 0 < BLOCK_SIZE < 256 bytes.
*/
typedef enum {
    BLOCK_SIZE_128_BIT      = 128 / 8,  /* 16 bytes block */
    BLOCK_SIZE_256_BIT      = 256 / 8,  /* 32 bytes block */
    BLOCK_SIZE_CUSTOM_VALUE = 0         /* you can set your own constant to use */
} paddingBlockSize;                     /* can be used as third argument to the function addPadding() */
```

# Demonstration

You can also find `PKCS7_test.out` in the `build` folder. Use it to see how algorithm PKCS7 works.

For example (3 bytes data and 128 bits block size):

```
./build/PKCS7_test.out 24 128
```

Output:

```
************************************

ORIGINAL DATA (size is 3 bytes):

ff	fe	fd	

************************************

WITH PADDING (now size is 16 bytes):

ff	fe	fd	d
d	d	d	d
d	d	d	d
d	d	d	d

************************************

REMOVE PADDING (size is 3 bytes):

ff	fe	fd	

************************************
```