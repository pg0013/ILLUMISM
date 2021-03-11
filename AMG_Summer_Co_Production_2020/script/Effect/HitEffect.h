/**
 * @file    HitEffect.h
 * @brief  �q�b�g�G�t�F�N�g�N���X
 *
 * @author Takuya Fujisawa
 * @date   2020/11/05
 */

#pragma once
#include"../Object/ObjectBase.h"

//�L�����N�^�[�̃G�t�F�N�g�ʒu���ߗp�萔
namespace
{
	constexpr int  NARI_OFFSET_LEFT = -80;
	constexpr int  NARI_OFFSET_RIGHT = -25;
	constexpr int  NONAME_OFFSET_LEFT = -45;
	constexpr int  NONAME_OFFSET_RIGHT = -55;
}

namespace illumism
{
	/**
	 * @brief �q�b�g�G�t�F�N�g
	 */
	class HitEffect : public ObjectBase
	{
	public:
		/**
		 * @brief�@ �R���X�g���N�^
		 *
		 * @param  _x	x���W
		 * @param  _y	y���W
		 * @param  _cnt	�����t���[����
		 */
		HitEffect(int _x, int _y, int _cnt);
		~HitEffect();

		/**
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @brief�@���Z����.
		 *
		 * @param _game�@�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @brief�@�`�揈��.
		 *
		 * @param _game�@�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

		/**
		 * @brief�@ �L�����N�^�[���Ƃ̈ʒu����
		 *
		 * @param  _charactor_type�@�L�����N�^�[�̎��
		 * @param  _direction	����
		 */
		void SetPositionOffset(int _charactor_type, int _direction);

	private:
		int m_hiteffect_graph[8] = { 0 };//!<�摜�n���h��
		int m_all_count;//!<�o������
	};
}