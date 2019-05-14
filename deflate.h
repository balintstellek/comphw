//
// Created by Bálint Stellek on 2019-05-11.
//

#ifndef DEFLATE_LZ77_H
#define DEFLATE_LZ77_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "misc.h"
#include "huffman_decoder.h"
#endif //DEFLATE_LZ77_H

class Lz77Comp {
private:
//public:
    std:: string text_;
    std:: string compressed_text_;
    std:: string uncompressed_text_;

public:
    Lz77Comp(std::string input_file_name);
    Lz77Comp();
    std::string GetText();
    void ReadFile(std::string input_file_name);
    void ReadCompressedFile(std::string input_file_name);
    void WriteTextToFile();
    void WriteCompressedTextToFile(std::string output_filename);
    void WriteUncompressedTextToFile();
    void WriteUncompressedTextToFile(std::string uncompressed_filename);
    void Compression();
    void Decompressor();
};

Lz77Comp::Lz77Comp(){
    text_="";
};

Lz77Comp::Lz77Comp(std::string input_file_name) {

    ReadFile(input_file_name);
}

std::string Lz77Comp::GetText() {
    return text_;
}

void Lz77Comp::ReadFile(std::string input_file_name) {

    std::ifstream ifs(input_file_name);

    std::string input;
    input.assign( (std::istreambuf_iterator<char>(ifs) ),
                  (std::istreambuf_iterator<char>()    ) );

    text_ = input.substr(0, input.size()-1);

}

void Lz77Comp::ReadCompressedFile(std::string input_file_name) {

    std::ifstream ifs(input_file_name, std::ios::binary);

    std::string input;
    input.assign( (std::istreambuf_iterator<char>(ifs) ),
                  (std::istreambuf_iterator<char>()    ) );

    compressed_text_ = input.substr(0, input.size()-1);
}

void Lz77Comp::WriteTextToFile() {
    std::ofstream output_file ("example.txt");

    if (output_file.is_open())
    {
        output_file << text_;
        output_file.close();
    }

}

void Lz77Comp::WriteCompressedTextToFile(std::string output_filename) {
    std::ofstream output_file (output_filename, std::ios::binary);

    if (output_file.is_open())
    {
        output_file << compressed_text_;
        output_file.close();
    }

}

void Lz77Comp::WriteUncompressedTextToFile(std::string uncompressed_filename) {
    std::ofstream output_file (uncompressed_filename);

    if (output_file.is_open())
    {
        output_file << uncompressed_text_;
        output_file.close();
    }

}

void Lz77Comp::Compression() {

    std::string compressed = "";
    int window_size = 4095;
    int pattern_size = 15;
    int i = 0;
    std::string full_text = text_;

    std::string bin = "";

    while(i < full_text.size())
    {
        std::string s1 { i >= window_size ? full_text.substr(i - window_size, window_size) : full_text.substr(0, i) };
        std::string s2 { full_text.substr(i, std::min(pattern_size, (int)full_text.size() - i)) };

        std::pair<int,int> match = longest_prefix(s1, s2);


        if(match.second == 0)
        {
            compressed += (char)0;
            //proba
            std::bitset<8> input_bit_c((char)0);
            bin += '0';

            //uj
            //if (code_table.find(full_text[i]) != code_table.end()) {
            //    //coda_table[full_text[i]];
            //    std::bitset<16> input_bit(code_table[full_text[i]]);
            //    compressed += (char)input_bit.to_ulong();;
            //}
            //
            //TODO: Check what happens if change the full texto to binary
            compressed += full_text[i];

            // Proba
            std::bitset<8> input_bit(full_text[i]);
            bin += full_text[i];
            //std::cout << bin << std::endl;
            //

            i++;
        }
        else
        {

            std::bitset<4> length(match.second);
            std::bitset<12> pos(match.first);
            std::bitset<16> concat(length.to_string() + pos.to_string());
            std::bitset<8> input_bit01(concat.to_string().substr(0,8));
            std::bitset<8> input_bit02(concat.to_string().substr(8,8));

            compressed += (char)input_bit01.to_ulong();
            //bin +=input_bit01.to_string();
            bin +=match.first;
            compressed += (char)input_bit02.to_ulong();
            //bin +=input_bit02.to_string();
            bin +=match.second;

            //std::cout << length;

            i += match.second;
        }
    }

    compressed_text_ = compressed;
    std::cout << "Lz comp ; " << std::endl << compressed << std::endl;
    std::cout << "Lz comp size; " << std::endl << compressed.size() << std::endl;
    std::cout << "Lz bin ; " << std::endl << bin << std::endl;
    WriteCompressedTextToFile("lz_test.bin");
    //
    std::string str = compressed;
    std::string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    std::cout << "Character With there Frequencies:\n";
    for (auto v=codes.begin(); v!=codes.end(); v++)
        std::cout << v->first <<' ' << v->second << std::endl;

    for (auto i: str)
        encodedString+=codes[i];


    std::cout << "\nEncoded Huffman data:\n" << encodedString << std::endl;
    std::cout << "\nSize of coded Huffman Data:\n" << encodedString.size() << std::endl;

    decodedString = decode_file(minHeap.top(), encodedString);
    std::cout << "\nDecoded Huffman Data:\n" << decodedString << std::endl;
    std::cout << "\nSize of Decoded Huffman Data:\n" << decodedString.size() << std::endl;
    std::string compressed_huff = "";
    for(int i = 0; i < encodedString.size(); i= i +8) {
        std::bitset<8> input_bit(encodedString.substr(i, 8));
        compressed_huff += (char)input_bit.to_ulong();
    }

    std::cout << "\ncomp Huffman Data:\n" << compressed_huff << std::endl;
    std::cout << "\ncomp size Huffman Data:\n" << compressed_huff.size() << std::endl;

    std::string uncompressed_huff = "";

    for(int i = 0; i < compressed_huff.size(); i= i +1) {
        std::bitset<8> input_bit(compressed_huff[i]);
        uncompressed_huff += input_bit.to_string();
    }
    std::cout << "\nDecoompressed Huffman Data:\n" << uncompressed_huff << std::endl;
    decodedString = decode_file(minHeap.top(), uncompressed_huff);
    std::cout << "\nDecoded Huffman Data:\n" << decodedString << std::endl;
    std::cout << "\nDecoded Huffman Data size" << decodedString.size() << std::endl;

    std::bitset<16> input_bit("01010111111110111111111000101011100");
    std::cout << "\nDSeparator:" << (char)input_bit.to_ulong() << std::endl;

    compressed_text_ = compressed_huff;
    WriteCompressedTextToFile("huffmandecoded_test.bin");
    Decompressor();
    cout << "\nUncompressed deflate:\n" << uncompressed_text_ << endl;

}

void Lz77Comp::Decompressor() {

    std::string compressed = compressed_text_;
    std::string uncompressed = "";
    int window_size = 4095;


    for(int i = 0; i < compressed.size(); i += 2)
    {
        std::bitset<8> input_bit01(compressed[i]);
        std::bitset<8> input_bit02(compressed[i+1]);
        std::bitset<16> concat(input_bit01.to_string() + input_bit02.to_string());
        std::bitset<4> length_bit(concat.to_string().substr(0,4));

        int length = length_bit.to_ulong();

        if(length == 0)
        {
            std::bitset<8> character_bit(concat.to_string().substr(8, 8));
            uncompressed += (char)character_bit.to_ulong();
            //std::cout << "FUCK ME!!!!" << std::endl;
            //std::cout << uncompressed << std::endl;
        }
        else
        {
            std::bitset<12> pos(concat.to_string().substr(4, 12));
            //std::cout << "FUCK ME!!!!" << std::endl;
            uncompressed += uncompressed.substr(std::max(0, (int) uncompressed.size() - window_size) +
                                                pos.to_ulong(), length);
            //std::cout << "FUCK ME!!!!" << std::endl;
            //std::cout << i << std::endl;
        }
    }

    uncompressed_text_ = uncompressed;
    std::cout << uncompressed << std::endl;

}