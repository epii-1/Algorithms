template<typename T>
void fs(T &number){
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


template<typename T>
char fsc(T &number) {
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
    return c;
}

template<typename T>
bool fsb(T &number) {
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || c == EOF || (c > 47 && c < 58)))
        c = getchar();

    if (c == EOF)
        return false;

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
    return true;
}