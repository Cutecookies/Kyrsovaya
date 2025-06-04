#include "stops.h"
#include <stdexcept>

Stops::Stops()
    : stops(new std::string[30]()),
    current_size(0),
    MAX_SIZE(30)
{}

Stops::Stops(const Stops& other)
    : stops(new std::string[other.MAX_SIZE]),
    current_size(other.current_size) {
    std::copy(other.stops, other.stops + other.current_size, stops);
}

Stops::~Stops() {
    delete[] stops;
}

size_t Stops::getSize() const {
    return current_size;
}

bool Stops::addStop(const std::string& stop) {
    if (current_size >= MAX_SIZE) {
        return false;
    }

    for (size_t i = 0; i < current_size; ++i) {
        if (stops[i] == stop) {
            return false;
        }
    }

    stops[current_size] = stop;
    ++current_size;
    return true;
}

std::string& Stops::operator[](size_t index) {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return stops[index];
}

const std::string& Stops::operator[](size_t index) const {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return stops[index];
}

Stops& Stops::operator=(const Stops& other) {
    if (this != &other) {
        std::string* new_stops = new std::string[other.MAX_SIZE];
        std::copy(other.stops, other.stops + other.current_size, new_stops);

        delete[] stops;

        stops = new_stops;
        current_size = other.current_size;
    }
    return *this;
}
