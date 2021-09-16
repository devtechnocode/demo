#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <string.h> 
int main() {
	int shmid, id; 
	int *s; 
	shmid = shmget(IPC_PRIVATE,sizeof(int), 0777|IPC_CREAT); 
	id = shmget(IPC_PRIVATE,sizeof(int), 0777|IPC_CREAT); 
	int *n; 
	n=(int*)shmat(id,0,0); 
	*n=1; 
	if (fork()==0){
		s=(int*)shmat(shmid,0,0); 
		n=(int*)shmat(id,0,0); 
		int k=0; 
		while(1) {
			while(*n!=2 && *n!=-1); 
			//printf("At process 2\n"); 
			if(*n==-1) break; 
			k+=*s**s; 
			*n=3;
		}
		printf("s: %d\n",k); 
		*s=k; 
		*n=1; 
		shmdt(s); 
		shmdt(n);
	}
	else{
		if (fork()==0) {
			s=(int*) shmat(shmid,0,0); 
			n=(int*)shmat(id,0,0);
			int k=0;
			while(1) {
				while(*n!=3 && *n!=-2); 
				//printf("At process 3\n"); 
				if(*n==-2) break; 
				k+=1; 
				*n=1;
		}
			printf("k: %d\n",k); 
			*s=k; 
			*n=1; 
			shmdt(s); 
			shmdt(n);
	}
		else{
			s=(int*)shmat(shmid,0,0); 
			n=(int*) shmat(id,0,0); 
			printf("From Parent Process, Enter Numbers and enter a special character # at the end: \n"); 
			char a[64]; 
			while(1) {
				while(*n!=1); 
				//printf("At process 1\n"); 
				gets(a); 
				if(!strcmp(a,"#")) {
					printf("Found a special character\n"); 
					*n=-1;
					 break;
			}
				*s=atoi(a); 
				*n=2;
		}
			while(*n!=1); 
			float p=*s; 
			*n=-2; 
			while(*n!=1); 
			p=p/(*s); 
			printf("From Parent Process, Average of squares: %F\n",p); 
			shmdt(s); 
			shmdt(n); 
			wait(NULL); 
			shmctl(shmid, IPC_RMID, 0); 
			shmctl(id, IPC_RMID, 0);
		}
	}
}
