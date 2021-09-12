#include <stdio.h>
#include <ctype.h>

// This function takes two array and one int variable as parameters
// to find the failed students who needs to take greater than 100 in final

void findFailed(int id[], int fin[], int size){
	int i;
	
	for(i=0; i<size; i++){
		if(fin[i] > 100){
			printf("ID: %d is failed from the course\n",id[i]);
		}
	}
}

// This function finds the number of integers in a file

int findSize(FILE *fptr){
	
	int status, counter = 0;
	
	// Temporary variable to read the numbers
	int sID;
	
	if(fptr == NULL){
		printf("Can not open .txt file\n");
	}
	else{
		status = fscanf (fptr, "%d", &sID);
		
		// Check if it was the end of the file
		while (status!=EOF)
		{
			counter++;
			status = fscanf (fptr, "%d", &sID);
		} 
	}
	
	fclose(fptr);
	
	// Returns how many numbers file has
	return counter;
}

// This function takes a file pointer, an array pointer and an integer size variable
// To read file and save the values in arr

void readFromFile(FILE *fptr, int *arr, int size){

	int data, status, counter = 0;
	
	if (fptr == NULL)
		printf ("Cannot open .txt for input!\n");
	else
	{ 	
		status = fscanf (fptr, "%d", &data);
		
		while (status != EOF)
		{
			arr[counter++] = data;
			status = fscanf (fptr, "%d", &data);
		}
		
		fclose (fptr);
	}
}

// This function takes two arrays and one integer as parameters
// Displays the arrays for a given size

void display(int id[], int arr[], int size){
	int i;
	for(i=0;i<size;i++){
		printf(" %d\t\t%d\n",id[i],arr[i]);
	}
}

// This method displays the menu

void menu(){
	printf("----------------------------------------------------------------\n");
	printf("----- Pass Grade : 70 ------ Midterm %%40 ------ Final %%60 ------\n");
	printf("--------------------------------MENU----------------------------\n");
	printf("1. Read ID and Midterm Informations of Students From Files\n");
	printf("2. Display the Grades\n");
	printf("3. Calculate the Average of Midterms\n");
	printf("4. Calculate the Final grade of each student to pass this course\n");
	printf("5. List the Failed Students (Final Grade is bigger than 100)\n");
	printf("6. Write Calculated Final Grade to Final.txt\n");
	printf("7. Exit\n");
	printf("----------------------------------------------------------------\n");
}

// This method is taking one array and one integer as the size of arr
// Finds the average of the array items

double average(int arr[], int size){
	double total = 0;
	int i;
	for(i=0;i<size;i++){
		total += arr[i];
	}
	total = total / size;
	return total;
}

// This method takes one array, one array pointer (to save results) and one integer value as the size of arrays
// Calculates the expected final grades of students to pass this course

void calculateFinalGrade(int mid[], int *final, int size){
	int i;
	for(i=0;i<size;i++){
		int res = (70-mid[i]*0.4)*10/6;
		final[i] = res;
	}
}

// This method takes one file pointer, one array and one integer as parameters
// Writes the items of array in a given size to the File
 
void writeToFile(FILE *fptr, int final[], int size){
	int i;
	for(i=0;i<size;i++){
		fprintf(fptr, "%d\n",final[i]);
	}
	fclose(fptr);
}

// Main function -> Program Starts Running from this function

int main(void){
	
	FILE *studentID = fopen("studentID.txt", "r");
	FILE *midterm, *finalFile;
	
	if(studentID == NULL){
		printf("The file was not found\n");
		return 0;
	}
	int size = findSize(studentID);

	int idArr[size], midtermArr[size], finalArr[size];
	double avg;
	int choice;
	
	menu();
	scanf("%d",&choice);
	
	while(choice!=7){
		switch(choice){
			case 1:
				// We need to reopen the studentID.txt since we read the file before in the findSize function
				studentID = fopen("studentID.txt", "r");
				readFromFile(studentID, idArr, size);
				midterm = fopen("midterm.txt", "r");
				readFromFile(midterm, midtermArr, size);
				break;
			case 2:
				printf("--ID---------Midterm----\n");
				display(idArr,midtermArr, size);
				break;
			case 3:
				avg = average(midtermArr, size);
				printf("--------------------------\n");
				printf("Average of Midterms: %.2lf\n",avg);
				break;
			case 4:
				calculateFinalGrade(midtermArr, finalArr, size);
				printf("-Midterm------Final--\n");
				display(midtermArr,finalArr, size);
				break;
			case 5:
				findFailed(idArr,finalArr,size);
				break;
			case 6:
				finalFile = fopen("final.txt","w");
				writeToFile(finalFile, finalArr, size);
				break;
		}	
		menu();
		scanf("%d",&choice);
		
	}
	fclose(midterm);
	fclose(studentID);
	fclose(finalFile);	
	
	return(0);
}
