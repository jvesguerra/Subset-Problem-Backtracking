#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

int main(){
	int start, move;
	//int i, candidate;

	FILE *fp;
	int numIn;
	int numOfTest;
	int i, j, k;

	int* candidate = (int*)malloc(10*sizeof(int));
	int cnt = 0;
	int candidate_size;

	fp = fopen("input.txt","rw");
	
	fscanf(fp,"%d",&numIn);
	numOfTest = numIn;
	printf("Number of Tests: %d\n",numOfTest);

	// saves data to an array
	while((fscanf(fp,"%d",&numIn)) == 1){
		candidate[cnt] = numIn;
		cnt++;
	}

	candidate_size = cnt;

	printf("Candidate Size: %d \n", candidate_size);

	for(i = 0; i < candidate_size; i++){
		printf("%d ", candidate[i]);
	}
	printf("\n");

	int nopts[candidate_size+2]; //array of top of stacks
	int option[candidate_size+2][candidate_size+2]; //array of stacks of options
	move = start = 0; 
	nopts[start]= 1;

	while (nopts[start] >0) //while dummy stack is not empty
	{
		if(nopts[move]>0) 
		{
			move++;
			nopts[move]=0; //initialize new move

			if(move == 1){	// initail fill the candidates
				for(j = candidate_size; j >= 1; j--){
					nopts[move]++;
					option[move][nopts[move]] = candidate[j-1];
					//printf("nopts[move] %i candidate %i\n", nopts[move], candidate[j-1]);           
				}
			}
			else{
				for(j = candidate_size; j >= 1; j--){
					//printf("%d ", candidate[j]);
					for(i=move-1;i>=1;i--)	// check for duplicates
						if(candidate[j-1]==option[i][nopts[i]]) break;

					if((!(i>=1))){ // no duplicates found
						option[move][++nopts[move]] = candidate[j-1];
						//printf("nopts[move] %i candidate %i\n", nopts[move], candidate[j]);
					}else{
						int set1_sum = 0;
						int set2_sum = 0;
						int *arr, *arr2;
						int counter = 0;
						int counter2 = 0;
						arr = (int*)calloc(candidate_size, sizeof(int));
						arr2 = (int*)calloc(candidate_size, sizeof(int));
						int checker;
						int flag;

						// FIND THE COMBINATIONS
						for(i=1;i<move;i++){
							set1_sum += option[i][nopts[i]];

							arr[counter] = option[i][nopts[i]];
							counter++;
						}
										

						// FIND THE OTHER HALF OF 1ST ARR
						for(int y = 0; y < candidate_size; y ++){
							flag = 0;
							for(int x =0; x < counter; x++){
								if(candidate[y] == arr[x]){
									flag = 1;
									break;
								}
							} 
							if (flag == 0) {
								set2_sum += candidate[y];

								arr2[counter2] = candidate[y];
								counter2++;
								}
						}
						
						// IF EQUAL PRINT BOTH SUBSETS
						if(set2_sum == set1_sum){
							if(nopts[1] == candidate_size){
								printf("{");
								for(int pt1 = 0; pt1 < counter; pt1++)
									printf("%2i", arr[pt1]);
								printf(" } {");
								for(int pt2 = 0; pt2 < counter2; pt2++)
									printf("%2i", arr2[pt2]);
								printf(" }");

								printf("\n");
							}
						}
						
						break;
					}							
				}
			}
		}
		else 
		{
				move--;
				nopts[move]--;

		}
	}
}