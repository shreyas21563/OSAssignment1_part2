#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
struct arguments{
	int argc;
	char **cmd;
	char *filename;
};
void* func(void *a){
    struct arguments *args = a;
    if(strcmp("ls", args->cmd[0])==0){
		if(args->argc==1){
			system("./ls");
		}
		else if(args->argc==2){
			if(strcmp(args->cmd[1], "-a")==0){
				system("./ls -a");
			}
			else if(strcmp(args->cmd[1], "-A")==0){
				system("./ls -A");
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	else if(strcmp("date", args->cmd[0])==0){
		if(args->argc==1){
			system("./date");
		}
		else if(args->argc==2){
			if(strcmp(args->cmd[1], "-u")==0){
				system("./date -u");
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else if(args->argc==3){
			if(strcmp(args->cmd[1], "-r")==0){
				char a[] = "./date -r ";
				char b[100];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a); 
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	else if(strcmp("cat", args->cmd[0])==0){
		if(args->argc==2){
			char a[] = "./cat ";
			char b[1000];
			for(int i = 0; i<strlen(args->cmd[1]); i++){
				b[i] = args->cmd[1][i];
			}
			strcat(a, args->filename);
			system(a);
		}
		else if(args->argc==3){
			if(strcmp(args->cmd[1], "-n")==0){
				char a[] = "./cat -n ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else if(strcmp(args->cmd[1], "-E")==0){
				char a[] = "./cat -E ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	else if(strcmp("rm", args->cmd[0])==0){
		if(args->argc==2){
			char a[] = "./rm ";
			char b[1000];
			for(int i = 0; i<strlen(args->cmd[1]); i++){
				b[i] = args->cmd[1][i];
			}
			strcat(a, args->filename);
			system(a);
		}
		else if(args->argc==3){
			if(strcmp("-i", args->cmd[1])==0){
				char a[] = "./rm -i ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else if(strcmp("-v", args->cmd[1])==0){
				char a[] = "./rm -v ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	else if(strcmp("mkdir", args->cmd[0])==0){
		if(args->argc==2){
			char a[] = "./mkdir ";
			char b[1000];
			for(int i = 0; i<strlen(args->cmd[1]); i++){
				b[i] = args->cmd[1][i];
			}
			strcat(a, args->filename);
			system(a);
		}
		else if(args->argc==3){
			if(strcmp(args->cmd[1], "-v")==0){
				char a[] = "./mkdir -v ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else if(strcmp(args->cmd[1], "-p")==0){
				char a[] = "./mkdir -p ";
				char b[1000];
				for(int i = 0; i<strlen(args->cmd[2]); i++){
					b[i] = args->cmd[2][i];
				}
				strcat(a, args->filename);
				system(a);
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	else{
		printf("Incorrect Command\n");
	}
}
int main(){
	char directory[1000];
	char str[1000];
	char s[1000];
	char *p_directory = calloc(1000, sizeof(char));
	pthread_t ptid;
	while(1){
		printf("%s >>> ", getcwd(s, sizeof(s)));
		scanf("%[^\n]%*c", directory);
		char *argv[1000];
		char * token = strtok(directory, " ");
		int count = 0;
   		while( token != NULL ) {
      		argv[count] = token;
      		token = strtok(NULL, " ");
			count++;
   		}
		if(strcmp(argv[0],"cd")==0){
			char *temp = calloc(1000, sizeof(char));
			getcwd(temp, 1000);
			bool nothing = true;
			if(count == 2){
				if(chdir(argv[1])!=0){
					nothing = false;
					perror(argv[1]);
				}
			}
			else if(count==3){
				if(strcmp("-m", argv[1])==0){
					if(chdir(argv[2])!=0){
						mkdir(argv[2], 0777);
						chdir(argv[2]);
					}
				}
				else if(strcmp("-v", argv[1])==0){
					if(chdir(argv[2])!=0){
						nothing = false;
						perror(argv[2]);
					}
					else{
						printf("\nDirectory changed to %s\n\n", getcwd(s, sizeof(s)));
					}
				}
				else{
					printf("No such Command Option\n");
				}
			}
			else{
				printf("Incorrect Command\n");
			}
			if(nothing){
				p_directory = temp;
			}
		}
		else if(strcmp(argv[0],"echo")==0){
			if(count==1){
				continue;
			}
			else if(strcmp(argv[1], "-n")==0){
				for(int i = 2; i<count; i++){
					printf("%s ", argv[i]);
				}
			}
			else if(strcmp(argv[1], "-b")==0){
				int *arr = calloc(128, sizeof(int));
				for(int j = 2; j<count; j++){
					for(int i = 0; i<strlen(argv[j]); i++){
						int a = argv[j][i];
						arr[a]++;
					}
				}
				for(int i = 0; i<128; i++){
					if(arr[i]!=0){
						printf("%c -> %d\n", i, arr[i]);
					}
				}
			}
			else{
				for(int i = 1; i<count; i++){
					printf("%s ", argv[i]);
				}
				printf("\n");
			}
		}
		else if(strcmp(argv[0], "pwd")==0){
			if(count==1){
				printf("%s\n", getcwd(s, 1000));
			}
			else if(count==2){
				if(strcmp(argv[1], "-t")==0){
					getcwd(s, sizeof(s));
					int integer = 3;
					printf("|->");
					for(int i = 1; i<strlen(s); i++){
						if(s[i]=='/'){
							printf("\n");
							for(int j = 0; j<integer; j++){
								printf(" ");
							}
							printf("|->");
							integer += 3;
						}
						else{
							printf("%c", s[i]);
						}
					}
					printf("\n");
				}
				else if(strcmp(argv[1], "-s")==0){
					printf("%s\n", p_directory);
				}
				else{
					printf("No such Command Option\n");
				}
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else if(strcmp(argv[0], "exit")==0){
			break;
		}
		else{
			struct arguments *args = malloc(sizeof(struct arguments));
			args->cmd = malloc(sizeof(sizeof(char)*100)*100);
			args->argc = count;
			if(count==3 && strcmp("date", argv[0])==0){
				args->filename = argv[2];
			}
			else if(strcmp("cat", argv[0])==0 || strcmp("rm", argv[0])==0 || strcmp("mkdir", argv[0])==0){
				if(count==2){
					args->filename = argv[1];
				}
				else if(count==3){
					args->filename = argv[2];
				}
			}
			for(int i = 0; i<count; i++){
				args->cmd[i] = argv[i];
			}
			pthread_create(&ptid, NULL, &func, args);
			pthread_join(ptid, NULL);
		}
	}
	return 0;
}
