#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>
//#include<sys/time.h>

#define DATABASE_NAME "./database.sqlite3"

int uid_global;
char access_global[100];
//struct timeval begin_tv;
//struct timeval end_tv;

int PrintAccess( void *, int, char **, char ** );

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
int ReqAccess( int did , int *uid, char *access )
{

	//gettimeofday(&begin_tv, NULL);

	printf("===========ReqAccess begin==========\n");

	char sql_req[100];

	memset( sql_req, 0x00, sizeof( sql_req ) );

	sprintf( sql_req, "select * from did_uid_access where did = %d", did );
	printf("%s\n", sql_req);

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
		PrintAccess,	//コールバック関数
		NULL,		//CB関数に渡す引数
		&err_msg	//エラーメッセージ
	);

	if( SQLITE_OK != ret ){
		sqlite3_close( conn );
		sqlite3_free( err_msg );
		exit( -1 );
	}else{
		*uid = uid_global;
		strcpy( access, access_global );
	}

	//後処理
	ret = sqlite3_close( conn );
	if( SQLITE_OK != ret ){
		exit( -1 );
	}

	//sleep(1);
	//gettimeofday(&end_tv, NULL);
	//printf("diff: %ld\n", end_tv.tv_usec - begin_tv.tv_usec);

	printf("============ReqAccess end===========\n");

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
int PrintAccess( void *get_prm, int col_cnt, char ** row_txt, char **col_name )
{
	//printf( "%s : %s\n", row_txt[0], row_txt[1] );
	printf( "%s %s\n", row_txt[1], row_txt[2] );

	uid_global = atoi(row_txt[1]);
	strcpy( access_global, row_txt[2] );

	return 0;
}
