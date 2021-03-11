/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundAttack.cpp.
 *
 * @brief	�n�ʂ���˂��o���U������
 */

#include "GroundAttack.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"../Effect/GroundParticle.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"
using namespace illumism;

GroundAttack::GroundAttack(int _x, int _y, int _angle, int _type)
{
	m_x = _x;
	m_y = _y;
	m_angle = _angle;

	//3��ނ���I��
	if (_type == 0)
		m_graph = ResourceServer::LoadGraph("resource/object/groundattack_p.png");
	else if (_type == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/groundattack_b.png");
	else
		m_graph = ResourceServer::LoadGraph("resource/object/groundattack_g.png");

	GetGraphSize(m_graph, &m_width, &m_height);
	Init();
}

GroundAttack::~GroundAttack()
{

}

void GroundAttack::Init()
{
	vector_x = cosf(DX_PI_F / 180.0f * (90.0f - m_angle));
	vector_y = sinf(DX_PI_F / 180.0f * (90.0f - m_angle));

	m_speed_x = static_cast<int>(25 * vector_x);
	m_speed_y = static_cast<int>(25 * vector_y);

	m_stop_count = 40;
	hit_circle_num = 0;
}

void GroundAttack::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//�͂��߂Ɍx����\������
	if (m_frame_count == 45)
	{
		GroundParticle* particle = new GroundParticle("resource/object/caution.png",
			static_cast<double>(m_x + m_speed_x * 60.0), static_cast<double>(m_y - m_speed_y * 60.0), 0, 0, 45);
		_game.m_objectserver.Add(particle);
	}

	//30�t���[���o�߂����瞙�������Ă���U��
	if (m_frame_count > 105)
	{
		m_x += m_speed_x;
		m_y -= m_speed_y;

		//�~�̓����蔻����Ԋu�Ŕz�u���ړ�
		for (int i = 0; i < 5; i++)
		{
			hit_r[i] = 110 - 10 * (i + 1);
			hit_cx[i] = m_x - static_cast<int>(20 - (400 - 100 * i) * vector_x);
			hit_cy[i] = m_y + static_cast<int>((400 - 100 * i) * vector_y);
		}
		for (int i = 0; i < 13; i++)
		{
			hit_r[5 + i] = 60 - 5 * (i + 1);
			hit_cx[5 + i] = m_x - static_cast<int>(20 + ((85 - 2 * i) * (i + 1)) * vector_x);
			hit_cy[5 + i] = m_y - static_cast<int>(((85 - 2 * i) * (i + 1)) * vector_y);
		}

		Hit(_game);

		SwitchDirection();
	}
}

void GroundAttack::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//�v���C���[�̑�����艺�͕`�悵�Ȃ�
	SetDrawArea(0, 0, SCREEN_WIDTH, GROUND + 25);
	DrawRotaGraph(x, m_y, 1.0, M_PI / 180.0 * m_angle, m_graph, TRUE);
	SetDrawArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//�J���p�����蔻��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�`�惂�[�h�𔼓����`��ɃZ�b�g
		for (int i = 0; i < 18; i++)
			DrawCircle(hit_cx[i] - modeGame->m_camera.GetScreenX(), hit_cy[i], hit_r[i], GetColor(255, 0, 0), TRUE);
		DrawCircle(x - 20, m_y, 10, GetColor(0, 0, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�s�����`��ɖ߂�
}
#endif // _DEBUG
}

void GroundAttack::SwitchDirection()
{
	if (m_y - m_height / 2 < 0)
	{
		//�����L�т�������A40�t���[���Î~����
		if (m_stop_count > 0)
		{
			m_stop_count--;
			m_speed_x = 0;
			m_speed_y = 0;

			return;
		}

		m_speed_x = static_cast<int>(15 * vector_x);
		m_speed_y = static_cast<int>(15 * vector_y);

		//�����������߂�
		m_speed_x *= -1;
		m_speed_y *= -1;
	}
}

void GroundAttack::Hit(Game& _game)
{
	//�����蔻��
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		//�v���C���[�̓����蔻��
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			if (IsHitToCircle(*(*iter)) == true)
			{
				(*iter)->AddHP(-10);
				if (hit_cx[hit_circle_num] < (*iter)->GetPosX() + GetPosHit_x())
					(*iter)->SetDirection(_game, (*iter)->GetPlayerNum(), TRUE);
				else
					(*iter)->SetDirection(_game, (*iter)->GetPlayerNum(), FALSE);
				(*iter)->Damage(_game);
			}
		}
	}
}

//�~�Ǝl�p�̓����蔻��
bool GroundAttack::IsHitToCircle(ObjectBase& _object)
{
	if (_object.GetHitNoCount() != 0)
		return false;

	if (_object.GetIsHitFlag())
	{
		for (int i = 0; i < 18; i++)
		{
			//�~�Ǝl�p�`�̓����蔻��
			//�~�̒��S���l�p�`�̏㉺�̔��a���ɂ���
			if (hit_cx[i] > _object.GetPosX() + _object.GetPosHit_x() &&
				hit_cx[i] < _object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() &&
				hit_cy[i] > _object.GetPosY() + _object.GetPosHit_y() - hit_r[i] &&
				hit_cy[i] < _object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() + hit_r[i])
			{
				hit_circle_num = i;
				return true;
			}

			//�~�̒��S���l�p�`�̍��E�̔��a���ɂ���
			if (hit_cx[i] > _object.GetPosX() + _object.GetPosHit_x() - hit_r[i] &&
				hit_cx[i] < _object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() + hit_r[i] &&
				hit_cy[i] > _object.GetPosY() + _object.GetPosHit_y() &&
				hit_cy[i] < _object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h())
			{
				hit_circle_num = i;
				return true;
			}

			//�~�̒��S���l�p�`�̊p�ɂ���
			if (pow((_object.GetPosX() + _object.GetPosHit_x() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() - hit_cy[i]), 2) < pow(hit_r[i], 2))
			{
				hit_circle_num = i;
				return true;
			}
		}
	}
	return false;
}