#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

// Set up the size of the arrays
#define size_n_H 5
#define size_Z 5


void print_string(char *string){
	// Get the string size
	int size = strlen(string);

	// Print the string 
	for (int i = 0; i < size; i++)
	{
		printf("%c", string[i]);
	}
	printf("\n");
}

void create_in_file(char *file_name, double n_H){
	
	// Define a file pointer
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL){
		perror("Error openning file!\n");
		exit(1);
	}

    fprintf(fp, "title PDR / Molecular cloud with an open geometry\n");
    fprintf(fp, "table ISM factor %s\n", "0.01"); // TODO: ISRF -- This needs to be changed
    fprintf(fp, "radius 30\n");
    fprintf(fp, "hden %.2f\n", n_H);

	// Close the file
	fclose(fp);

	// Print succesful message
	printf("File %s created!\n", file_name);            	

}

void delete_file_and_its_contents(char *directory_name){

	char cmd[1000] = { 0 }; 					// create a character array that is going to store the command line argument
	sprintf(cmd, "rm -rf %s", directory_name); 	// rm -rf directory_name

	int check =  system(cmd);
	if (check){
		printf("Unable to delete the file!\n");
		perror("Exiting the code with an error 2\n");
		exit(2);
	}
}


int main(){
	// Initialize the arrays. These arrays hold the values for hydrogen number density: n_H, metallicity: Z, UV ISRF: G, turbulence: v, cosmic rays: CR. Directories and cloudy input files will be created 
	// according to the values stored in these arrays.  
	double n_H[size_n_H] = {-1, -0.5, 0.0, 0.5, 1.0};
	double Z[size_Z] = {-1, -0.5, 0.0, 0.5, 1.0}; 

	char directory_name[500];
	char file_name[1000]; 


	// Create directories and cloudy input files. 
	for (int index_n = 0;index_n < 1 && index_n < size_n_H; index_n++){
		for (int index_Z = 0; index_Z < 1 && index_Z < size_Z; index_Z++){

            // Use sprintf to concatenate
            sprintf(directory_name, "hden%.2f_metallicity%.2f", n_H[index_n], Z[index_Z]);
            sprintf(file_name, "%s/hden%.2f_metallicity%.2f.in", directory_name, n_H[index_n], Z[index_Z]);

            // Create file 
            int check = mkdir(directory_name, 0777); 
            // 0777 is the file permission setting in linux. "read, write, & execute for owner, group and others"
            if (!check){
            	printf("Directory %s created!\n", directory_name);
            	create_in_file(file_name, n_H[index_n]);
            }
            else{
            	printf("Unable to create directory: %s. Breaking from the program!\n", directory_name);
            }

            // delete_file_and_its_contents(directory_name);
		}
	}


	return 0; 
}