#include <Windows.h>
#include <std_lib_facilities.h>

struct answer
{
	string ans;
	bool right;
};

struct question
{
	string quest;
	vector<answer> answers;
};

vector<question> get_questions();
void read_quests(vector<question>&, ifstream&);
int interview(vector<question>);
void out_intformation(int);

main()
{
	try
	{
		vector<question> questions = get_questions();
		int count_right = interview(questions);
		out_intformation(count_right);
	}
	catch (const std::exception& e)
	{
		cout << e.what
	}
	SetConsoleOutputCP(1251);

	
}

vector<question> get_questions()
{
	vector<question> questions;
	ifstream ifile{ "questions.txt" };
	read_quests(questions, ifile);
	ifile.close();
}

void read_quests(vector<question>& questions, ifstream& ifile)
{
	while (!ifile.eof())
	{

	}
}