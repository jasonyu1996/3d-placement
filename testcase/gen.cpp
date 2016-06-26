#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<fstream>
#include<map>
#define rd(nn, ii) (rand()%(nn)+(ii))
using namespace std ;
typedef long long LL ;
typedef long double ld  ;

int N, M, ks ;
map< pair<LL, LL>, int> MP ;

int main()
{
	int i, j ;
	N = 40 ;
	srand(time(0)) ;
	ofstream os("Input.txt") ;
	for(i = 1; i <= N; i ++)
	{
		os << rd(500, 1) << " " << rd(500, 1) << " " << rd(500, 1) << endl ;
	}
	return 0 ;
}
