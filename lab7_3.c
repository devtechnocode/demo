#include <stdio.h>
#include <sys/ipc.h>

#include <string.h> 
int main() {
	int shmid, id; 
	char *s; 
	shmid = shmget(IPC_PRIVATE, 256*sizeof(char), 0777|IPC_CREAT); 
	id = shmget(IPC_PRIVATE,sizeof(int), 0777| IPC_CREAT); 
	int *n; 
	n=(int*)shmat(id,0,0); 
	*n=2; 
	if (fork()==0) {
		s=shmat(shmid,0,0); 
		printf("Reading from Child Process-1: "); 
		n=(int*)shmat(id,0,0); 
		gets(s); 
		*n=1; 
		shmdt(s);
		shmdt(n);
	} 
	else
	{
		 if (fork()==0){
			s=shmat(shmid,0,0); 
			printf("Reading from Child Process-2: "); 
			n=(int*)shmat(id,0,0); 
			while(*n!=3); 
			gets(s); 
			*n=1; 
			shmdt(s); 
			shmdt(n);
	}
		else{
			s=shmat(shmid,0,0); 
			char a[512]; 
			n=(int*)shmat(id,0,0); 
			while(*n!=1); 
			strcpy(a,s); 
			*n=3; 
			while(*n!=1); 
			strcat(a," "); 
			strcat(a,s); 
			printf("Printing from Parent Process: %s\n", a); 				shmdt(s); 				
			shmdt(n); 
			wait(NULL); 
			shmctl(shmid, IPC_RMID, 0); 
			shmctl(id, IPC_RMID, 0);
		}
	}
}


