//
// Created by Bálint Stellek on 2019-05-11.
//

#ifndef DEFLATE_BINARY_H
#include <iostream>
#include <vector>
#include <map>
#define DEFLATE_BINARY_H

#endif //DEFLATE_BINARY_H

std::map<char, int> CountCharacters(std::string words) {

    std::map<char, int> char_map;
    std::map<char,int>::iterator it = char_map.begin();

    for (char& _char : words) {
        //std::cout << _char << std::endl;
        if (char_map.find(_char) != char_map.end()) {
            char_map[_char]++;
        } else {
            char_map.insert (it, std::pair<char,int>(_char,1));
        }
    }

    return char_map;

}

std::string TextToBinaryString(std::string words) {
    std::string binary_string = "";
    for (char& _char : words) {
        binary_string +=std::bitset<8>(_char).to_string();
    }
    return binary_string;
}

std::vector<std::string> RemoveDupWord(std::string str) {
    std::vector<std::string> string_vector;
    std::string word = "";

    for (unsigned int i = 0; i < str.size(); i++) {
        //std::cout << str[i];
        if (str[i] == ' ' && str[i+1] != ' ') {

            string_vector.push_back(word);
            word = "";
        } else {
            word = word + str[i];
            //std::cout << word;
        }
    }

    return string_vector;
}

std::pair<int, int> longest_prefix(std::string s1, std::string s2)
{
    int pos =0;
    int length =0;

    for(int i = 0; i < s1.size(); i++)
    {
        int l =0;
        while(i+l < s1.size() && l < s2.size() && s1[i+l] == s2[l])
            l++;

        if(l > length)
        {
            pos = i;
            length = l;
        }

        if(i == s1.size() - length || length == s2.size())
            return std::pair<int,int>(pos, length);
    }

    return std::pair<int,int>(pos, length);
}