#include <stdio.h>
#include <sys/shm.h> 
#include <string.h> 
int main() {
	int shmid; 
	char *s; 
	shmid = shmget(IPC_PRIVATE, 256*sizeof(char), 0777|IPC_CREAT); 
	if (fork()==0){
		s=shmat(shmid,0,0); 
		sleep(10); 
		printf("Printing from Child Process: "); 
		for(int i=0;i<strlen(s);i++){
			if(s[i]>=97 && s[i]<=122){
				s[i]-=32;
			}
		}
			printf("%s\n",s); 
			shmdt(s); 
			shmctl(shmid, IPC_RMID, 0);
}
	else{
		s=shmat(shmid,0,0); 
		printf("Reading Input from parent: "); 
		gets(s); 
		shmdt(s); 
		wait(NULL);
	}
}
