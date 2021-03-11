/**
 * @file	AMG_Summer_Co_Production_2020\script\Spotlight.cpp.
 *
 * @brief	�Q�[���M�~�b�N�ł���X�|�b�g���C�g�̃N���X
 */

#include "Spotlight.h"
#include"SpotLightHit.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Spotlight::Spotlight(int _num, int move_time)
{
	//4��ނ̐F����I��
	if (_num == 0)
		m_graph = ResourceServer::LoadGraph("resource/object/spotlight_b_test.png");
	if (_num == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/spotlight_p_test.png");
	if (_num == 2)
		m_graph = ResourceServer::LoadGraph("resource/object/spotlight_g_test.png");
	if (_num == 3)
		m_graph = ResourceServer::LoadGraph("resource/object/spotlight_y_test.png");

	m_move_time = move_time;
	Init();
}

void Spotlight::Init()
{
	m_x = 0;
	m_y = 0;

	m_width = 480;
	m_height = 1212;

	m_speed = 8;
	m_move_x = 0;
}

Spotlight::~Spotlight()
{
}

void Spotlight::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//move_time�b�o�߂�����A�s�[���p�����蔻��𐶐�
	if (m_frame_count == 60 * m_move_time)
	{
		spotlight_hit = new SpotLightHit();
		spotlight_hit->SetPosition(m_x + m_width / 2 - spotlight_hit->GetWidth() / 2 + Move(),
			m_y + GROUND - 100);
		_game.m_objectserver.Add(spotlight_hit);
	}

	if (m_frame_count > 60 * m_move_time + 90)
		Damage(_game);
}

int Spotlight::Move()
{
	//m_movetime�b���E�ɃX�|�b�g���C�g���ړ�
	if (m_frame_count < 60 * m_move_time)
	{
		m_move_x += m_speed;
		if (m_move_x < -m_width)
			m_speed *= -1;
		if (m_move_x > m_width)
			m_speed *= -1;

		return m_move_x;
	}
	else
		return m_move_x;

}

void Spotlight::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 175);
	//���R�ό`�ŃX�|�b�g���C�g�̒��_���Œ肵�A�n�ʂɓ����镔�������ړ�������
	DrawModiGraph(x, m_y - 100, x + m_width, m_y - 100,
		x + m_width + Move(), GROUND + 275, x + Move(), GROUND + 275,
		m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Spotlight::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}