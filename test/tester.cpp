#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

#include "huffman.h"

namespace huffman {

namespace testing {

template <typename Ty, typename Comp, typename Alloc>
std::ostream& operator << (std::ostream& out, const std::set<Ty, Comp, Alloc>& s) {
  out << "{";
  std::copy(std::begin(s), std::end(s), std::ostream_iterator<Ty>(out, ", "));
  out << "}";
  return out;
}

template <typename Key, typename Ty, typename Hash, typename Pred, typename Alloc>
std::ostream& operator << (
  std::ostream& out,
  const std::unordered_map<Key, Ty, Hash, Pred, Alloc>& m) {
  out << "{\n";
  for (const auto& item : m) {
    out << "  " << item.first << ": " << item.second << ",\n";
  }
  out << "}";
  return out;
}



template <typename Ty1, typename Ty2>
std::ostream& operator << (std::ostream& out, const std::pair<Ty1, Ty2>& p) {
  out << "<" << p.first << ", " << p.second << ">";
  return out;
}

template <typename T>
bool assert_equal(
  std::ostream& out,
  const T& result,
  const T& expected,
  const std::string& comment) {
  if (result != expected) {
    out << comment << '\n';
    out << "Got:\n" << result << '\n';
    out << "Expected:\n" << expected << '\n';
    return false;
  }
  return true;
}

std::string generate_random_string(const size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    auto text = std::string(length, 0);
    std::generate_n(text.begin(), length, randchar);
    return text;
}

bool run_test(std::ostream& out, const std::string& text) {
  out << "Testing encoding and decoding of text:\n" << text << '\n';
  auto decode_result = huffman::decode(huffman::encode(text));
  if (!decode_result.ok) {
    out << "Cannot decode encoded string\n";
    return false;
  }
  return assert_equal(
    out,
    decode_result.decoded,
    text,
    "Text after encoding and decoding back differs from the original\n");
}

} // namespace testing

} // namespace huffman


int main() {
  using namespace huffman::testing;
  for (auto length = std::size_t{1}; length < 20; ++length) {
    auto text = generate_random_string(length);
    if(!run_test(std::cout, text)) {
      return 1;
    }
  }
  return 0;
}