#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
// Function to compare two arrays of not same length and find their different elements
void compare_arrays(int *array1, int *array2, int size1, int size2) {
  int i, j;

  // Iterate over the arrays and compare the elements
  for (i = 0; i < size1; i++) {
    if (i >= size2) {
      printf("The different element at index %d is: %d\n", i, array1[i]);
    } else if (array1[i] != array2[i]) {
      printf("The different element at index %d is: %d\n", i, array1[i]);
    }
  }

  for (j = size1; j < size2; j++) {
    printf("The different element at index %d is: %d\n", j, array2[j]);
  }
}

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
					//printf("nopts[move] %i candidate %i\n", nopts[move], candidate[j]);           
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
						int *arr;
						int counter = 0;
						arr = (int*)calloc(candidate_size, sizeof(int));
						int checker;

						for(i=1;i<move;i++){
							//printf("%d ",option[i][nopts[i]]);
							//printf("\n");
							set1_sum += option[i][nopts[i]];

							arr[counter] = option[i][nopts[i]];
							counter++;
						}
						// for(int k=0;k<counter;k++)
						// 	printf("%2i",arr[k]);
						printf("\n");						
						//printf("\n%d\n",set1_sum);

						printf("Remaining numbers: ");
						for(int y = 0; y < candidate_size; y ++){
							for(int x =0; x < counter; x++){
								if(candidate[y] != arr[x]){
									printf("%d ",candidate[y]);
								}
							} 
						}

						
						// printf("\n");
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