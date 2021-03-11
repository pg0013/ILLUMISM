/**
 * @file	AMG_Summer_Co_Production_2020\script\GameSign.h.
 *
 * @brief	�Q�[���J�E���g��READY?�Ȃǂ�\������p�[�e�B�N��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	GameSign
	 *
	 * @brief	�C���Q�[�����̕W����`�悷��N���X
	 */
	class GameSign :
		public ObjectBase
	{
	public:
		/**
		 * @fn	GameSign::GameSign(const char* _filename, int _x, int _y, int _cnt);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_filename	�摜��
		 * @param 	_x		 	x���W
		 * @param 	_y		 	y���W
		 * @param 	_cnt	 	�摜��`�悷�鎞��
		 */
		GameSign(const char* _filename, int _x, int _y, int _cnt);
		~GameSign();

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

	private:
		int m_count;	//!< �摜�\���J�E���^
	};
}