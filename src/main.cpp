#include <algorithm>
#include <iterator>
#include <iostream>

#include "huffman.h"


int run() {
  std::ostream& out = std::cout;
  std::istream& in = std::cin;
  out
      << "Given a string we build its huffman encoding and the huffamn table .\n";
  out << "Enter text for encoding: ";
  auto text = std::string{};
  in >> text;
  auto code = huffman::encode(text);
  out << "Original text: " << text << '\n';
  out << "Encoded text: " << code.encoded << '\n';
  out << "Text has " << code.table.size() << " unique symbols\n";
  out << "Original text size: " << text.size() << '\n';
  out << "Encoded text size: " << code.encoded.size() << '\n';
  out << "Huffman table: \n";
  for (const auto& item : code.table) {
    out << item.first << ": " << item.second << '\n';
  }
  auto decode_result = huffman::decode(code);
  if (!decode_result.ok) {
    out << "Internal error. Cannot decode encoded string " << text << '\n';
    return 1;
  }
  if (text != decode_result.decoded) {
    out << "Decoded text does not coincide with the original text";
  }
  out << "Decoded text: " << decode_result.decoded << '\n';
  return 0;
}

int main()
{
    run();
    return 0;
}
