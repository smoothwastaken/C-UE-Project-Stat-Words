#include "util.h"

int caractereDunMot(unsigned char c) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 192 && c <= 255) || (c >= '0' && c <= '9') || c == '\'' || c == '-') {
            return 1;
        } else {
            return 0;
        }
}

int caractereFinDePhrase(unsigned char c) {
    if (c == '.' || c == '!' || c == '?') {
        return 1;
    } else {
        return 0;
    }
}
