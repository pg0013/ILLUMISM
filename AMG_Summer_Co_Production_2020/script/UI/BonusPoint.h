/**
 * @file	AMG_Summer_Co_Production_2020\script\BonusPoint.h.
 *
 * @brief	�X�R�A�{�[�i�X���[�h�Ń{�[�i�X�|�C���g��`�悷��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BonusPoint
  *
  * @brief	�{�[�i�X�|�C���g��`�悷��N���X
  *
  */
	class BonusPoint : public ObjectBase
	{
	public:
		/**
		 * @fn	BonusPoint::BonusPoint();
		 *
		 * @brief	Default constructor
		 * 				�p�����[�^��SetParam�Őݒ�
		 *
		 */
		BonusPoint();
		~BonusPoint();

		/**
		 * @fn	virtual OBJECT_TYPE BonusPoint::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	void BonusPoint::SetParam(const char* _filename, double x, double y, double vx, double vy, int cnt);
		 *
		 * @brief	�p�����[�^��ݒ�
		 * 				���I�ɐ������Ȃ��̂ŁA�R���X�g���N�^�ł͂Ȃ����̊֐��Ńp�����[�^��ݒ肷��
		 *
		 * @param 	_filename	�摜��
		 * @param 	x		 	x���W
		 * @param 	y		 	y���W
		 * @param 	vx		 	x�����̈ړ���
		 * @param 	vy		 	y�����̈ړ���
		 * @param 	cnt		 �G�t�F�N�g��������
		 */
		void SetParam(const char* _filename, double x, double y, double vx, double vy, int cnt);

		/**
		 * @fn	void BonusPoint::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BonusPoint::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

	public:
		int m_graph;	//!< �摜�n���h��
		double	_x, _y;		//!< ���W
		double	_vx, _vy;	//!< �ړ�����
		int		_cnt;   //!< ����J�E���^
	};
}