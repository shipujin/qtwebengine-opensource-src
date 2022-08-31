// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/text/mathml_operator_dictionary.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/renderer/platform/wtf/text/character_names.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

namespace blink {

static const UChar32 category_a[]{
    0x2190, 0x2191, 0x2192, 0x2193, 0x2194, 0x2195, 0x2196, 0x2197, 0x2198,
    0x2199, 0x219C, 0x219D, 0x219E, 0x219F, 0x21A0, 0x21A1, 0x21A2, 0x21A3,
    0x21A4, 0x21A5, 0x21A6, 0x21A7, 0x21A8, 0x21A9, 0x21AA, 0x21AB, 0x21AC,
    0x21BC, 0x21BD, 0x21BE, 0x21BF, 0x21C0, 0x21C1, 0x21C2, 0x21C3, 0x21C4,
    0x21C5, 0x21C6, 0x21C7, 0x21C8, 0x21C9, 0x21CA, 0x21CB, 0x21CC, 0x21D0,
    0x21D1, 0x21D2, 0x21D3, 0x21D4, 0x21D5, 0x21D6, 0x21D7, 0x21D8, 0x21D9,
    0x21DA, 0x21DB, 0x21DC, 0x21DD, 0x21E0, 0x21E1, 0x21E2, 0x21E3, 0x21E4,
    0x21E5, 0x21E6, 0x21E7, 0x21E8, 0x21E9, 0x21EA, 0x21EB, 0x21EC, 0x21ED,
    0x21EE, 0x21EF, 0x21F0, 0x21F3, 0x21F5, 0x21F6, 0x21FD, 0x21FE, 0x21FF,
    0x27F0, 0x27F1, 0x27F5, 0x27F6, 0x27F7, 0x27F8, 0x27F9, 0x27FA, 0x27FB,
    0x27FC, 0x27FD, 0x27FE, 0x27FF, 0x2952, 0x290A, 0x290B, 0x290C, 0x290D,
    0x290E, 0x290F, 0x2910, 0x2912, 0x2913, 0x2921, 0x2922, 0x294E, 0x294F,
    0x2950, 0x2951, 0x2952, 0x2953, 0x2954, 0x2955, 0x2956, 0x2957, 0x2958,
    0x2959, 0x295A, 0x295B, 0x295C, 0x295D, 0x295E, 0x295F, 0x2960, 0x2961,
    0x296E, 0x296F, 0x2B45, 0x2B46};

static const UChar32 category_b[]{
    0x002B, 0x002D, 0x002F, 0x00B1, 0x00F7, 0x0322, 0x2044, 0x2212, 0x2213,
    0x2214, 0x2215, 0x2216, 0x2218, 0x2224, 0x2227, 0x2228, 0x2229, 0x222A,
    0x2236, 0x2238, 0x228C, 0x228D, 0x228E, 0x228F, 0x2293, 0x2294, 0x2295,
    0x2296, 0x2298, 0x229D, 0x229E, 0x229F, 0x22BB, 0x22BC, 0x22BD, 0x22C4,
    0x22C6, 0x22CE, 0x22CF, 0x22D2, 0x22D3, 0x2795, 0x2796, 0x2797, 0x27F4,
    0x29BC, 0x29F6, 0x2A22, 0x2A23, 0x2A24, 0x2A25, 0x2A26, 0x2A27, 0x2A28,
    0x2A29, 0x2A2A, 0x2A2B, 0x2A2C, 0x2A2D, 0x2A2E, 0x2A38, 0x2A39, 0x2A3A,
    0x2A40, 0x2A41, 0x2A42, 0x2A43, 0x2A44, 0x2A45, 0x2A46, 0x2A47, 0x2A48,
    0x2A49, 0x2A4A, 0x2A4B, 0x2A4C, 0x2A4D, 0x2A4E, 0x2A4F, 0x2A51, 0x2A52,
    0x2A53, 0x2A54, 0x2A55, 0x2A56, 0x2A57, 0x2A58, 0x2A59, 0x2A5A, 0x2A5B,
    0x2A5C, 0x2A5D, 0x2A5E, 0x2A5F, 0x2A60, 0x2A61, 0x2A62, 0x2A63, 0x2ADA,
    0x2ADB, 0x2AFB, 0x2AFD, 0x2B32,
};

static const UChar32 category_c[]{
    0x0025, 0x002A, 0x002E, 0x003F, 0x0040, 0x005E, 0x005F, 0x007C, 0x00B7,
    0x00D7, 0x0323, 0x032B, 0x032F, 0x0332, 0x2022, 0x2043, 0x2206, 0x220E,
    0x2217, 0x223F, 0x2240, 0x2297, 0x2299, 0x22A0, 0x22A1, 0x22C5, 0x22C7,
    0x22C9, 0x22CA, 0x22CB, 0x22CC, 0x2305, 0x2306, 0x25A0, 0x25A1, 0x25AA,
    0x25AB, 0x25AD, 0x25AE, 0x25AF, 0x25B0, 0x25B1, 0x27CB, 0x27CD, 0x2981,
    0x2982, 0x2999, 0x299A, 0x29B5, 0x29C2, 0x29C3, 0x29C9, 0x29CA, 0x29CB,
    0x29CC, 0x29CD, 0x29D8, 0x29D9, 0x29DB, 0x29DF, 0x29E0, 0x29E2, 0x29E7,
    0x29E8, 0x29E9, 0x29EA, 0x29EB, 0x29EC, 0x29ED, 0x29F8, 0x29F9, 0x29FA,
    0x29FB, 0x2A1D, 0x2A1E, 0x2A1F, 0x2A20, 0x2A21, 0x2A2F, 0x2A30, 0x2A31,
    0x2A32, 0x2A33, 0x2A34, 0x2A35, 0x2A36, 0x2A37, 0x2A3B, 0x2A3C, 0x2A3D,
    0x2A3F, 0x2A50, 0x2ADC, 0x2ADD, 0x2AFE,
};

static const UChar32 category_d[]{
    0x0021, 0x002B, 0x002D, 0x00AC, 0x00B1, 0x0332, 0x2018, 0x201C, 0x2200,
    0x2201, 0x2203, 0x2204, 0x2207, 0x2212, 0x2213, 0x221F, 0x2220, 0x2221,
    0x2222, 0x223C, 0x22BE, 0x22BF, 0x2310, 0x2319, 0x2795, 0x2796, 0x27C0,
    0x299B, 0x299C, 0x299D, 0x299E, 0x299F, 0x29A0, 0x29A1, 0x29A2, 0x29A3,
    0x29A4, 0x29A5, 0x29A6, 0x29A7, 0x29A8, 0x29A9, 0x29AA, 0x29AB, 0x29AC,
    0x29AD, 0x29AE, 0x29AF, 0x2AEC, 0x2AED,
};

static const UChar32 category_e[]{
    0x0021, 0x0022, 0x0026, 0x0027, 0x0060, 0x00A8, 0x00B0, 0x00B2,
    0x00B3, 0x00B4, 0x00B8, 0x00B9, 0x02CA, 0x02CB, 0x02D8, 0x02D9,
    0x02DA, 0x02DD, 0x0311, 0x0320, 0x0325, 0x0327, 0x032A, 0x0332,
    0x2019, 0x201A, 0x201B, 0x201D, 0x201E, 0x201F, 0x2032, 0x2033,
    0x2034, 0x2035, 0x2036, 0x2037, 0x2057, 0x20DB, 0x20DC, 0x23CD,
};

static const UChar32 category_f[]{
    0x0028, 0x005B, 0x007B, 0x007C, 0x2016, 0x2308, 0x230A, 0x2329, 0x2772,
    0x27E6, 0x27E8, 0x27EA, 0x27EC, 0x27EE, 0x2980, 0x2983, 0x2985, 0x2987,
    0x2989, 0x298B, 0x298D, 0x298F, 0x2991, 0x2993, 0x2995, 0x2997, 0x29FC,
};

static const UChar32 category_g[]{
    0x0029, 0x005D, 0x007C, 0x007D, 0x2016, 0x2309, 0x230B, 0x232A, 0x2773,
    0x27E7, 0x27E9, 0x27EB, 0x27ED, 0x27EF, 0x2980, 0x2984, 0x2986, 0x2988,
    0x298A, 0x298C, 0x298E, 0x2990, 0x2992, 0x2994, 0x2996, 0x2998, 0x29FD,
};

static const UChar32 category_h[]{
    0x222B, 0x222C, 0x222D, 0x222E, 0x222F, 0x2230, 0x2231, 0x2232, 0x2233,
    0x2A0B, 0x2A0C, 0x2A0D, 0x2A0E, 0x2A0F, 0x2A10, 0x2A11, 0x2A12, 0x2A13,
    0x2A14, 0x2A15, 0x2A16, 0x2A17, 0x2A18, 0x2A19, 0x2A1A, 0x2A1B, 0x2A1C};

static const UChar32 category_i[]{
    0x005E, 0x005F, 0x007E, 0x00AF, 0x02C6, 0x02C7, 0x02C9, 0x02CD,
    0x02DC, 0x02F7, 0x0302, 0x203E, 0x2322, 0x2323, 0x23B4, 0x23B5,
    0x23DC, 0x23DD, 0x23DE, 0x23DF, 0x23E0, 0x23E1,
};

static const UChar32 category_j[]{
    0x220F, 0x2210, 0x2211, 0x22C0, 0x22C1, 0x22C2, 0x22C3,
    0x2A00, 0x2A01, 0x2A02, 0x2A03, 0x2A04, 0x2A05, 0x2A06,
    0x2A07, 0x2A08, 0x2A09, 0x2A0A, 0x2AFC, 0x2AFF,
};

static const UChar32 category_k[]{
    0x2145, 0x2146, 0x2202, 0x221A, 0x221B, 0x221C,
};

static const UChar32 category_l[]{
    0x005C, 0x2061, 0x2062, 0x2063, 0x2064,
};

static const UChar32 category_m[]{
    0x002C,
    0x003A,
    0x003B,
};

template <typename T, size_t N>
bool IsInCategory(const T (&table)[N], UChar32 character) {
  return std::binary_search(table, table + base::size(table), character);
}

String FromUChar32(UChar32 c) {
  StringBuilder input;
  input.Append(c);
  return input.ToString();
}

TEST(MathOperatorDictionaryTest, Infix) {
  for (UChar32 ch = 0; ch < kMaxCodepoint; ch++) {
    String s = FromUChar32(ch);
    s.Ensure16Bit();
    if (ch >= kCombiningMinusSignBelow &&
        ch <= kGreekCapitalReversedDottedLunateSigmaSymbol) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kNone);
    } else if (IsInCategory(category_a, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kA);
    } else if (IsInCategory(category_b, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kB);
    } else if (IsInCategory(category_c, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kC);
    } else if (IsInCategory(category_l, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kDorEorL);
    } else if (IsInCategory(category_m, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kInfix) ==
                  MathMLOperatorDictionaryCategory::kM);
    }
  }
}

TEST(MathOperatorDictionaryTest, Prefix) {
  for (UChar32 ch = 0; ch < kMaxCodepoint; ch++) {
    String s = FromUChar32(ch);
    s.Ensure16Bit();
    if (ch >= kCombiningMinusSignBelow &&
        ch <= kGreekCapitalReversedDottedLunateSigmaSymbol) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kNone);
    } else if (IsInCategory(category_d, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kDorEorL);
    } else if (IsInCategory(category_f, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kForG);
    } else if (IsInCategory(category_h, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kH);
    } else if (IsInCategory(category_j, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kJ);
    } else if (IsInCategory(category_k, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kK);
    } else {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPrefix) ==
                  MathMLOperatorDictionaryCategory::kNone);
    }
  }
}

TEST(MathOperatorDictionaryTest, Postfix) {
  for (UChar32 ch = 0; ch < kMaxCodepoint; ch++) {
    String s = FromUChar32(ch);
    s.Ensure16Bit();
    if (ch >= kCombiningMinusSignBelow &&
        ch <= kGreekCapitalReversedDottedLunateSigmaSymbol) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kNone);
    } else if (ch == kArabicMathematicalOperatorMeemWithHahWithTatweel ||
               ch == kArabicMathematicalOperatorHahWithDal) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kI);
    } else if (IsInCategory(category_e, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kDorEorL);
    } else if (IsInCategory(category_g, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kForG);
    } else if (IsInCategory(category_i, ch)) {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kI);
    } else {
      EXPECT_TRUE(FindCategory(s, MathMLOperatorDictionaryForm::kPostfix) ==
                  MathMLOperatorDictionaryCategory::kNone);
    }
  }
}

}  // namespace blink