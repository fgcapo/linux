#include <limits>
#include <iostream>
#include <iomanip>

using namespace std;

int MATRIX[8][6] = {
  {15, 20, 25, 45, 60, 66},
  {20, 28, 35, 50, 72, 85},
  {30, 50, 55, 58, 93, 95},
  {40, 60, 65, 68, 100, 106},
  {50, 65, 70, 75, 105, 115},
  {68, 75, 80, 90, 110, 120},
  {69, 88, 90, 120, 130, 150},
  {91, 92, 110, 140, 160, 180}
};

const int COLS = sizeof(MATRIX[0]) / sizeof(MATRIX[0][0]);
const int ROWS = sizeof(MATRIX) / sizeof(MATRIX[0]);

typedef decltype(MATRIX) MTYPE;

struct Coordinate {
	int row;
	int column;
	Coordinate(int r = -1, int c = -1) { row = r; column = c; }

	bool inbounds(MTYPE matrix) {
		return row >= 0 && column >= 0 && row < ROWS && column < COLS;
	}

	bool isBefore(Coordinate p) {
		return row <= p.row && column <= p.column;
	}

	void setToAverage(Coordinate min, Coordinate max) {
		row = (min.row + max.row) / 2;
		column = (min.column + max.column) / 2;
	}
};

ostream& operator<<(ostream &o, Coordinate &c) {
  return o << '(' << c.row << ", " << c.column << ')';
}

void print_spaces(int depth) {
  for(int i = 0; i < depth; i++) cout << ' ';
}

Coordinate findElement(MTYPE matrix, Coordinate origin, Coordinate dest, int x, int depth);
Coordinate partitionAndSearch(MTYPE matrix, Coordinate origin, Coordinate dest, Coordinate pivot, int elem, int depth);
 
Coordinate partitionAndSearch(MTYPE matrix, Coordinate origin, Coordinate dest, Coordinate pivot, int elem, int depth) {
	print_spaces(depth);
  cout << "partitionAndSearch(origin=" << origin << ", dest=" << dest << ", pivot=" << pivot <<")\n";

	Coordinate lowerLeftOrigin = Coordinate(pivot.row, origin.column);
  Coordinate lowerLeftDest = Coordinate(dest.row, pivot.column - 1);
  Coordinate upperRightOrigin = Coordinate(origin.row, pivot.column);
  Coordinate upperRightDest = Coordinate(pivot.row - 1, dest.column);
	
  Coordinate result = findElement(matrix, lowerLeftOrigin, lowerLeftDest, elem, depth+1);
	print_spaces(depth);
  cout << "findElement(llo=" << lowerLeftOrigin << ", lld=" << lowerLeftDest << ") returned " << result << endl;
  if (result.row == -1) {
		result = findElement(matrix, upperRightOrigin, upperRightDest, elem, depth+1);
		print_spaces(depth);
    cout << "findElement(uro=" << upperRightOrigin << ", urd=" << upperRightDest << ") returned " << result << endl;
  }
  return result;
}

Coordinate findElement(MTYPE matrix, Coordinate origin, Coordinate dest, int x, int depth) {
	if (!origin.inbounds(matrix) || !dest.inbounds(matrix)) return Coordinate();
	
	if (matrix[origin.row][origin.column] == x) return origin;
  else if (!origin.isBefore(dest)) return Coordinate();

  /* Set start to start of diagonal and end to the end of the
  * diagonal. Since the grid may not be square, the end of the
  * diagonal may not equal dest. */
  Coordinate start = origin;
  int diagDist = min(dest.row - origin.row, dest.column - origin.column);
  Coordinate end = Coordinate(start.row + diagDist, start.column + diagDist);
  Coordinate p = Coordinate();
 
  /* Do binary search on the diagonal, looking for the first
  * element greater than x */
  while (start.isBefore(end)) {
		p.setToAverage(start, end);
		if (x > matrix[p.row][p.column]) {
			start.row = p.row + 1;
			start.column = p.column + 1;
		} else {
			end.row = p.row - 1;
			end.column = p.column - 1;
		}
  }
 
  /* Split the grid into quadrants. Search the bottom left and the top right. */
  return partitionAndSearch(matrix, origin, dest, start, x, depth+1);
}


// returns (first_row-1,first_col) if the key is less than the first diagonal square given
// find the adjacent elements along the diagonal that contain the search key
tuple<int, int> binary_search_diagonal(int key, int mat[ROWS][COLS], int first_row, int first_col, int last_row, int last_col) {
  auto error =  make_tuple<int, int>(-1,-1);
  if(first_row > last_row || first_col > last_col) return error;

  int num_rows = num_rows;
  int num_cols = num_cols;
  int num_diag_cells = min(num_rows, num_cols);

  // deal with at least 2x2 matrices for now
  if(num_diag_cells > 2) {
    int mid_diag = num_diag_cells / 2;//first_col + (num_cols)/2;
    
    int rix_top_left = first_row + mid_diag;
    int cix_top_left = first_col + mid_diag;

    int rix_bottom_right = first_row + mid_diag + 1;
    int cix_bottom_right = first_col + mid_diag + 1;

    int lower_el = mat[rix_top_left][cix_top_left];
    int higher_el = mat[rix_bottom_right][cix_bottom_right];

    // found it
    if(key == lower_el) return make_tuple(rix_top_left, cix_top_left);
    if(key == higher_el) return make_tuple(rix_bottom_right, cix_bottom_right);
    
    else if(key > lower_el && key < higher_el) {
      // search the top right and bottom left sections of the matrix given by the calling arguments
    }
    
    //key may be in the rest of the matrix we cut off
    else if (key > higher_el) { 
      if(num_diag_cells < num_rows) {
        // more of the matrix to search below
      } else if(num_diag_cells < num_cols) {
        // more of the matrix to search to the right
      }
    //do the save as above for the lower? can we cut off matrix above or to the left?
    }

    return error;
  }

  return error;
}

  
int main() {
  //int *a = static_cast<int*>(MATRIX[0]);
  //a[r*COLS+c];

  cout << "RxC = " << ROWS << "x" << COLS << endl;// << setw(4) << '+';

	for(int c = 0; c < COLS; c++) cout << setw(4) << c;
	cout << endl;

  for(int r = 0; r < ROWS; r++) {
    cout << r;
    for(int c = 0; c < COLS; c++) {
      cout << setw(4) << MATRIX[r][c];
    }
    cout << endl;
  }

	int key = 73;
	cout << "\n\nLooking for " << key << endl;

	Coordinate result = findElement(MATRIX, Coordinate(0, 0), Coordinate(ROWS-1, COLS-1), key, 0);
  cout << endl << "result = (" << result.row << ", " << result.column << ")\n";

  return 0;
}
