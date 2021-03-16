# DigitalSign

## Version
1.0.0

## Authors

Shahaf Fridman

Hagit 


## Purpose

Signing and authentication of a text file via the *Folding Method*.

This code uses RSA algorithm to generate private and public keys.

Then, a .txt file can be signed using the private key of user A. The signed file is sent along with the public key and the signature files and can be authenticated via user B's public key and the file's signature.

## Usage
First, clone this repo:

```$ git clone https://github.com/Shahaf11111/DigitalSign.git```

Then enter a terminal inside the directory and choose from below:

### Build
```$ make build```

Compiles the whole code into an executable object file.

### Key-Pair Generation 
```$ make genkeys```

Creates a public key file and a private key file.

### File Signing 
```$ make sign [input file path: string]```

Sign the input file name into a signature file.

### File Authentication 
```$ make auth [input file path: string]```

Authenticate a file and its signature.

## References
- https://blog.finjan.com/hashing-algorithms-a-closer-look-at-the-methods-and-applications-for-encryption/
- https://www.baeldung.com/folding-hashing-technique
- https://www.lexology.com/library/detail.aspx?g=3305446b-36c2-47ad-ba9a-e4b70132f0ca

#
Enjoy! :smiley:
