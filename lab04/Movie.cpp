#include "Movie.h"

Movie& Movie::operator=(const Movie& other) {
    title = other.title;
    rating = other.rating;
    return *this;
}

bool operator==(const Movie& m1, const Movie& m2) {
    return(m1.title == m2.title && m1.rating == m2.rating);
}

bool isValidRating(float r) {
    return(r >= 0.0 && r <= 5.0);
}