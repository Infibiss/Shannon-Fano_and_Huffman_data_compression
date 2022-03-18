#include <bits/stdc++.h>
#include <windows.h>

using namespace std;


HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
void yellow(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN);}
void white(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);}
void red(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED);}
void green(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN);}


struct Code
{
	char a; 
	int p;
	string q;
};

bool comp(Code a, Code b){return a.p > b.p;}
bool stcomp(pair <int, string> a, pair <int, string> b){return a.first > b.first;}

vector <Code> arr;
vector < pair <bool, int> > used(1000);
string first_s;

void text(string s)
{
	yellow();
	cout << s;
	white();

}

void clear()
{
	arr.clear();
	for(int i = 0; i < used.size(); i++)
	{
		used[i].first = false;
		used[i].second = 0;
	}
}

void input1()
{
	cin.ignore(256, '\n');
	getline(cin, first_s);

	for(int i = 0; i < first_s.size(); i++)
	{
		if(used[first_s[i] + 'a'].first == false)
		{
			used[first_s[i] + 'a'].first = true;
			if(!arr.empty())
				used[first_s[i] + 'a'].second = arr.size();

			arr.push_back({first_s[i], 1, ""}); // a p q
		}
		else
			arr[used[first_s[i] + 'a'].second].p++;
	}

	sort(arr.begin(), arr.end(), comp);

	for(int i = 0; i < arr.size(); i++)
		used[arr[i].a + 'a'].second = i;

}

void haffman_makebit()
{
	vector < pair <int, string> > st;

	for(int i = 0; i < arr.size(); i++)
	{
		string s = "";
		s += arr[i].a;
		st.push_back({arr[i].p, s});
	}

	sort(st.begin(), st.end(), stcomp);


	if(st.size() == 1)
		arr[0].q += '0';
	while(st.size() != 1)
	{
		int minsum = 99999999, l, r;
		for(int i = st.size() - 1; i > 0; i--)
		{
			if(st[i].first + st[i - 1].first < minsum)
			{
				minsum = st[i].first + st[i - 1].first;
				l = i - 1, r = i;
				if(minsum == 0) break;
			}
		}

		for(int i = 0; i < st[l].second.size(); i++)
			for(int j = 0; j < arr.size(); j++)
				if(arr[j].a == st[l].second[i])
				{
					arr[j].q += '1';
					break;
				}

		for(int i = 0; i < st[r].second.size(); i++)
			for(int j = 0; j < arr.size(); j++)
				if(arr[j].a == st[r].second[i])
				{
					arr[j].q += '0';
					break;
				}

		st[l].second += st[r].second;
		st[l].first += st[r].first;
		st.erase(st.begin() + r);
	}

	for(int i = 0; i < arr.size(); i++)
		reverse(arr[i].q.begin(), arr[i].q.end());
}

void fano_makebit(int begin, int end)
{
	if(end - begin == 1)
		return;
	int minabs = -1, minpos = -1;
	int left = 0, right = 0;

	for(int i = begin; i < end; i++)
		right += arr[i].p;

	for(int i = begin; i < end; i++)
	{
		if(abs(left - right) < minabs || minabs == -1)
		{
			minabs = abs(left - right);
			minpos = i;
		}
		left += arr[i].p;
		right -= arr[i].p;
	}

	for(int i = minpos; i < end; i++)
		arr[i].q += '0';
	for(int i = minpos - 1; i >= begin; i--)
		arr[i].q += '1';

	if(end - begin <= 2)
		return;

	fano_makebit(minpos, end);
	fano_makebit(begin, minpos);
}

void mainout()
{
	text("\nLine length - "); 
	cout << first_s.size() << '\n';
	text("Number of symbols - ");
	cout << arr.size() << '\n';

	text("Print \"P\"? Yes/No\n");
	string inp;
	cin >> inp;
	bool flag = true;
	if(inp == "No" || inp == "no" || inp == "2")
		flag = false;

	int sumbits = 0;
	if(flag)
	{
		green();
		cout << "A P Q\n";
		white();
		for(int i = 0; i < arr.size(); i++)
		{
			sumbits += arr[i].p * arr[i].q.size();
			cout << arr[i].a << ' ' << arr[i].p << ' ' << arr[i].q << '\n';
		}
	}
	else
	{
		green();
		cout << "A Q\n";
		white();
		for(int i = 0; i < arr.size(); i++)
		{
			sumbits += arr[i].p * arr[i].q.size();
			cout << arr[i].a << ' ' << arr[i].q << '\n';
		}
	}
	cout << '\n';

	text("Sum of bits - ");
	cout << sumbits << '\n';
	text("Bit`s cost - ");
	cout << double(sumbits) / first_s.size() << '\n';


	red();
	for(int i = 0; i < first_s.size(); i++)
		cout << arr[used[first_s[i] + 'a'].second].q;
	cout << '\n';

	green();
	cout << "\nComplete!\n";
	white();
	cout << '\n';
}

void decrypt(string scripted)
{
	red();
	string pref = "";
	for(int i = 0; i < scripted.size(); i++)
	{
		pref += scripted[i];
		for(int j = 0; j < arr.size(); j++)
		{
			if(pref == arr[j].q)
			{
				cout << arr[j].a;
				pref = "";
				break;
			}

		}
	}
}

signed main()
{
	while(true)
	{
		text("1) Encrypt FANO 2) Encrypt HAFFMAN 3) Decrypt 4) Clear cmd 5) Stop\n");

		char input;
		cin >> input;
		input -= '0';

		if(input == 1)
		{
			text("Write a line\n");

			input1();

			fano_makebit(0, arr.size());

			mainout();
		}
		else if(input == 2)
		{
			text("Write a line\n");

			input1();

			haffman_makebit();

			mainout();
		}
		else if(input == 3)
		{
			text("Write the symbols with their codes\nWrite \"Stop\" when you end\n");

			string s;
			cin.ignore(256, '\n');
			while(1)
			{
				getline(cin, s);
				if(s == "Stop" || s == "stop")
					break;
				Code x;
				x.a = s[0];
				s.erase(s.begin(), s.begin() + 2);
				x.q = s;
				arr.push_back(x);
			}

			text("Write a binary line to decrypt\n");

			cin >> first_s;

			decrypt(first_s);

			cout << "\n\n";
		}
		else if(input == 4)
			system("cls");
		else
		{
			red();
			cout << "Stopped";
			break;
		}

		clear();
	}
	return 0;
}
