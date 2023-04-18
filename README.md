# Threaded CMD Tool for Encryption and Decryption

This is a CMD tool that implements a threadpool mechanism to parallelize an encryption algorithm provided in a shared library. The goal is to utilize multi-cores in a system to improve performance and speed up the encryption process. The encryption algorithm is not very efficient and takes 5ms for each character, with a limit of 1024 bytes of data. The tool takes input from stdIn and outputs the encrypted or decrypted data to stdOut.
Usage

### The CMD tool can be used with the following syntax:
````bash
coder key [-e | -d] < input_file > output_file
````

where: 

- `coder` is the name of the compiled executable of the CMD tool.
- `key` is the encryption key to be used in the encryption or decryption process.
- `-e` is an optional flag to specify encryption mode.
- `-d` is an optional flag to specify decryption mode.
- `<` input_file is an optional input file from which the data will be read. If not provided, the tool will read from stdIn.
- `>` output_file is an optional output file to which the encrypted or decrypted data will be written. If not provided, the tool will write to stdOut.

Alternatively, the tool can also be used with piping to pass data through the CMD tool, like this:

```bash
cat input_file | coder key [-e | -d] > output_file
```

## Example Usage
To encrypt a file named my_original_file with an encryption key of 2 and write the encrypted data to a file named encrypted_file, the following command can be used:
````bash
coder 2 -e < my_original_file > encrypted_file
````
To decrypt a file named my_decrypted_file with an encryption key of 2 and write the decrypted data to a file named my_original_file, the following command can be used:
````bash
coder 2 -d < my_decrypted_file > my_original_file
````

## Implementation Details
The CMD tool implements a threadpool mechanism to parallelize the encryption or decryption process. It utilizes multiple threads to divide the input data into smaller chunks and process them concurrently using the shared library functions "encode" and "decode". Synchronization techniques, as studied in class, are used to ensure thread safety and avoid race conditions when accessing shared resources.

The tool is designed to make efficient use of the available CPU cores on the system, maximizing the parallel processing capabilities and improving performance compared to a single-threaded approach. 

## More Information
The CMD tool is expected to be thoroughly tested, including both functional and performance testing. Automatic tests may be conducted to evaluate the correctness and efficiency of the tool. It is recommended to test the tool with various input sizes, encryption keys, and system configurations to ensure its robustness and reliability.
Conclusion

This CMD tool provides a threaded solution for encrypting and decrypting data using a shared library with an inefficient encryption algorithm. By parallelizing the encryption process, it aims to improve performance and utilize multi-cores in a system effectively. Proper synchronization techniques are implemented to ensure thread safety.

## License
[MIT](https://choosealicense.com/licenses/mit/)