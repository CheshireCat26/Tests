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
void read_quests(vector<question>&, ifstream& const);
void read_answers(question& que, ifstream& const ifile);
int interview(vector<question>);
void out_intformation(int);


main()
{
	try
	{
		vector<question> questions = get_questions();
		int count_right = interview(questions);
		out_intformation(count_right);
		keep_window_open();
	}
	catch (const std::exception& e)
	{
		cout << e.what << '\n';
		keep_window_open();
	}
	SetConsoleOutputCP(1251);

	
}

//Получает вопросы
vector<question> get_questions()
{
	vector<question> questions;
	ifstream ifile{ "questions.txt" };
	read_quests(questions, ifile);
	ifile.close();
	return questions;
}

//Читает вопросы из файла
void read_quests(vector<question>& questions, ifstream& const ifile)
{
	while (!ifile.eof())
	{
		char mark;
		ifile >> mark;
		if (mark != '?')
			error("ОШИБКА: вопрос не найден");
		
		question que;
		ifile >> que.quest;
		read_answers(que, ifile);
		questions.push_back(que);
	}
}

//Читает ответы из файла
void read_answers(question& que, ifstream& const ifile)
{
	char mark{' '};
	while (mark != '?')
	{
		ifile >> mark;
		if (mark == '\n')
			continue;

		if (mark != '+' && mark != '-')
			error("ОШИБКА: не найдено ответа");

		answer ans;
		ifile >> ans.ans;
		if (mark == '+')
			ans.right = true;
		else
			ans.right = false;

		que.answers.push_back(ans);
	}
}

int interview(vector<question> quests)
{
	for (int i = 0; i != quests.size(); i++)
	{
		
	}
}