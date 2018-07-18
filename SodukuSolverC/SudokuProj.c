/*
	SUDOKU Solver program:
	Implement in multiple ways to study performance improvement.
	1. Plain single function program
	2. Modular program
	3. Using recursion
	4. Using dynamic memory allocation

Modification History:
		Author: Anbumani Manikantan
		Initial version date: 15-Jan-2016
		Version: 1.0 => Plain C program with one function.
*/

# include <stdio.h>
# include <conio.h>

/* Declare two matrices.
	1. Done matrix (9x9) which shows the cells with actual value for the computed cells and 0 for remaining cells
	2. Possibility Matrix (9x9x9) which show the possible values for not computed cells */
typedef unsigned char UINT8;

/* randomly generated hard 
UINT8 doneMat[9][9] = {
						{8,0,1,6,0,0,0,2,0},
						{0,0,3,0,0,7,0,0,9},
						{0,0,7,0,0,9,4,0,0},
						{0,0,0,0,8,0,2,7,0},
						{0,0,0,0,0,0,0,0,0},
						{0,5,8,0,3,0,0,0,0},
						{0,0,9,3,0,0,5,0,0},
						{0,6,0,0,0,2,3,0,1} };
*/

/* randomly generated - easy */
UINT8 doneMat[9][9] = {
						{7,2,0,3,0,0,0,6,9},
						{3,4,0,6,0,2,5,0,0},
						{0,0,9,0,0,7,0,0,1},
						{6,0,0,0,0,0,8,1,0},
						{4,0,0,7,0,5,0,0,3},
						{0,7,3,0,0,0,0,0,5},
						{1,0,0,2,0,0,7,0,0},
						{0,0,6,8,0,3,0,5,4},
						{5,8,0,0,0,6,0,9,2} };
/*
UINT8 doneMat[9][9] = {
						{0,2,0,0,0,0,0,4,0},
						{0,5,3,0,7,0,6,9,0},
						{9,0,0,2,0,6,0,0,5},
						{0,0,1,7,0,9,3,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,7,5,0,8,2,0,0},
						{6,0,0,9,0,3,0,0,4},
						{0,8,9,0,5,0,1,2,0},
						{0,7,0,0,0,0,0,8,0}};
*/
						
UINT8 possibleMat[9][9][9];

void printDone(void)
{
	printf("\nDone matrix:\n");
	for (int r=0; r<9; r++)
	{
		for(int c=0; c<9; c++)
		{
			printf("%d",doneMat[r][c]);
			if((c+1)%3 == 0) printf(" ");
		}
		printf("\n");
		if((r+1)%3 == 0) printf("\n");
	}
}

void printPsbl(void)
{
	printf("\nPossible matrix:");
	for (int r=0; r<9; r++)
	{
		for(int m=0; m<1; m++)
		{
			printf("\n%d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d",possibleMat[r][0][m], possibleMat[r][0][m+1], possibleMat[r][0][m+2],
																					  possibleMat[r][1][m], possibleMat[r][1][m+1], possibleMat[r][1][m+2],
																					  possibleMat[r][2][m], possibleMat[r][2][m+1], possibleMat[r][2][m+2],
																					  possibleMat[r][3][m], possibleMat[r][3][m+1], possibleMat[r][3][m+2],
																					  possibleMat[r][4][m], possibleMat[r][4][m+1], possibleMat[r][4][m+2],
																					  possibleMat[r][5][m], possibleMat[r][5][m+1], possibleMat[r][5][m+2],
																					  possibleMat[r][6][m], possibleMat[r][6][m+1], possibleMat[r][6][m+2],
																					  possibleMat[r][7][m], possibleMat[r][7][m+1], possibleMat[r][7][m+2],
																					  possibleMat[r][8][m], possibleMat[r][8][m+1], possibleMat[r][8][m+2]);
			printf("\n%d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d",possibleMat[r][0][m+3], possibleMat[r][0][m+4], possibleMat[r][0][m+5],
																					  possibleMat[r][1][m+3], possibleMat[r][1][m+4], possibleMat[r][1][m+5],
																					  possibleMat[r][2][m+3], possibleMat[r][2][m+4], possibleMat[r][2][m+5],
																					  possibleMat[r][3][m+3], possibleMat[r][3][m+4], possibleMat[r][3][m+5],
																					  possibleMat[r][4][m+3], possibleMat[r][4][m+4], possibleMat[r][4][m+5],
																					  possibleMat[r][5][m+3], possibleMat[r][5][m+4], possibleMat[r][5][m+5],
																					  possibleMat[r][6][m+3], possibleMat[r][6][m+4], possibleMat[r][6][m+5],
																					  possibleMat[r][7][m+3], possibleMat[r][7][m+4], possibleMat[r][7][m+5],
																					  possibleMat[r][8][m+3], possibleMat[r][8][m+4], possibleMat[r][8][m+5]);	
			printf("\n%d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d  %d%d%d %d%d%d %d%d%d",possibleMat[r][0][m+6], possibleMat[r][0][m+7], possibleMat[r][0][m+8],
																					  possibleMat[r][1][m+6], possibleMat[r][1][m+7], possibleMat[r][1][m+8],
																					  possibleMat[r][2][m+6], possibleMat[r][2][m+7], possibleMat[r][2][m+8],
																					  possibleMat[r][3][m+6], possibleMat[r][3][m+7], possibleMat[r][3][m+8],
																					  possibleMat[r][4][m+6], possibleMat[r][4][m+7], possibleMat[r][4][m+8],
																					  possibleMat[r][5][m+6], possibleMat[r][5][m+7], possibleMat[r][5][m+8],
																					  possibleMat[r][6][m+6], possibleMat[r][6][m+7], possibleMat[r][6][m+8],
																					  possibleMat[r][7][m+6], possibleMat[r][7][m+7], possibleMat[r][7][m+8],
																					  possibleMat[r][8][m+6], possibleMat[r][8][m+7], possibleMat[r][8][m+8]);

		}
		if((r+1)%3 == 0) printf("\n");
	}
}

void main(void)
{
	/* Declare a variable to track the number of cells completed */
	UINT8 doneCnt = 0;
	
	printf("Hi,	 Anbu");
	/* Initialize the possible matrix */
	for (int row=0; row<9; row++)
	{
		for (UINT8 col=0; col<9; col++)
		{
			/* if value is NOT filled for this row and col in done matrix */
			if (!doneMat[row][col])
			{
				/* Fill the possible matrix with all 1 */
				possibleMat[row][col][0] = 1;
				possibleMat[row][col][1] = 1;
				possibleMat[row][col][2] = 1;
				possibleMat[row][col][3] = 1;
				possibleMat[row][col][4] = 1;
				possibleMat[row][col][5] = 1;
				possibleMat[row][col][6] = 1;
				possibleMat[row][col][7] = 1;
				possibleMat[row][col][8] = 1;
			}
			else
			{
				/* Increment the done count value */
				doneCnt++;
				
				/* Fill the possible matrix with all 0 */
				possibleMat[row][col][0] = 0;
				possibleMat[row][col][1] = 0;
				possibleMat[row][col][2] = 0;
				possibleMat[row][col][3] = 0;
				possibleMat[row][col][4] = 0;
				possibleMat[row][col][5] = 0;
				possibleMat[row][col][6] = 0;
				possibleMat[row][col][7] = 0;
				possibleMat[row][col][8] = 0;
			}
		}
	}
	printf("\nDone count is %d\n", doneCnt);
	printPsbl();
	printDone();
	
	//getch();
	/* Loop until done count reaches 81 */
	int lpcnt = 0;
	int dnv = 0;
	while(doneCnt < 81)
	{
		//if (getch() == 'q') break;
		
		//printf("\nResult before the inner loop count %d\n", lpcnt++);
		/*for(UINT8 row=0; row<9; row++) {
			printf("\n");
			for(UINT8 col=0; col<9; col++) {
				printf("%d  ",doneMat[row][col]); } }
		printf("\n\n");
			*/
			
		for(UINT8 row=0; row<9; row++)
		{
			for(UINT8 col=0; col<9; col++)
			{
				if(!doneMat[row][col])
				{
					int mr = 3*(row/3);
					int mc = 3*(col/3);
					//printf("\nChecking [%d][%d] : [%d][%d]", row,col,mr,mc);
					for(UINT8 val=1; val<=9; val++)
					{
						/* Check if this value is possible for this cell by looking into the current row, col and mini matrix values */
						if(possibleMat[row][col][val-1])
						{
							dnv = ((doneMat[row][0] == val) || (doneMat[row][1] == val) || (doneMat[row][2] == val) || (doneMat[row][3] == val) || (doneMat[row][4] == val) || (doneMat[row][5] == val) || (doneMat[row][6] == val) || (doneMat[row][7] == val) || (doneMat[row][8] == val) ||
							   (doneMat[0][col] == val) || (doneMat[1][col] == val) || (doneMat[2][col] == val) || (doneMat[3][col] == val) || (doneMat[4][col] == val) || (doneMat[5][col] == val) || (doneMat[6][col] == val) || (doneMat[7][col] == val) || (doneMat[8][col] == val) ||
							   (doneMat[mr][mc] == val) || (doneMat[mr][mc+1] == val) || (doneMat[mr][mc+2] == val) || (doneMat[mr+1][mc] == val) || (doneMat[mr+1][mc+1] == val) || (doneMat[mr+1][mc+2] == val) || (doneMat[mr+2][mc] == val) || (doneMat[mr+2][mc+1] == val) || (doneMat[mr+2][mc+2] == val) );
							if(dnv != 0)
							{
								/* Reset the possible matrix value for this cell value */
								possibleMat[row][col][val-1] = 0;
								//printf("\n==| row[%d] col[%d] val[%d] = %d ", row,col,val-1,possibleMat[row][col][val-1]);
							}
						}
					}
					//if (getch() == 'q') break;
					/* After checking all possible values, if only one value is possible then update the done matrix */
					if((possibleMat[row][col][0] + possibleMat[row][col][1] + possibleMat[row][col][2] + possibleMat[row][col][3] + possibleMat[row][col][4] + possibleMat[row][col][5] + possibleMat[row][col][6] + possibleMat[row][col][7] + possibleMat[row][col][8]) == 1)
					{
						//printf("\n[%d:%d] %d %d %d %d %d %d %d %d %d ",row,col,possibleMat[row][col][0], possibleMat[row][col][1], possibleMat[row][col][2], possibleMat[row][col][3], possibleMat[row][col][4], possibleMat[row][col][5], possibleMat[row][col][6], possibleMat[row][col][7], possibleMat[row][col][8]);
						for(UINT8 val=0; val<9; val++)
						{
							if (possibleMat[row][col][val])
							{
								doneMat[row][col] = val+1;
								possibleMat[row][col][val] = 0;
								doneCnt++;
								//printf("\nDone [%d][%d]=%d Count is %d\n", row,col,val+1, doneCnt);
								
								//printPsbl();
								//printDone();								
								//if (getch() == 'q') break;
							}
						}
					}
					//printPsbl();
					//printDone();
				}
				
			}
		}
	}
	
	printf("\nAt the end\n");
	printDone();
	
}
