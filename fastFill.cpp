template<typename T>
void fastFill(T* v, const T& x, size_t n) {
    if (n == 0)
        return;
    size_t s(1);
    *v = x;
    while (s + s <= n) {
        memcpy((v + s), v, s * sizeof(x));
        s += s;
    }
    memcpy((v + s), v, (n - s) * sizeof(x));
}