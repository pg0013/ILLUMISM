/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Hit.cpp.
 *
 * @brief	�v���C���[�ɑ΂��铖���蔻�菈��
 */

#include"Player.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Hit(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			//�������g�Ɠ������Ă�������O
			if ((*iter) == this) { continue; }

			//���v���C���[�Ɠ����蔻��
			if (IsHit(*(*iter)) == true)
			{
				//����ɂ̂߂肱�܂Ȃ��悤�ɏ���
				if (m_x <= (*iter)->GetPosX())
				{
					//�X�e�[�W�E�[�ł̂��蔲���h�~
					if ((*iter)->GetPosX() >= STAGE_WIDTH_RIGHT - m_width)
					{
						m_x = (*iter)->GetPosX() + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w;
						return;
					}
					//����������o���A�����̍��W���X�V
					(*iter)->SetPosition(m_x - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w, (*iter)->GetPosY());
					m_x = (*iter)->GetPosX() + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w;
				}
				if (m_x > (*iter)->GetPosX())
				{
					//�X�e�[�W���[�ł̂��蔲���h�~
					if ((*iter)->GetPosX() <= STAGE_WIDTH_LEFT)
					{
						m_x = (*iter)->GetPosX() - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w;
						return;
					}
					//����������o���A�����̍��W���X�V
					(*iter)->SetPosition(m_x + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w, (*iter)->GetPosY());
					m_x = (*iter)->GetPosX() - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w;
				}
			}

			//ATTACK���ꂽ�瑊��Ƀ|�C���g�����Z���A���Z�|�C���g�����Z�b�g
			(*iter)->AddPOINT(-m_attacked_point);
			m_attacked_point = 0;
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::ATTACK)
		{
			if (IsHit(*(*iter)) == true)
			{
				//�_���[�W���󂯂Ă���Ƃ��͖���
				if (m_player_state != DAMAGE)
				{
					if (GetPOINT() >= -ATTACK_DAMAGE)//����|�C���g����������|�C���g��ݒ�
						m_attacked_point = ATTACK_DAMAGE;
					else
						m_attacked_point = 0;//�Ȃ�������|�C���g���Ƃ�Ȃ�
					AddPOINT(m_attacked_point);//�����̃|�C���g�����Z
					SetDamagedDirection(_game);
					Damage(_game);
					//�����ATTACK�����蔻�������
					(*iter)->Damage(_game);
				}
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BULLET_DAMAGE);
				SetDamagedDirection(_game);
				Damage(_game);
				//�e�ۂ�����
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::POINT)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddPOINT(10);
				PlaySE("resource/se/getpoint.wav", _game);
				//�^�b�`�I�u�W�F�N�g������
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::SPMOVE)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(SPMOVE_DAMAGE);
				if ((*iter)->GetDirection_x() == LEFT)
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::FALLATTACK)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BOSS_ATTACK_DAMAGE);
				if (m_x <= (*iter)->GetPosX() + (*iter)->GetPosHit_x() + (*iter)->GetPosHit_w() / 2)
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::CROSSBEAM)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BOSS_ATTACK_DAMAGE);
				if ((*iter)->GetPosX() > 0 && m_x + m_hit_x + m_hit_w / 2 <= (*iter)->GetPosX() + (*iter)->GetPosHit_x())
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else if ((*iter)->GetPosX() > 0 && m_x + m_hit_x + m_hit_w / 2 > (*iter)->GetPosX() + (*iter)->GetPosHit_x())
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
			}
		}
	}
}

void Player::SetDamagedDirection(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			//�������g�Ɠ������Ă�������O
			if ((*iter) == this) { continue; }

			//������U�����󂯂���E������
			if (m_x <= (*iter)->GetPosX())
			{
				m_turn_flag = FALSE;
				m_direction_x = RIGHT;
			}
			//������U�����󂯂��獶������
			if (m_x > (*iter)->GetPosX())
			{
				m_turn_flag = TRUE;
				m_direction_x = LEFT;
			}
		}
	}
}