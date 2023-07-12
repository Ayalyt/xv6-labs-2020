#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int RecurProcess(int* oldTunnel){
	close(oldTunnel[1]);
	int Tunnel[2];
	int prime;
	int tmp;
	if(read(oldTunnel[0], &prime, 4) > 0){
		printf("prime %d\n",prime);
		pipe(Tunnel);
		while(read(oldTunnel[0],&tmp,4) > 0){
			if(tmp % prime != 0){
				write(Tunnel[1],&tmp,4);
			}
		}
		if(fork()==0){
			RecurProcess(Tunnel);
			close(Tunnel[0]);
		}
		close(oldTunnel[0]);
		close(Tunnel[1]);
		wait((int*)0);
	}
	else{
		close(oldTunnel[0]);
	}
	exit(0);
}

int main(){
	int fd[2];
	pipe(fd);
	for(int i = 2; i < 36; i++){
		write(fd[1], &i, 4);
	}
	if(fork()==0){
		RecurProcess(fd);
	}
	else{
		close(fd[1]);
		wait((int*)0);
	}
	exit(0);
}
