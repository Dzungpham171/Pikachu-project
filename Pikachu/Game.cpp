﻿#include "Game.h"

Game::Game(int mode)
{
	_mode = mode;
	_x = LEFT, _y = TOP;
	board = new BoardView(_mode, LEFT, TOP);
	isPlaying = false;
	_lockedBlock = 0;
	_lockedBlockPair.clear();
	_remainBlocks = _mode * _mode;
}

Game::~Game() {
	delete board;
	board = nullptr;
}

void Game::startGame() 
{
	Controller::clearConsole();
	isPlaying = false;
	printInterface();
	_x = board->getXAt(0, 0);
	_y = board->getYAt(0, 0);
	Controller::gotoXY(_x, _y);
	board->selectedBlock(_x, _y);
	putchar(board->getPokemons(_x, _y));
	Controller::gotoXY(_x, _y);
	while (!isPlaying && _remainBlocks) {
		switch (Controller::getConsoleInput())
		{
		case 0:
			Controller::playSound(ERROR_SOUND);
			break;
		case 1:
			Controller::showCursor(false);
			Controller::setConsoleColor(BLACK, WHITE);
			Controller::clearConsole();
			return;
		case 2:
			moveUp();
			break;
		case 3:
			moveLeft();
			break;
		case 4:
			moveRight();
			break;
		case 5:
			moveDown();
			break;
		case 6:
			lockBlock();
			break;
		}
	}
	Controller::setConsoleColor(BLACK, WHITE);
	Controller::clearConsole();
	isPlaying = false;
	_remainBlocks = _mode * _mode;
}

void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x += 8;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
	
}

void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x -= 8;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveDown()
{
	if (_y < board->getYAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y += 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y -= 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::printInterface()
{
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::gotoXY(98, 28);
	cout << "Esc : Exit";
}

char Game::getPokemons(int x, int y)
{
	return board->getPokemons(x, y);
}

void Game::lockBlock()
{
	Controller::playSound(ENTER_SOUND);
	if (board->getCheck(_x, _y) == _LOCK || board->getCheck(_x, _y) == _DELETE) {
		return;
	}
	board->lockBlock(_x, _y);
	
	_lockedBlockPair.push_back(pair<int, int>(_x, _y));
	_lockedBlock++;

	if (_lockedBlock == 2) {
		deleteBlock();
	}
}

bool Game::checkMatchedPokemons(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	return (board->getPokemons(firstBlock.first, firstBlock.second) == board->getPokemons(secondBlock.first, secondBlock.second));
}

bool Game::checkIMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	// check line y -> check value of x
	if (firstBlock.second == secondBlock.second) {
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);
		for (int i = firstBlock.first + 8; i < secondBlock.first; i += 8) {
			if (board->getCheck(i, firstBlock.second) != _DELETE) {
				return 0;
			}
		}
		return 1;
	}
	// check line x -> check value of y
	if (firstBlock.first == secondBlock.first) {
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);
		for (int i = firstBlock.second + 4; i < secondBlock.second; i += 4) {
			if (board->getCheck(firstBlock.first, i) != _DELETE) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

bool Game::checkLMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Lcorner;
	Lcorner.first = firstBlock.first;
	Lcorner.second = secondBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(Lcorner, secondBlock) && checkIMatching(Lcorner, firstBlock))
			return 1;
	}
	
	Lcorner.first = secondBlock.first;
	Lcorner.second = firstBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(firstBlock, Lcorner) && checkIMatching(secondBlock, Lcorner))
			return 1;
	}
	return 0;
}
bool Game::checkUMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	return 0;
}
bool Game::checkZMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	return 0;
}

bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	if (!checkMatchedPokemons(firstBlock, secondBlock))
		return 0;
	if (checkIMatching(firstBlock, secondBlock))
		return 1;
	if (checkLMatching(firstBlock, secondBlock))
		return 1;
	return 0;
}
void Game::deleteBlock() {
	_lockedBlock = 0;
	if (!checkMatching(_lockedBlockPair[0], _lockedBlockPair[1])) {
		for (auto block : _lockedBlockPair)
			board->unselectedBlock(block.first, block.second);
		_lockedBlockPair.clear();
		board->selectedBlock(_x, _y);
		return;
	}

	_remainBlocks -= 2;
	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();
}

