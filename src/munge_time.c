#include "munge_time.h"
#include "string.h"

const char* const HOUR_WORDS[] = {
    "twelve",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven"
};

void munge_time(int hours, int minutes, char* text, size_t length) {
    // Clear buffer.
    memset(text, 0, length);

    // Threshold of anticipation.
    if (minutes >= 34) {
        hours += 1;
    }

    // Convert to 12-hour time, because it's quaint.
    if (hours == 24) {
        hours -= 24;
    } else if (hours > 11) {
        hours -= 12;
    }

    const char* str_hour = HOUR_WORDS[hours];
    char* str_prepend = "";
    char* str_append = "";

    // Carefully construct an addled response.
    if (minutes == 0) {
        str_prepend = "pretty\nsure it's\n";
    } else if (minutes >= 1 && minutes < 6) {
        str_append = "\nish\ni guess";
    } else if (minutes >= 6 && minutes < 12) {
        str_prepend = "little\nafter\n";
    } else if (minutes >= 12 && minutes < 19) {
        str_prepend = "quarter\npast\n";
        str_append = "?";
    } else if (minutes >= 19 && minutes < 27) {
        str_prepend = "i dunno\nafter\n";
    } else if (minutes >= 27 && minutes < 34) {
        str_prepend = "half\npast\n";
        str_append = "?";
    } else if (minutes >= 34 && minutes < 42) {
        str_prepend = "way not\n";
        str_append = "\nyet";
    } else if (minutes >= 42 && minutes < 49) {
        str_prepend = "quarter\ntill\n";
        str_append = "?";
    } else if (minutes >= 49 && minutes < 55) {
        str_prepend = "like\nalmost\n";
    } else if (minutes >= 55 && minutes < 60) {
        str_append = "\nish\ni guess";
    } else {
        str_hour = "i\ndon't\neven";
    }

    // Construct display text.
    if (str_prepend) {
        strncat(text, str_prepend, length);
        length -= sizeof(str_prepend);
    }

    strncat(text, str_hour, length);
    length -= sizeof(str_hour);

    if (str_append) {
        strncat(text, str_append, length);
        length -= sizeof(str_append);
    }
}
