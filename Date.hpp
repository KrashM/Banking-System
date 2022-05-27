#pragma once

#include "Includes.hpp"

class Date{

    public:
        Date();
        Date(const time_t);
        Date(const Date &);

        Date &operator =(const Date &);

        const char *toString() const;

    private:
        time_t time;

        void copy(const Date &);

};