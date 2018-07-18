//Sudoku solver version 3.1
// Possibility Matrix creation
#include "Sudoku_Solver_v3.1.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h>

using namespace std;

#define BLK(r,c) ( (r/3)*3 + c/3 )

int main() {

	int inputMat[9][9] = {
		{6,8,1,0,0,9,5,3,7},
		{5,4,2,7,3,8,1,6,9},
		{9,7,3,1,6,5,8,4,2},
		{0,0,4,6,7,0,3,9,0},
		{3,6,9,5,8,4,2,7,1},
		{0,0,0,0,0,3,4,0,6},
		{4,0,0,0,0,0,0,1,3},
		{0,0,5,0,0,0,0,2,0},
		{2,0,0,0,0,0,9,0,0}
	};
/* Logical error in the program
	int inputMat[9][9] = {
		{7,1,0,0,0,0,0,0,0},
		{9,3,0,8,7,0,4,0,0},
		{0,0,0,5,1,0,0,0,0},
		{0,2,8,7,0,0,0,0,9},
		{0,0,0,2,0,1,0,0,0},
		{6,0,0,0,0,8,5,7,0},
		{0,0,0,0,3,5,0,0,0},
		{0,0,2,0,8,4,0,1,5},
		{0,0,0,0,0,0,0,8,4}
	};
*/
	Sudoku sud(&inputMat[0][0]);
	cout << "Hi" << endl;

	//sud.Solve();
	//sud.display();
	//cout << endl;

	sud.dispMat();
	cout << endl;

	sud.Solve();
	//sud.dispPossMap();

	return 0;
}

//==================================================
// *************  Constructor   ********************
//==================================================
Sudoku::Sudoku(int* inputMat) {
	// Copy the input matrix
	std::copy(&inputMat[0], &inputMat[0]+81, &m_mMat[0][0]);

	std::copy(&inputMat[0], &inputMat[0]+81, &m_copyMat[0][0]);

	// count the number of elements present in the input matrix (81 - number of zeros in the matrix)
	m_nElementCnt = 81 - std::count(&m_mMat[0][0], &m_mMat[8][8], 0);
}

//==================================================
// *************  UpdatePossMat   ******************
//==================================================
void Sudoku::PencilMarking() {
	// Fill Row vectors
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			m_vRow[r].push_back(m_mMat[r][c]);
		}
	}

	// Fill Col vectors
	for(int c=0; c<9; c++) {
		for(int r=0; r<9; r++) {
			m_vCol[c].push_back(m_mMat[r][c]);
		}
	}

	// Fill Block vectors
	for(int b=0; b<9; b++) {
		for(int r=0; r<3; r++) {
			for(int c=0; c<3; c++) {
				m_vBlk[b].push_back(m_mMat[(b/3)*3+r][(b%3)*3+c]);
			}
		}
	}

	// Fill possiblity Matrix
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			if(m_mMat[r][c] == 0) {
				vector<int> tV; 	// Temporary vector to store possible values
				for(int v=1; v<=9; v++) {
					if( (std::find(m_vRow[r].begin(), m_vRow[r].end(),v) == m_vRow[r].end()) &&
					        (std::find(m_vCol[c].begin(), m_vCol[c].end(),v) == m_vCol[c].end()) &&
					        (std::find(m_vBlk[BLK(r,c)].begin(), m_vBlk[BLK(r,c)].end(),v) == m_vBlk[BLK(r,c)].end())
					  )
						tV.push_back(v);
				}
				m_mPosMat[r][c] = tV;
				m_mRowPos[r].insert(make_pair(tV,c));
				m_mColPos[c].insert(make_pair(tV,r));
				m_mBlkPos[(r/3)*3 + c%3].insert(make_pair(tV,(r%3)*3 + c%3));
			}
		}
	}
}

//==================================================
// *************  Destructor   ********************
//==================================================
Sudoku::~Sudoku() {

}

//==================================================
// *************  Display   ********************
//==================================================
void Sudoku::display() {
	cout << "Sudoku Matrix" << endl;
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			cout << setw(2) << m_mMat[r][c] << " ";
		}
		cout << endl;
	}

	cout << "Elements found = " << m_nElementCnt << endl;
	cout << "Row Vectors:" << endl;
	// Disply Row vector
	for(int r=0; r<9; r++) {
		for(auto itR = m_vRow[r].begin(); itR != m_vRow[r].end(); itR++) {
			cout << *itR << " ";
		}
		cout << endl;
	}

	// Disply Col vector
	cout << "Col Vectors:" << endl;
	for(int c=0; c<9; c++) {
		for(auto itC = m_vCol[c].begin(); itC != m_vCol[c].end(); itC++) {
			cout << *itC << " ";
		}
		cout << endl;
	}

	// Disply Block vector
	cout << "Block Vectors:" << endl;
	for(int b=0; b<9; b++) {
		for(auto itB = m_vBlk[b].begin(); itB != m_vBlk[b].end(); itB++) {
			cout << *itB << " ";
		}
		cout << endl;
	}
}


//==================================================
// *************  display matrix   ********************
//==================================================
void Sudoku::dispMat() {
	cout << "Matrix: " << m_nElementCnt << " Elements completed " << endl;
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			cout << setw(2) << m_mMat[r][c] << " ";
		}
		cout << endl;
	}
	//getch();
}

void Sudoku::dispCpMat() {
	cout << "Copy Matrix: " << endl;
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			cout << setw(2) << m_copyMat[r][c] << " ";
		}
		cout << endl;
	}
}

//==================================================
// *************  display vector   ********************
//==================================================
void Sudoku::dispVec(vector<int> vec) {
	cout << "[";
	for(auto it=vec.begin(); it<vec.end(); it++) {
		cout << *it << " ";
	}
	cout << "]";
}

//==================================================
// *************  Display   ********************
//==================================================
void Sudoku::dispPoss() {
	cout << "Possibility Matrix " << endl;

	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			if(!m_mPosMat[r][c].empty()) {
				cout << "[" << r <<":" << c << "] ";
				dispVec(m_mPosMat[r][c]);
				cout << endl;
			}
		}
	}
}

//==================================================
// *************  Display Possibilty map *******
//==================================================
void Sudoku::dispPossMap() {
	cout << "Possibility Maps " << endl;

	// row map
	cout << "Row possibilities " << endl;
	for(int r=0; r<9; r++) {
		cout << "Row[" << r << "]: ";
		for(auto it=m_mRowPos[r].begin(); it!=m_mRowPos[r].end(); ++it ) {
			cout << "{" << it->second << ", ";
			dispVec(it->first);
			cout << "}, ";
		}
		cout << endl;
	}
}

//==================================================
// *************  Solve ****************************
//==================================================
void Sudoku::Solve() {
	SliceNDice();

	PencilMarking();
	dispPoss();
	LoneSingles();

	HiddenSingles();

	dispMat();
	NakedPairs();
	dispMat();
	dispPoss();
	
	NakedTriplets();
	dispMat();
	dispPoss();
	
	NakedQuads();
	dispMat();
	dispPoss();
}


//==================================================
// *************  Update Element *******
//==================================================
void Sudoku::updateElement(int row, int col, int val) {
	m_nElementCnt++;
	m_mMat[row][col] = val;
	m_mPosMat[row][col].clear();
	cout << "==> updating [" << row << "," << col << "]:" << val << "Elements found = " <<  m_nElementCnt << endl;

	dispMat();
	getch();

	// Update possibility matrix
	// Row
	for(int c=0; c<9; c++) {
		if(!m_mPosMat[row][c].empty()) {
			auto loc = std::find(m_mPosMat[row][c].begin(), m_mPosMat[row][c].end(),val);
			if(loc != m_mPosMat[row][c].end()) {
				m_mPosMat[row][c].erase(loc);
				if(m_mPosMat[row][c].size() == 1) {
					updateElement(row, c, m_mPosMat[row][c][0]);
				}
			}
		}
	}

	// Col
	for(int r=0; r<9; r++) {
		if(!m_mPosMat[r][col].empty()) {
			auto loc = std::find(m_mPosMat[r][col].begin(), m_mPosMat[r][col].end(),val);
			if(loc != m_mPosMat[r][col].end()) {
				m_mPosMat[r][col].erase(loc);
				if(m_mPosMat[r][col].size() == 1) {
					updateElement(r, col, m_mPosMat[r][col][0]);
				}
			}
		}
	}

	// Blk
	for(int r=(row/3)*3; r<(row/3)*3+3; r++) {
		for(int c=(col/3)*3; c<(col/3)*3+3; c++) {
			if(!m_mPosMat[r][c].empty()) {
				auto loc = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(),val);
				if(loc != m_mPosMat[r][c].end()) {
					m_mPosMat[r][c].erase(loc);
					if(m_mPosMat[r][c].size() == 1) {
						updateElement(r, c, m_mPosMat[r][c][0]);
					}
				}
			}
		}
	}
}

//==================================================
// *************  Display Possibilty map *******
//==================================================
void Sudoku::SliceNDice() {
	bool foundElem = false;

	do {
		foundElem = false;
		// Mask with values and check if they have one 0.
		for(int v=1; v<=9; v++) {
			mask(v);

			// Check single elements
			// row
			for(int r=0; r<9; r++) {
				int zCnt = 0;
				int cIdx = 0;

				for(int c=0; c<9; c++) {
					if(m_copyMat[r][c] == 0) {
						zCnt++;
						cIdx = c;
					}
				}
				if(zCnt == 1) {
					updateElement(r, cIdx, v);
					foundElem = true;
					v--;
				}
			}
			if (foundElem) continue;

			// col
			for(int c=0; c<9; c++) {
				int zCnt = 0;
				int rIdx = 0;

				for(int r=0; r<9; r++) {
					if(m_copyMat[r][c] == 0) {
						zCnt++;
						rIdx = r;
					}
				}
				if(zCnt == 1) {
					updateElement(rIdx, c, v);
					foundElem = true;
					v--;
				}
			}
			if (foundElem) continue;

			// blk
			for(int c=0; c<9; c++) {
				int zCnt = 0;
				int rIdx = 0;

				for(int r=0; r<9; r++) {
					if(m_copyMat[r][c] == 0) {
						zCnt++;
						rIdx = r;
					}
				}
				if(zCnt == 1) {
					updateElement(rIdx, c, v);
					foundElem = true;
					v--;
				}
			}
			if (foundElem) continue;
		}
		dispMat();
	} while((foundElem == true) && (m_nElementCnt < 91));
	cout << endl << endl << "Slice and Dice is completed !!! " << endl;
	getch();
}

//==================================================
// *************  mask   ********************
//==================================================
void Sudoku::mask(int val) {
	cout << " Masking with " << val << endl;

	// Take copy of the current matrix
	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			m_copyMat[r][c] = m_mMat[r][c];
		}
	}
	cout << "Before updating ";
	dispCpMat();

	for(int r=0; r<9; r++) {
		for(int c=0; c<9; c++) {
			if(m_mMat[r][c] == val) {
				maskRow(r);
				maskCol(c);
				maskBlk(r,c);
				break;
			}
		}
	}
	dispCpMat();
}

//==================================================
// *************  MaskRow   ********************
//==================================================
void Sudoku::maskRow(int r) {
	for (int c=0; c<9; c++)
		m_copyMat[r][c] = E_MASK;
}

//==================================================
// *************  maskCol   ********************
//==================================================
void Sudoku::maskCol(int c) {
	for (int r=0; r<9; r++)
		m_copyMat[r][c] = E_MASK;
}

//==================================================
// *************  maskBlk   ********************
//==================================================
void Sudoku::maskBlk(int br, int bc) {
	for (int r=3*(br/3); r<3*(br/3)+3; r++) {
		for (int c=3*(bc/3); c<3*(bc/3)+3; c++) {
			m_copyMat[r][c] = E_MASK;
		}
	}
}


//==================================================
// *************  Lone Singles   ********************
//==================================================
void Sudoku::LoneSingles() {
	cout << "Lone Singles: " << endl;
	bool found = false;

	do {
		found = false;

		for(int r=0; r<9; r++) {
			for(int c=0; c<9; c++) {
				if(m_mPosMat[r][c].size() == 1) {
					updateElement(r, c, m_mPosMat[r][c][0]);
					found = true;
					dispPoss();
				}
			}
		}
	} while(found);
}

//==================================================
// *************  Hidden Singles   ********************
//==================================================
void Sudoku::HiddenSingles() {
	// Find hidden singles in rows
	for(int r=0; r<9; r++) {

		vector<int> tempV;
		// merge all possibility values in a row
		for(int c=0; c<9; c++) {
			if(!m_mPosMat[r][c].empty()) {
				tempV.insert(tempV.end(), m_mPosMat[r][c].begin(), m_mPosMat[r][c].end());
			}
		}
		// Check if a value is apprears only one time in the row
		for(int v=1; v<=9; v++) {
			if(std::count(tempV.begin(), tempV.end(), v) == 1) { // hidden singles found
				for(int c=0; c<9; c++) {
					if(std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v) != m_mPosMat[r][c].end() ) {
						updateElement(r, c, v);
						break;
					}
				}
			}
		}
	}

	// Find hidden singles in cols
	for(int c=0; c<9; c++) {

		vector<int> tempV;
		// merge all possibility values in a col
		for(int r=0; r<9; r++) {
			if(!m_mPosMat[r][c].empty()) {
				tempV.insert(tempV.end(), m_mPosMat[r][c].begin(), m_mPosMat[r][c].end());
			}
		}
		// Check if a value is apprears only one time in the col
		for(int v=1; v<=9; v++) {
			if(std::count(tempV.begin(), tempV.end(), v) == 1) { // hidden singles found
				for(int r=0; r<9; r++) {
					if(std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v) != m_mPosMat[r][c].end() ) {
						updateElement(r, c, v);
						break;
					}
				}
			}
		}
	}

	// Find hidden singles in blocks
	for(int b=0; b<9; b++) {

		vector<int> tempV;
		// merge all possibility values in a col
		for(int r=(b/3)*3; r<(b/3)*3+3; r++) {
			for(int c=(b%3)*3; c<(b/3)*3+3; c++) {
				if(!m_mPosMat[r][c].empty()) {
					tempV.insert(tempV.end(), m_mPosMat[r][c].begin(), m_mPosMat[r][c].end());
				}
			}
		}
		// Check if a value is apprears only one time in the block
		for(int v=1; v<=9; v++) {
			if(std::count(tempV.begin(), tempV.end(), v) == 1) { // hidden singles found
				for(int r=(b/3)*3; r<(b/3)*3+3; r++) {
					for(int c=(b%3)*3; c<(b/3)*3+3; c++) {
						if(!m_mPosMat[r][c].empty()) {
							if(std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v) != m_mPosMat[r][c].end() ) {
								updateElement(r, c, v);
								break;
							}
						}
					}
				}
			}
		}
	}

	cout << "End of Hidden Singles" << endl;
}


//==================================================
// *************  Naked Pairs   ********************
//==================================================
void Sudoku::NakedPairs() {
	cout << endl << endl << "Naked pair starts " << endl << endl;

	// Check in the rows
	cout << "==> Row naked pairs <==" << endl;
	for(int r=0; r<9; r++) {
		// collect all the possibility vectors into a multimap of possibility vector and its position
		multimap<vector<int>, int> rowMMap;
		for(int c=0; c<9; c++) {
			if(!m_mPosMat[r][c].empty()) {
				rowMMap.insert(make_pair(m_mPosMat[r][c],c));
			}
		}
		vector<int> npv;
		int pos[2];

		if(findNakedPair(rowMMap, npv, pos)) {
			for(int c=0; c<9; c++) {
				if((c==pos[0]) || (c==pos[1])) continue;
				// Erase first element from possibility matrix in the other cells
				auto it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[0]);
				if(it != m_mPosMat[r][c].end()) {
					cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
					m_mPosMat[r][c].erase(it);
				
					if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
						updateElement(r,c, m_mPosMat[r][c][0]);
					}
				}

				// Erase second element from possibility matrix in the other cells
				it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[1]);
				if(it != m_mPosMat[r][c].end()) {
					cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
					m_mPosMat[r][c].erase(it);
				
					if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
						updateElement(r,c, m_mPosMat[r][c][0]);
					}
				}
			}
		}
	}

	cout << endl << endl <<"Column Naked pairs " << endl;
	// Check in the cols
	for(int c=0; c<9; c++) {
		// collect all the possibility vectors into a multimap of possibility vector and its position
		multimap<vector<int>, int> colMMap;
		for(int r=0; r<9; r++) {
			if(!m_mPosMat[r][c].empty()) {
				colMMap.insert(make_pair(m_mPosMat[r][c],r));
			}
		}
		vector<int> npv;
		int pos[2];

		if(findNakedPair(colMMap, npv, pos)) {
			cout << "Naked pairs found at [" << pos[0] << "," << c << "] and [" << pos[1] << "," << c << "]" << "with values ";
			dispVec(npv);
			for(int r=0; r<9; r++) {
				if((r==pos[0]) || (r==pos[1])) continue;
				// Erase first element from possibility matrix in the other cells
				auto it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[0]);
				if(it != m_mPosMat[r][c].end()) {
					cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
					m_mPosMat[r][c].erase(it);
					
					if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
						updateElement(r,c, m_mPosMat[r][c][0]);
					}
				}

				// Erase second element from possibility matrix in the other cells
				it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[1]);
				if(it != m_mPosMat[r][c].end()) {
					cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
					m_mPosMat[r][c].erase(it);
					
					if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
						updateElement(r,c, m_mPosMat[r][c][0]);
					}
				}
			}
		}
	}

	cout << endl << "Block Naked pairs " << endl;
	// Check in the blocks
	for(int b=0; b<9; b++) {
		// collect all the possibility vectors into a multimap of possibility vector and its position
		int br = (b/3)*3;
		int bc = (b%3)*3;
		multimap<vector<int>, int> blkMMap;
		for(int r=br; r<br+3; r++) {
			for(int c=bc; c<bc+3; c++) {
				if(!m_mPosMat[r][c].empty()) {
					blkMMap.insert(make_pair(m_mPosMat[r][c], (r-br)*3 + c-bc));
				}
			}

		}
		vector<int> npv;
		int pos[2];

		if(findNakedPair(blkMMap, npv, pos)) {
			int r1 = br+(pos[0]/3);
			int c1 = bc+(pos[0]%3);
			int r2 = br+(pos[1]/3);
			int c2 = bc+(pos[1]%3);
			cout << "Naked pairs found at [" << r1 << "," << c1 << "] and [" << r2 << "," << c2 << "]" << "with values ";
			dispVec(npv);
			for(int r=br; r<br+3; r++) {
				for(int c=bc; c<bc+3; c++) {
					if((r==r1) && (c==c1)) continue;
					if((r==r2) && (c==c2)) continue;
					// Erase first element from possibility matrix in the other cells
					if(!m_mPosMat[r][c].empty()) {
						auto it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[0]);
						if(it != m_mPosMat[r][c].end()) {
							cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
							m_mPosMat[r][c].erase(it);
							
							if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
								updateElement(r,c, m_mPosMat[r][c][0]);
							}
						}

						// Erase second element from possibility matrix in the other cells
						it = std::find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), npv[1]);
						if(it != m_mPosMat[r][c].end()) {
							cout << " Removing value " << *it << " from [" << r << "," << c << "]" << endl;
							m_mPosMat[r][c].erase(it);
							
							if(m_mPosMat[r][c].size() == 1){	// if it an only candidate
								updateElement(r,c, m_mPosMat[r][c][0]);
							}
						}
					}
				}
			}
		}
	}

}

//==================================================
// *************  Naked Pairs   ********************
//==================================================
bool Sudoku::findNakedPair(multimap< vector<int>, int > m, vector<int> &npv, int *pos) {
	// display the multimap
	cout<<"Input multi map to find naked pair" <<endl;
	
	for (auto mi : m) {		// display the input multimap
		dispVec(mi.first);
		cout << mi.second << endl;
	}
	for (auto mi : m) {
		if((mi.first.size() == 2) && (m.count(mi.first) == 2)) {

			npv = mi.first;

			pair< multimap< vector<int>, int >::iterator, multimap< vector<int>, int >::iterator > mRan; // matching range
			mRan = m.equal_range(npv);
			for(auto it=mRan.first; it!= mRan.second; it++) {
				*pos++ = it->second;
			}

			cout << "Naked pair is found " << *(pos-2) << "," << *(pos-1) << endl;
			dispVec(npv);
			return true;
		}
	}
	cout << "Naked Pair is not found " << endl;
	return false;
}


//==================================================
// *************  Naked Triplets   ********************
//==================================================
void Sudoku::NakedTriplets(){
	cout << endl << endl << "Naked Triplets starts " << endl << endl;

	// Check in the rows
	cout << "==> Row naked triplets <==" << endl;
	
	for(int r=0; r<9; r++) {
		multimap<int, vector<int> > mTrp;
		vector<int> vTrp;
		int aPos[3];
		
		// create multimap of row
		for(int c=0; c<9; c++){
			if(!m_mPosMat[r][c].empty()){
				mTrp.insert(make_pair(c,m_mPosMat[r][c]));
			}
		}
		
		if(findTriplets(mTrp, vTrp, aPos)){
			// remove the elements from the other cells
			for(int c=0; c<9; c++){
				if((c==aPos[0]) || (c==aPos[1]) || (c==aPos[2])){	// skip if index is part of triplets
					continue;
				}
				if(m_mPosMat[r][c].empty()) continue;	// skip the empty matrix
				
				for( auto v : vTrp ){
					auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
					if(it != m_mPosMat[r][c].end()){
						cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
						m_mPosMat[r][c].erase(it);
					}
				}
				if(m_mPosMat[r][c].size() == 1){
					updateElement(r,c,m_mPosMat[r][c][0]);
				}
			}
		}
	}
	
	// Check in the cols
	cout << endl << "==> Column naked triplets <==" << endl;
	
	for(int c=0; c<9; c++) {
		multimap<int, vector<int> > mTrp;
		vector<int> vTrp;
		int aPos[3];
		
		// create multimap of column
		for(int r=0; r<9; r++){
			if(!m_mPosMat[r][c].empty()){
				mTrp.insert( make_pair( r, m_mPosMat[r][c] ) );
			}
		}
		
		if(findTriplets(mTrp, vTrp, aPos)){
			// remove the elements from the other cells
			for(int r=0; r<9; r++){
				if((r==aPos[0]) || (r==aPos[1]) || (r==aPos[2])){	// skip if index is part of triplets
					continue;
				}
				if(m_mPosMat[r][c].empty()) continue;	// skip the empty matrix
				
				for( auto v : vTrp ){
					auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
					if(it != m_mPosMat[r][c].end()){
						cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
						m_mPosMat[r][c].erase(it);
					}
				}
				if(m_mPosMat[r][c].size() == 1){
					updateElement(r,c,m_mPosMat[r][c][0]);
				}
			}
		}
	}

	// Check in the blocks
	cout << endl << "==> Block naked triplets <==" << endl;

	for(int b=0; b<9; b++) {
		multimap<int, vector<int> > mTrp;
		vector<int> vTrp;
		int aPos[3];
		
		// collect all the possibility vectors into a multimap of possibility vector and its position
		int br = (b/3)*3;
		int bc = (b%3)*3;
		
		for(int r=br; r<br+3; r++) {
			for(int c=bc; c<bc+3; c++) {
				if(!m_mPosMat[r][c].empty()) {
					mTrp.insert(make_pair((r-br)*3 + c-bc, m_mPosMat[r][c]));
				}
			}
		}

		if(findTriplets(mTrp, vTrp, aPos)){
			// remove the elements from the other cells
			for(int r=br; r<br+3; r++) {
				for(int c=bc; c<bc+3; c++) {
					int pos = (r-br)*3 + c-bc;
					if((pos==aPos[0]) || (pos==aPos[1]) || (pos==aPos[2])){	// skip if index is part of triplets
						continue;
					}
					if(m_mPosMat[r][c].empty()) continue;		// skip if the matrix is empty

					for( auto v : vTrp ){
						auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
						if(it != m_mPosMat[r][c].end()){
							cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
							m_mPosMat[r][c].erase(it);
						}
					}
					if(m_mPosMat[r][c].size() == 1){
						updateElement(r,c,m_mPosMat[r][c][0]);
					}
				}
			}
		}
	}
}

//==================================================
// *************  findTriplets   ********************
//==================================================
bool Sudoku::findTriplets(multimap < int, vector<int> > m, vector<int> &trp, int *pos){
	// Size of multimap should be atleast 3
	if(m.size() < 3){
		cout<< " findTriplets size of input multimap is less than 3 [" << m.size() << "]" << endl;
		return false;
	}
	
	// iterate with atleast 3 candidates
	int cnt=0;
	for(auto mi=m.begin(); cnt <= m.size() - 3; mi++, cnt++){
		cout << "Starting with position " << mi->first;
		dispVec(mi->second);
		cout << endl;
		
		// skip the candidates with more than 3 elements
		if(mi->second.size() > 3) continue;
		
		// Create triple multimap and elements vector
		multimap<int, vector<int> > mTrpl;
		vector<int> vTrpl;
		
		mTrpl.insert(make_pair(mi->first, mi->second));		// Initialize the Triple map
		vTrpl = mi->second;		// Initialize the Triple vector
		
		// iterate entire multimap to find matching candidates with the current candidate
		auto m3i=++mi;
		--mi;
		for(; m3i != m.end(); m3i++){
			// skip the candidates with more than 3 elements
			if(m3i->second.size() > 3) continue;
			
			// merge the elements to Triple vector and see if there are not more than 3 unique elements
			vector<int> tempV = vTrpl;
			uniqueMerge(tempV,m3i->second);
			
			// skip the candidate if the merged vector size is more than 3
			if(tempV.size() > 3) continue;
			
			// Update the candiate to Triple map and vector
			cout << "Merging multimap with " << m3i->first;
			dispVec(m3i->second);
			cout << endl;
			mTrpl.insert(make_pair(m3i->first, m3i->second));
			vTrpl = tempV;
		}
		
		// if the size of Quad map is 3, then Naked Triplet has been found
		if(mTrpl.size() == 3){
			cout << endl << "!!! NAKED TRIPLET Found !!!" << endl;
			cout << "Triplet elements ";
			dispVec(vTrpl);
			cout << endl << "Triplet positions [";
			trp = vTrpl;
			int i=0;
			for(auto mti=mTrpl.begin(); mti != mTrpl.end(); i++, mti++ ){
				pos[i] = mti->first;
				cout << pos[i] << " ";
			}
			cout << "]" << endl;
			return true;
		}
		
		if(mTrpl.size() > 3){
			cout << endl << " !!! Triplet size is greater than 3 is  unacceptable. returning false !!!" << endl;
			return false;
		}
	}
	return false;
}


//==================================================
// *************  NakedQuads   ********************
//==================================================
void Sudoku::NakedQuads(){
	cout << endl << endl << "Naked Quads starts " << endl << endl;

	// Check in the rows
	cout << "==> Row naked Quads <==" << endl;
	
	for(int r=0; r<9; r++) {
		multimap<int, vector<int> > mQuad;
		vector<int> vQuad;
		int aPos[4];
		
		// create multimap of row
		for(int c=0; c<9; c++){
			if(!m_mPosMat[r][c].empty()){
				mQuad.insert(make_pair(c,m_mPosMat[r][c]));
			}
		}
		
		if(findQuads(mQuad, vQuad, aPos)){
			// remove the elements from the other cells
			for(int c=0; c<9; c++){
				if((c==aPos[0]) || (c==aPos[1]) || (c==aPos[2]) || (c==aPos[3])){	// skip if index is part of quads
					continue;
				}
				if(m_mPosMat[r][c].empty()) continue;	// skip the empty matrix
				
				for( auto v : vQuad ){
					auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
					if(it != m_mPosMat[r][c].end()){
						cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
						m_mPosMat[r][c].erase(it);
					}
				}
				if(m_mPosMat[r][c].size() == 1){
					updateElement(r,c,m_mPosMat[r][c][0]);
				}
			}
		}
	}
	
	// Check in the cols
	cout << endl << "==> Column naked quads <==" << endl;
	
	for(int c=0; c<9; c++) {
		multimap<int, vector<int> > mQuad;
		vector<int> vQuad;
		int aPos[4];
		
		// create multimap of column
		for(int r=0; r<9; r++){
			if(!m_mPosMat[r][c].empty()){
				mQuad.insert( make_pair( r, m_mPosMat[r][c] ) );
			}
		}
		
		if(findQuads(mQuad, vQuad, aPos)){
			// remove the elements from the other cells
			for(int r=0; r<9; r++){
				if((r==aPos[0]) || (r==aPos[1]) || (r==aPos[2]) || (r==aPos[3]) ){	// skip if index is part of quads
					continue;
				}
				if(m_mPosMat[r][c].empty()) continue;	// skip the empty matrix
				
				for( auto v : vQuad ){
					auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
					if(it != m_mPosMat[r][c].end()){
						cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
						m_mPosMat[r][c].erase(it);
					}
				}
				if(m_mPosMat[r][c].size() == 1){
					updateElement(r,c,m_mPosMat[r][c][0]);
				}
			}
		}
	}

	// Check in the blocks
	cout << endl << "==> Block naked quads <==" << endl;

	for(int b=0; b<9; b++) {
		multimap<int, vector<int> > mQuad;
		vector<int> vQuad;
		int aPos[4];
		
		// collect all the possibility vectors into a multimap of possibility vector and its position
		int br = (b/3)*3;
		int bc = (b%3)*3;
		
		for(int r=br; r<br+3; r++) {
			for(int c=bc; c<bc+3; c++) {
				if(!m_mPosMat[r][c].empty()) {
					mQuad.insert(make_pair((r-br)*3 + c-bc, m_mPosMat[r][c]));
				}
			}
		}

		if(findQuads(mQuad, vQuad, aPos)){
			// remove the elements from the other cells
			for(int r=br; r<br+3; r++) {
				for(int c=bc; c<bc+3; c++) {
					int pos = (r-br)*3 + c-bc;
					if((pos==aPos[0]) || (pos==aPos[1]) || (pos==aPos[2]) || (pos==aPos[3])){	// skip if index is part of quads
						continue;
					}
					if(m_mPosMat[r][c].empty()) continue;		// skip if the matrix is empty

					for( auto v : vQuad ){
						auto it = find(m_mPosMat[r][c].begin(), m_mPosMat[r][c].end(), v);
						if(it != m_mPosMat[r][c].end()){
							cout << "Removing " << v << " from [" << r << "," << c << "]" << endl;
							m_mPosMat[r][c].erase(it);
						}
					}
					if(m_mPosMat[r][c].size() == 1){
						updateElement(r,c,m_mPosMat[r][c][0]);
					}
				}
			}
		}
	}
}

//==================================================
// *************  findQuads   ********************
//==================================================
bool Sudoku::findQuads(multimap < int, vector<int> > m, vector<int> &quad, int *pos){
	// Size of multimap should be atleast 4
	if(m.size() < 4){
		cout<< " findQuads size of input multimap is less than 4 [" << m.size() << "]" << endl;
		return false;
	}
	
	// iterate with atleast 4 candidates
	int cnt=0;
	for(auto mi=m.begin(); cnt <= m.size() - 4; mi++, cnt++){
		//cout << "Starting with position " << mi->first;
		//dispVector(mi->second);
		//cout << endl;
		
		// skip the candidates with more than 4 elements
		if(mi->second.size() > 4) continue;
		
		// Create quad multimap and elements vector
		multimap<int, vector<int> > mQuad;
		vector<int> vQuad;
		
		mQuad.insert(make_pair(mi->first, mi->second));		// Initialize the Quad map
		vQuad = mi->second;		// Initialize the Quad vector
		
		// iterate entire multimap to find matching candidates with the current candidate
		auto m4i=++mi;
		--mi;
		for(; m4i != m.end(); m4i++){
			// skip the candidates with more than 4 elements
			if(m4i->second.size() > 4) continue;
			
			// merge the elements to Quad vector and see if there are not more than 4 unique elements
			vector<int> tempV = vQuad;
			uniqueMerge(tempV,m4i->second);
			
			// skip the candidate if the merged vector size is more than 4
			if(tempV.size() > 4) continue;
			
			// Update the candiate to Quad map and vector
			mQuad.insert(make_pair(m4i->first, m4i->second));
			vQuad = tempV;
		}
		
		// if the size of Quad map is 4, then Naked Quad has been found
		if(mQuad.size() == 4){
			cout << endl << "!!! NAKED QUAD Found !!!" << endl;
			cout << "Quad elements ";
			dispVec(vQuad);
			cout << endl << "Quad positions [";
			quad = vQuad;
			int i=0;
			for(auto mqi=mQuad.begin(); mqi != mQuad.end(); i++, mqi++ ){
				pos[i] = mqi->first;
				cout << pos[i] << " ";
			}
			cout << "]" << endl;
			return true;
		}
		if(mQuad.size() > 4){
			cout << endl << " !!! Quad size is greater than 4 is  unacceptable. returning false !!!" << endl;
			return false;
		}
	}
	return false;
}


void Sudoku::uniqueMerge(vector<int> &inV, vector<int> secV){
	// Merge the vectors
	inV.insert(inV.end(), secV.begin(), secV.end());
	
	// sort the merged vector
	sort(inV.begin(), inV.end());
	
	// get unique elements
	std::vector<int>::iterator itu;
	itu = unique(inV.begin(), inV.end());
	inV.resize( std::distance(inV.begin(),itu) );
}



/*
hard
{8,0,1,6,0,0,0,2,0},
		{0,0,3,0,0,7,0,0,9},
		{0,0,7,0,0,9,4,0,0},
		{0,0,0,0,8,0,2,7,0},
		{0,0,0,0,0,0,0,0,0},
		{0,5,8,0,3,0,0,0,0},
		{0,0,9,3,0,0,5,0,0},
		{0,6,0,0,0,2,3,0,1}

		{0,0,0,0,0,0,0,0,2},
		{0,0,0,0,9,5,4,0,0},
		{0,0,6,8,0,0,0,0,0},
		{0,8,5,0,2,0,9,4,1},
		{0,0,0,1,0,9,7,3,8},
		{1,0,0,0,0,0,2,5,6},
		{0,0,0,9,0,0,0,0,4},
		{0,0,7,6,0,0,3,0,0}

easy
	 {0, 0, 0, 0, 2, 0, 0, 0, 3},
		{0, 0, 6, 4, 0, 0, 0, 0, 0},
		{0, 5, 1, 0, 0, 7, 0, 0, 0},
		{5, 0, 0, 0, 0, 0, 2, 1, 8},
		{2, 6, 0, 0, 0, 0, 0, 3, 9},
		{9, 7, 8, 0, 0, 0, 0, 0, 4},
		{0, 0, 0, 9, 0, 0, 3, 8, 0},
		{0, 0, 0, 0, 0, 3, 1, 0, 0},
		{8, 0, 0, 0, 4, 0, 0, 0, 0}

can't resolve
	int inputMat[9][9] = {
		{6,8,1,0,0,9,5,3,7},
		{5,4,2,7,3,8,1,6,9},
		{9,7,3,1,6,5,8,4,2},
		{0,0,4,6,7,0,3,9,0},
		{3,6,9,5,8,4,2,7,1},
		{0,0,0,0,0,3,4,0,6},
		{4,0,0,0,0,0,0,1,3},
		{0,0,5,0,0,0,0,2,0},
		{2,0,0,0,0,0,9,0,0}


*/
