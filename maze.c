#include <stdio.h>
#include <stdlib.h>

/**************************************************
 *         THE BIG AND FAT CHALLENGES             *
 *                                                *
 * Develop and test each part!                    *
 * Validate development while building code       *
 * Explain what you're doing while you code       *
 *                                                *
 *************************************************/

#define WALL '#'
#define END  '+'
#define PASSED '.'

// TODO: isn't it possible to make directions easier to manipulate?
// they can be an increment of X or Y
enum directions {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};

typedef struct {
	int y, x;
	enum directions d;

	int lins, cols;
	char **maze;
} t_maze;


/*
 * Print the maze along with the current position and direction
 */
void print_maze (t_maze *m) {
	int i, j;

	if (!m) {
		return;
	}

	printf ("-> (%d, %d) %d\n", m->x, m->y, m->d);
	for (i = 0; i < m->lins; i++) {
		for (j = 0; j < m->cols; j++) {
			putchar (m->maze[i][j]);
		}
		putchar ('\n');
	}
	putchar ('\n');
}

t_maze *free_maze (t_maze *m) {
	if (!m) {
		return;
	}

	while (--m->lins >= 0) {
		free(m->maze[m->lins]);
	}

	free (m->maze);
	free (m);
	return NULL;
}

/*
 * Read the maze from a file and initialize it
 * The file should be in the format:
 * <LINS> <COLS> <START_X> <START_Y>
 * MMMMM...
 * MMMMMM...
 * ...
 * MMMMM...
 *
 * Where M is the representation of the maze. Possible chars are:
 *  # wall
 *  + end of the maze (more than one allowd)
 *  _ blank space, where it's possible to move
 */
t_maze *read_maze (char *file) {
	FILE *f = fopen (file, "r");

	if (!f) {
		return NULL;
	}

	// Create a maze, read it's size and initial position
	t_maze *my_maze = (t_maze *) malloc (sizeof (t_maze));
	fscanf (f, "%d %d %d %d\n", &(my_maze->lins), &(my_maze->cols),
			&(my_maze->x), &(my_maze->y));

	// Allocate the maze array
	int lin;
	my_maze->maze = (char **) malloc (sizeof (char *) * my_maze->lins);
	for (lin = 0; lin < my_maze->lins; lin++) {
		my_maze->maze[lin] = (char *) malloc (sizeof (char) * (my_maze->cols + 1));
	}

	// Now, read the maze contents
	lin = 0;
	while (lin < my_maze->lins && !feof (f)) {
		int read, col = 0;
		do {
			read = getc (f);

			if (read != '\n') {
				my_maze->maze[lin][col++] = read;
			}
		} while (read != '\n');
		lin++;
	}

	fclose (f);
	return my_maze;
}

/*
 * Check if a move is within bounds or not
 */
int check_bounds (t_maze *p) {
	return !((p->x < 0) ||
		(p->x > p->cols - 1) ||
		(p->y < 0) ||
		(p->y > p->lins - 1));
}

/*
 * Check if it's possible to move from current (x, y) in direction d.
 * Also, check if the monkey haven't already passed in the specified position
 */
int can_move (t_maze p) {
	switch (p.d) {
		case DIR_RIGHT: p.x++; break;
		case DIR_LEFT:  p.x--; break;
		case DIR_UP:    p.y--; break;
		case DIR_DOWN:  p.y++; break;
	}

	// have the bounds been respected after moving?
	if (!check_bounds (&p)) {
		return 0;
	}

	// we can move unless we have a wall and haven't passed through that pos.
	return p.maze[p.y][p.x] != PASSED && p.maze[p.y][p.x] != WALL;
}

/*
 * Make a move from (x, y) in direction d and reset the direction
 * If a solution is found in the future position, returns 1, otherwise,
 * on normal moves, return 0
 */
int move_and_reset (t_maze *p) {
	switch (p->d) {
		case DIR_RIGHT:
			p->x++; break;
		case DIR_LEFT:
			p->x--; break;
		case DIR_UP:
			p->y--; break;
		case DIR_DOWN:
			p->y++; break;
	}

	if (p->maze[p->y][p->x] == END) {
		return 1;
	}

	p->maze[p->y][p->x] = PASSED;
	p->d = DIR_UP;

	return 0;
}

#define SOLUTION_FOUND -1
int solve_maze_recur (t_maze pos) {

	// Mmm.. so check the bounds
	if (!check_bounds (&pos)) {
		return 0;
	} 
	
	// Now, try moving in the 4 directions
	while (pos.d <= DIR_RIGHT) {
		if (can_move (pos)) {
			if (move_and_reset (&pos)) {
				printf ("Hoooray! Solution found! We're at (%d, %d).\n", pos.x, pos.y);
				print_maze(&pos);
				return SOLUTION_FOUND;
			}

			print_maze(&pos);

			if (solve_maze_recur (pos) == SOLUTION_FOUND) {
				return SOLUTION_FOUND;
			}
		}

		// Back from the recursion, try another direction
		pos.d++;
	}

	return 0;
}

int solve_maze (t_maze *maze) {
	return solve_maze_recur (*maze);
}

int main (int argc, char *argv[]) {
	if (argc > 1) {
		t_maze *m = read_maze (argv[1]);
		solve_maze (m);
		m = free_maze (m);

		return 0;
	}

	fprintf (stderr, "Usage: %s <maze_file>\n", argv[0]);
}
