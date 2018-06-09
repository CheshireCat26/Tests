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
bool check_answer(const question& que, const vector<int>& user_ans);
bool consist(int i, vector<int>);
void out_intformation(int, int);


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	try
	{
		vector<question> questions = get_questions();
		int count_right = interview(questions);
		out_intformation(count_right, questions.size());
		keep_window_open();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << '\n';
		keep_window_open();
	}
	

	
}


vector<question> get_questions()
{
	vector<question> questions;
	ifstream ifile{ "questions.txt" };
	read_quests(questions, ifile);
	if (questions.size() == 0)
		error("�� ������� ��������");
	ifile.close();
	return questions;
}


void read_quests(vector<question>& questions, ifstream& const ifile)
{
	while (!ifile.eof())
	{
		char mark{' '};
		while (mark != '?')
			ifile >> mark;
		
		question que;
		getline(ifile, que.quest);
		read_answers(que, ifile);
		questions.push_back(que);
	}
}


void read_answers(question& que, ifstream& const ifile)
{
	char mark{ ' ' };
	while (mark != '?' && !ifile.eof())
	{
		ifile >> mark;
		if (mark == '\n' )
			continue;
		if (mark == '?')
		{
			ifile.putback(mark);
			break;
		}

		if (mark == ' ')
			break;

		if (mark != '+' && mark != '-')
			error("�������� ������ ������");

		answer ans;
		getline(ifile, ans.ans);
		if (mark == '+')
			ans.right = true;
		else
			ans.right = false;

		que.answers.push_back(ans);
		mark = ' ';
	}
}

int interview(vector<question> const quests)
{
	int sum_rigth{0};
	for (int i = 0; i != quests.size(); i++)
	{
		out_quest(quests[i]);
		cout << "> ";
		vector<int> user_ans = get_user_ans();
		if (check_answer(quests[i], user_ans))
			sum_rigth++;
	}

	return sum_rigth;
}

void out_quest(question const que)
{
	cout << que.quest << '\n';
	const vector<answer>& this_answers = que.answers;
	for (int i = 0; i != this_answers.size(); i++)
	{
		const answer& ans = this_answers[i];
		cout << '\t' << i << ')' <<ans.ans << '\n';
	}
}

vector<int> get_user_ans()
{
	vector<int> user_ans;
	for (char i; cin >> i;)
	{
		if (i == ';')
			break;

		int val;
		if (i == '0' || i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8' || i == '9')
		{
			cin.putback(i);
			cin >> val;
		}
		user_ans.push_back(val);
	}
		
	return user_ans;
}

bool check_answer(const question& que, const vector<int>& user_ans)
{

	for (int i = 0; i != que.answers.size(); i++)
	{
		if (que.answers[i].right && !consist(i, user_ans))
			return false;
		if (!que.answers[i].right && consist(i, user_ans))
			return false;
	}
	return true;
}

bool consist(int val, vector<int> mass)
{
	for (int i = 0; i != mass.size(); i++)
		if (val == mass[i])
			return true;

	return false;
}

void out_intformation(int rigth, int count_que)
{
	cout << "���������� �������: " << rigth << " �� " << count_que <<'\n';
	cout << "������� ����������: " << double(rigth) / count_que * 100 << "%\n";
}