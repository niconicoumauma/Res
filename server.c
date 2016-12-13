#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>	// sockaddr_in6

#define P_LEN 65536		// UDP以下のペイロード長

void debug(void *in_addr, int len)
{
	int i;
	unsigned char *in_str = ( unsigned char * )in_addr;

	printf("===== debug begin =====\n");
	printf("ADDR : %p\n", in_str);
	// printf("ADDR : %p\n", in_addr);
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

int main (void)
{
	// 変数
	int snd_status;
	int soc_snd;	// 送信用
	int soc_rcv;	// 受信用
	struct sockaddr_in6 addr;
	unsigned char t_payload[P_LEN];
	unsigned char *dst_addr = "2001:2f8:1c2:125:f4e4:727a:ecd4:670d";

	// 変数初期化
	memset( t_payload, 0x00, sizeof( t_payload ) );

	// ----------
	if( ( soc_snd = socket( AF_INET6, SOCK_DGRAM, 0 ) ) < 0 ){
		perror( "socket" );
		return -1;
	}

	// ---------
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(60001);
	addr.sin6_addr = in6addr_any;
	inet_pton(AF_INET6, dst_addr, addr.sin6_addr.s6_addr);

	// bind
	//if( bind( soc_snd, ( struct sockaddr * )&addr, sizeof( addr ) ) == -1 ){
	//	perror( "bind" );
	//}

	if( snd_status = sendto( soc_snd, NULL, 0, 0, ( struct sockaddr * )&addr, sizeof( addr ) ) < 0 ){
		perror("sendto");
		exit( 1 );
	}

	printf( "sent status: %d\n", snd_status );

	close(soc_snd);

	debug( &addr, sizeof( addr ) );

	return 0;

}
