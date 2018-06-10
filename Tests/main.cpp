#include <Windows.h>
#include "std_lib_facilities.h"

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
void read_quests(vector<question>&, istream& const);
void read_answers(question& que, istream& const ifile);
int interview(vector<question>, vector<int>& ind_worng);
void out_quest(question const que);
vector<int> get_user_ans();
bool check_answer(const question& que, const vector<int>& user_ans);
bool consist(int i, vector<int>);
void out_intformation(int, vector<int>& wrong, vector<question>& questions);

//Êîëëè÷åòâî âîïðîñîâ
const int count_quest = 20;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	try
	{
		vector<question> questions = get_questions();
		vector<int> wrong;
		int count_right = interview(questions, wrong);
		out_intformation(count_right, wrong, questions);
		keep_window_open();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << '\n';
		keep_window_open();
	}
	

	
}

//Âîçâðàùàåò âîïðîñû èç ôàéëà questions.txt
vector<question> get_questions()
{
	vector<question> questions;
	ifstream ifile{ "questions.txt" };
	read_quests(questions, ifile);
	if (questions.size() == 0)
		error("Íå íàéäåíî âîïðîñîâ");
	ifile.close();
	return questions;
}

//×òåíèå âîïðîñîâ èç ïîòîêà 
void read_quests(vector<question>& questions, istream& const ifile)
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

//×òåíèå îòâåòîâ íà âîïðîñ èç ïîòîêà
void read_answers(question& que, istream& const ifile)
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
			error("Íåâåðíûé ñèìâîë îòâåòà");

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

//Îïðîñ ïîëüçîâàòåëñÿ
int interview(vector<question> const quests, vector<int>& ind_worng)
{
	int sum_rigth{0};

	vector<int> prevs;
	for (int i = 0; i != count_quest; i++)
	{
		int numb = rand() % quests.size();
		while (consist(numb, prevs))
			numb = rand() % quests.size();
		prevs.push_back(numb);

		out_quest(quests[numb]);
		cout << "> ";
		vector<int> user_ans = get_user_ans();
		if (check_answer(quests[numb], user_ans))
			sum_rigth++;
		else
			ind_worng.push_back(numb);
	}

	return sum_rigth;
}

//Âûââîä âîïîïðîñà è îòâåòîâ íà íåãî
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

//Ïîëó÷åíèå îòâåòîâ îò ïîëüçîâàòåëñÿ
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

//Ïðîâåðêà îòâåòîâ ïîëüçîâàòåëñÿ
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

//Âûâîä ðåçóëüòàòîâ òåñòèðîâàíèÿ
void out_intformation(int rigth, vector<int>& wrong, vector<question>& questions)
{
	cout << "Ïðàâèëüíûõ îòâåòîâ: " << rigth << " èç " << count_quest <<'\n';
	cout << "Ïðîöåíò óñïåøíîñòè: " << double(rigth) / count_quest * 100 << "%\n";
	cout << "Âîïðîñû ñ ïðàâèèëüíûìè îòâåòàìè, íà êîòîðûå âû îòâåòèëè íåâåðíî:\n";
	for (int i : wrong)
	{
		cout << questions[i].quest << '\n';
		for (int j = 0; j != questions[i].answers.size(); j++)
			if (questions[i].answers[j].right)
				cout << '\t' <<questions[i].answers[j].ans << '\n';
	}
}
