//
//  StringDistance.cpp
//  SPUAsm
//
//  Created by Александр Дремов on 15.10.2020.
//

#include "StringDistance.hpp"
#include <string.h>
#include <stdlib.h>


static int min3(int a, int b, int c)
{
    if (a < b && a < c) {
        return a;
    }
    if (b < a && b < c) {
        return b;
    }
    return c;
}

static unsigned int levenshtein_matrix_calculate(edit **mat, const char *str1, size_t len1,
                                                 const char *str2, size_t len2)
{
    unsigned int i, j;
    for (j = 1; j <= len2; j++) {
        for (i = 1; i <= len1; i++) {
            unsigned int substitution_cost;
            unsigned int del = 0, ins = 0, subst = 0;
            unsigned int best;
            if (str1[i - 1] == str2[j - 1]) {
                substitution_cost = 0;
            }
            else {
                substitution_cost = 1;
            }
            del = mat[i - 1][j].score + 1; /* deletion */
            ins = mat[i][j - 1].score + 1; /* insertion */
            subst = mat[i - 1][j - 1].score + substitution_cost; /* substitution */
            best = (unsigned int) min3((int)del,(int)ins, (int)subst);
            mat[i][j].score = best;
            mat[i][j].arg1 = str1[i - 1];
            mat[i][j].arg2 = str2[j - 1];
            mat[i][j].pos = i - 1;
            if (best == del) {
                mat[i][j].type = DELETION;
                mat[i][j].prev = &mat[i - 1][j];
            }
            else if (best == ins) {
                mat[i][j].type = INSERTION;
                mat[i][j].prev = &mat[i][j - 1];
            }
            else {
                if (substitution_cost > 0) {
                    mat[i][j].type = SUBSTITUTION;
                }
                else {
                    mat[i][j].type = NONE;
                }
                mat[i][j].prev = &mat[i - 1][j - 1];
            }
        }
    }
    return mat[len1][len2].score;
}

static edit **levenshtein_matrix_create(size_t len1,
                                        size_t len2)
{
    unsigned int i, j;
    edit **mat = (edit **)malloc((len1 + 1) * sizeof(edit *));
    if (mat == NULL) {
        return NULL;
    }
    for (i = 0; i <= len1; i++) {
        mat[i] = (edit *)malloc((len2 + 1) * sizeof(edit));
        if (mat[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }
    }
    for (i = 0; i <= len1; i++) {
        mat[i][0].score = i;
        mat[i][0].prev = NULL;
        mat[i][0].arg1 = 0;
        mat[i][0].arg2 = 0;
    }
    
    for (j = 0; j <= len2; j++) {
        mat[0][j].score = j;
        mat[0][j].prev = NULL;
        mat[0][j].arg1 = 0;
        mat[0][j].arg2 = 0;
    }
    return mat;
}

unsigned int levenshtein_distance(const char *str1, const char *str2, edit **script)
{
    const size_t len1 = strlen(str1), len2 = strlen(str2);
    unsigned int i, distance;
    edit **mat, *head;
    
    /* If either string is empty, the distance is the other string's length */
    if (len1 == 0) {
        return (unsigned int)len2;
    }
    if (len2 == 0) {
        return (unsigned int)len1;
    }
    /* Initialise the matrix */
    mat = levenshtein_matrix_create(len1, len2);
    if (!mat) {
        *script = NULL;
        return 0;
    }
    /* Main algorithm */
    distance = levenshtein_matrix_calculate(mat, str1, len1, str2, len2);
    /* Read back the edit script */
    *script = (edit *)malloc(distance * sizeof(edit));
    if (*script) {
        i = distance - 1;
        for (head = &mat[len1][len2];
             head->prev != NULL;
             head = head->prev) {
            if (head->type != NONE) {
                memcpy(*script + i, head, sizeof(edit));
                i--;
            }
        }
    }
    else {
        distance = 0;
    }
    /* Clean up */
    for (i = 0; i <= len1; i++) {
        free(mat[i]);
    }
    free(mat);
    
    return distance;
}
