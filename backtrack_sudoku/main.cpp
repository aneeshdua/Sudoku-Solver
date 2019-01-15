//SUDOKU SOLVER FOR 9X9 SUDOKUS

#include<iostream>
#include<string>
#include<fstream>
#include<ctype.h>
#include<algorithm>

using namespace std;

struct cell
{
	char value;
	string candidates;
};

class sudoku
{
	cell prob[9][9];
public:
	void create_markup();
	void set_candidates(int, int);
	int linear_check(int, int, char);
	int check_box(int, int, char);
	void read_prob();
	void validate_prob();
	void solve();
	void print_prob();
	bool valid_soln();
	bool backtrack(cell prob[9][9]);
	bool get_empty(int&, int&);
	bool is_it_solved();
};

void sudoku::read_prob()
{
	cout << "Enter the file name of the sudoku puzzle to be solved(with.txt extension)" << endl;
	string name;
	//cin >> name;
	ifstream file("sudoku_prob.txt");
	if (file.is_open())
	{
		string line;
		file >> line;
		int j = 0;
		while (!file.eof())
		{
			for (int i = 0; i < 9; i++)
			{
				//cout << line[i];
				if (isdigit(line[i]))
				{
					prob[j][i].value = line[i];
					//cout << prob[i][j].value;
				}
				else
				{
					prob[j][i].value = '0';
					//cout << prob[i][j].value;
				}
			}
			//cout << endl;
			j++;
			file >> line;
		}
		j = 8;
		for (int i = 0; i < 9; i++)
		{
			//cout << line[i];
			if (isdigit(line[i]))
			{
				prob[j][i].value = line[i];
				//cout << prob[i][j].value;
			}
			else
			{
				prob[j][i].value = '0';
				//cout << prob[i][j].value;
			}
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file. Please check the file." << endl;
		system("PAUSE");
		exit(0);
	}
}

void sudoku::print_prob()
{
	cout << " -------------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << " | ";
		for (int j = 0; j < 9; j++)
		{
			cout << prob[i][j].value << " ";
			if ((j+1) % 3 == 0)
				cout << "| ";
		}
		cout << endl;
		if((i+1) % 3 ==0)
			cout << " -------------------------"<<endl;
	}
	//system("PAUSE");
}

void sudoku::validate_prob() // CHECK IF GIVEN SUDOKU IS VALID
{
	int counter = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (prob[i][j].value != 0)
				counter++;
		}
	}
	if (counter < 17)
	{
		cout << "Invalid sudoku" << endl;
		cin.get();
		exit(0);
	}
}

bool sudoku::get_empty(int &row, int &colm)
{
	for (row = 0; row < 9; row++)
	{
		for (colm = 0; colm < 9; colm++)
		{
			if (prob[row][colm].value == '0')
			{
				//cout << prob[row][colm].value;
				return true;
			}
		}
	}
	return false;
}

int sudoku::linear_check(int row, int colm, char candidate)
{
	for (int i = 0; i < 9; i++)
	{
		if (candidate == prob[row][i].value)
		{
			return 1;
		}
	}
	for (int j = 0; j < 9; j++)
	{
		if (candidate == prob[j][colm].value)
		{
			return 1;
		}
	}
	return 0;
}

int sudoku::check_box(int row, int colm, char candidate)
{
	int row_region[3], colm_region[3];
	if (row <= 2)
	{
		row_region[0] = 0;
		row_region[1] = 1;
		row_region[2] = 2;
	}
	else if (row < 6)
	{
		row_region[0] = 3;
		row_region[1] = 4;
		row_region[2] = 5;
	}
	else
	{
		row_region[0] = 6;
		row_region[1] = 7;
		row_region[2] = 8;
	}
	if (colm <= 2)
	{
		colm_region[0] = 0;
		colm_region[1] = 1;
		colm_region[2] = 2;
	}
	else if (colm < 6)
	{
		colm_region[0] = 3;
		colm_region[1] = 4;
		colm_region[2] = 5;
	}
	else
	{
		colm_region[0] = 6;
		colm_region[1] = 7;
		colm_region[2] = 8;
	}
	for (int i = row_region[0]; i <= row_region[2]; i++)
	{
		for (int j = colm_region[0]; j <= colm_region[2]; j++)
		{
			//cout << row << " " << colm << " " << candidate << prob[i][j].value;
			if (prob[i][j].value == candidate)
				return 1;
		}
	}
	return 0;
}

void sudoku::set_candidates(int row, int colm)
{
	prob[row][colm].candidates = "123456789";
	char temp_candidates[] = { '1' , '2', '3', '4', '5', '6', '7', '8','9' };
	for (int i = 0; i < 9; i++)
	{
		int flag1 = linear_check(row, colm, temp_candidates[i]);
		int flag2 = check_box(row, colm, temp_candidates[i]);
		if (flag1 == 1 || flag2 == 1)
		{
			//prob[row][colm].candidates.erase(prob[row][colm].candidates.begin() + index);
			prob[row][colm].candidates.erase(std::remove(prob[row][colm].candidates.begin(), prob[row][colm].candidates.end(), temp_candidates[i]), prob[row][colm].candidates.end());
			//cout << prob[row][colm].candidates<<endl;
		}
	}
}

void sudoku::create_markup()  //CREATE CANDIDATES SET FOR EACH EMPTY CELL  
{
	for (int row = 0; row < 9; row++)
	{
		for (int colm = 0; colm < 9; colm++)
		{
			if (prob[row][colm].value == '0')
			{
				set_candidates(row, colm);
			}
		}
	}
}

void sudoku::solve()
{
	create_markup();
	int flag = 0;
	do //SINGLETON CANDIDATE SET 
	{
		flag = 0;
		for (int row = 0; row < 9; row++)
		{
			for (int colm = 0; colm < 9; colm++)
			{
				if (prob[row][colm].value == '0')
				{
					if (prob[row][colm].candidates.length() == 1)
					{
						flag = 1;
						prob[row][colm].value = prob[row][colm].candidates.at(0);
						//cout << row << ' ' << colm << ' ' << prob[row][colm].value << endl;
					}
				}
			}
		}
		create_markup();
	} while (flag == 1);
	if (!is_it_solved())
		backtrack(prob);
}

bool sudoku::is_it_solved()
{
	for (int row = 0; row < 9; row++)
	{
		for (int colm = 0; colm < 9; colm++)
		{
			if (prob[row][colm].value == '0')
				return false;
		}
	}
	return true;
}

bool sudoku::backtrack(cell prob[9][9])
{
	int i = 0;
	int row, colm;
	if (!get_empty(row, colm))
	{
		return true;
	}
	//cell temp[9][9];
	int len = prob[row][colm].candidates.length();
	while (i < len)
	{
		int flag1 = linear_check(row, colm, prob[row][colm].candidates[i]);
		int flag2 = check_box(row, colm, prob[row][colm].candidates[i]);
		if (flag1 !=1 && flag2 !=1)
		{
			prob[row][colm].value = prob[row][colm].candidates[i];
			//print_prob();
			create_markup();
			//solve();
			if (backtrack(prob))
				return true;
			prob[row][colm].value = '0';
		}
		i++;
	}
	return false;
}

int main()
{
	cout << "================================================================================\n";
	cout << "                       Welcome to the Sudoku Solver \n";
	cout << "================================================================================\n";
	sudoku puzzle;
	puzzle.read_prob();
	puzzle.create_markup();
	puzzle.solve();
	puzzle.print_prob();
	cout << "Thank You for using Sudoku Ninja for your puzzle \n\n";
	system("PAUSE");
	return 0;
}