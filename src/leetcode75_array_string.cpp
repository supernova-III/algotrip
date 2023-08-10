
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

// Two pointers solution
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

  int i = 0;
  int j = s.size() - 1;
  while (i < j) {
    // we incrementing left pointer until we have a vowel
    while (notVowel(s[i]) && i < j) {
      ++i;
    }

    // decrementing right pointer until we have a wovel
    while (notVowel(s[j]) && i < j) {
      --j;
    }

    // If loop ended because both pointer have reached vowels, we swap the
    // vowels
    if (i < j) {
      std::swap(s[i++], s[j--]);
    }
  }
  return s;
}

TEST(reverseVowels, tests) {
  EXPECT_EQ(reverseVowels_tp("hello"), "holle");
  EXPECT_EQ(reverseVowels_tp("leetcode"), "leotcede");
  EXPECT_EQ(reverseVowels_tp("ai"), "ia");
  EXPECT_EQ(reverseVowels_tp("a."), "a.");
}

// Given an input string s, reverse the order of the words.
// A word is defined as a sequence of non-space characters. The words in s will
// be separated by at least one space. Return a string of the words in reverse
// order concatenated by a single space. Note that s may contain leading or
// trailing spaces or multiple spaces between two words. The returned string
// should only have a single space separating the words. Do not include any
// extra spaces.
std::string reverseWords(std::string s) {
  struct StackFrame {
    size_t begin;
    size_t count;
  };

  size_t stack_ptr = 0;
  std::vector<StackFrame> stack = {};

  size_t i = 0;
  while (i < s.size()) {
    if (s[i] != ' ') {
      const auto begin = i;
      while (i < s.size() && s[i] != ' ') {
        ++i;
      }
      stack.emplace_back(begin, i - begin);
      while (i < s.size() && s[++i] == ' ') {
      }
    } else {
      ++i;
    }
  }

  std::string result = {};
  for (size_t i = stack.size(); i-- > 0;) {
    const auto& frame = stack[i];
    result += s.substr(frame.begin, frame.count);
    result += " ";
  }
  result.pop_back();
  return result;
}

TEST(reverseWords, tests) {
  EXPECT_EQ(reverseWords("the sky is blue"), "blue is sky the");
  EXPECT_EQ(reverseWords("  hello world  "), "world hello");
  EXPECT_EQ(reverseWords("a good   example"), "example good a");
}

// Given an integer array nums, return an array answer such that answer[i] is
// equal to the product of all the elements of nums except nums[i]. The product
// of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer. You
// must write an algorithm that runs in O(n) time and without using the division
// operation.
//
// The concept that solves this problem is called sliding window. Let's say we
// have an array A = [a b c d e f]. For each element, we accumulate a product of
// all previous elements except this exact element, and storing in a separate
// array:
//
// [ 1 1 1 1 1 1 ] - initial state, the prefix p is equals to 1: p = 1
//
// for the second element, that corresponds to b, we do p = p * A[1 - 1] = p *
// a:
//
//       _
// [ [a] b c d e f ], p = a
// [  1  a 1 1 1 1 ]
//
// same thing for the next element, c: p = p * A[2 - 1] = p * b = a * b:
//         _
// [ [a b] c d e f ], p = p*b = ab
// [ 1 a ab 1 1 1 ]
// and so on:
//           _
// [ [a b c] d e f ], p = p*c = abc
// [ 1 a ab abc 1 1 ]
//             _
// [ [a b c d] e f ], p = p*d = abcd
// [ 1 a ab abc abcd, 1 ]
//               _
// [ [a b c d e] f ], p = p*e = abcde
// [1 a ab abc abcd abcde]
//
// As we can see, for the last element we have the right answer. To finish with
// the rest elements, we just have to pass the input in reverse order,
// accumulating a product of all next element after the current:
//           _
// [ a b c d e [f] ], p = f
// [ 1 a ab abc abcdf abcde ]
//         _
// [ a b c d [e f] ], p = p*e = ef
// [ 1 a ab abcef abcdf abcde ]
//       _
// [ a b c [d e f] ], p = p*d = def
// [ 1 a abdef abcef abcdf abcde ]
//     _
// [ a b [c d e f] ], p = p*c = cdef
// [ 1 acdef abdef abcef abcdf abcde ]
//
// [ a [b c d e f] ], p = p*b = bcdef
// [ bcdef acdef abdef abcef abcdf abcde ]
//
// SLIDING WINDOW!
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
  int prefix = 1;
  std::vector<int> res = {};
  res.reserve(nums.size());
  res.push_back(1);
  for (int i = 1; i < nums.size(); ++i) {
    prefix *= nums[i - 1];
    res.push_back(prefix);
  }

  prefix = 1;
  for (int i = nums.size() - 1; i-- > 0;) {
    prefix *= nums[i + 1];
    res[i] *= prefix;
  }
  return res;
}

TEST(produceExceptSelf, tests) {
  const auto res1 = std::vector<int>{24, 12, 8, 6};
  EXPECT_EQ(productExceptSelf({1, 2, 3, 4}), res1);
  const auto res2 = std::vector<int>{0, 0, 9, 0, 0};
  EXPECT_EQ(productExceptSelf({-1, 1, 0, -3, 3}), res2);
}
