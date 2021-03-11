/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Appeal.cpp.
 *
 *	@brief	�A�s�[���A�N�V�����̏����iLB�j
 */

#include"Player.h"
#include"../Effect/Particle.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Appeal(Game& _game)
{
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_5)
	{
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

		//�A�s�[�����͎��Ԍv�������Ȃ�
		if (m_appeal_flag == false)
		{
			//���͋Z�p�ɉ��������Ԃ��L�^
			modeGame->m_coopmove_controller.SetPushTime(PLAYER_NUM, GetNowCount());
			//�A�j���[�V�����J�n�t���[�����L�^
			m_appeal_frame = m_frame_count;
			m_move_flag = false;
		}

		for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
		{
			if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::SPOTLIGHT)
			{
				if (IsHit(*(*iter)) == false)
					break;

				AddPOINT(100);
				AddMP(50);
				//�X�|�b�g���C�g�̓����蔻�������
				(*iter)->Damage(_game);

				//�A�s�[�������G�t�F�N�g�𐶐�
				for (int i = 0; i < 100; i++)
				{
					double vx = (GetRand(12) - 6) / 10.0;
					double vy = -GetRand(25) / 10.0;

					Particle* particle = new Particle("resource/object/fly_test_13.png",
						m_x + 50, m_y + 210, vx, 1.5 * vy, 50);
					particle->SetBright(255, 255, 0);

					_game.m_objectserver.Add(particle);
				}
			}
		}
	}

	//�A�j���[�V������L�����ԓ��Ȃ��
	if (m_frame_count - m_appeal_frame < 80)
	{
		if (m_frame_count - m_appeal_frame == 0)
			PlaySE("resource/se/appeal.wav", _game);

		m_appeal_flag = true;
		m_player_state = APPEAL;
		m_animation_running_flag = true;
		m_graph = m_appeal_graph[((m_frame_count - m_appeal_frame) / 2 % 40)];
	}
	else
	{
		m_appeal_flag = false;
		m_animation_running_flag = false;	
		m_appeal_frame = 0;
		m_inertia = 0;

		//�����ꂽ���Ԃ̏�����
		//���Ԃ�0�ɂ��Ȃ��̂́A�����v�Z������Ƃ���0���Ɠ�����������ɂȂ��Ă��܂�����
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		modeGame->m_coopmove_controller.SetPushTime(PLAYER_NUM, (PLAYER_NUM - 1) * 999);

		m_player_state = JUMP;
	}
}