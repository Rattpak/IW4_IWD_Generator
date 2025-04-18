#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unordered_set>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include "color.hpp"
#include "zip.h"
#include "minizip/zip.h"
#include "minizip/unzip.h"
#include <regex>

using std::string;
namespace fs = std::filesystem;

bool configExist();
bool isValidFileName(const string&);
std::string loadData();
void storeData(std::string);
std::vector<string> iwdFileSearch(string);
string removeDoubleQuotes(const string&);
string toIWI(string);
void printSimilarities(std::vector<string>, std::vector<string>, string, string&);
std::vector<string> removeImagesPrefix(const std::vector<string>&);
string removeImagesPrefix(string);
void createFolderExists(const string&);
string getCurrentModel(string);
void create_zip_archive(string);

string currentModel;
string spdataDir;

int main() {
    bool cnt = true;
    std::vector<string> img_names;
    string in = "";
    string root = "";

    if (configExist()) {
        root = loadData();
        std::cout << "Loaded MW2 Root folder at: " << dye::aqua(root) << std::endl;
    }
    else {
        std::cout << "Type or Drag your MW2 Root folder below" << std::endl;
        getline(std::cin, root);
        root = removeDoubleQuotes(root);
        storeData(root);
    }

    string dest = root + "/custom_iwd/";
    spdataDir = root + "/spdata/";
    createFolderExists(spdataDir);
    createFolderExists(dest);
    
    short convMode = 0;
    std::cout << dye::light_green("Choose Operation:") << std::endl;
    std::cout << dye::light_green("\t0 - Single Conversion") << std::endl;
    std::cout << dye::light_green("\t1 - Batch Conversion") << std::endl;
    std::cout << dye::yellow("> ");
    std::cin >> convMode;

    std::vector<string> batchItems;

    if (convMode == 0) {
        std::cout << "Drag the ripped xmodel folder onto window or type path below." << std::endl;
        std::cin.ignore();
        getline(std::cin, in);
        in = removeDoubleQuotes(in);
        currentModel = getCurrentModel(in);
        //do main operations
        string imgdir = in + "/_images/";
        DIR* dir = opendir(imgdir.c_str());
        if (dir == nullptr) {
            std::cout << "Could not open directory" << std::endl;
            return 1;
        }
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr) {
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
            }
            else {
                string fileName = ent->d_name;
                img_names.push_back(toIWI(fileName));
            }
        }
        closedir(dir);
    }
    else {
        std::cout << "Drag the ripped xmodel folder onto window or type path below." << std::endl;
        std::cout << dye::aqua("For batch conversions, press ENTER after each input. Hit ENTER again when done") << std::endl;
        string tPath = "";
        std::cin.ignore();
        while (1) {
            getline(std::cin, tPath);
            tPath = removeDoubleQuotes(tPath);
            if (tPath.empty()) { //exit batch input
                std::cout << dye::light_green("\nBatch Input Complete...") << std::endl;
                break;
            }
            batchItems.push_back(tPath);
        }
        string fname = "default";
        std::cout << dye::aqua("Enter a name for the IWD file") << std::endl;
        getline(std::cin, fname);
        if (fname.empty() || !isValidFileName(fname)) {
            std::cout << dye::yellow("Invalid name; Generating using name 'default'") << std::endl;
            fname = "default/";
            currentModel = "default";//file name based off this and im not rewriting
        }
        else {
            currentModel = fname;
        }
        std::cout << dye::aqua("Preparing conversion on ") << dye::aqua(batchItems.size()) << dye::aqua(" models") << std::endl;

        //do main operations
        for (int i = 0; i < batchItems.size(); i++) {
            string imgdir = batchItems[i] + "/_images/";
            DIR* dir = opendir(imgdir.c_str());
            if (dir == nullptr) {
                std::cout << "Could not open directory" << std::endl;
                return 1;
            }
            struct dirent* ent;
            while ((ent = readdir(dir)) != nullptr) {
                if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
                }
                else {
                    string fileName = ent->d_name;
                    img_names.push_back(toIWI(fileName));
                }
            }
            closedir(dir);
        }

    }
      
    
    

    std::cout << "Found " << img_names.size() << " images" << std::endl;
    std::vector<string> iwd00 = iwdFileSearch(root + "/main/iw_00.iwd");
    std::vector<string> iwd01 = iwdFileSearch(root + "/main/iw_01.iwd");
    std::vector<string> iwd02 = iwdFileSearch(root + "/main/iw_02.iwd");
    std::vector<string> iwd03 = iwdFileSearch(root + "/main/iw_03.iwd");
    std::vector<string> iwd04 = iwdFileSearch(root + "/main/iw_04.iwd");
    std::vector<string> iwd05 = iwdFileSearch(root + "/main/iw_05.iwd");
    std::vector<string> iwd06 = iwdFileSearch(root + "/main/iw_06.iwd");
    std::vector<string> iwd07 = iwdFileSearch(root + "/main/iw_07.iwd");
    std::vector<string> iwd08 = iwdFileSearch(root + "/main/iw_08.iwd");
    std::vector<string> iwd09 = iwdFileSearch(root + "/main/iw_09.iwd");
    std::vector<string> iwd10 = iwdFileSearch(root + "/main/iw_10.iwd");
    std::vector<string> iwd11 = iwdFileSearch(root + "/main/iw_11.iwd");
    std::cout << "Loaded all MW2 IWD Files...\n\n" << std::endl;

    std::cout << dye::on_light_aqua("----------[iwd00]----------") << std::endl;
    printSimilarities(img_names, iwd00, root + "/main/iw_00.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd01]----------") << std::endl;
    printSimilarities(img_names, iwd01, root + "/main/iw_01.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd02]----------") << std::endl;
    printSimilarities(img_names, iwd02, root + "/main/iw_02.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd03]----------") << std::endl;
    printSimilarities(img_names, iwd03, root + "/main/iw_03.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd04]----------") << std::endl;
    printSimilarities(img_names, iwd04, root + "/main/iw_04.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd05]----------") << std::endl;
    printSimilarities(img_names, iwd05, root + "/main/iw_05.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd06]----------") << std::endl;
    printSimilarities(img_names, iwd06, root + "/main/iw_06.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd07]----------") << std::endl;
    printSimilarities(img_names, iwd07, root + "/main/iw_07.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd08]----------") << std::endl;
    printSimilarities(img_names, iwd08, root + "/main/iw_08.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd09]----------") << std::endl;
    printSimilarities(img_names, iwd09, root + "/main/iw_09.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd10]----------") << std::endl;
    printSimilarities(img_names, iwd10, root + "/main/iw_10.iwd", dest);
    std::cout << dye::on_light_aqua("----------[iwd11]----------") << std::endl;
    printSimilarities(img_names, iwd11, root + "/main/iw_11.iwd", dest);
    std::cout << "\n\n\n";  
    //package iwd
  
    create_zip_archive(dest + currentModel);

    
    std::cout << "\n\n\n";
    system("pause");
}

string removeDoubleQuotes(const string& str)
{
    string result;
    for (char c : str) {
        if (c != '"') {
            result += c;
        }
    }
    return result;
}

string toIWI(string filename) {
    size_t pos = filename.rfind('.');
    if (pos != std::string::npos) {
        filename.erase(pos);
    }
    return filename + ".iwi";

}
std::vector<string> iwdFileSearch(string path) {
    std::vector<string> v;
    const char* zipfile = path.c_str();
    unzFile uf = unzOpen(zipfile);
    if (!uf) {
        fprintf(stderr, "cannot open %s\n", zipfile);
        return v;
    }

    int ret = unzGoToFirstFile(uf);
    while (ret == UNZ_OK) {
        char filename[256];
        unz_file_info64 file_info;
        ret = unzGetCurrentFileInfo64(uf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
        if (ret != UNZ_OK) {
            fprintf(stderr, "error reading file info: %d\n", ret);
            break;
        }
        v.push_back(filename);

        ret = unzGoToNextFile(uf);
    }
    unzClose(uf);
    return removeImagesPrefix(v);
}

void printSimilarities(std::vector<string> v1, std::vector<string> v2, string iwd, string& out) {
    zip* z = zip_open(iwd.c_str(), 0, nullptr);
    if (z == nullptr) {
        std::cerr << dye::red("Error opening zip file: ") << iwd << std::endl;
        return;
    }
    for (const string& s : v1) {
        if (find(v2.begin(), v2.end(), s) != v2.end()) {
            std::cout << s << std::endl;
            for (int i = 0; i < zip_get_num_files(z); i++) {
                zip_file* f = zip_fopen_index(z, i, 0);
                if (f == nullptr) {
                    std::cerr << dye::red("Error opening zip file entry: ") << i << std::endl;
                    continue;
                }
                const char* name = zip_get_name(z, i, 0);
                if (name == nullptr) {
                    std::cerr << dye::red("Error getting zip file entry name: ") << i << std::endl;
                    zip_fclose(f);
                    continue;
                }
                if (s == removeImagesPrefix(name)) {
                    //std::cout << s << " == " << removeImagesPrefix(name) << std::endl;
                    std::stringstream buf;
                    char buffer[1024];
                    int bytes_read;
                    while ((bytes_read = zip_fread(f, buffer, 1024)) > 0) {
                        buf.write(buffer, bytes_read);
                    }
                    string t = out +currentModel;
                    createFolderExists(t);
                    t = t + "/" + s;
                    //std::cout << "t = " << t << std::endl;
                    std::ofstream out(t, std::ios::binary);
                    out << buf.rdbuf();
                    out.close();
                }
                zip_fclose(f);
            }
        }
    }
    zip_close(z);
}

std::vector<string> removeImagesPrefix(const std::vector<string>& strings) {
    std::vector<std::string> result;
    const std::string prefix = "images/";
    for (const std::string& str : strings) {
        if (str.find(prefix) == 0) {
            result.push_back(str.substr(prefix.size()));
        }
        else {
            result.push_back(str);
        }
    }
    return result;
}

string removeImagesPrefix(string str) {
    if (str.find("images/") == 0) {
        str.erase(0, 7);
    }
    return str;
}

void createFolderExists(const string& path) {
    if (!fs::exists(path)) {
        try {
            fs::create_directory(path);
        }
        catch (const std::exception& e) {
            std::cerr << dye::red("Error creating directory: ") << e.what() << '\n';
        }
    }
}

std::string getCurrentModel(string filepath) {
    std::size_t found = filepath.find_last_of("/\\");
    return filepath.substr(found + 1);
}

void create_zip_archive(string path) {
    string zipname = spdataDir + currentModel + ".iwd";
    std::cout << "Generating IWD...\n\nIWD INFO: " << zipname << std::endl;
    zipFile zip_archive = zipOpen(zipname.c_str(), APPEND_STATUS_CREATE);

    DIR* dir = opendir(path.c_str());
    if (dir == NULL) {
        std::cout << dye::red("Error opening directory: ") << dye::red(path) << std::endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string filename = entry->d_name;
        if (filename == "." || filename == "..") {
            continue;
        }
        string file_path = path + "/" + filename;
        zip_fileinfo file_info = { 0 };
        int zip_error = zipOpenNewFileInZip(zip_archive, ("images/" + filename).c_str(), &file_info, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
        if (zip_error != ZIP_OK) {
            std::cout << "Error adding file to zip archive: " << file_path << std::endl;
            continue;
        }
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Error opening file: " << file_path << std::endl;
            continue;
        }

        char buffer[1024];
        while (file.read(buffer, 1024)) {
            zipWriteInFileInZip(zip_archive, buffer, 1024);
        }

        //write remaining data to zip archive
        int remaining = file.gcount();
        if (remaining > 0) {
            zipWriteInFileInZip(zip_archive, buffer, remaining);
        }

        zipCloseFileInZip(zip_archive);
    }
    closedir(dir);
    zipClose(zip_archive, NULL);
}

std::string loadData() {
    char* appdata = nullptr;
    size_t len;
    std::string filepath;
    if (_dupenv_s(&appdata, &len, "APPDATA") == 0) {
        filepath = std::string(appdata) + "\\rattpak\\iw4_iwd_gen\\config.cfg";
        free(appdata);
    }
    else {
        throw std::runtime_error("Error getting APPDATA environment variable");
    }
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return "";
    }
    std::string data((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();
    return data;
}

void storeData(std::string data) {
    char* appdata = nullptr;
    size_t len;
    std::string filepath;
    if (_dupenv_s(&appdata, &len, "APPDATA") == 0) {
        filepath = std::string(appdata) + "\\rattpak\\iw4_iwd_gen\\config.cfg";
        free(appdata);
    }
    else {
        throw std::runtime_error("Error getting APPDATA environment variable");
    }
    std::filesystem::path filePath(filepath);
    std::filesystem::create_directories(filePath.parent_path());
    std::ofstream file(filepath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error creating config.cfg file" << std::endl;
    }
    file << data;
    file.close();
    if (file.fail()) {
        std::cerr << "Error writing data to config.cfg" << std::endl;
    }
}

bool configExist() {
    char* appdata = nullptr;
    size_t len;
    std::string filepath;
    if (_dupenv_s(&appdata, &len, "APPDATA") == 0) {
        filepath = std::string(appdata) + "\\rattpak\\iw4_iwd_gen\\config.cfg";
        free(appdata);
    }
    else {
        throw std::runtime_error("Error getting APPDATA environment variable");
    }
    std::ifstream file(filepath);
    if (file.good()) {
        file.close();
        return true;
    }
    else {
        return false;
    }
}


bool isValidFileName(const string& fileName) {
    // Define a regular expression that matches any forbidden characters
    std::regex forbiddenChars("[\\\\/:*?\"<>|]");
    // Check if the file name contains any of the forbidden characters
    return !std::regex_search(fileName, forbiddenChars);
}