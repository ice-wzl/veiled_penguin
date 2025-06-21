
# veiled_penguin 🐧

veiled_penguin is a Linux Crypter written in C++17. It recursively traverses a Linux file system, identifying and listing files that meet specific criteria for encryption. This tool is designed for educational and research purposes, particularly in the context of penetration testing and red teaming.

⚠️ **DISCLAIMER:** This software is provided for educational and research purposes only. Use it at your own risk. The author is not responsible for any damage caused to systems, data loss, or illegal activities resulting from the use or misuse of this tool. This tool encrypts and irreversibly modifies files. Once encrypted, files are not recoverable. By using this software, you agree to take full responsibility for your actions.

## Features ✨

*   **Recursive File System Traversal:** Explores the Linux file system to identify potential encryption targets.
*   **Targeted Encryption:** Selects files based on predefined criteria, avoiding critical system files to maintain system stability.
*   **Key Generation:** Generates a unique 20-byte key for each file requiring encryption.
*   **XOR Encryption:** Encrypts files using a XOR cipher with the generated key.
*   **Directory Exclusion:** Avoids specific directories (e.g., `/boot`, `/usr/lib`, `/proc`) to prevent system damage.
*   **Permission Awareness:** Checks for read permissions before traversing directories and write permissions before attempting to encrypt files.
*   **Symlink Avoidance:** Actively avoids symbolic links to prevent potential issues.
*   **Extension Filtering:** Excludes files with specific extensions (e.g., `.img`, `.elf`, `.so`) and files without extensions.

## Installation 🛠️

### Prerequisites

*   A Linux environment
*   g++ compiler
*   CMake (optional, for building with a Makefile)
*   C++17 support

### Building from Source

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/ice-wzl/veiled_penguin.git
    cd veiled_penguin
    ```

2.  **Compile the code:**

    *   **Dynamic Linking:**

        ```bash
        g++ veiledpenguin.cpp -o veiledpenguin -std=c++17 -lstdc++fs
        ```

    *   **Static Linking:**

        ```bash
        g++ veiledpenguin.cpp -o veiledpenguin -std=c++17 -lstdc++fs -static -static-libstdc++
        ```

    *   **Using Makefile:**

        ```bash
        make dynamic # for dynamic linking
        # or
        make static # for static linking
        ```

## Usage 🚀

1.  **Run the compiled executable:**

    ```bash
    ./veiledpenguin
    ```

    **Important Considerations:**

    *   The tool will recursively traverse the file system and encrypt eligible files.
    *   Avoid running this tool on production systems without thorough testing.
    *   Be aware that encrypted files are not recoverable.

## Testing Status ✅

| Testing Status | Distro        |
| :------------- | :------------ |
| Working        | Ubuntu 22.04  |
| Working, use Static | CentOS 7      |
| Not Tested     | CentOS 8      |
| Not Tested     | Rocky         |
| Not Tested     | Debian        |
| Not Tested     | RHEL          |

*   All tested times are sub 5 minutes on systems with default packages, binaries, and many user generated files.

## Contribution Guidelines 🤝

Contributions are welcome! If you'd like to contribute to veiled\_penguin, please follow these guidelines:

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Make your changes and test them thoroughly.
4.  Submit a pull request with a clear description of your changes.

## License 📜

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```
