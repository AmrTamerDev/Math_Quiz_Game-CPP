#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4 };
enum enOperationType { AddOp = 1, SubOp = 2, MulOp = 3, DivOp = 4, MixOp = 5 };

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool isPass = false;
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

short ReadHowManyQuestions()
{
	int NumberOfQuestions = 0;
	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 100);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

int SimpleColculator(short Number1, short Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::AddOp:
		return Number1 + Number2;
	case enOperationType::SubOp:
		return Number1 - Number2;
	case enOperationType::MulOp:
		return Number1 * Number2;
	case enOperationType::DivOp:
		return (Number2 != 0) ? (Number1 / Number2) : 0;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (OpType == enOperationType::MixOp)
	{
		OpType = (enOperationType)RandomNumber(1, 4);
	}
	if (QuestionLevel == enQuestionsLevel::MixLevel)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	Question.QuestionLevel = QuestionLevel;
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleColculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleColculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleColculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{

	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::AddOp:
		return "+";
	case enOperationType::SubOp:
		return "-";
	case enOperationType::MulOp:
		return "*";
	case enOperationType::DivOp:
		return "/";
	default:
		return "Mix";
	}

}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "__________\n";
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswer++;
		cout << "Right Answer :-)\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
		Quizz.NumberOfWrongAnswer++;
	}
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Mid", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n___________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n___________________________\n\n";
	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level     : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answer: " << Quizz.NumberOfWrongAnswer << endl;
	cout << "___________________________\n";
	SetScreenColor(Quizz.isPass);
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do you want to play again? Y or N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}