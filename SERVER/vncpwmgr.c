#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>
#include<sys/time.h>

#define VNCPW_LEN 8

#define DATABASE_NAME "./database.sqlite3"
#define CHANGE_PW_SCRIPT_NAME "./ChangeVncPasswd.sh"

char username_global[100];
char vncpasswd_global[10];
struct timeval tv;


int print_resp( void *, int, char **, char ** );

/**
 * @brief 概要説明
 *
 * UIDからユーザネームを検索し
 *
 * @param[in]	uid	ユーザID
 *
 * @retval		0	変更成功
 * @retval		1	変更失敗
 *
 */
int ChangePasswd( int uid , char *username, char *vncpasswd )
{

	
	printf("===========ChangePw begin===========\n");


	char sql_req[100];// = {"select * from username_uid where uid = 1000"};

	memset( username_global, 0x00, sizeof( username_global ) );
	memset( vncpasswd_global, 0x00, sizeof( vncpasswd_global ) );
	memset( sql_req, 0x00, sizeof( sql_req ) );

	sprintf( sql_req, "select * from username_uid where uid = %d", uid );
	//printf("%s\n", sql_req);

	int ret = 0;
	sqlite3 *conn = NULL;
	char *err_msg = NULL;
	char sql_str[255];
	memset( &sql_str[0], 0x00, sizeof( sql_str ) );

	//アクセス
	ret = sqlite3_open( DATABASE_NAME, &conn );
	//アクセスできなかった場合
	if( SQLITE_OK != ret ){
		exit( -1 );
	}

	//SQL文発効
	snprintf( sql_str, sizeof( sql_str ) - 1, sql_req );
	ret = sqlite3_exec(
		conn,		//DBコネクション
		sql_str,	//SQL文
		print_resp,	//コールバック関数
		NULL,		//CB関数に渡す引数
		&err_msg	//エラーメッセージ
	);

	if( SQLITE_OK != ret ){
		sqlite3_close( conn );
		sqlite3_free( err_msg );
		exit( -1 );
	}else{
		strcpy( username, username_global );
		strcpy( vncpasswd, vncpasswd_global );
	}

	//後処理
	ret = sqlite3_close( conn );
	if( SQLITE_OK != ret ){
		exit( -1 );
	}
	printf("============ChangePw end============\n");
	return 0;
}

/**
 * @brief 概要説明
 *
 * SQL文に対する応答
 *
 * @param[out]	get_prm		sqlite3_exec()の第4引数
 * @param[in]	col_cnt		行数
 * @param[out]	row_txt		行内容
 * @param[out]	col_name	列名
 * @retval		0			常にゼロ
 */
int print_resp( void *get_prm, int col_cnt, char ** row_txt, char **col_name )
{
	//printf( "%s : %s\n", row_txt[0], row_txt[1] );
	//printf( "%s\n", row_txt[1] );
	//strcpy( username_global, row_txt[1] );

	int i;
	char vncpw_change_command[256];
	char rand_num = 0;
	char onetime_passwd[10];

	memset( vncpw_change_command, 0x00, sizeof( vncpw_change_command ) );


	// パスワード生成初期化
	memset( onetime_passwd, 0x00, sizeof( onetime_passwd ) );
	gettimeofday(&tv, NULL);
	srand( tv.tv_sec + tv.tv_usec );

	// パスワード生成(8文字:VNCパスワードの制約) 
	for( i = 0; i < VNCPW_LEN; i++ ){
		rand_num = rand() % 66;
		if( 0 <= rand_num && rand_num < 4 ){			// ( # | $ | % | & )
			rand_num -= 0;	
			onetime_passwd[i] = 35 + rand_num;
			if( rand_num == 3 ){
				onetime_passwd[i] -= 5;
			}else if( rand_num == 1 ){
				onetime_passwd[i] += 28;
			}
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
			printf("(vncpwmgr.c):print_resp(): Failed to generate VNCpassword.");
		}
	}
	// 終端文字処理
	onetime_passwd[i] = '\0';

	// パスワード変更処理
	sprintf( vncpw_change_command, "%s %s %s", CHANGE_PW_SCRIPT_NAME, row_txt[1], onetime_passwd );
	//printf(">>>>: %s\n", vncpw_change_command);
	printf("<VNC-Password change phase begin>\n");
	system(vncpw_change_command);
	printf("<VNC-Password change phase end>\n");
	//printf("Password: %s\n", onetime_passwd);

	// グローバル変数へ格納
	strcpy( username_global, row_txt[1] );
	strcpy( vncpasswd_global, onetime_passwd );

	return 0;
}
