#include <iostream>
//#include "huffman_coder.h"
//#include "huffman_decoder.h"
#include "deflate.h"
#include "lz77.h"

int main(int argc, char* argv[]) {

    std::string algorithm = argv[1];
    std::string direction = argv[2];
    std::string file_name_01 = argv[3];
    std::string file_name_02 = argv[4];
    std::string file_name_03 = "";

    if(argc == 6) file_name_03 = argv[5];

    if(algorithm == "-lz" && direction == "-c")  {
        Lz77Comp* lz77 = new Lz77Comp(file_name_01);
        lz77->Compression();
        lz77->WriteCompressedTextToFile(file_name_02);
    }
    else if (algorithm == "-lz" && direction == "-d") {
        Lz77Comp* lz77 = new Lz77Comp();
        lz77->ReadCompressedFile(file_name_01);
        lz77->Decompressor();
        lz77->WriteUncompressedTextToFile(file_name_02);
    }
    else if (algorithm == "-def" && direction == "-c") {
        Deflate *deflate = new Deflate(file_name_01);
        deflate->Compression();
        deflate->WriteCompressedTextToFile(file_name_02);
    }
    else if (algorithm == "-def" && direction == "-d") {
        Deflate *deflate = new Deflate(file_name_03);
        deflate->Compression();
        deflate->ReadCompressedFile(file_name_01);
        deflate->Decompressor();
        deflate->WriteUncompressedTextToFile(file_name_02);
    }

    return 0;
}