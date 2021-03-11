/**
 * @file	AMG_Summer_Co_Production_2020\script\Particle.h.
 *
 * @brief	�G�t�F�N�g�p�p�[�e�B�N��
 * @author	Takuya Fujisawa
 */

#pragma once
#include"../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Particle
	 *
	 * @brief	�p�[�e�B�N���N���X
	 *
	 */
	class Particle :public ObjectBase
	{
	public:

		/**
		 * @fn	Particle::Particle(const char* _filename, double x, double y, double vx, double vy, int cnt);
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
		Particle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		~Particle();

		/**
		 * @fn	virtual OBJECT_TYPE Particle::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	virtual void Particle::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Process(Game& _game);

		/**
		 * @fn	virtual void Particle::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Draw(Game& _game) override;

		/**
		 * @fn	void Particle::SetBright(int _r, int _g, int _b)
		 *
		 * @brief	�p�[�e�B�N���̕`��F���w��
		 *
		 * @param 	_r	 RED
		 * @param 	_g	 GREEN
		 * @param 	_b	 BLUE
		 */
		void SetBright(int _r, int _g, int _b) { _red = _r, _green = _g, _blue = _b; }

	public:
		int m_graph[2]; //!< �摜�n���h��
		double	_x, _y;		//!<���W
		double	_vx, _vy;	//!< �ړ�����
		int		_cnt;   //!< ����J�E���^
		int _sizeratio; //!< �摜�̍ő�̑傫�����L�^
		int _red, _green, _blue;//!<RGB�p�ϐ�
	};
}