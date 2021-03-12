#include <string>
#include <unordered_map>


namespace huffman {

struct huffman_code {
  std::string encoded;
  std::unordered_map<char, std::string> table;
};

struct huffman_decode {
  std::string decoded;
  bool ok;
};

huffman_code encode(const std::string& text);

huffman_decode decode(
  const std::string& encoded,
  const std::unordered_map<char, std::string>& table);

huffman_decode decode(const huffman_code& code);

} // namespace huffman
