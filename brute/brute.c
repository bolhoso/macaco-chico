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

	print_solution (combination);

	if (curr_idx >= SIZE)
		return;

	memcpy (aux, combination, sizeof(int)*SIZE);
	while (curr_idx < SIZE) {
		while (aux[curr_idx] < MAX_CHARS) {
			aux[curr_idx]++;
			combine (aux, curr_idx+1);
		}

		curr_idx++;
	}
}

int main () {
	int sol[] = {1, 1, 1};
	combine (sol, 0);

	return 0;
}
