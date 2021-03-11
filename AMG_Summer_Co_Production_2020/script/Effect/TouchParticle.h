/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchParticle.h.
 *
 * @brief	�^�b�`�Ń|�C���g���l���������Ƃ�\������G�t�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	TouchParticle
	 *
	 * @brief	�^�b�`�Ń|�C���g���l���������Ƃ�\������p�[�e�B�N���̃N���X
	 *
	 */
	class TouchParticle :
		public ObjectBase
	{
	public:
		/**
		 * @fn	TouchParticle::TouchParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
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
		TouchParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		~TouchParticle();

		/**
		 * @fn	virtual OBJECT_TYPE TouchParticle::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	virtual void TouchParticle::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void	Process(Game& _game);

		/**
		 * @fn	virtual void TouchParticle::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void	Draw(Game& _game) override;

		/**
		 * @fn	void TouchParticle::SetBright(int _r, int _g, int _b)
		 *
		 * @brief	�p�[�e�B�N���̕`��F���w��
		 *
		 * @param 	_r	 RED
		 * @param 	_g	 GREEN
		 * @param 	_b	 BLUE
		 */
		void SetBright(int _r, int _g, int _b) { _red = _r, _green = _g, _blue = _b; }

	private:
		int m_graph;	//!< �摜�n���h��
		double	_x, _y;		//!< ���W
		double	_vx, _vy;	//!< �ړ�����
		int		_cnt;   //!< ����J�E���^
		int _sizeratio; //!< �摜�̍ő�̑傫�����L�^
		int _red, _green, _blue;//!<RGB�p�ϐ�
	};
}