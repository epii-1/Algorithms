#https://liu.kattis.com/problems/generalchineseremainder
def extended_gcd(a, b):
    s = 0 
    old_s = 1
    t = 1
    old_t= 0
    r = b
    old_r = a
    tt = 0
    while (r != 0):
        q = old_r // r
        tt = r
        r = old_r - q * r
        old_r = tt
        tt = s
        s = old_s - q * s
        old_s = tt
        tt = t
        t = old_t - q * t
        old_t = tt
    
    return (old_s, old_t)

def gcd(a, b):
    if a < b:
        b1 = b
        b = a
        a = b1
    while(b > 0):
       b1 = a%b
       a = b
       b = b1
    return a

def chinese_reminder(a, b, n, m):
    g = gcd(n, m)
    if(a % g != b % g):
        return ("no solution", "");
    n = n//g
    m = m//g
    c1, c2 = extended_gcd(n, m)
    k = n*m*g
    x = ((b*c1*n + a*c2*m) % k + k) % k
    return (x, k);


def main():
    T = int(input())

    for x in range(T):
        l = input().strip().split(' ')
        
        a = int(l[0])
        n = int(l[1])
        b = int(l[2])
        m = int(l[3])

        ans1, ans2 = chinese_reminder(a,b,n,m)
        print(ans1, ans2)
    


if __name__ == "__main__":
    main()