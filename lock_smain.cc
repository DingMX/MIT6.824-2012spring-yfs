#include "rpc.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lock_server.h"

#include "jsl_log.h"

// Main loop of lock_server

int
main(int argc, char *argv[])
{
  int count = 0;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  srandom(getpid());

  if(argc != 2){
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    exit(1);
  }

  char *count_env = getenv("RPC_COUNT");
  if(count_env != NULL){
    count = atoi(count_env);
  }

  //jsl_set_debug(2);

#ifndef RSM
  lock_server ls;
  rpcs server(atoi(argv[1]), count);
  server.reg(lock_protocol::stat, &ls, &lock_server::stat);
  /* lab #1 */
  /* server handles client's acquire/release by grant/release */
  server.reg(lock_protocol::acquire, &ls, &lock_server::grant);
  server.reg(lock_protocol::release, &ls, &lock_server::release);
  /* lab #1 */
#endif


  while(1)
    sleep(1000);
}
