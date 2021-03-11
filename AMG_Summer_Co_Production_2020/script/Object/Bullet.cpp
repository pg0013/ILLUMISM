/**
 * @file	AMG_Summer_Co_Production_2020\script\Bullet.cpp.
 *
 * @brief	�v���C���[�����˂���e�ۃI�u�W�F�N�g�̃N���X
 */

#include "Bullet.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"
using namespace illumism;

Bullet::Bullet(int _num)
{
	//�e�v���C���[�ŐF�Ⴂ�̉摜��ǂݍ���
	if (_num == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/bullet_player1.png");
	if (_num == 2)
		m_graph = ResourceServer::LoadGraph("resource/object/bullet_player2.png");
	m_player_num = _num;
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_width = 100;
	m_height = 84;
	m_speed = BULLET_SPEED;
	m_direction_x = 0;
	m_direction_y = 0;
}

void Bullet::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//�΂ߕ����ł����x�����ɂ���
	if (m_direction_x != 0 && m_direction_y != 0)
		m_speed = BULLET_SPEED / static_cast<int>(sqrt(2));
	else
		m_speed = BULLET_SPEED;

	//�e���ړ�
	m_x += m_speed * m_direction_x;
	m_y += m_speed * m_direction_y;


	//��ʊO�ɏo����폜
	if (m_x < 0 || m_x + m_width > SCREEN_WIDTH ||
		m_y < 0 || m_y + m_height > GROUND)
	{
		_game.m_objectserver.Delete(this);
	}

	Hit(_game);
}

//���t���[���Ă΂��`�揈��
void Bullet::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//8�����Ɍ����邽�߂̉�]�A���]�A�`�揈��
	if (m_direction_x == RIGHT && m_direction_y == UP)
	{
		//�E��
		DrawRotaGraph3(x - 35, m_y + m_height / 2 - 80, 0, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 7 / 4, m_graph, TRUE, FALSE);
	}
	else if (m_direction_x == LEFT && m_direction_y == UP)
	{
		//����
		DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 - 80, m_width, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 1 / 4, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == RIGHT && m_direction_y == DOWN)
	{
		//�E��
		DrawRotaGraph3(x - 35, m_y + m_height / 2 + 80, 0, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 1 / 4, m_graph, TRUE, FALSE);
	}
	else if (m_direction_x == LEFT && m_direction_y == DOWN)
	{
		//����
		DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 + 80, m_width, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 7 / 4, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == LEFT)
	{
		//��
		DrawRotaGraph3(x, m_y + 5, 0, 0, 1.0f, 1.0f,
			0, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == RIGHT)
	{
		//�E
		DrawRotaGraph3(x, m_y + 5, 0, 0, 1.0f, 1.0f,
			0, m_graph, TRUE, FALSE);
	}
	else if (m_direction_y == UP)
	{
		if (m_turn_flag == true)
		{
			//������Ȃ��獶
			DrawRotaGraph3(x + 195, m_y + m_height - 170, 0, 0, 1.0f, 1.0f,
				DX_PI_F * 3 / 2, m_graph, TRUE, FALSE);
		}
		else
		{
			//������Ȃ���E
			DrawRotaGraph3(x - 165, m_y + m_height - 170, 0, 0, 1.0f, 1.0f,
				DX_PI_F * 3 / 2, m_graph, TRUE, FALSE);
		}
	}
	else if (m_direction_y == DOWN)
	{
		if (m_turn_flag == true)
		{
			//�������Ȃ��獶
			DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 + 80, m_width, m_height / 2, 1.0f, 1.0f,
				DX_PI_F * 7 / 4, m_graph, TRUE, TRUE);
		}
		else
		{
			//�������Ȃ���E
			DrawRotaGraph3(x - 35, m_y + m_height / 2 + 80, 0, m_height / 2, 1.0f, 1.0f,
				DX_PI_F * 1 / 4, m_graph, TRUE, FALSE);
		}
	}

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

void Bullet::Hit(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
		{
			//�������g�Ɠ������Ă�������O
			if ((*iter) == this) { continue; }

			if (IsHit(*(*iter)) == true)
			{
				//�e�̃_���[�W����
				Damage(_game);
				(*iter)->Damage(_game);
			}
		}
	}
}

void Bullet::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	if (_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//��
	{
		m_direction_y = UP;
		m_turn_flag = _turn_flag;
		if (m_turn_flag == true)//��
		{
			m_hit_x = 33 + 195;
			m_hit_y = -(m_width - m_height - 10) - 170;
		}
		else
		{
			m_hit_x = 33 - 165;
			m_hit_y = -(m_width - m_height - 10) - 170;
		}
		m_hit_w = 15;
		m_hit_h = 20;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//��
	{
		m_direction_y = DOWN;
		if (_turn_flag == true)
		{
			m_direction_x = LEFT;
			m_hit_x = m_width / 2 - 15 + 35;
			m_hit_y = m_height + 5 + 80;
		}
		else
		{
			m_direction_x = RIGHT;
			m_hit_x = m_width / 2 - 35;
			m_hit_y = m_height + 5 + 80;
		}
		m_hit_w = 15;
		m_hit_h = 20;
	}
	if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)//��
	{
		m_direction_x = LEFT;
		m_turn_flag = _turn_flag;

		m_hit_x = 11;
		m_hit_y = 33 + 5;
		m_hit_w = 20;
		m_hit_h = 15;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)//�E
	{
		m_direction_x = RIGHT;
		m_turn_flag = _turn_flag;

		m_hit_x = 68;
		m_hit_y = 33 + 5;
		m_hit_w = 20;
		m_hit_h = 15;
	}

	//�j���[�g������Ԃ̎��͉摜�̌����ɍ��킹�Ēe�̌��������߂�
	if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX == 0 &&
		_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX == 0)
	{
		if (_turn_flag == true)//�j���[�g������
		{
			m_direction_x = LEFT;
			m_turn_flag = _turn_flag;

			m_hit_x = 11;
			m_hit_y = 33 + 5;
			m_hit_w = 20;
			m_hit_h = 15;
		}
		else//�j���[�g�����E
		{
			m_direction_x = RIGHT;
			m_turn_flag = _turn_flag;

			m_hit_x = 68;
			m_hit_y = 33 + 5;
			m_hit_w = 20;
			m_hit_h = 15;
		}
	}

	if (m_direction_x == RIGHT && m_direction_y == UP)//�E��
	{
		m_hit_x = m_width / 2 - 3 - 35;
		m_hit_y = -m_height / 2 + 18 - 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == LEFT && m_direction_y == UP)//����
	{
		m_hit_x = m_width / 2 - 13 + 35;
		m_hit_y = -m_height / 2 + 18 - 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == RIGHT && m_direction_y == DOWN)//�E��
	{
		m_hit_x = m_width / 2 - 35;
		m_hit_y = m_height + 5 + 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == LEFT && m_direction_y == DOWN)//����
	{
		m_hit_x = m_width / 2 - 15 + 35;
		m_hit_y = m_height + 5 + 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
}

void Bullet::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}