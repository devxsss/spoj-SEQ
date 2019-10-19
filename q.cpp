#include <iostream>
#include <vector>


using matrix = std::vector< std::vector<long long> >;
constexpr long long mod = 1000000000;   // 1,000,000,000


int fib( int N, const std::vector<long long>& b1, std::vector<long long> c1, int k );
matrix mul( const matrix& lhs, const matrix& rhs, int k );
matrix poww( const matrix& base, int e, int k );


int main()
{
    int cas;
    std::cin >> cas;

    for ( int i { 1 }, k; i <= cas; ++i) {
        std::cin >> k;
        std::vector<long long> b1 ( k + 1 );
        std::vector<long long> c2 ( k + 1 );

        for ( int j { 1 }, b; j <= k; ++j ) {
            std::cin >> b;
            b1[j] = b;
            
        }
        for(int i = 1;i<=k;++i) b1[i] %= mod;
        for( int o { 1 }, c; o <= k; ++o ) {
            std::cin >> c;
            c2[o] = c;
        }

        int n;
        std::cin >> n;
        int y=fib( n, b1, c2, k );
        if(y>=0)
         std::cout << y << '\n';
    }
}


matrix mul( const matrix& lhs, const matrix& rhs, int k )
{
    matrix result( k + 1, std::vector<long long>(k + 1) );
    for ( int i { 1 }; i <= k; ++i ) {
        for ( int j { 1 }; j <= k; ++j ) {
            for ( int m { 1 }; m <= k; ++m ) {
                result[i][j] = ( result[i][j] + ( lhs[i][m] * rhs[m][j] ) ) % mod;
            }
        }
    }
    return result;
}


matrix poww( const matrix& base, int e, int k )
{
    if ( e == 1 ) {
        return base;
    }

    if ( e % 2 ) {
        return mul( base,
                    poww( base, e - 1, k ),
                    k );
    }

    matrix result = poww( base, e/2, k ); 
    return mul( result, result, k );
}


int fib( int N, const std::vector<long long>& b1, std::vector<long long> c1, int k )
{
    std::vector<long long> result ( k + 1 );

    for (int i { 1 }; i <= k; ++i) {
        result[i] = b1[i];
    }

    matrix tmp( k + 1, std::vector<long long>( k + 1 ) );

    for ( int y { 1 }; y <= k; ++y ) {
        for ( int u { 1 }; u <= k; ++u ) {
            if ( y + 1 == u ) {
                tmp[y][u] = 1;
            }
        }
    }

    for ( int i { 1 }; i <= k; ++i ) {
        long long y { c1.back() };
        c1.pop_back();
        tmp[k][i] = y;
    }

    if ( N <= k ) {
        std::cout << b1[N] << '\n';
        return -2;
    }

    tmp = poww ( tmp, N - 1, k );

    long long res {};
    for ( int i { 1 }; i <=k ; ++i ) {
        res = ( res + tmp[1][i] * result[i] ) % mod;
    }
    return res;
   

}