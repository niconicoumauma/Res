#include "includes.h"


void debug(void *in_addr, int len)
{
	int i;
	unsigned char *in_str = ( unsigned char * )in_addr;

	printf("===== debug begin =====\n");
	printf("ADDR : %p\n", in_str);
	printf( "LEN : %d[bit]\n", len * 8 );
	printf( "   7  15  23  31  39  47  55  63\n" );
	printf( "|--------------------------------|\n" );
	for(i = 1; i < len + 1; i++){
		printf("  %02x", ( unsigned char )*in_str);
		in_str++;
		if(i % 8 == 0) printf("\n");
	}
	printf("\n");

	printf("====== debug end ======\n");

}
