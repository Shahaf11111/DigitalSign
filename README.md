# DigitalSign

## Version
1.0.0

## Authors

Shahaf Fridman

Hagit 


## Purpose

Signing and authenticating of a text file via the *Folding Method*.

Reference: https://blog.finjan.com/hashing-algorithms-a-closer-look-at-the-methods-and-applications-for-encryption/

## Usage

### Build
`make build`

Generates the 'DigitalSign.o' object file.

### Key-Pair Generation `make genkeys`

Creates a public key file and a private key file.

### File Signing `make sign [input file name]`

Sign the input file name into a signature file.

### File Authentication `make auth [input file name]`

Authenticate a file and its signature.


Enjoy!
