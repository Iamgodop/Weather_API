#include <stdio.h>
#include <string.h>

#define FILE_CONTENT_LENGTH 500

void main()
{
	char api[200], city[50], *buffer, file_content[FILE_CONTENT_LENGTH], delimitor[] = "\"";

	input: printf("Enter city name: ");
	gets(city);

	sprintf(api, "curl \"https://api.openweathermap.org/data/2.5/weather?q=%s&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\" > weather.txt", city);
	system(api);

	FILE *fp_weather = fopen("weather.txt", "r");
	fgets(file_content, FILE_CONTENT_LENGTH, fp_weather);

	if (! strcmp(file_content, "{\"cod\":\"404\",\"message\":\"city not found\"}"))
	{
		printf("%s: city not found!\n", city);
		goto input;
	}

	else
	{
		buffer = strtok(file_content, delimitor);
		while (strcmp(buffer, "temp"))
		{
			buffer = strtok(NULL, delimitor);
		}
		buffer = strtok(NULL, delimitor);
		buffer[0] = buffer[strlen(buffer) - 1] = ' ';
		printf("Temperature in %s is%sC", city, buffer);	
	}
}
