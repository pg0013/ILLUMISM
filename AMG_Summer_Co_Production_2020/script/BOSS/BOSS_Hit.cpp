/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Hit.cpp.
 *
 * @brief	ƒvƒŒƒCƒ„[‚©‚ç‚ÌUŒ‚‚É‘Î‚·‚é“–‚½‚è”»’è
 */

#include"BOSS.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
using namespace illumism;

void BOSS::Hit(Game& _game)
{
	if (m_params.HP < 0)
		return;

	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		//ATTACK‚Ì“–‚½‚è”»’è
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::ATTACK)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(ATTACK_DAMAGE);
				modeGame->AddPlayerDamage((*iter)->GetPlayerNum(), -ATTACK_DAMAGE);

				Damage(_game);
				(*iter)->Damage(_game);
			}
		}

		//’eŠÛ‚Ì“–‚½‚è”»’è
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(-2);
				modeGame->AddPlayerDamage((*iter)->GetPlayerNum(), 2);

				Damage(_game);
				(*iter)->Damage(_game);
			}
		}

		//•KE‹Z‚Ì“–‚½‚è”»’è
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::SPMOVE)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(-2);
				modeGame->AddPlayerDamage((*iter)->GetPlayerNum(), 2);

				Damage(_game);
			}
		}

		//‹¦—Í‹Z‚Ì“–‚½‚è”»’è
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::COOP)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(-2);

				Damage(_game);
			}
		}
	}
}