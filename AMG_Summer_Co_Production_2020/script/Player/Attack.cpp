/**
 * @file	AMG_Summer_Co_Production_2020\script\Attack.cpp.
 *
 * @brief	ATTACK用当たり判定のクラス
 */

#include "Attack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Attack::Attack(int _player_num)
{
	m_player_num = _player_num;
	Init();
}

Attack::~Attack()
{
}

void Attack::Init()
{
	m_x = 0;
	m_y = 0;

	m_width = 160;
	m_height = 25;

	m_hit_x = 0;
	m_hit_y = 0;
	m_hit_w = 0;
	m_hit_h = 0;
}

void Attack::Process(Game& _game)
{
	ObjectBase::Process(_game);

	AttackActivate(_game, 0, 5);
}

void Attack::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	//方向の設定
	if (_game.m_xinput_state[_num - 1].ThumbLX < 0)
	{
		m_direction_x = LEFT;
		m_turn_flag = true;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLX > 0)
	{
		m_direction_x = RIGHT;
		m_turn_flag = false;
	}

	//ニュートラル状態の時は画像の向きに合わせて弾の向きを決める
	if (_game.m_xinput_state[_num - 1].ThumbLX == 0 &&
		_game.m_xinput_state[_num - 1].ThumbLY == 0)
	{
		if (_turn_flag == true)
		{
			m_direction_x = LEFT;
			m_turn_flag = true;
		}
		else
		{
			m_direction_x = RIGHT;
			m_turn_flag = false;
		}
	}
}

void Attack::AttackActivate(Game& _game, const int _startframe, const int _activetime)
{
	auto elapsed_time = m_frame_count - _startframe;	//経過時間
	if (elapsed_time < 0)//遅延時間中は何もしない
	{
		return;
	}
	else if (elapsed_time < _activetime)
	{
		//ATTACK判定出現中
		m_hit_w = m_width;
		m_hit_h = m_height;
	}
	else
	{
		//有効時間を過ぎたら破棄
		Damage(_game);
	}

}

void Attack::Draw(Game& _game)
{
#ifdef _DEBUG
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		//攻撃の当たり判定
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h - 50,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

void Attack::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}