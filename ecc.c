#include <stdio.h>

typedef struct{
    long long x, y;
} Ponto;

long long mod(long long a, long long p);
long long mod_pow(long long base, long long exp, long long p);
long long mod_inv(long long a, long long p);
Ponto soma_pontos(Ponto Q, Ponto G, long long a, long long p);
Ponto multiplicacao_escalar(long long n, Ponto G, long long a, long long p);

int main(){
    Ponto G, R;
    long long esc_n, par_a, prm_p;

    while(1){
        scanf("%lld", &esc_n);

        if(!esc_n) break;

        scanf("%lld %lld %lld %lld", &par_a, &prm_p, &(G.x), &(G.y));

        R = multiplicacao_escalar(esc_n, G, par_a, prm_p);
        printf("%lld %lld\n", R.x, R.y);
    }

    return 0;
}

long long mod(long long a, long long p){
    long long r = a % p;
    return r < 0 ? r + p : r;
}

long long mod_pow(long long base, long long exp, long long p){
    long long res = 1;

    base = mod(base, p);

    while (exp > 0) {
        if (exp % 2) res = mod(res * base, p);
        
        base = mod(base * base, p);
        exp /= 2;
    }

    return res;
}

long long mod_inv(long long a, long long p){
    return mod_pow(a, p - 2, p);
}

Ponto soma_pontos(Ponto Q, Ponto G, long long a, long long p){
    if (G.x == 0 && G.y == 0) return Q;
    if (Q.x == 0 && Q.y == 0) return G;

    if (Q.x == G.x && mod(Q.y + G.y, p) == 0) {
        Ponto O = {0, 0};
        return O;
    }

    long long lambda;

    if (Q.x != G.x || Q.y != G.y) {
        long long num = mod(G.y - Q.y, p);
        long long den = mod(G.x - Q.x, p);
        long long inv_den = mod_inv(den, p);

        lambda = mod(num * inv_den, p);
    } else {
        if (Q.y == 0) {
            Ponto O = {0, 0};
            return O;
        }

        long long num = mod(3 * mod(Q.x * Q.x, p) + a, p);
        long long den = mod(2 * Q.y, p);
        long long inv_den = mod_inv(den, p);
        lambda = mod(num * inv_den, p);
    }

    long long xr = mod(mod(lambda * lambda, p) - Q.x - G.x, p);
    long long yr = mod(mod(lambda * mod(Q.x - xr, p), p) - Q.y, p);

    Ponto R = {xr, yr};
    return R;
}

Ponto multiplicacao_escalar(long long n, Ponto G, long long a, long long p){
    Ponto R = {0, 0};
    Ponto temp = G;

    while (n > 0) {
        if (n & 1) R = soma_pontos(R, temp, a, p);

        temp = soma_pontos(temp, temp, a, p);
        n >>= 1;
    }

    return R;
}