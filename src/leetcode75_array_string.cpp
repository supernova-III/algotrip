
// You are given two strings word1 and word2. Merge the strings by adding
// letters in alternating order, starting with word1. If a string is longer than
// the other, append the additional letters onto the end of the merged string.
// Return the merged string.
//
// Input: word1 = "abc", word2 = "pqr"
// Output: "apbqcr"
// Explanation: The merged string will be merged as so:
// word1:  a   b   c
// word2:    p   q   r
// merged: a p b q c r
//
// Input: word1 = "ab", word2 = "pqrs"
// Output: "apbqrs"
// Explanation: Notice that as word2 is longer, "rs" is appended to the end.
// word1:  a   b
// word2:    p   q   r   s
// merged: a p b q   r   s
//
// Input: word1 = "abcd", word2 = "pq"
// Output: "apbqcd"
// Explanation: Notice that as word1 is longer, "cd" is appended to the end.
// word1:  a   b   c   d
// word2:    p   q
// merged: a p b q c   d
// Pattern: do for common => do for the rest
std::string mergeAlternately(std::string word1, std::string word2) {
  std::string result = {};
  result.reserve(word1.size() + word2.size());
  const auto& longest_string = word1.size() > word2.size() ? word1 : word2;
  const size_t common_len = std::min(word1.size(), word2.size());

  // Do for common part
  for (size_t i = 0; i < common_len; ++i) {
    result.push_back(word1[i]);
    result.push_back(word2[i]);
  }

  // Do for the rest if applicable
  for (size_t i = common_len; i < longest_string.size(); ++i) {
    result.push_back(longest_string[i]);
  }
  return result;
}

TEST(mergeAlternately, tests) {
  EXPECT_EQ(mergeAlternately("abc", "pqr"), "apbqcr");
  EXPECT_EQ(mergeAlternately("ab", "pqrs"), "apbqrs");
  EXPECT_EQ(mergeAlternately("abcd", "pq"), "apbqcd");
}

// For two strings s and t, we say "t divides s" if and only if s = t + ... + t
// (i.e., t is concatenated with itself one or more times). Given two strings
// str1 and str2, return the largest string x such that x divides both str1 and
// str2.
//
// Input: str1 = "ABCABC", str2 = "ABC"
// Output: "ABC"
//
// Input: str1 = "ABABAB", str2 = "ABAB"
// Output: "AB"
//
// Input: str1 = "LEET", str2 = "CODE"
// Output: ""
//
// The GCD will be substring of length GCD(l1, l2)
//
// There is a pattern of comparing two strings combined in a different way.
// The main idea is that is we generalizing concept of GCD of strings,
// the strings must have similar properties as numbers, e.g. they have to be
// commutative... This is the key for te solution
std::string gcdOfStrings(std::string str1, std::string str2) {
  const std::string sum12 = str1 + str2;
  const std::string sum21 = str2 + str1;
  if (sum12 != sum21) {
    return {};
  }
  str2.assign(str1.begin(), str1.begin() + std::gcd(str1.size(), str2.size()));
  return str2;
}

TEST(gcdOfStrings, tests) {
  EXPECT_EQ(gcdOfStrings("ABCABC", "ABC"), "ABC");
  EXPECT_EQ(gcdOfStrings("ABABAB", "ABAB"), "AB");
  EXPECT_EQ(gcdOfStrings("LEET", "CODE"), "");
}

// You have a long flowerbed in which some of the plots are planted, and some
// are not. However, flowers cannot be planted in adjacent plots. Given an
// integer array flowerbed containing 0's and 1's, where 0 means empty and 1
// means not empty, and an integer n, return true if n new flowers can be
// planted in the flowerbed without violating the no-adjacent-flowers rule and
// false otherwise.
bool canPlaceFlowers(const std::vector<int>& flowerbed, int n) {
  int nZeros = 1;
  for (size_t i = 0; i < flowerbed.size(); ++i) {
    if (flowerbed[i]) {
      nZeros = 0;
    } else {
      ++nZeros;
      if (nZeros == 3) {
        nZeros = 1;
        n -= 1;
      }
    }
  }
  ++nZeros;
  n -= (nZeros % 3 == 0);
  return n <= 0;
}

TEST(canPlaceFlowers, test) {
  EXPECT_TRUE(canPlaceFlowers({1, 0, 0, 0, 1}, 1));
  EXPECT_FALSE(canPlaceFlowers({1, 0, 0, 0, 1}, 2));
  EXPECT_TRUE(canPlaceFlowers({0, 0, 1, 0, 1}, 1));
  EXPECT_TRUE(canPlaceFlowers({0, 0, 0}, 2));
  EXPECT_TRUE(canPlaceFlowers({1, 0, 0, 0, 0, 0, 1}, 2));
}

// Given a string s, reverse only all the vowels in the string and return it.
// The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower
// and upper cases, more than once.
std::string reverseVowels(std::string s) {
  std::vector<char> stack = {};
  auto isVowel = [](char c) {
    switch (c) {
      case 'a':
      case 'A':
      case 'e':
      case 'E':
      case 'i':
      case 'I':
      case 'o':
      case 'O':
      case 'u':
      case 'U': return true;
    }
    return false;
  };
  for (const auto c : s) {
    if (isVowel(c)) {
      stack.push_back(c);
    }
  }
  size_t stack_ptr = stack.size();
  for (size_t i = 0; i < s.size(); ++i) {
    if (isVowel(s[i])) {
      s[i] = stack[--stack_ptr];
    }
  }
  return s;
}

std::string reverseVowels_tp(std::string s) {
  auto notVowel = [](char c) {
    switch (c) {
      case 'a':
      case 'A':
      case 'e':
      case 'E':
      case 'i':
      case 'I':
      case 'o':
      case 'O':
      case 'u':
      case 'U': return false;
    }
    return true;
  };

  size_t i = 0;
  size_t j = s.size() - 1;
  while (true) {
    while (i < s.size() / 2 && notVowel(s[i])) {
      ++i;
    }

    while (j > s.size() / 2 && notVowel(s[j])) {
      --j;
    }
    if (i >= s.size() / 2 && j <= s.size() / 2) break;
    std::swap(s[i++], s[j--]);
  }
  return s;
}

TEST(reverseVowels, tests) {
  EXPECT_EQ(reverseVowels_tp("hello"), "holle");
  EXPECT_EQ(reverseVowels_tp("leetcode"), "leotcede");
  EXPECT_EQ(reverseVowels_tp("ai"), "ia");
}
