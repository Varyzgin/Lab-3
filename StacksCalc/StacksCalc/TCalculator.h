#pragma once
#include<string>
#include"TStack.h"
class TCalculator
{
	TStack<double> st_a;
	TStack<char> st_char;
	string expr;
	string postfix; // ������� ����������� ������ ���������
	int prior(char op) {
		switch (op)
		{
		case'(': return 0;
		case'+': return 1;
		case'-': return 1;
		case'*': return 2;
		case'/': return 2;
		case'^': return 3;
		}
		return 0;
	}

public:
	TCalculator() {}
	TCalculator(TCalculator& TC) {
		expr = TC.expr;
		postfix = TC.postfix;
	}
	~TCalculator() {}

	TCalculator& operator=(TCalculator& TC) {
		expr = TC.expr;
		postfix = TC.postfix;
		return *this;
	}
	void SetExpr(string _expr) {
		expr = _expr;
	}
	string GetExpr() {
		return expr;
	}
	string GetPostfix() {
		return postfix;
	}
	bool CheckExpr()
	{
		for (int i = 0; i < expr.length(); i++) {
			if (expr[i] == '(')
				st_char.Push(expr[i]);
			else if (expr[i] == ')')
				if (st_char.Empty()) return false;
				else st_char.Pop();
		}
		if (st_char.Empty())
			return true;
		else return false;
	}

	void ToPostfix() {
		// ���-�� ������ ������� expr �� ������ ������ ��� ��������� ��
		string infix = "(" + expr + ")";
		postfix = ""; // ������ �������
		st_char.Clear();
		string a_dig = ""; // ������������� ������ ��� ����� � >= 1 ������

		for (int i = 0; i < infix.size(); i++) {
			if (infix[i] == ' ') continue; // ���������� �� �������� �� ��������
			if (isdigit(infix[i])) {
				a_dig += infix[i];
			}
			else {
				if (a_dig != "") {
					postfix += a_dig;
					a_dig = "";
					postfix += " ";
				}

				if (infix[i] == '(')
				{
					st_char.Push(infix[i]);
				}
				else if (infix[i] == ')') // ���� ����������� ������ - ����������� �� ����� � ��������� �� �� ������ (
				{
					while (st_char.Top() != '(')
					{
						postfix += st_char.Pop();
						postfix += " ";
					}
					st_char.Pop(); // ������ ����������� ������
				}
				else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
				{
					while (prior(infix[i]) <= prior(st_char.Top()))
					{
						postfix += st_char.Pop();
						postfix += " ";
					}
					st_char.Push(infix[i]);
				}
			}
		}
		if (!postfix.empty())
			postfix.pop_back(); // ������ ������ ����� ���������
	}

	double CalcPostfix() {
		double tmp;
		st_a.Clear();
		string a_dig = "";
		if (postfix.empty()) throw"Empty";
		for (int i = 0; i < postfix.length(); i++) {
			if (isdigit(postfix[i])) {
				a_dig += postfix[i];
			}
			else if (postfix[i] == ' ' && isdigit(postfix[i - 1])) {
				double a = stod(a_dig);
				st_a.Push(a);
				a_dig = "";
			}

			else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
			{
				if (st_a.Empty()) throw("No more digits");
				double second = st_a.Pop();
				if (st_a.Empty()) throw("No more digits");
				double first = st_a.Pop();
				switch (postfix[i])
				{
				case '+':
					tmp = first + second;
					st_a.Push(tmp);
					break;
				case '-':
					tmp = first - second;
					st_a.Push(tmp);
					break;
				case '*':
					tmp = first * second;
					st_a.Push(tmp);
					break;
				case '/':
					tmp = first / second;
					st_a.Push(tmp);
					break;
				case '^':
					tmp = 1;
					for (int j = 0; j < second; j++)
						tmp *= first;
					st_a.Push(tmp);
					break;
				}
			}
		}
		if (st_a.Empty()) throw("No more digits");
		else {
			double a = st_a.Pop();
			if (st_a.Empty()) return a;
			else throw("Too much digits");
		}
	}
};

/*������� 2 + 3 * 4 ^ (1 + 2)

	 was A + B
	 bacame A B +

	 was 2 + 3* 4
	 became 2 3 4 * +

	 was 2 + 3* 4 - 5
	 became 2 3 4 * + 5 -

	 was 2 + 3* 4^2 - 5
	 became 2 3 4 2 ^ * + 5 -
	 was (2 + 3)* 4^2 - 5
	 became 2 3 + 4 2 ^ * 5 -
	 was (2 + 3)* 4^(2 - 5)
	 became 2 3 + 4 2 5 - ^ *
	 was 1/(2 + 3)* 4^(2 - 5)
	 became 1 2 3 + 4 2 5 - ^ * /

	 ����� �������� �� ��������� �������
	 ��������:
	 ������ ����� � ����
	 ��������� ���� - �������� ��� �������� �� �����
		  - ������ �������� - ������� �� ����� -
		  - ��������� � ����� �� �������





	 ����� ��� �������� ������������
	 ���� 4 - , �� �� ����� ������ ������� �����
	 ���� 4 5 - +, �������� ������� �����
	 ���� 4 3 2 -, �������� ������ ���������� �����
	 �� � ������
	   � ������� ����� ����� ������� ���������� �����, ��� ��������� ������





	 ��������� ������������ ����������� ������ � ���������
 ��� ������ �����(1 + 2) * 4
 ������ ������() - ���������
 (1 + 2)) * 4
 ((((((1 + 2) * 4
	 ))((1 + )2 * 4()
		 ��������:
 �������� ���� - ���������(-������, ���������) - �������
	 �������������� ������������
 ���� ��������������� ������ - ������ � ����,
 ���� ����������� ��������� �� �����
 ���� ������� �� �������, �� �� ���������
 ���� ���� � ����� �� ������ - ���� �� ���������
 ��� ������ - string
 �����
 str.size
 str.lengh
 ��� cin � cout  ������� ����������� �� ������� �������
 ���� ������������ getline(cin, str) ������ ��� �� enter





  ���� 9 �����!


	 ������ � ��������������� �����������
	 2 + 3 * 4 ^ 5
	 2 3 4 5 ^ * +
	 2�� - � �������
	 + ��������� ->  � ���� ��
	 3�� - � �������
	 * ��������� -> ���������� ����������, ���� ������ � ���,
	 �� ��� �������� � ���� -> � ���� ��
	 4�� - � �������
	 ^ ��������� -> ���������� ����������, ���� ������ � ���,
	 �� ��� �������� � ���� -> � ���� ��
	 5�� - � �������

	 ������� ���� ��� ����� ������

	 �������� - ����������� �� ����� � ��

	 2 + 3 - 4 ^ 5
	 2 3 + 4 5 ^ -

	 22 + (3-2*2) ^ 5
	 22 3 2 2 * - 5 ^ +
	 ���� ����� ( ������ - ���������� �� � ����
	 ���� ����� ) ������ - ���������� ��� ��������

	 2�� - � �������
	 + ��������� ->  � ���� ��
	 ( ������� - ���������� �� � ����
	 3�� - � �������
	 - ��������� ->  � ���� ��
	 * ��������� -> ���������� ����������, ���� ������ � ���,
	 �� ��� �������� � ���� -> � ���� ��
	 2�� - � �������
	 ) ������ -> ������� �� ����� ��� (* � -), ������� �� (.,
	 ����������� ��������� � ������


	 ^ ��������� -> ���������� ����������, ���� ������ � ���,
	 �� ��� �������� � ���� -> � ���� ��
	 5�� - � �������
	 ���������

	 !! ��������� ( = 0 !!
	 (��������� � ���� ��� ���������)

	 //����������� ������� ������ � ������ � � �����, ����� �� ����
	 //������ ��������� ����������

	 ���������� ��������:
	 ( = 0
	 +- = 1
	 * / = 2
	 ^    = 3

	 2 + (2 * 2 - 1) ^ 5

	 2�� - � �������
	 + ��������� ->  � ���� ��
	 ( ������� - ���������� �� � ����
	 2�� - � �������
	 * ��������� -> ���������� ����������, ���� ������ � ���,
	 �� ��� �������� � ���� -> � ���� ��
	 2�� - � �������
	 - ��������� -> ���������� ����������, ������, ����������� *, ����� � ����
	 1�� - � �������
	 ) ������ -> ������� �� ����� *, � (, ���������� * � ������
	 � ��

	 */