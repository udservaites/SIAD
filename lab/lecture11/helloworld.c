
#include <stdio.h>
#include <string.h>


int main(void) {

	printf("Content-Type: text/plain; charset=utf-8\n\n");
	printf("Hello World!\n\n");

	char* data = getenv("QUERY_STRING");
	printf("String: %s", data);

	char name[100];
	char password[100];

	sscanf(data, "name=%[^&]&password=%s\n", name, password);

	printf("Name: %s Password: %s\n", name, password);

	char official_name[20] = "Rebecca";
	char official_password[20] = "programmingrocks";

	if((strcmp(name, official_name) == 0) && (strcmp(password, official_password) == 0)) {
		printf("Success!!\n Your username is: %s Your password is: %s", name, password);
	} else {
		printf("That username/password combination does not exist. Please try again.");
	}



}
