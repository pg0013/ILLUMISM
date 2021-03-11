/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotLightHit.h.
 *
 * @brief	�X�|�b�g���C�g��~���̓����蔻��
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"

namespace illumism
{
	/**
 * @class	SpotLightHit
 *
 * @brief	�X�|�b�g���C�g�p�����蔻��N���X
 *
 */
	class SpotLightHit : public ObjectBase
	{
	public:
		SpotLightHit();
		~SpotLightHit();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SpotLightHit::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::SPOTLIGHT; }

		/**
		 * @fn	void SpotLightHit::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void SpotLightHit::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SpotLightHit::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void SpotLightHit::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SpotLightHit::SpotlightHitActivate(Game& _game, const int _startframe, const int _activetime);
		 *
		 * @brief	�X�|�b�g���C�g�p�w�莞�ԓ������蔻���L���ɂ���.
		 *
		 * @param [in,out]	_game	   	�Q�[���N���X�̎Q��
		 * @param 		  	_startframe	�����蔻���L���J�n����
		 * @param 		  	_activetime	�����蔻��L�����p�����鎞��
		 */
		void SpotlightHitActivate(Game& _game, const int _startframe, const int _activetime);
	};
}