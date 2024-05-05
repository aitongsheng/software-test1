#include "pch.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include<vector>
#include<stack>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <ctime>
#include <random>
#include<queue>

using namespace std;
vector<string> FAP;//Four arithmetic problems
int topicCount = 0;//��Ŀ����
string choiceOpe = "+";//�����
int maxNumber = 0;//����������
bool judgeDeci = 0;//�Ƿ���С��
bool judgeDrac = 0;//�Ƿ�������
int howMany = 0;//���ٸ�����������
void function() {
	default_random_engine ran_num1;
	uniform_int_distribution<int> scopeInt(0, 10000);
	ran_num1.seed(time(0));
	for (int n = 0; n < topicCount; ++n) {
		queue<string> number;
		queue<char> oper;
		char tempChar = '#';
		FAP.push_back(string());
		int len = 0;
		int signBrac = 0;
		for (int i = 0; i < howMany; ++i) {
			int tempInt = scopeInt(ran_num1) % maxNumber;
			if (tempChar == '(') {
				tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 3)];
				oper.push(tempChar);
				number.push('(' + to_string(tempInt));
				signBrac++;
			}
			else if (tempChar == ')')
			{
				tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 3)];
				oper.push(tempChar);
				number.push(to_string(tempInt) + ')');
				signBrac--;
			}
			else {
				oper.push(tempChar);
				number.push(to_string(tempInt));
			}

			tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - len)];
			len = 0;
			if (tempChar == '.') {
				len = 1;
				i--;
			}
			if (!signBrac && tempChar == ')') {
				tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 2)];
			}

		}

		oper.pop();
		while (!oper.empty()) {
			FAP[n].append(number.front());
			number.pop();
			FAP[n].append(1, oper.front());
			oper.pop();
		}
		FAP[n].append(number.front());
		for (int i = signBrac; i > 0; --i) {
			FAP[n].append(1, ')');
		}
		FAP[n].append(1, '=');
	}
}

void generateProblems() {
    default_random_engine ran_num1;
    uniform_int_distribution<int> scopeInt(0, 10000);
    ran_num1.seed(time(0));
    FAP.clear(); // �����һ�εĽ��
    for (int n = 0; n < topicCount; ++n) {
        queue<string> number;
        queue<char> oper;
        char tempChar = '#';
        FAP.push_back(string());
        int signBrac = 0;
        for (int i = 0; i < howMany; ++i) {
            int tempInt = scopeInt(ran_num1) % maxNumber;
            if (tempChar == '(') {
                tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 3)];
                oper.push(tempChar);
                number.push('(' + to_string(tempInt));
                signBrac++;
            }
            else if (tempChar == ')') {
                tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 3)];
                oper.push(tempChar);
                number.push(to_string(tempInt) + ')');
                signBrac--;
            }
            else {
                oper.push(tempChar);
                number.push(to_string(tempInt));
            }

            tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 1)];
            if (signBrac == 0 && tempChar == ')') {
                tempChar = choiceOpe[scopeInt(ran_num1) % (choiceOpe.size() - 2)];
            }
        }
        oper.pop();
        while (!oper.empty()) {
            FAP[n].append(number.front());
            number.pop();
            FAP[n].append(1, oper.front());
            oper.pop();
        }
        FAP[n].append(number.front());
        for (int i = signBrac; i > 0; --i) {
            FAP[n].append(1, ')');
        }
        FAP[n].append(1, '=');
    }
}

void processInput(int tc, const string& ops, int maxNum, bool deci, bool drac, int hm) {
    topicCount = tc;
    choiceOpe = ops;
    maxNumber = maxNum;
    judgeDeci = deci;
    judgeDrac = drac;
    howMany = hm;

    if (judgeDrac) choiceOpe.append("()");
    if (judgeDeci) choiceOpe.append(1, '.');
    generateProblems();
}


extern void function();  // �������function()����
extern vector<string> FAP;  // ʹ���ⲿ��������ԭʼ�����еı���
extern int topicCount, maxNumber, howMany;
extern string choiceOpe;
extern bool judgeDeci, judgeDrac;

// ������
class ArithmeticTest : public ::testing::Test {
protected:
    void SetUp() override {
        // ��ʼ������
        FAP.clear();
        topicCount = 10;  // ������Ŀ����
        choiceOpe = "+-*/";  // ���������
        maxNumber = 100;  // �������������
        judgeDeci = false;  // �����Ƿ���С������
        judgeDrac = false;  // �����Ƿ��С����
        howMany = 2;  // ���ö��ٸ�����������
    }

    void TearDown() override {
        // ������
        FAP.clear();
    }
};

// ����function()�Ƿ�Ԥ�ڹ���
TEST_F(ArithmeticTest, GeneratesCorrectNumberOfProblems) {
    function();
    EXPECT_EQ(topicCount, FAP.size());  // ��֤������Ŀ�������Ƿ���ȷ
}

// ������Ӹ����������鲻ͬ��������Ϊ
TEST_F(ArithmeticTest, CorrectOperationFormat) {
    function();
    for (const auto& problem : FAP) {
        EXPECT_NE(problem.find('='), std::string::npos) << "Each problem should end with an '=' sign.";
    }
}

// ������
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


