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
void out_quest(question const que);
vector<int> get_user_ans();
void out_intformation(int, int);


main()
{
	try
	{
		vector<question> questions = get_questions();
		int count_right = interview(questions);
		out_intformation(count_right, questions.size());
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

int interview(vector<question> const quests)
{
	int sum_rigth;
	for (int i = 0; i != quests.size(); i++)
	{
		out_quest(quests[i]);
		cout << "> ";
		vector<int> user_ans = get_user_ans();
		if (check_answer(quests[i], user_ans))
			sum_rigth++;
	}
}

void out_quest(question const que)
{
	cout << que.quest << '\n';
	const vector<answer>& this_answers = que.answers;
	for (int i = 0; i != this_answers.size(); i++)
	{
		const answer& ans = this_answers[i];
		cout << '\t' << ans.ans << '\n';
	}
}

vector<int> get_user_ans()
{
	vector<int> user_ans;
	for (int i; cin >> i;)
		user_ans.push_back(i);
	return user_ans;
}

bool check_answer(const question& que, const int sum_rigth)
{
	bool ret{true};

	for (int i = 0; i != que.answers.size(); i++)
	{
		
	}
}