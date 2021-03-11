/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS.h.
 *
 * @brief	�{�X�I�u�W�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"BOSS_CENTER.h"
#include"BOSS_LEFT.h"
#include"BOSS_RIGHT.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	class Game;	//<��d�C���N���[�h�h�~

/**
 * @class	BOSS
 *
 * @brief	�{�X�I�u�W�F�N�g�N���X
 *
 */
	class BOSS : public ObjectBase
	{
	public:
		BOSS();
		~BOSS();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @enum	BOSS_STATE
		 *
		 * @brief	�{�X�̏�ԑJ�ڗp�ϐ�
		 */
		enum BOSS_STATE
		{
			APPEAR, DEFAULT, MOVE, FALL_ATTACK, LASER_ATTACK, SIMPLE_LASER, GROUND_ATTACK, CROSS_LASER,
			DAMAGE, DESTROY
		};

		/**
		 * @fn	void BOSS::AddHP(int _damage)
		 *
		 * @brief	�_���[�W�ʂ�HP�ɉ��Z
		 *
		 * @param 	_damage	The damage.
		 */
		void AddHP(int _damage) { m_params.HP += _damage; }

		/**
		 * @fn	void BOSS::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS::Draw(Game& _game) override;
		 *
		 * @brief	�{�X��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS::Hit(Game& _game);
		 *
		 * @brief �����蔻��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void BOSS::Damage(Game& _game);
		 *
		 * @brief	�_���[�W���󂯂��Ƃ��Ƀ_���[�W�摜�֐؂�ւ�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void BOSS::Destroy(Game& _game);
		 *
		 * @brief	�{�X���j���̏���
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Destroy(Game& _game);

	private:
		/**
		 * @fn	void BOSS::State(Game& _game);
		 *
		 * @brief �{�X�̏�ԑJ��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void State(Game& _game);

		/**
		 * @fn	void BOSS::SelectNextAttack();
		 *
		 * @brief	�s���U����I�ԏ���
		 * @detail	���߂� FALL_ATTACK, LASER_ATTACK, SIMPLE_LASER, GROUND_ATTACK, CROSS_LASER
		 * 				�̏��ōU�����s���A���ׂĂ̍U�����s������O��̍U���ȊO��4�킩�烉���_���őI��
		 *
		 */
		void SelectNextAttack();

		/**
		 * @fn	void BOSS::Appear(Game& _game);
		 *
		 * @brief	�{�X�o������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Appear(Game& _game);

		/**
		 * @fn	void BOSS::Move(Game& _game);
		 *
		 * @brief	�{�X�ړ�����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Move(Game& _game);

		/**
		 * @fn	void BOSS::FallAttack(Game& _game);
		 *
		 * @brief�@�������̍U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void FallAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateFallAttack(Game& _game);
		 *
		 * @brief	�������̍U���𐶐�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GenerateFallAttack(Game& _game);

		/**
		 * @fn	void BOSS::GroundAttack(Game& _game);
		 *
		 * @brief	�n�ʂ��瞙�U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GroundAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateGroundAttack(Game& _game);
		 *
		 * @brief	���U���𐶐�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GenerateGroundAttack(Game& _game);

		/**
		 * @fn	void BOSS::SimpleLaser(Game& _game);
		 *
		 * @brief	������݂̂̃��[�U�[�U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void SimpleLaser(Game& _game);

		/**
		 * @fn	void BOSS::GenerateSimpleLaser(Game& _game);
		 *
		 * @brief	������̂݃��[�U�[�U���𐶐�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GenerateSimpleLaser(Game& _game);

		/**
		 * @fn	void BOSS::CrossLaser(Game& _game);
		 *
		 * @brief	�����������[�U�[�U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void CrossLaser(Game& _game);

		/**
		 * @fn	void BOSS::GenerateCrossLaser(Game& _game);
		 *
		 * @brief	�����������[�U�[�U���𐶐�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GenerateCrossLaser(Game& _game);

		/**
		 * @fn	void BOSS::LaserAttack(Game& _game);
		 *
		 * @brief	�v���C���[�Ɍ��������[�U�[�U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void LaserAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateLaserAttack(Game& _game);
		 *
		 * @brief	�v���C���[�Ɍ��������[�U�[�U���𐶐�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void GenerateLaserAttack(Game& _game);

		/**
		 * @fn	void BOSS::PlaySE(const char* _filename, const float _pan, Game& _game);
		 *
		 * @brief	���ʉ��Đ�
		 *
		 * @param 		  	_filename	�����t�@�C����
		 * @param 		  	_pan	 		���E�o�����X�ݒ�Ax���W������
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void PlaySE(const char* _filename, Game& _game);

		BOSS_CENTER m_center;   //!< �{�X�����p�[�c��`��
		BOSS_LEFT m_left;   //!< �{�X���p�[�c��`��
		BOSS_RIGHT m_right; //!< �{�X�E�p�[�c��`��

		sound::PlayWAVE m_se;  //!< ���ʉ�

	private:
		int m_boss_state;   //!< ��ԑJ�ڗp�ϐ�
		int m_pre_boss_state;   //!< �O��̏�ԑJ�ڂ��L�^

		int m_speed_x;  //!< �ړ����x
		int m_speed_y;

		bool once_flag; //!< ��ԑJ�ڈڍs���Ɉ�x�����s���鏉���������p�t���O
		bool once_death_flag;   //!< ���j���p�t���O
		bool attack_random_flag;	//!< �U���������_���ōs���t���O
		bool m_damage_flag; //!< �_���[�W���󂯂��Ƃ��̃t���O

		int m_start_frame;  //!< ��Ԉڍs���̃t���[�����L�^
		int m_damage_frame; //!< �_���[�W���󂯂��Ƃ��̃t���[�����L�^

		bool m_blinking_flag;   //!< �{�X���j���̓_�ŃJ�E���g�p�t���O
	};
}