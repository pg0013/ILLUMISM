/**
 * @file	AMG_Summer_Co_Production_2020\script\Player.cpp
 *
 * @brief	プレイヤーに関する処理
 */

#include "Player.h"
#include"DxLib.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"../Utility/Utility.h"
#define _USE_MATH_DEFINES
#include<math.h>
using namespace illumism;

Player::Player(const int _num, const int _charatype)
{
	SetType(ObjectBase::OBJECT_TYPE::PLAYER);
	PLAYER_NUM = _num;
	m_player_num = _num;

	//プレイヤーごとに違うキャラクター画像の読み込み
	if (PLAYER_NUM == 1)
		LoadCharaGraph(_charatype);
	else if (PLAYER_NUM == 2)
		LoadCharaGraph(_charatype);

	Init();
}

Player::~Player()
{
	m_se.Pause();
	m_se.Destroy();
}

void Player::Init()
{
	m_width = BODY_W;
	m_height = BODY_H;

	//プレイヤーごとに初期位置と向きを設定
	if (PLAYER_NUM == 1)
	{
		m_x = 540;
		m_y = SCREEN_HEIGHT / 2;
		m_direction_x = RIGHT;
		m_turn_flag = false;
	}
	else if (PLAYER_NUM == 2)
	{
		m_x = 1365;
		m_y = SCREEN_HEIGHT / 2;
		m_direction_x = LEFT;
		m_turn_flag = true;
	}

	m_player_state = APPEAR;
	m_hit_no_count = 60;

	//プレイヤーのパラメータを初期化
	m_params.HP = 100;
	m_params.MP = 0;
	m_params.POINT = 0;

	m_speed = MOVE_SPEED;
	m_inertia = 0;

	//当たり判定位置を調整
	m_hit_x = -40;
	m_hit_y = -50;
	m_hit_w = 55;
	m_hit_h = 150;

	m_falling_speed = 0;

	m_bullet_frame_count = 0;
	m_respawn_time = 0;

	m_jump_frame = 0;
	m_attack_frame = -ANIM_FRAME;
	m_touch_frame = -ANIM_FRAME;
	m_damage_frame = 0;
	m_appeal_frame = 0;

	m_graph = m_wait_graph[0];
	m_animation_running_flag = false;

	m_ishit_flag = true;

	m_fly_time = FLY_TIME;
	m_fly_flag = false;
	m_fly_trigger_flag = false;
	m_fly_frame = 0;

	m_move_flag = false;
	m_pushRT_count = 0;
	m_RT_flag = false;
	m_oldRT_flag = false;

	//状態遷移用フラグ
	m_attack_flag = false;
	m_touch_flag = false;
	m_appeal_flag = false;
	m_spmove_flag = false;
	m_isAlive_flag = true;

	m_attacked_point = 0;

	m_combo = -1;
	m_max_combo = 0;
}

void Player::Process(Game& _game)
{
	ObjectBase::Process(_game);

	if (m_isAlive_flag)
	{
		Input(_game);
		State(_game);
		Hit(_game);
	}

	OffScreen();

	//リスポーン処理へ遷移
	if (m_params.HP <= 0)
	{
		m_player_state = RESPOWN;
		Respawn(_game);
	}

	ParamsProcess(_game);
	UpdatePlayerUI(_game);

	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	modeGame->m_camera.SetPlayerPosX(PLAYER_NUM - 1, m_x);
}

void Player::Input(Game& _game)
{
	/*
	* 以下の状態の時には、他の状態には遷移させない
	* 時間経過で状態遷移を行う
	*/
	if (m_player_state == DAMAGE ||
		m_player_state == APPEAR ||
		m_player_state == RESPOWN ||
		m_isAlive_flag == false)
		return;

	m_oldRT_flag = m_RT_flag;
	//Rトリガー入力検出用
	if (_game.m_xinput_state[PLAYER_NUM - 1].RightTrigger == 255)
		m_RT_flag = true;
	else
		m_RT_flag = false;

	/*
	* SHOOTとATTACKボタンを同時押しを禁止するため、同時押しされたらATTACKが優先
	* LT押しっぱなしでBボタンが押されたら、ATTACKが実行された後にSHOOTに戻る
	*/
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_3 &&
		m_appeal_flag == false &&
		m_attack_flag == false &&
		m_fly_flag == false &&
		m_spmove_flag == false)
		m_player_state = TOUCH;
	else if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_2 &&
		m_appeal_flag == false &&
		m_fly_flag == false &&
		m_spmove_flag == false &&
		m_touch_flag == false)
		m_player_state = ATTACK;
	else 	if (_game.m_xinput_state[PLAYER_NUM - 1].RightTrigger == 255 &&
		m_appeal_flag == false &&
		m_attack_flag == false &&
		m_fly_flag == false &&
		m_spmove_flag == false &&
		m_touch_flag == false)
		m_player_state = SHOOT;

	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_1 &&
		m_appeal_flag == false &&
		m_attack_flag == false &&
		m_fly_trigger_flag == false &&
		m_spmove_flag == false)
		m_player_state = JUMP;

	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_4 &&
		m_appeal_flag == false &&
		m_attack_flag == false &&
		m_fly_flag == false)
		m_player_state = SPMOVE;

	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_5 &&
		m_y + m_height == GROUND &&
		m_attack_flag == false &&
		m_spmove_flag == false)
		m_player_state = APPEAL;

	if (_game.m_xinput_state[PLAYER_NUM - 1].LeftTrigger == 255 &&
		m_appeal_flag == false &&
		m_attack_flag == false &&
		m_spmove_flag == false)
		m_player_state = FLY;
	else
	{
		//FLY状態出ないときにも飛行時間を回復する
		m_fly_frame--;
		if (m_fly_frame < 0)
		{
			m_fly_frame = 0;
			m_fly_time = FLY_TIME;
		}
		m_fly_flag = false;
	}

	//終了処理が行われず状態遷移した場合のためのフラグ初期化処理
	if (m_frame_count - m_touch_frame < 32 &&
		m_player_state != TOUCH)
	{
		m_touch_flag = false;
	}
}

void Player::State(Game& _game)
{
	switch (m_player_state)
	{
	case APPEAR:
		Appear(_game);
		break;
	case JUMP:
		Move(_game);
		Jump(_game);
		break;
	case SHOOT:
		Shoot(_game);
		Move(_game);
		Jump(_game);
		break;
	case ATTACK:
		Move(_game);
		Attack(_game);
		break;
	case SPMOVE:
		SPMove(_game);
		break;
	case TOUCH:
		Move(_game);
		Jump(_game);
		Touch(_game);
		break;
	case FLY:
		Move(_game);
		Fly(_game);
		break;
	case APPEAL:
		Appeal(_game);
		break;
	case DAMAGE:
		Damage(_game);
		break;
	}
}

void Player::UpdatePlayerUI(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

	//所持ポイント表示を更新
	modeGame->m_gameUI_controller.m_playerUI.m_pointUI.SetPoint(PLAYER_NUM, m_params.POINT);
	//hpゲージを更新
	modeGame->m_gameUI_controller.m_playerUI.m_hpbarUI.SetHP(PLAYER_NUM, m_params.HP);
	//必殺技ゲージ表示を更新
	modeGame->m_gameUI_controller.m_playerUI.m_spmoveUI.SetMP(PLAYER_NUM, m_params.MP);
	//飛行ゲージを更新
	modeGame->m_gameUI_controller.m_playerUI.m_flybarUI.SetFlyTime(PLAYER_NUM, m_fly_frame);
}

void Player::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//リスポーン中はプレイヤーを描画しない
	if (m_isAlive_flag == false)
		return;

	// 当たり判定カウンタがある場合は、点滅半透明にする
	if (m_hit_no_count > 0 && (m_frame_count / 4 % 2) == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	}

	//向きによって、キャラごとに位置調整
	if (m_turn_flag == true)
	{
		if (modeGame->GetPlayerCharactor(PLAYER_NUM) == NARI1 || modeGame->GetPlayerCharactor(PLAYER_NUM) == NARI2)
			DrawRotaGraph(x - 25, m_y + 25, 0.9, 0.0, m_graph, TRUE, FALSE);
		if (modeGame->GetPlayerCharactor(PLAYER_NUM) == NONAME1 || modeGame->GetPlayerCharactor(PLAYER_NUM) == NONAME2)
			DrawRotaGraph(x - 15, m_y + 25, 0.9, 0.0, m_graph, TRUE, FALSE);
	}
	else
	{
		if (modeGame->GetPlayerCharactor(PLAYER_NUM) == NARI1 || modeGame->GetPlayerCharactor(PLAYER_NUM) == NARI2)
			DrawRotaGraph(x, m_y + 25, 0.9, 0.0, m_graph, TRUE, TRUE);
		if (modeGame->GetPlayerCharactor(PLAYER_NUM) == NONAME1 || modeGame->GetPlayerCharactor(PLAYER_NUM) == NONAME2)
			DrawRotaGraph(x - 10, m_y + 25, 0.9, 0.0, m_graph, TRUE, TRUE);
	}

	//noname用タッチエフェクト
	if (m_noname_toucheffect[0] != 0 && m_touch_flag == true)
	{
		int frame = (m_frame_count - m_touch_frame) / 2;
		if (frame >= 13)
			frame = 13;
		if (m_turn_flag == true)//R
			DrawRotaGraph(x, m_y, 1.0, 0.0, m_noname_toucheffect[(frame / 2) % 7], TRUE, FALSE);
		else//L
			DrawRotaGraph(x, m_y, 1.0, 0.0, m_noname_toucheffect[(frame / 2) % 7], TRUE, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		//体の当たり判定
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

//画面外に出ないように処理
void Player::OffScreen()
{
	if (m_x < STAGE_WIDTH_LEFT) { m_x = STAGE_WIDTH_LEFT; }
	if (m_x + m_width > STAGE_WIDTH_RIGHT) { m_x = STAGE_WIDTH_RIGHT - m_width; }
	if (m_y < 0) { m_y = 0; }
	if (m_y + m_height > GROUND) { m_y = GROUND - m_height; }
}


void Player::ParamsProcess(Game& _game)
{
	if (m_params.HP <= 0)
		m_params.HP = 0;
	if (m_params.HP >= 100)
		m_params.HP = 100;

	if (m_params.MP >= MP_MAX)
		m_params.MP = MP_MAX;

	if (m_params.POINT <= 0)
		m_params.POINT = 0;

	//プレイヤーのポイントをゲームクラスで記録
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	modeGame->SetPlayerPoint(PLAYER_NUM, m_params.POINT);
}

void Player::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	if (m_player_num != _num)
		return;

	if (_turn_flag == true)
	{
		m_turn_flag = true;
		m_direction_x = LEFT;
	}
	else
	{
		m_turn_flag = false;
		m_direction_x = RIGHT;
	}
}

void Player::PlaySE(const char* _filename, Game& _game)
{
	m_se.Load(_filename);
	m_se.SetVolume(SE_VOLUME);
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_se.Pan(m_x + m_width / 2 - modeGame->m_camera.GetScreenX());
	m_se.PlayBackGround(m_se);
}

void Player::LoadCharaGraph(const int _charatype)
{
	switch (_charatype)
	{
	case NARI1:
		ResourceServer::LoadDivGraph("resource/player/nari_wait1.png", 30, 30, 1, 500, 500, m_wait_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dash1.png", 20, 20, 1, 500, 500, m_dash_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_jump1.png", 27, 27, 1, 500, 500, m_jump_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_attack1.png", 27, 27, 1, 500, 500, m_attack_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_touch1.png", 15, 15, 1, 500, 500, m_touch_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_horizontally1.png", 5, 5, 1, 500, 500, m_shoot_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_upward1.png", 5, 5, 1, 500, 500, m_shoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_diagonallyupward1.png", 5, 5, 1, 500, 500, m_shoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_diagonallydownward1.png", 5, 5, 1, 500, 500, m_shoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_horizontally1.png", 20, 20, 1, 500, 500, m_dashshoot_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_upward1.png", 20, 20, 1, 500, 500, m_dashshoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_diagonallyupward1.png", 20, 20, 1, 500, 500, m_dashshoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_diagonallydownward1.png", 20, 20, 1, 500, 500, m_dashshoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_appeal1.png", 40, 40, 1, 500, 500, m_appeal_graph);
		m_specialmove_graph = ResourceServer::LoadGraph("resource/player/nari_attack1.png");
		ResourceServer::LoadDivGraph("resource/player/nari_damage1.png", 15, 15, 1, 500, 500, m_damage_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_die1.png", 45, 45, 1, 500, 500, m_death_graph);
		m_lightball_graph = ResourceServer::LoadGraph("resource/player/trans.png");
		break;
	case NARI2:
		ResourceServer::LoadDivGraph("resource/player/nari_wait2.png", 30, 30, 1, 500, 500, m_wait_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dash2.png", 20, 20, 1, 500, 500, m_dash_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_jump2.png", 27, 27, 1, 500, 500, m_jump_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_attack2.png", 27, 27, 1, 500, 500, m_attack_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_touch2.png", 15, 15, 1, 500, 500, m_touch_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_horizontally2.png", 5, 5, 1, 500, 500, m_shoot_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_upward2.png", 5, 5, 1, 500, 500, m_shoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_diagonallyupward2.png", 5, 5, 1, 500, 500, m_shoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_shoot_diagonallydownward2.png", 5, 5, 1, 500, 500, m_shoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_horizontally2.png", 20, 20, 1, 500, 500, m_dashshoot_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_upward2.png", 20, 20, 1, 500, 500, m_dashshoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_diagonallyupward2.png", 20, 20, 1, 500, 500, m_dashshoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_dashshoot_diagonallydownward2.png", 20, 20, 1, 500, 500, m_dashshoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_appeal2.png", 40, 40, 1, 500, 500, m_appeal_graph);
		m_specialmove_graph = ResourceServer::LoadGraph("resource/player/nari_attack2.png");
		ResourceServer::LoadDivGraph("resource/player/nari_damage2.png", 15, 15, 1, 500, 500, m_damage_graph);
		ResourceServer::LoadDivGraph("resource/player/nari_die2.png", 45, 45, 1, 500, 500, m_death_graph);
		m_lightball_graph = ResourceServer::LoadGraph("resource/player/trans.png");
		break;
	case NONAME1:
		ResourceServer::LoadDivGraph("resource/player/noname_wait1.png", 30, 30, 1, 500, 500, m_wait_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dash1.png", 20, 20, 1, 500, 500, m_dash_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_jump1.png", 27, 27, 1, 500, 500, m_jump_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_attack1.png", 27, 27, 1, 500, 500, m_attack_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_touch1.png", 15, 15, 1, 500, 500, m_touch_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_horizontally1.png", 5, 5, 1, 500, 500, m_shoot_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_upward1.png", 5, 5, 1, 500, 500, m_shoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_diagonallyupward1.png", 5, 5, 1, 500, 500, m_shoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_diagonallydownward1.png", 5, 5, 1, 500, 500, m_shoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_horizontally1.png", 20, 20, 1, 500, 500, m_dashshoot_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_upward1.png", 20, 20, 1, 500, 500, m_dashshoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_diagonallyupward1.png", 20, 20, 1, 500, 500, m_dashshoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_diagonallydownward1.png", 20, 20, 1, 500, 500, m_dashshoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_appeal1.png", 40, 40, 1, 500, 500, m_appeal_graph);
		m_specialmove_graph = ResourceServer::LoadGraph("resource/player/noname_attack1.png");
		ResourceServer::LoadDivGraph("resource/player/noname_damage1.png", 15, 15, 1, 500, 500, m_damage_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_die1.png", 45, 45, 1, 500, 500, m_death_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_touch_effecthand.png", 7, 7, 1, 700, 700, m_noname_toucheffect);
		m_lightball_graph = ResourceServer::LoadGraph("resource/player/trans.png");
		break;
	case NONAME2:
		ResourceServer::LoadDivGraph("resource/player/noname_wait2.png", 30, 30, 1, 500, 500, m_wait_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dash2.png", 20, 20, 1, 500, 500, m_dash_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_jump2.png", 27, 27, 1, 500, 500, m_jump_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_attack2.png", 27, 27, 1, 500, 500, m_attack_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_touch2.png", 15, 15, 1, 500, 500, m_touch_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_horizontally2.png", 5, 5, 1, 500, 500, m_shoot_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_upward2.png", 5, 5, 1, 500, 500, m_shoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_diagonallyupward2.png", 5, 5, 1, 500, 500, m_shoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_shoot_diagonallydownward2.png", 5, 5, 1, 500, 500, m_shoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_horizontally2.png", 20, 20, 1, 500, 500, m_dashshoot_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_upward2.png", 20, 20, 1, 500, 500, m_dashshoot_up_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_diagonallyupward2.png", 20, 20, 1, 500, 500, m_dashshoot_upleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_dashshoot_diagonallydownward2.png", 20, 20, 1, 500, 500, m_dashshoot_downleft_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_appeal2.png", 40, 40, 1, 500, 500, m_appeal_graph);
		m_specialmove_graph = ResourceServer::LoadGraph("resource/player/noname_attack2.png");
		ResourceServer::LoadDivGraph("resource/player/noname_damage2.png", 15, 15, 1, 500, 500, m_damage_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_die2.png", 45, 45, 1, 500, 500, m_death_graph);
		ResourceServer::LoadDivGraph("resource/player/noname_touch_effecthand.png", 7, 7, 1, 700, 700, m_noname_toucheffect);
		m_lightball_graph = ResourceServer::LoadGraph("resource/player/trans.png");
		break;
	}
}