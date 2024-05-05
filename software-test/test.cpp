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
int topicCount = 0;//题目总数
string choiceOpe = "+";//运算符
int maxNumber = 0;//最大的运算结果
bool judgeDeci = 0;//是否有小数
bool judgeDrac = 0;//是否有括号
int howMany = 0;//多少个数参与运算
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
    FAP.clear(); // 清空上一次的结果
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


extern void function();  // 声明你的function()函数
extern vector<string> FAP;  // 使用外部声明访问原始代码中的变量
extern int topicCount, maxNumber, howMany;
extern string choiceOpe;
extern bool judgeDeci, judgeDrac;

// 测试类
class ArithmeticTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化环境
        FAP.clear();
        topicCount = 10;  // 设置题目总数
        choiceOpe = "+-*/";  // 设置运算符
        maxNumber = 100;  // 设置最大运算数
        judgeDeci = false;  // 设置是否有小数运算
        judgeDrac = false;  // 设置是否带小括号
        howMany = 2;  // 设置多少个数参与运算
    }

    void TearDown() override {
        // 清理工作
        FAP.clear();
    }
};

// 测试function()是否按预期工作
TEST_F(ArithmeticTest, GeneratesCorrectNumberOfProblems) {
    function();
    EXPECT_EQ(topicCount, FAP.size());  // 验证生成题目的数量是否正确
}

// 可以添加更多测试来检查不同参数的行为
TEST_F(ArithmeticTest, CorrectOperationFormat) {
    function();
    for (const auto& problem : FAP) {
        EXPECT_NE(problem.find('='), std::string::npos) << "Each problem should end with an '=' sign.";
    }
}

// 主函数
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


