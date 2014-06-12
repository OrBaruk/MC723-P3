#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <ctime>

using namespace std;

int main(){	
	freopen("calc_area.in","w",stdout);
	srand(time(NULL));
	int n = rand()%1010 + 1010;
	printf("%d\n",8*n);
	for(int j = 0 ; j < 8*n ; j++){
		printf("%d %d\n",rand()%100,-(rand()%100));
	}
	
	return 0;
}

