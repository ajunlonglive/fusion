#define PCRE2_CODE_UNIT_WIDTH 8

#include <iostream>
#include <pcre2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iterator>
#include <vector>
#include <cstring>
#include <sstream>

std::vector<unsigned char> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<unsigned char> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

std::string HexString(std::vector<std::uint8_t> &bytes)
{
    std::stringstream ss;
    for (std::size_t i = 0; i < bytes.size(); i++)
    {
        if (i != 0)
        {
            ss << ", ";
        }
        ss << "0x" << std::hex << static_cast<int>(bytes[i]);
    }
    return ss.str();
}


int main() {
    int errorcode;
    uint8_t *bytes;
    PCRE2_SIZE erroroffset;
    PCRE2_SIZE bytescount;
    // const pcre2_code *list_of_codes[1];

    // PCRE2_SPTR pattern = reinterpret_cast<const unsigned char *>("^.*?\\s");
    // // PCRE2_SPTR pattern2 = reinterpret_cast<const unsigned char *>("second pattern");

    // list_of_codes[0] = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errorcode, &erroroffset, NULL);
    // // list_of_codes[1] = pcre2_compile(pattern2, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errorcode, &erroroffset, NULL);
    // errorcode = pcre2_serialize_encode(list_of_codes, 1, &bytes, &bytescount, NULL);

    // FILE* fd = fopen( "test.bin", "wb" );
    // errorcode = fwrite(bytes, 1, bytescount, fd);
    // fclose(fd);

    pcre2_code *decode_code;

    std::vector<unsigned char> fileData = readFile("test.bin");
    uint8_t *bytes_read = fileData.data();

    // std::string tests = HexString(fileData);

    // std::cout << tests << std::endl;
    // for(int f = 0; f < fileData.size(); f++) {
    //     std::cout << fileData[f] << std::flush;
    // }

    int32_t number_of_codes = pcre2_serialize_decode(&decode_code, 1, bytes_read, NULL);
    PCRE2_UCHAR *result;
    size_t resultlen;


    PCRE2_SPTR subject = reinterpret_cast<const unsigned char *>("first pattern");   

    if(decode_code) {
        pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(decode_code, NULL);

        if(pcre2_match(decode_code, subject, strlen((char *)subject), 0, 0, match_data, NULL) >= 0) {
            pcre2_substring_get_bynumber(match_data, 0, &result, &resultlen);
        } else {
            result = NULL;
            resultlen = 0;
        }

        pcre2_match_data_free(match_data);
        pcre2_code_free(decode_code);
    } else {
        std::cout << "error bos" << std::endl;
        PCRE2_UCHAR error[256]; 
        pcre2_get_error_message(errorcode, error, sizeof(error));
    }

    const char *resf = result ? (char *)result : "GA ADA YANG SESUAI";

    std::cout << resf << std::endl;

    return 0;
}