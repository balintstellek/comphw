#!/bin/sh

file_name=$1

./comphw -huff -c ${file_name} compressed-huff-${file_name}.bin
./comphw -huff -d compressed-huff-${file_name}.bin decompressed-huff-${file_name} ${file_name}

./comphw -lz -c ${file_name} compressed-lz-${file_name}.bin
./comphw -lz -d compressed-lz-${file_name}.bin decompressed-lz-${file_name}

./comphw -def -c ${file_name} compressed-deflate-${file_name}.bin
./comphw -def -d compressed-deflate-${file_name}.bin decompressed-deflate-${file_name} ${file_name}

