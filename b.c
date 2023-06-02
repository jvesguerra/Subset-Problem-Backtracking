#include <stdio.h>
#include <stdlib.h>
#define N 3

int main(){
	int start, move;
    int firstn, solnCounter; // ADDED but idk the initial value
	//int i, candidate;

	FILE *fp;
	int numIn;
	int numOfTest;
	int i, j;

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

			// ==== ADDED =====
            if (move==N+1) {} // do nothing
            // ================
            else if(move == 1){	// initital fill the candidates
				for(j = candidate_size; j >= 1; j--){
					nopts[move]++;
					option[move][nopts[move]] = candidate[j-1];
					//printf("nopts[move] %i candidate %i\n", nopts[move], candidate[j]);           
				}
                // ==== ADDED =====
                printf("S = ");
                for(j=0; j<candidate_size; j++) // print array
                    print("%d ", candidate[j]);
                printf("\n\nPartitionings:\n");
                // ===============
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
                        // === ADDED =====
                        if (firstn == option[1][nopts[1]]) { // idk what must be the initial value of firstn
                            int temp[candidate_size];   // set a temporary array
                            memcpy(temp, candidate, sizeof(candidate));

                            int n = sizeof(temp) / sizeof(temp[0]); // set a temporary array size

                            int *arr1, *arr2;
                            arr1 = (int*)calloc(candidate_size, sizeof(int));
                            arr2 = (int*)calloc(candidate_size, sizeof(int));

                            for (i=1; i<move; i++) { // left size
                                arr1[(i-1)] = option[i][nopts[i]];
                                n = delete_element_by_value(temp, option[i][nopts[i]], n); // not sure the right implementation of this function
                            }

                            for (int i=0; i<n; i++) { // right side
                                arr2[i] = temp[i];
                            }

                            if(is_equal_sum(arr1, arr2, N) == 1) { // if true
                                printf("\t");
                                for(j=0; j<candidate_size; j++) // print array
                                    print("%d ", arr1[j]);
                                for(j=0; j<candidate_size; j++) // print array
                                    print("%d ", arr2[j]);
                                printf("\n");
                                solnCounter++; 
                            }
                        }
                        // ==============
						for(i=1;i<move;i++)
							printf("%3i",option[i][nopts[i]]);
							printf("\n");
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