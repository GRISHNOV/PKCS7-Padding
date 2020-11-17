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
