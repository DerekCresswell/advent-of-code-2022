
/**
 *
 * Advent of Code 2022.
 * Day 1
 *
 * Part 1: 74198
 *
 * Part 2: 209914
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (argc != 3) {

		printf("Usage: calorie-counter <input-file> <top-n-to-track>\n");
		return 1;

	}

	// Open the input file.
	FILE *fd = fopen(argv[1], "r");

	// Track the max 3 calories found.
	int tracking_n = strtol(argv[2], NULL, 10);
	int *max_calories = malloc(sizeof(int) * tracking_n);

	int running_count = 0;

	// Read each line from the file.
	size_t max_line_length = 256;
	char *current_line = malloc(sizeof(char) * max_line_length);
	int characters_read;
	do {

		characters_read = getline(&current_line, &max_line_length, fd);

		// Check if a blank line was read.
		if (characters_read == 1) {

			// Check if we have a new max.
			int min_calories_index = 0;
			for (int i = 1; i < tracking_n; i++) {

				if (max_calories[min_calories_index] > max_calories[i]) {
					min_calories_index = i;
				}

			}

			if (max_calories[min_calories_index] < running_count) {
				max_calories[min_calories_index] = running_count;
			}

			// Reset our running count.
			running_count = 0;
			continue;

		}

		// Otherwise, scan this line for it's number and add to our count.
		int calories = 0;
		int found = sscanf(current_line, "%d\n", &calories);

		if (found == 1) {
			running_count += calories;
		}

	} while(characters_read > 0);

	printf("Max calories:");

	int sum = 0;
	for (int i = 0; i < tracking_n; i++) {
		printf(" %d", max_calories[i]);
		sum += max_calories[i];
	}


	printf("\nTotal: %d\n", sum);

	free(current_line);
	free(max_calories);

	return 0;

}
