/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObject.cpp
 *
 * @brief	�^�b�`�I�u�W�F�N�g�̃N���X
 */

#include "TouchObject.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

TouchObject::TouchObject(int _num)
{
	//2��ނ̌`��3��ނ̑傫������
	// �����蔻��A�������x�A�l���|�C���g��ݒ�
	if (_num == 1)
	{
		ResourceServer::LoadDivGraph("resource/object/note_circle_sheet_small.png", 5, 5, 1, 200, 200, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 20;
		m_hit_y = 20;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 12;
		m_params.POINT = 25;
		m_params.MP = 10;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_C;
	}
	else if (_num == 2)
	{
		ResourceServer::LoadDivGraph("resource/object/note_square_sheet_small.png", 5, 5, 1, 200, 200, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 20;
		m_hit_y = 20;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 12;
		m_params.POINT = 25;
		m_params.MP = 10;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_S;
	}
	else if (_num == 3 || _num == 4)
	{
		ResourceServer::LoadDivGraph("resource/object/note_circle_sheet_middle.png", 5, 5, 1, 220, 220, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 30;
		m_hit_y = 30;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 8;
		m_params.POINT = 20;
		m_params.MP = 5;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_C;
	}
	else if (_num == 5 || _num == 6)
	{
		ResourceServer::LoadDivGraph("resource/object/note_square_sheet_middle.png", 5, 5, 1, 220, 220, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 30;
		m_hit_y = 30;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 8;
		m_params.POINT = 20;
		m_params.MP = 5;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_S;
	}
	else if (_num == 7 || _num == 8 || _num == 9)
	{
		ResourceServer::LoadDivGraph("resource/object/note_circle_sheet_large.png", 5, 5, 1, 265, 265, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 40;
		m_hit_y = 40;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 5;
		m_params.POINT = 10;
		m_params.MP = 1;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_C;
	}
	else if (_num == 10 || _num == 11 || _num == 12)
	{
		ResourceServer::LoadDivGraph("resource/object/note_square_sheet_large.png", 5, 5, 1, 265, 265, m_anim_graph);
		m_graph = m_anim_graph[0];
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 40;
		m_hit_y = 40;
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_width - m_hit_x * 2;
		m_speed = 5;
		m_params.POINT = 10;
		m_params.MP = 1;
		m_type = ObjectBase::OBJECT_TYPE::TOUCH_S;
	}

	Init();
}

TouchObject::~TouchObject()
{
}

void TouchObject::Init()
{
	m_anim_frame = 0;
	m_damage_flag = false;
}

void TouchObject::Process(Game& _game)
{
	ObjectBase::Process(_game);

	m_y += m_speed;

	if (m_y > GROUND)
		_game.m_objectserver.Delete(this);
}

void TouchObject::Damage(Game& _game)
{
	//�A�j���[�V�������Đ����邽�߁A�����ɂ͍폜���������蔻��𖳌��ɂ���
	m_anim_frame = m_frame_count;
	m_damage_flag = true;
	m_type = ObjectBase::OBJECT_TYPE::NOHIT;
	m_speed = 1;
}

void TouchObject::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//�X�e�[�W��艺�͕`�悵�Ȃ�
	SetDrawArea(0, 0, SCREEN_WIDTH, GROUND + m_hit_h);

	//�^�b�`���ꂽ��A�j���[�V�����Đ�
	if (m_damage_flag)
	{
		if (m_frame_count - m_anim_frame < 20)
		{
			//���X�ɓ����ɂȂ�
			SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(216 - 10.8 * (static_cast<double>(m_frame_count) - static_cast<double>(m_anim_frame))));
			m_graph = m_anim_graph[((m_frame_count - m_anim_frame) / 4) % 5];
			DrawRotaGraph(x + m_width / 2, m_y + m_height / 2, 1.0 + 0.02 * (static_cast<double>(m_frame_count) - static_cast<double>(m_anim_frame)), 0, m_graph, TRUE);
		}
		else
		{
			_game.m_objectserver.Delete(this);
		}
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 216);
		DrawRotaGraph(x + m_width / 2, m_y + m_height / 2, 1.0, 0, m_graph, TRUE);
	}

	SetDrawArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


#ifdef _DEBUG
	if (m_type == ObjectBase::OBJECT_TYPE::TOUCH_S ||
		m_type == ObjectBase::OBJECT_TYPE::TOUCH_C)
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