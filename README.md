# Simple Password Manager in C

This is a simple command-line password manager implemented in the C programming language. This project is meant to serve as an educational tool for learning about C programming, data structures, file I/O, and basic security measures.

## Features

- Add, view, update, and delete credentials.
- List all stored credentials.
- Generate random passwords.
- Use a master password to protect stored credentials.
- Encrypt data with a simple Caesar cipher before saving to file.
- Save and load data to and from a file.

## Installation and Usage

To compile the program, navigate to the directory containing `password_manager.c` and use the `gcc` compiler:

```bash
gcc password_manager.c -o password_manager
```

Then, to run the program:

```bash
./password_manager
```

Follow the prompts to interact with the password manager.

## Disclaimer
This project uses a simple Caesar cipher for data encryption, which is not secure for storing sensitive data. The master password is also stored in plaintext within the program. This project is intended for educational purposes and should not be used to store actual sensitive data.

## Contributing
If you'd like to contribute to this project, please open an issue or submit a pull request.

License
This project is licensed under the MIT License. See LICENSE for more information.