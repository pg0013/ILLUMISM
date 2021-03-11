/**
 * @file    LandingParticle.h
 * @brief  ���n�G�t�F�N�g�p�p�[�e�B�N��
 * 
 * @author Takuya Fujisawa
 * @date   2020/10/26
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	* @brief ���n�G�t�F�N�g�p�p�[�e�B�N���N���X
	*/
	class LandingParticle : public ObjectBase
	{
	public:
		/**
		 * @brief �R���X�g���N�^.
		 *
		 * @param _x				x���W
		 * @param _y				y���W
		 * @param _cnt				�o������
		 */
		LandingParticle(int _x, int _y, int _cnt);
		~LandingParticle();

		/**
		 * @fn	virtual OBJECT_TYPE GroundParticle::GetType()
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

	private:
		int m_landing_graph[10] = { 0 };
		int m_all_count;
	};
}