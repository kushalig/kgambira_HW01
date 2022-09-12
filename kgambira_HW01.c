#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int string_in_list(char** list, int n, char *s){
	for(int i=0;i<n;i++){
		if(strcmp(list[i], s)==0){
			return 1;
		}
	}
	return 0;
}

void get_unique(char** list, int n){
	int counter = 0;
	for(int i=0;i<n;i++){
			if(string_in_list(list, i-1, list[i])==0){
				counter++;
				printf("%s, ", list[i]);
			}
	}
	if(counter>0){
		printf("\nThere are total %d unique degrees.\n", counter);
	}
}

void get_max(char** list, int n, char** fname, char** lname){
	// find top 3 gpa scores
	float m1 = -100;
	float m2 = -100;
	float m3 = -100;

	for(int i=0; i<n;i++){
		float val = atof(list[i]);
		if(val>m1){
			m3=m2;
			m2=m1;
			m1=val;
		}
		else if(val>m2 && val!=m1){
			m3=m2;
			m2=val;
		}
		else if(val>m3 && val !=m2 && val!=m1){
			m3=val;
		}
	}
	// printf("%f %f %f\n", m1, m2, m3);
	// Print all the students who scored the highest marks
	int counter = 0;
	for(int i=0; i<n;i++){
		float val = atof(list[i]);
		if(val==m1){
			counter++;
			printf("%s %s - %f\n", fname[i], lname[i], m1);
		}
	}
	// if(counter<3){
		for(int i=0; i<n;i++){
			float val = atof(list[i]);
			if(val==m2){
				counter++;
				printf("%s %s - %f\n", fname[i], lname[i], m2);
			}
		}
	// }
	// if(counter<3){
		for(int i=0; i<n;i++){
			float val = atof(list[i]);
			if(val==m3){
				counter++;
				printf("%s %s - %f\n", fname[i], lname[i], m3);
			}
		}
	// }
}

void avg_credit_hr(char **list, int n){
	float sum = 0;
	for(int i=0;i<n;i++){
		sum = sum + atof(list[i]);
	}
	printf("Average Credit Hour = %0.4f\n", sum/n);
}

void avg_gpa(char** major, char** gpa, int n){
	float sum = 0;
	int tot = 0;
	for(int i=0;i<n;i++){
		if(strcmp(major[i], "Computer Science")==0){
			sum = sum + atof(gpa[i]);
			tot++;
		}
	}
	printf("Average GPA of Computer Science Students = %0.4f\n", sum/tot);
}

int unique_adv(char** adv, char** major, char* major_name, int n){
	// create a list of adv with major_name major
	int counter = 0;

	for(int i=0; i<n; i++){
		if(strcmp(major[i], major_name)==0){
			int flag = 0;
			for(int j=0; j<i; j++){
				if(strcmp(major[j], major_name)==0){
					if(strcmp(adv[i], adv[j])==0){
						flag = 1;
						break;
					}
				}
			}
			if(flag==0){
				counter++;
				// printf("%d %s was not found earlier\n", i, major[i]);
				// printf("%s\n", adv[i]);
			}
		}
	}
	return counter;

}
void department_number(char** major, char** adv, int n){
	int counter = 0;
	for(int i=0;i<n;i++){
		// if(strcmp(major[i], "Undeclared")!=0){
			if(string_in_list(major, i-1, major[i])==0){
				counter++;
				printf("%s - ", major[i]);
				printf("%d\n", unique_adv(adv, major, major[i], n));
			}
		// }
	}
}

int main() {
	
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int tot_lines = 0;
    fp = fopen("students_dataset.csv", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        tot_lines++;

    }
   
    tot_lines--;
    fclose(fp);

    line = NULL;
    len = 0;
    fp = fopen("students_dataset.csv", "r");

    char** fname = malloc(sizeof(char**) * tot_lines);
    char** lname = malloc(sizeof(char**) * tot_lines);
    char** major = malloc(sizeof(char**) * tot_lines);
    char** degree = malloc(sizeof(char**) * tot_lines);
    char** gpa = malloc(sizeof(char**) * tot_lines);
    char** credit_hr = malloc(sizeof(char**) * tot_lines);
    char** ta = malloc(sizeof(char**) * tot_lines);
    char** adv = malloc(sizeof(char**) * tot_lines);

    int i = 0;
    getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);

    	// split at each comma
    	char *pt;
    	if(line[strlen(line)-1]=='\n'){
    		line[strlen(line)-1]='\0';
    	}
	    pt = strtok (line,",");
	    fname[i] = malloc(strlen(pt) + 1);
		strcpy(fname[i], pt);

		pt = strtok (NULL, ",");
	    lname[i] = malloc(strlen(pt) + 1);
		strcpy(lname[i], pt);
		
		pt = strtok (NULL, ",");
	    major[i] = malloc(strlen(pt) + 1);
		strcpy(major[i], pt);
		
		pt = strtok (NULL, ",");
	    degree[i] = malloc(strlen(pt) + 1);
		strcpy(degree[i], pt);
		
		pt = strtok (NULL, ",");
	    gpa[i] = malloc(strlen(pt) + 1);
		strcpy(gpa[i], pt);
		
		pt = strtok (NULL, ",");
	    credit_hr[i] = malloc(strlen(pt) + 1);
		strcpy(credit_hr[i], pt);
		
		pt = strtok (NULL, ",");
	    ta[i] = malloc(strlen(pt) + 1);
		strcpy(ta[i], pt);
		
		pt = strtok (NULL, ",");
	    adv[i] = malloc(strlen(pt) + 1);
		strcpy(adv[i], pt);

		i++;

    }
    // i = tot_lines-1;
	// printf("%s %s %s %s %s %s %s %s", fname[i], lname[i], major[i], degree[i], gpa[i], credit_hr[i], ta[i], adv[i]);

	printf("-----------------------------");	
	printf("\n>>Problem 1: How many different degrees do we have? Display their names.\n\n");
	get_unique(degree, tot_lines);

	printf("-----------------------------");	
	printf("\n>>Problem 2: What is the full name of the 3 students who have the highest GPA? If we have multiple, print them all.\n\n");
	get_max(gpa, tot_lines, fname, lname);

	printf("-----------------------------");	
	printf("\n>>Problem 3: What are the average credit hours of the college?\n\n");
	avg_credit_hr(credit_hr, tot_lines);

	printf("-----------------------------");	
	printf("\n>>Problem 4: What is the average GPA of the students whose department is Computer Science?\n\n");
	avg_gpa(major, gpa, tot_lines);

	printf("-----------------------------");	
	printf("\n>>Problem 5: Display the list of departments along with the total number of advisors.\n\n");
	department_number(major, adv, tot_lines);

    fclose(fp);
    if (line)
        free(line);
}
