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

Generates the 'DigitalSign.o' object file.

Enter the terminal and execute:

`make build`


### Key-Pair Generation

Creates a public key file and a private key file.

Enter the terminal and execute:

`make genkeys`


### File Signing

Sign the input file name into a signature file.

Enter the terminal and execute:

`make sign [input file name]`


### File Authentication

Authenticate a file and its signature.

Enter the terminal and execute:

`make auth [input file name]`


Enjoy!
