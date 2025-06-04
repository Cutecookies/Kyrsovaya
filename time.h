#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
private:
    int hours;
    int minutes;

public:
    Time(int h = 0, int m = 0);
    void validate();
    void addMinutes(int min);
    int toMinutes() const;
    std::string toString() const;
    int getHours() const;
    int getMinutes() const;
    void clearTime();
};

#endif // TIME_H
