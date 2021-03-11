/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectBase.cpp.
 *
 * @brief	�Q�[�����̃I�u�W�F�N�g�̊��N���X
 */

#include "ObjectBase.h"
#include"DxLib.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
using namespace illumism;

ObjectBase::ObjectBase()
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	m_frame_count = 0;
	m_hit_no_count = 0;
	m_player_num = 0;
}

void ObjectBase::Process(Game& _game)
{
	if (m_hit_no_count > 0)
		m_hit_no_count--;

	m_frame_count++;
}

void ObjectBase::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//�摜�̌����𔽓]����
	if (m_turn_flag == true)
		DrawTurnGraph(x, m_y, m_graph, TRUE);
	else
		DrawGraph(x, m_y, m_graph, TRUE);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//�J���p�����蔻��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�`�惂�[�h�𔼓����`��ɃZ�b�g
		//�̂̓����蔻��
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�s�����`��ɖ߂�
	}
#endif // _DEBUG
}

bool ObjectBase::IsHit(ObjectBase& _object)
{
	if (m_ishit_flag)
	{
		if (m_x + m_hit_x < _object.m_x + _object.m_hit_x + _object.m_hit_w &&		//����x���W��r
			_object.m_x + _object.m_hit_x < m_x + m_hit_x + m_hit_w &&					//�E��x���W��r
			m_y + m_hit_y < _object.m_y + _object.m_hit_y + _object.m_hit_h &&		//����y���W��r
			_object.m_y + _object.m_hit_y < m_y + m_hit_y + m_hit_h						//�E��y���W��r
			&& m_hit_no_count == 0 && _object.m_hit_no_count == 0)						//���G���Ԃ��������m�F
			return true;
	}
	return false;
}