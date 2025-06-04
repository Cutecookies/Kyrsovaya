#include "time.h"

Time::Time(int h, int m) : hours(h), minutes(m) {
    validate();
}

void Time::validate() {
    if (hours < 0) {
        hours = 0;
    } else if (hours > 23) {
        hours = 23;
    }

    if (minutes < 0) {
        minutes = 0;
    } else if (minutes > 59) {
        minutes = 59;
    }
}

void Time::addMinutes(int min) {
    minutes += min;
    hours += minutes / 60;
    minutes %= 60;
    hours %= 24;
    validate();
}

int Time::toMinutes() const {
    return hours * 60 + minutes;
}

std::string Time::toString() const {
    return (hours < 10 ? "0" : "") + std::to_string(hours) + ":" +
           (minutes < 10 ? "0" : "") + std::to_string(minutes);
}

int Time::getHours() const {
    return hours;
}

int Time::getMinutes() const {
    return minutes;
}

void Time::clearTime() {
    minutes = 0;
    hours = 0;
}
