#ifndef STOPS_H
#define STOPS_H

#include <string>

class Stops {
private:
    std::string* stops;
    size_t current_size;
    const size_t MAX_SIZE = 30;

public:
    Stops();
    Stops(const Stops& other);
    ~Stops();

    size_t getSize() const;
    bool addStop(const std::string& str);
    std::string& operator[](size_t index);
    const std::string& operator[](size_t index) const;
    Stops& operator=(const Stops& other);
};

#endif // STOPS_H
