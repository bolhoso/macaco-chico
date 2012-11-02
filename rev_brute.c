#include <stdio.h>
#include <string.h>

const char LETTERS[] = {'B', 'C', 'G'};
const int SIZE = 3, MAX_CHARS = 3; 

void print_solution (int *c) {
	int i;
	for (i = 0; i < SIZE; i++) {
		printf ("%d ", c[i]);
		if (i == SIZE - 1)
			putchar('\n');
	}
}

void combine (int *combination, int curr_idx) {
	int aux[SIZE];

	if (curr_idx < 0)
		return;

	memcpy (aux, combination, sizeof(int)*SIZE);
	while (curr_idx >= 0) {
		do {
			print_solution (aux);
			aux[curr_idx]++;
		} while (aux[curr_idx] < MAX_CHARS);

		combine (aux, curr_idx-1);
		curr_idx--;
	}
}

int main () {
	int sol[] = {1, 1, 1};
	combine (sol, SIZE-1);

	return 0;
}
