#include <stdio.h>
#include <assert.h>

// TODO: implement diagonal moves


/**************************************************
 *         THE BIG AND FAT CHALLENGES             *
 *                                                *
 * Develop and test each part!                    *
 * Validate development while building code       *
 * Explain what you're doing while you code       *
 *                                                *
 *************************************************/

#define WALL '*'
#define END  '+'
#define PASSED '.'

// TODO: isn't it possible to make directions easier to manipulate?
// they can be an increment of X or Y
enum directions {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};

struct pos {
	char y, x;
	enum directions d;
};

#define MAX_LIN 8
#define MAX_COL 16

// TODO: read maze from file
// 1 2
// MAZE
char maze[MAX_LIN][MAX_COL] = {
	{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
	{' ', ' ', ' ', '*', ' ', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+'},
	{'*', ' ', '*', '*', '*', ' ', ' ', '*', '*', ' ', '*', ' ', '*', '*', '*', '*'},
	{'*', ' ', '*', ' ', ' ', ' ', '*', '*', '*', ' ', '*', ' ', '*', ' ', '*', '*'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', ' ', '*'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', '*', '*', ' ', '*', '*', ' ', '*'},
	{'*', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
	{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
};


void print_maze () {
	int i, j;
	for (i = 0; i < MAX_LIN; i++) {
		for (j = 0; j < MAX_COL; j++) {
			putchar (maze[i][j]);
		}
		putchar ('\n');
	}
	putchar ('\n');
}

/*
 * Check if a move is within bounds or not
 */
int check_bounds (struct pos *p) {
	return !((p->x < 0) ||
		(p->x > MAX_COL - 1) ||
		(p->y < 0) ||
		(p->y > MAX_LIN - 1));
}

/*
 * Check if it's possible to move from current (x, y) in direction d.
 * Also, check if the monkey haven't already passed in the specified position
 */
int can_move (char maze[MAX_LIN][MAX_COL], struct pos p) {
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
	return maze[p.y][p.x] != PASSED && maze[p.y][p.x] != WALL;
}

/*
 * Make a move from (x, y) in direction d and reset the direction
 * If a solution is found in the future position, returns 1, otherwise,
 * on normal moves, return 0
 */
int move_and_reset (char maze[MAX_LIN][MAX_COL], struct pos *p) {
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

	if (maze[p->y][p->x] == END) {
		return 1;
	}

	maze[p->y][p->x] = PASSED;
	p->d = DIR_UP;

	return 0;
}

// TODO: nof_moves!
#define SOLUTION_FOUND -1
int solve_maze_recur (char maze[MAX_LIN][MAX_COL], struct pos pos) {

	// Mmm.. so check the bounds
	struct pos *p = &pos;
	if (!check_bounds (&pos)) {
		return 0;
	} 
	
	// Change the current coordinate according to the direction and reset
	// direction
	if (can_move (maze, pos)) { 
		if (move_and_reset (maze, &pos)) {
			printf ("Hoooray! Solution found! We're at (%d, %d).\n", pos.x, pos.y);
			return SOLUTION_FOUND;
		}
	}

	// Now, try moving in the 4 directions
	while (pos.d <= DIR_RIGHT) {
		if (can_move (maze, pos)) {

			printf ("-> (%d, %d) %d\n", pos.x, pos.y, pos.d);
			print_maze();

			if (solve_maze_recur (maze, pos) == SOLUTION_FOUND) {
				return SOLUTION_FOUND;
			}
		}

		// Back from the recursion, try another direction
		pos.d++;
	}

	return 0;
}

int solve_maze (char maze[MAX_LIN][MAX_COL]) {
	struct pos start = {1, 0, DIR_RIGHT};
	return solve_maze_recur (maze, start);
}

void test_check_bounds() {
	struct pos p1 = {0, 0, DIR_LEFT};
	assert (!check_bounds(&p1));

	struct pos p2 = {0, 0, DIR_RIGHT};
	assert (check_bounds(&p2));

	struct pos p3 = {0, 0, DIR_DOWN};
	assert (check_bounds(&p3));

	struct pos p4 = {0, 0, DIR_UP};
	assert (!check_bounds(&p4));
}

void test_check_move () {
	struct pos p1 = {1, 0, DIR_RIGHT};
	assert (!can_move(maze, p1));
}

void test_solve () {
	char simple_maze[MAX_LIN][MAX_COL] = {
		{' ', '+'},
	};

	struct pos start = {0, 0, DIR_RIGHT};
	solve_maze_recur (simple_maze, start);
}

int main () {
	solve_maze (maze);

	
	return 0;
}
