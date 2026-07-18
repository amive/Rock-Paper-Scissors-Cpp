#include <iostream>
#include <Windows.h> // Delete this line and lines (122,126,130), If not on windows.
#include <cstdlib>
using namespace std;

// I'm Dumb for forgetting that Structures exist
enum enGameChoice { rock = 1, paper = 2, scissors = 3 };
enum enGameResult { win = 1, loss = 2, tie = 3 };

int readNum(string msg) {
	int num;
	cout << "\n\n" << msg;
	cin >> num;
	return num;
}

int randomNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}

int readRounds() {
	return readNum("Enter the number of rounds: ");
}

enGameChoice readPlayerChoice() {
	int choice;
	do {
		choice = readNum("Enter your choice (1:rock, 2:paper, 3:scissors): ");
	} while (choice != 1 && choice != 2 && choice != 3);

	switch (choice) {
	case 1:
		return enGameChoice::rock;
		break;
	case 2:
		return enGameChoice::paper;
		break;
	case 3:
		return enGameChoice::scissors;
		break;
	}
}

enGameChoice computerChoice() {
	return (enGameChoice) randomNum(1, 3);
}

void printChoice(enGameChoice choice) {
	switch (choice) {
	case enGameChoice::rock:
		cout << "Rock";
		break;
	case enGameChoice::paper:
		cout << "Paper";
		break;
	case enGameChoice::scissors:
		cout << "Scissors";
		break;
	}
}

enGameResult getWinner(enGameChoice playerChoice, enGameChoice computerChoice) {
	// Tie
	if (playerChoice == computerChoice) {
		return enGameResult::tie;
	}
	// Win
	if (playerChoice == enGameChoice::rock && computerChoice == enGameChoice::scissors) {
		return enGameResult::win;
	}
	else if (playerChoice == enGameChoice::paper && computerChoice == enGameChoice::rock) {
		return enGameResult::win;
	}
	else if (playerChoice == enGameChoice::scissors && computerChoice == enGameChoice::paper) {
		return enGameResult::win;
	}
	// Loss
	if (playerChoice == enGameChoice::scissors && computerChoice == enGameChoice::rock) {
		return enGameResult::loss;
	}
	else if (playerChoice == enGameChoice::rock && computerChoice == enGameChoice::paper) {
		return enGameResult::loss;
	}
	else if (playerChoice == enGameChoice::paper && computerChoice == enGameChoice::scissors) {
		return enGameResult::loss;
	}
}

void printRoundWinner(enGameResult gameResult) {
	if (gameResult == enGameResult::win) {
		cout << "\n\t*You Won The Round*";
	}
	else if (gameResult == enGameResult::loss) {
		cout << "\n\t*Computer Won The Round*";
	}
	else cout << "\n\t*Tie*";
}

int trackResults(enGameResult result, int rounds, enGameChoice playerChoice, enGameChoice ComputerChoice) {
	int winCount = 0, lossCount = 0, tieCount = 0;
	for (int i = 0; i < rounds;i++) {
		if (getWinner(playerChoice, ComputerChoice) == enGameResult::win) {
			winCount++;
		}
		else if (getWinner(playerChoice, ComputerChoice) == enGameResult::loss) {
			lossCount++;
		}
		else
			tieCount++;
	}
	if (result == enGameResult::win) {
		return winCount;
	}
	else if (result == enGameResult::loss) {
		return lossCount;
	}
	else return tieCount;
}

void executeWinEffect(enGameResult gameResult) {
	if (gameResult == enGameResult::win) {
		system("color 27");
		Beep(880, 200);
	}
	if (gameResult == enGameResult::loss) {
		system("color 47");
		Beep(440, 500);
	}
	if (gameResult == enGameResult::tie) {
		system("color 67");
		Beep(540, 330);
	}
}

void printFinalMessage(int wins, int losses, int ties) {
	if (wins > losses) {
		cout << "\n\t\t\t___________________________\n\n\t\t\tG A M E  O V E R ~ " << "YOU WIN\n\t\t\t___________________________";
		executeWinEffect(enGameResult::win);
		return;
	}
	if (losses > wins){
		cout << "\n\t\t\t___________________________\n\n\t\t\tG A M E  O V E R ~ " << "YOU LOSE\n\t\t\t___________________________";
		executeWinEffect(enGameResult::loss);
		return;
	}
	if (wins == 0 && losses == 0 || wins == losses) {
		cout << "\n\t\t\t________________________\n\n\t\t\tG A M E  O V E R ~ " << "TIE\n\t\t\t________________________";
		executeWinEffect(enGameResult::tie);
		return;
	}
}

void resetSettings() {
	system("color 07");
}

void reset() {
	resetSettings();
	system("cls");
}

bool repeatProgram() {
	char choice = 'n';
	cout << "\n\n Play again? (Y/n): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		return true;
	}
	else if (choice == 'N' || choice == 'n') {
		return false;
	}
	else {
		cout << "\n\nEnter (Y/n) only!\n";
		repeatProgram();
	}
}

void startGame() {
	int gameRounds = readRounds();
	int currentRound = 1;
	enGameResult GameResult;
	int wins = 0, losses = 0, ties = 0;
	cout << "\n\n------------------------Player VS Computer------------------------" << endl;
	for (int i = 1;i <= gameRounds;i++) {
		cout << "\n\n\n\t\t\t~[Round " << i << "]~";
		enGameChoice playerChoice = readPlayerChoice();
		enGameChoice ComputerChoice = computerChoice();
		GameResult = getWinner(playerChoice, ComputerChoice);

		wins += trackResults(enGameResult::win, currentRound, playerChoice, ComputerChoice);
		losses += trackResults(enGameResult::loss, currentRound, playerChoice, ComputerChoice);
		ties += trackResults(enGameResult::tie, currentRound, playerChoice, ComputerChoice);

		cout << "\n\t--------------------------------\n\tYour choice:  \t";
		printChoice(playerChoice);
		cout << "\n\t--------------------------------\n\tComputer's choice: ";
		printChoice(ComputerChoice);
		cout << "\n\t--------------------------------";
		printRoundWinner(GameResult);
		cout << endl;

		cout << "\n\tResults:\t" << wins << " W  " << losses << " L  " << ties << " T  \n";

		executeWinEffect(GameResult);
		resetSettings();
	}
	printFinalMessage(wins,losses,ties);
	if (repeatProgram()) {
		reset();
		startGame();
	}
}

int main()
{
	srand((unsigned)time(NULL));

	startGame();
}
