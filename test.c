#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "riakdrv.h"

int main() {
	RIAK_CONN * conn;
	char ** buckets;
	int res, n_buckets, i;

	printf("Connecting... ");
	conn = riak_init("127.0.0.1", 8087, 0, NULL);
	if(conn == NULL) {
		printf("connection failed!\n");
		return 1;
	}
	printf("OK\n");

	res = riak_ping(conn);
	printf("Ping: %s\n",  res == 0 ? "OK" : "ERROR");
	if(res != 0) {
		printf("Error code: %d\n", res);
		return 1;
	}

	buckets = riak_list_buckets(conn, &n_buckets);
	for(i=0; i<n_buckets; i++)
		printf("bucket: %s\n", buckets[i]);

	printf("Closing connection... ");
	riak_close(conn);
	printf("OK\n");

	return 0;
}
