/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOverlay.cpp.
 *
 * @brief	画面遷移モード
 * 				キャプチャかフェードかを指定して画面遷移を行う
 * 				キャプチャでは、表示画面の上からオーバーレイ表示
 * 				フェードでは、画面を暗転させる
 */

#include "ModeOverlay.h"
#include "DxLib.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
using namespace illumism;

bool ModeOverlay::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	return true;
}

bool ModeOverlay::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	DeleteGraph(m_graph);

	return true;
}

void	ModeOverlay::Capture(int fadecnt)
{
	m_count = fadecnt;
	m_all = fadecnt;

	 //画面サイズと同じスクリーンの作成
	m_graph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	 //画面に表示されている画像の取り込み
	GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_graph);
}

void ModeOverlay::Fade(int fadecount, int fadetype)
{
	m_count = fadecount;
	m_all = fadecount;
	m_fade_type = fadetype;

	//画面サイズと同じスクリーンの作成
	m_graph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//黒画像の不透明度を調節して暗転を行う方法はうまくいかなかったので、
	//画面外から描画されていない部分をスクリーンとして切り取り、暗転用画像として使用している。
	GetDrawScreenGraph(2*SCREEN_WIDTH, 2*SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, m_graph);
}

bool ModeOverlay::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_count--;

	if (m_count <= 0)
		_game.m_modeserver->Del(this);

	return true;
}

bool ModeOverlay::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	// α値を計算
	int alpha;

	if (m_fade_type == FADE_IN)
		alpha = 255 * m_count / m_all;
	if(m_fade_type == FADE_OUT)
		alpha = 255- 255 * m_count / m_all;

	// 上に画面を被せる
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		// 半透明描画指定
	DrawGraph(0, 0, m_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

	return true;
}