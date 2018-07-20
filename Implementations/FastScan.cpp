#ifndef _UNLOCKED
#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif
#endif


template<typename T>
inline void first(T &number, T& c) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c > 47 && c < 58))
		c = gc();
}

template<typename T>
inline void set_negative(T& c, bool& negative){
	if (c == '-') {
		// number is negative
		negative = true;

		// extract the next character from the buffer
		c = gc();
	}
}

template<typename T>
inline void first_negative(T &number, T& c, bool& negative) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == '-' || (c > 47 && c < 58)))
		c = gc();

	set_negative(c, negative);
}

template<typename T>
inline bool first_bool(T &number, T& c) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == EOF || (c > 47 && c < 58)))
		c = gc();

	return c != EOF;
}

template<typename T>
inline bool first_negative_bool(T &number, T& c, bool& negative) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == '-' || c == EOF || (c > 47 && c < 58)))
		c = gc();

	set_negative(c, negative);

	return c != EOF;
}

template<typename T>
inline void loop(T &number, T& c) {
	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;
}

template<typename T>
inline void decimal(T &number, T& c) {
	if (c == '.') {
		c = gc();
		for (T pot(0.1); (c>47 && c<58); c = gc(), pot *= 0.1)
			number += (c - 48)*pot;
	}
}

template<typename T>
inline void end_negative(T &number, bool& negative) {
	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number *= -1;
}


template<typename T>
void fsnd(T &number){
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

	first_negative(number, c, negative);
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
}


template<typename T>
char fsndc(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

	first_negative(number, c, negative);
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
    return c;
}

template<typename T>
bool fsndb(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

	if (!first_negative_bool(number, c, negative))
		return false;
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
    return true;
}


template<typename T>
void fsd(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	decimal(number, c);
}


template<typename T>
char fsdc(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	decimal(number, c);
	return c;
}

template<typename T>
void fs(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
}


template<typename T>
char fsc(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	return c;
}

template<typename T>
void fsn(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	end_negative(number, negative);
}


template<typename T>
char fsnc(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	end_negative(number, negative);
	return c;
}

template<typename T>
bool fsnb(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	if (!first_negative_bool(number, c, negative))
		return false;
	loop(number, c);
	end_negative(number, negative);
	return true;
}