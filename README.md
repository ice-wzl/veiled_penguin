# veiled_penguin
![art](https://github.com/user-attachments/assets/489826d0-6d57-41e5-87a0-d3f7d11dd523)

## Overview
- veiled_penguin is a Linux Crypter. It will recursively walk a linux file system and build a list of files that meet certain criteria as good candidates to crypt.
- It will then generate a key for each file that requires crypting that is 20 bytes. From there it will crypt each file on the system.
- It will avoid below directories recursively.
````
{"/boot", "/usr/lib", "/proc", "/usr/sbin", "/usr/bin", "/sbin", "/usr/share", "/bin", "/dev", "/sys", "/run", "/snap"};
````
- It will ensure that you have read permissions in each directory walked, if you do not have permissions it simply wont walk further, moving onto other directories. It will actively avoid symlinks.
- For each directory encountered with the right permissions it will list all the files in the directory.
- It will avoid files with the below extensions. It will also avoid files with no extension. While encrypting binaries and other common files with no extension (.mozilla) files, there often is no purpose and only makes the system unusable. The goal of VEPE is to encrypt all user files while avoiding bricking the system entirely. VEPE will end up encrypting all the configs in `/etc` thus no user logins will be permitted.  However, if there is an active session via the console, or ssh that session will not be killed and the user can use the system (mostly).
````
{".img", ".elf", ".so"}
````
- It will avoid all files without an extension, i.e. `file` will be avoided while `file.txt` will be encrypted
- It will check if you have write permissions to the file and add it to a `vector` if you have the right permissions.
- At this point you will have a `vector` with all the files that are good encryption candidates. VEPE will then open each file in that `vector` and `xor` the first byte of the file with the first byte of the key. It will xor the second byte of the file with the second byte of the key. It will continue to do this iterating over the bytes of the file and the bytes of the key until reaching the end of the file.
- While iterating over the bytes in the file it will write the resulting `xor'd` byte to a new file with the same name and path as the origional file appending `.enc` to the resulting output file.
- When VEPE finishes `xor'ing` a file it will then remove that file from the system.
## Testing Status

| Testing Status | Distro       |
| -------------- | ------------ |
| Working | Ubuntu 22.04 |
| Working, use Static | Centos 7 |
| Not Tested | Centos 8 |
| Not Tested | Rocky |
| Not Tested | Debian |
| Not Tested | RHEL |
## Timing
- All tested times are sub 5 minutes on systems with default packages, binaries, and many user generated files.

# Compiling
- See Actions tab for pre-compiled binaries
- Ensure to use `std=c++17` as this program uses `std::filesystem` and requires `<= c++17`
````
# dynamic
g++ veiledpenguin.cpp -o veiledpenguin -std=c++17 -lstdc++fs
# static
g++ veiledpenguin.cpp -o veiledpenguin -std=c++17 -lstdc++fs -static -static-libstdc++
````
## Errors during testing
