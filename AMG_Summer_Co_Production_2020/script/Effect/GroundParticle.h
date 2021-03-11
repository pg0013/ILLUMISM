/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundParticle.h.
 *
 * @brief	�{�X�̞����n�ʂ���˂��o���U����cation�\���G�t�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	  * @class	GroundParticle
	  *
	  * @brief	�{�X�̞����n�ʂ���˂��o���U����cation�\���G�t�F�N�g�N���X
	  *
	  */
	class GroundParticle : public ObjectBase
	{
	public:

		/**
		 * @fn	GroundParticle::GroundParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_filename	�摜��
		 * @param 	x		 	x���W
		 * @param 	y		 	y���W
		 * @param 	vx		 	x�����̈ړ���
		 * @param 	vy		 	y�����̈ړ���
		 * @param 	cnt		 �G�t�F�N�g��������
		 */
		GroundParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		~GroundParticle();

		/**
		 * @fn	virtual OBJECT_TYPE GroundParticle::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	virtual void GroundParticle::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void	Process(Game& _game);

		/**
		 * @fn	virtual void GroundParticle::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void	Draw(Game& _game) override;

	public:
		int m_graph;			//!< �摜�n���h��
		double	_x, _y;		//!< ���W
		double	_vx, _vy;	//!< �ړ�����
		int		_cnt;				//!< ����J�E���^
	};
}