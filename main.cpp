#include <iostream>
//#include "huffman_coder.h"
//#include "huffman_decoder.h"
#include "deflate.h"

int main()
{

   /* char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);*/
    Lz77Comp* lz77 = new Lz77Comp("2554-0.txt");
    lz77->Compression();
    lz77->WriteCompressedTextToFile("huffmandecoded_test.bin");
    lz77->Decompressor();
    lz77->WriteUncompressedTextToFile("decompressed_example.txt");
    //lz77->WriteCompressedTextToFile(file_name_02);

    /*string str = "stellek balint egy sexy";
    string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    cout << "Character With there Frequencies:\n";
    for (auto v=codes.begin(); v!=codes.end(); v++)
        cout << v->first <<' ' << v->second << endl;

    for (auto i: str)
        encodedString+=codes[i];

    cout << "\nEncoded Huffman data:\n" << encodedString << endl;

    decodedString = decode_file(minHeap.top(), encodedString);
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl;*/
    return 0;
}