//
// Created by Bálint Stellek on 2019-05-15.
//

#ifndef COMPHW_HUFFMAN_COMP_H
#define COMPHW_HUFFMAN_COMP_H
#include "huffman.h"
#endif //COMPHW_HUFFMAN_COMP_H

class HuffmanComp {
private:
    std:: string text_;
    std:: string compressed_text_;
    std:: string uncompressed_text_;

public:
    HuffmanComp();
    HuffmanComp(std::string input_file_name);
    void Compression();
    void Decompressor();
    void ReadFile(std::string input_file_name);
    void ReadCompressedFile(std::string input_file_name);
    void WriteCompressedTextToFile(std::string output_filename);
    void WriteUncompressedTextToFile(std::string uncompressed_filename);
};

HuffmanComp::HuffmanComp(){
    text_="";
    compressed_text_ = "";
    uncompressed_text_ = "";
};


HuffmanComp::HuffmanComp(std::string input_file_name) {

    ReadFile(input_file_name);
}


void HuffmanComp::Compression() {

    std::string str = text_;
    std::string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());

    string sxx = "";
    for (auto i: str) {
        sxx.push_back(i);

        encodedString += codes[sxx];
        sxx = "";
    }

    std::string compressed_huff = "";
    for(int i = 0; i < encodedString.size(); i= i +8) {
        std::bitset<8> input_bit(encodedString.substr(i, 8));
        compressed_huff += (char)input_bit.to_ulong();
    }

    compressed_text_ = compressed_huff;
}

void HuffmanComp::Decompressor() {

    std::string compressed = compressed_text_;
    std::string uncompressed = "";
    std::string uncompressed_huff = "";
    std::string decoded = "";

    for(int i = 0; i < compressed.size(); i= i + 1) {
        std::bitset<8> input_bit(compressed[i]);
        uncompressed_huff += input_bit.to_string();
        //std::cout << "FOS" << i << std::endl;

    }
    decoded = decode_file(minHeap.top(), uncompressed_huff);

    uncompressed_text_ = decoded;
}


void HuffmanComp::ReadFile(std::string input_file_name) {

    std::ifstream ifs(input_file_name);

    std::string input;
    input.assign( (std::istreambuf_iterator<char>(ifs) ),
                  (std::istreambuf_iterator<char>()    ) );

    text_ = input.substr(0, input.size()-1);

}

void HuffmanComp::ReadCompressedFile(std::string input_file_name) {

    std::ifstream ifs(input_file_name, std::ios::binary);

    std::string input;
    input.assign( (std::istreambuf_iterator<char>(ifs) ),
                  (std::istreambuf_iterator<char>()    ) );

    compressed_text_ = input.substr(0, input.size()-1);
}

void HuffmanComp::WriteCompressedTextToFile(std::string output_filename) {
    std::ofstream output_file (output_filename, std::ios::binary);

    if (output_file.is_open())
    {
        output_file << compressed_text_;
        output_file.close();
    }

}

void HuffmanComp::WriteUncompressedTextToFile(std::string uncompressed_filename) {
    std::ofstream output_file (uncompressed_filename);

    if (output_file.is_open())
    {
        output_file << uncompressed_text_;
        output_file.close();
    }

}