#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/time.h>

#define VNCPW_LEN 8

struct timeval tv;

int main( void )
{
	int i;
	char rand_num;

	char onetime_passwd[10];


	while(1){
	memset( onetime_passwd, 0, sizeof( onetime_passwd ) );
	printf("================\n");
	gettimeofday(&tv, NULL);
	srand( tv.tv_sec + tv.tv_usec );

	for( i = 0; i < VNCPW_LEN; i++ ){
		rand_num = rand() % 66;

		if( 0 <= rand_num && rand_num < 4 ){			// ( # | $ | % | & )
			rand_num -= 0;
			onetime_passwd[i] = 35 + rand_num;
		}else if( 4 <= rand_num  && rand_num < 14 ){	// [ 0 - 9 ]
			rand_num -= 4;
			onetime_passwd[i] = 48 + rand_num;
		}else if( 14 <= rand_num && rand_num < 40 ){	// [ A - Z ]
			rand_num -= 14;
			onetime_passwd[i] = 65 + rand_num;
		}else if( 40 <= rand_num && rand_num < 66 ){	// [ a - z ]
			rand_num -= 40;
			onetime_passwd[i] = 97 + rand_num;
		}else{
		}
	}

	onetime_passwd[i] = '\0';

	printf("Password: %s\n", onetime_passwd);

	}
	return 0;
}
