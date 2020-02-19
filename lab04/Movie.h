#ifndef MOVIE_H
#define MOVIE_H

#include <string>

struct Movie {
    std::string title;
    float rating;

    Movie& operator=(const Movie& other);
};

bool operator==(const Movie& m1, const Movie& m2);
bool isValidRating(float r);

#endif