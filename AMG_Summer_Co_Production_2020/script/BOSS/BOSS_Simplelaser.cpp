/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Simplelaser.cpp.
 *
 * @brief	������݂̂̃��[�U�[�U������
 */

#include"BOSS.h"
#include"CrossLaser.h"
#include"../Game.h"
using namespace illumism;

void BOSS::SimpleLaser(Game& _game)
{
	if (once_flag)
	{
		PlaySE("resource/se/bossmotion.wav", _game);

		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//�\������
	if (m_frame_count - m_start_frame < 90)
		return;

	//20�b�ԍU��
	if (m_frame_count - m_start_frame < 60 * 20)
	{
		GenerateSimpleLaser(_game);
		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateSimpleLaser(Game& _game)
{
	int laser_count = 0;

	//��������Ă���I�u�W�F�N�g�̐��𐔂���
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::CROSSBEAM)
		{
			laser_count++;
		}
	}

	//���[�U�[����ʊO�ɓ��B���Ă���A���̃��[�U�[�𐶐�����
	if (laser_count < 1)
	{
		//�㉺���E���烉���_���ɐ���
		::CrossLaser* cross_laser = new ::CrossLaser(GetRand(3));
		cross_laser->SetSpeed(6 + GetRand(4));

		_game.m_objectserver.Add(cross_laser);
	}
}