#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main( void ) {
	MYSQL *mysql = NULL;
	mysql = mysql_init(NULL);
	if ( mysql == NULL ) {
		printf("init:%s\n", mysql_error(mysql));
		exit(EXIT_SUCCESS);
	}

	if ( !mysql_real_connect(mysql, "localhost", \
			"root", "m123", "uplook", 0, NULL, 0) ) {
		printf("connect:%s\n", mysql_error(mysql));
		exit(EXIT_SUCCESS);
	}

	//printf("connect success!\n");
	int ret;
	ret=mysql_query(mysql, "delete from stu_info where stid=2;");
	if ( ret != 0 ) {
		printf("query:%s\n", mysql_error(mysql));
		exit(EXIT_SUCCESS);
	}
	//printf("%d行受影响!\n", mysql_affected_rows(mysql));
	
	ret=mysql_query(mysql, "select * from class;");
	if ( ret != 0 ) {
		printf("query:%s\n", mysql_error(mysql));
		exit(EXIT_SUCCESS);
	}
	
	int i;
	MYSQL_ROW mysql_row;
	MYSQL_RES * mysql_res;
	MYSQL_FIELD *mysql_field;
	mysql_res = mysql_store_result(mysql);
	int cols = mysql_num_fields(mysql_res);
	if ( mysql_res ) {
		while ( mysql_field = mysql_fetch_field(mysql_res) ) {
			printf("%s\t", mysql_field->name);
		}
		
		printf("\n");
	
		while ( mysql_row=mysql_fetch_row(mysql_res) ) {
			for (i=0; i<cols; i++) {
				printf("%s\t", mysql_row[i]);
			}
			printf("\n");
		}
	}
	mysql_free_result(mysql_res);
	
	mysql_close(mysql);
	return 0;
}

