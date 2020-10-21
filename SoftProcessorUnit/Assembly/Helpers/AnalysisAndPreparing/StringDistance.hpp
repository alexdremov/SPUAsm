//
//  StringDistance.hpp
//  SPUAsm
//
//  Created by Александр Дремов on 15.10.2020.
//

#ifndef StringDistance_hpp
#define StringDistance_hpp

#include <cstdio>

typedef enum {
    INSERTION,
    DELETION,
    SUBSTITUTION,
    NONE
} LevenshteinEditType;
 
struct LevenshteinEdit {
    unsigned int score;
    LevenshteinEditType type;
    char arg1;
    char arg2;
    unsigned int pos;
    struct LevenshteinEdit *prev;
};
typedef struct LevenshteinEdit LevenshteinEdit;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"


static int min3(int a, int b, int c);

static unsigned int levenshtein_matrix_calculate(LevenshteinEdit **mat, const char *str1, size_t len1,
                                                 const char *str2, size_t len2);

static LevenshteinEdit **levenshtein_matrix_create(size_t len1, size_t len2);

unsigned int levenshtein_distance(const char *str1, const char *str2, LevenshteinEdit **script);

size_t trimwhitespace(char *out, size_t len, const char *str);

#pragma clang diagnostic pop
#endif /* StringDistance_hpp */

