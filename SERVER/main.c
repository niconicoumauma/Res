#include "includes.h"

int ReqAccess( int, int *, char * );
int ChangePasswd( int, char *, char * );
void debug( void *, int );


int main( int argc,char *argv[] )
{

	char username[100];
	char password[100];
	int did = 1;
	int uid;
	char access[100];

	did = atoi(argv[1]);

	printf("\n=======================MAIN begin========================\n");
	printf("(main.c) DisplayID : %d\n", did);
	// 変数初期化
	memset( username, 0x00, sizeof( username ) );
	memset( password, 0x00, sizeof( password ) );
	memset( access, 0x00, sizeof( access ) );


	//printf("This is MAIN.C.\n");

	ReqAccess(did, &uid, access);
	printf("(main.c) Uid    : %d\n", uid);
	printf("(main.c) Access : %s\n", access);

	ChangePasswd(uid, username, password);
	printf("(main.c) Username : %s\n", username);
	printf("(main.c) Password : %s\n", password);

	printf("=======================MAIN end========================\n");
	return 0;

}
