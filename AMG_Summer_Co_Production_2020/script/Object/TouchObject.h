/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObject.h.
 *
 * @brief	��ʏォ��~���Ă���^�b�`�I�u�W�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
  * @class	TouchObject
  *
  * @brief	�^�b�`�I�u�W�F�N�g�̃N���X
  *
  */
	class TouchObject : public ObjectBase
	{
	public:

		/**
		 * @fn	TouchObject::TouchObject(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	�^�b�`�I�u�W�F�N�g�̎��
		 */
		TouchObject(int _num);
		~TouchObject();

		/**
		 * @fn	virtual OBJECT_TYPE TouchObject::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return m_type; }

		/**
		 * @fn	void TouchObject::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void TouchObject::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void TouchObject::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g�̍폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void TouchObject::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

	private:
		ObjectBase::OBJECT_TYPE m_type; //!< �I�u�W�F�N�g�̃^�C�v��ݒ�

		const int BODY_W = 220; //!< �I�u�W�F�N�g�T�C�Y
		const int BODY_H = 220;
		int m_anim_frame;   //!< �A�j���[�V�����J�n�t���[�����L�^
		int m_anim_graph[5];	//!<�摜�n���h��
		bool m_damage_flag; //!<	�^�b�`���ꂽ���̉ۗp�t���O
	};
}