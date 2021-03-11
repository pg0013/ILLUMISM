/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveController.cpp.
 *
 * @brief	���͋Z�����Ŕ�������SPMoveObject���Ǘ�����N���X
 * 				�e�v���C���[��LB�����������Ԃ̍�����500ms�ȓ��̎��ɋ��͋Z�𐶐�
 */

#include"CoopMoveController.h"
#include"../Object/CoopMoveObject.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

CoopMoveController::CoopMoveController()
{
	//������500�ɂȂ�Ȃ��悤�ɏ�����
	for (int i = 0; i < 2; i++)
		m_pushtime[i] = 999 * i;
	m_difftime = 999;
}

CoopMoveController::~CoopMoveController()
{
}

void CoopMoveController::Process(Game& _game)
{
	int coop_count = 0;

	//��������Ă���COOP�I�u�W�F�N�g�̐��𐔂���
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::COOP)
		{
			coop_count++;
		}
	}

	//���͋Z�͉�ʂ�1�����`�悳��Ȃ�
	if (coop_count < 1)
	{
		//�v���C���[��LB�����������Ԃ̍����𒲂ׂ�
		SetDiffTime(m_pushtime);

		//500ms�ȓ��ŋ��͋Z�𐶐�
		if (m_difftime >= 0 && m_difftime <= 500)
		{
			CoopMoveObject* coop_object = new CoopMoveObject();
			_game.m_objectserver.Insert(coop_object);

			//������500�ɂȂ�Ȃ��悤�ɏ�����
			for (int i = 0; i < 2; i++)
				m_pushtime[i] = 999 * i;
		}
	}
}

void CoopMoveController::SetPushTime(int _num, int _frame)
{
	m_pushtime[_num - 1] = _frame;
}

void CoopMoveController::SetDiffTime(int _pushtime[2])
{
	m_difftime = abs(_pushtime[0] - _pushtime[1]);
}