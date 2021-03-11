/**
 * @file	AMG_Summer_Co_Production_2020\script\GameUIController.cpp.
 *
 * @brief	ÉQÅ[ÉÄÉÇÅ[ÉhÇÃUIÇä«óù
 */

#include"GameUIController.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

GameUIController::GameUIController()
{
}

GameUIController::~GameUIController()
{

}

void GameUIController::Process(Game& _game)
{
	m_playerUI.Process(_game);
}

void GameUIController::Draw(Game& _game)
{
	m_playerUI.Draw(_game);
}