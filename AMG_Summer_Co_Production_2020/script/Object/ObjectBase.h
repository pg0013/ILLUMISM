#pragma once
/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectBase.h.
 *
 * @brief	**�I�u�W�F�N�g�̊��N���X
 * @author	Takuya Fujisawa
 */

namespace illumism
{
	class Game;	//��d�C���N���[�h�h�~

	/**
	 * @class	ObjectBase
	 *
	 * @brief	�I�u�W�F�N�g�̊��N���X
	 *
	 */
	class ObjectBase
	{
	public:
		ObjectBase();
		~ObjectBase();

		/**
		 * @enum	OBJECT_TYPE
		 *
		 * @brief	�I�u�W�F�N�g�̎�ޗp�萔
		 */
		enum class OBJECT_TYPE
		{
			PLAYER, FLY, BULLET, TOUCH_S, TOUCH_C, COOP, POINT,
			NOHIT, UI, ATTACK, SPOTLIGHT, SPMOVE, PARTICLE,
			BOSS, FALLATTACK, GROUNDATTACK, CROSSBEAM, LASER
		};

		/**
		 * @fn	virtual OBJECT_TYPE ObjectBase::GetType() = 0;
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() = 0;

		/**
		 * @struct	PARAMS
		 *
		 * @brief	�v���C���[�p�p�����[�^
		 *
		 */
		struct PARAMS
		{
			int HP;
			int MP;
			int POINT;
		};

		/**
		 * @fn	void ObjectBase::AddHP(int _value)
		 *
		 * @brief	HP�ɉ��Z
		 *
		 * @param 	_value	�_���[�W��.
		 */
		void AddHP(int _value) { m_params.HP += _value; }

		/**
		 * @fn	void ObjectBase::AddMP(int _value)
		 *
		 * @brief	MP�ɒl�����Z
		 *
		 * @param 	_value	���Z����l
		 */
		void AddMP(int _value) { m_params.MP += _value; }

		/**
		 * @fn	void ObjectBase::AddPOINT(int _value)
		 *
		 * @brief	�|�C���g�����Z
		 *
		 * @param 	_value	���Z����l
		 */
		void AddPOINT(int _value) { m_params.POINT += _value; }

		/**
		 * @fn	int ObjectBase::GetHP()
		 *
		 * @brief	HP��Ԃ�
		 *
		 * @returns	The hp.
		 */
		int GetHP() { return m_params.HP; }

		/**
		 * @fn	int ObjectBase::GetMP()
		 *
		 * @brief	MP��Ԃ�
		 *
		 * @returns	The mp.
		 */
		int GetMP() { return m_params.MP; }

		/**
		 * @fn	int ObjectBase::GetPOINT()
		 *
		 * @brief	�����|�C���g����Ԃ�
		 *
		 * @returns	The point
		 */
		int GetPOINT() { return m_params.POINT; }

		/**
		 * @fn	virtual void ObjectBase::Init();
		 *
		 * @brief	����������
		 *
		 */
		virtual void Init();

		/**
		 * @fn	virtual void ObjectBase::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Process(Game& _game);

		/**
		 * @fn	virtual void ObjectBase::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Draw(Game& _game);

		/**
		 * @fn	virtual void ObjectBase::SetDirection(Game& _game, int _num, bool _turn_flag)
		 *
		 * @brief	�I�u�W�F�N�g�̕�����ݒ�
		 *
		 * @param [in,out]	_game	  	�Q�[���N���X�̎Q��
		 * @param 		  	_num	  		�v���C���[�ԍ�
		 * @param 		  	_turn_flag		�摜���]�t���O
		 */
		virtual void SetDirection(Game& _game, int _num, bool _turn_flag) {}

		/**
		 * @fn	virtual bool ObjectBase::IsHit(ObjectBase& _object);
		 *
		 * @brief	�I�u�W�F�N�g���m�̓����蔻�菈��
		 *
		 * @param [in,out]	_object	�I�u�W�F�N�g�x�[�X�̎Q��
		 *
		 * @returns	�����蔻��̉�
		 */
		virtual bool IsHit(ObjectBase& _object);

		/**
		 * @fn	virtual void ObjectBase::Damage(Game& _game)
		 *
		 * @brief	�I�u�W�F�N�g�̍폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Damage(Game& _game) {}

		/**
		 * @fn	inline void ObjectBase::SetPosition(int _x, int _y)
		 *
		 * @brief	���W��ݒ�
		 *
		 * @param 	_x		x���W
		 * @param 	_y		y���W
		 */
		inline void SetPosition(int _x, int _y) { m_x = _x; m_y = _y; }

		/**
		 * @fn	inline int ObjectBase::GetWidth()
		 *
		 * @brief	Gets the width
		 *
		 * @returns	The width.
		 */
		inline int GetWidth() { return m_width; }

		/**
		 * @fn	inline int ObjectBase::GetHeight()
		 *
		 * @brief	Gets the height
		 *
		 * @returns	The height.
		 */
		inline int GetHeight() { return m_height; }

		/**
		 * @fn	inline int ObjectBase::GetPosX()
		 *
		 * @brief	X���W��Ԃ�
		 *
		 * @returns	The position x coordinate.
		 */
		inline int  GetPosX() { return m_x; }

		/**
		 * @fn	inline int ObjectBase::GetPosY()
		 *
		 * @brief	Y���W��Ԃ�
		 *
		 * @returns	The position y coordinate.
		 */
		inline int  GetPosY() { return m_y; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_x()
		 *
		 * @brief	�����蔻��̍���x���W��Ԃ�
		 *
		 * @returns	The position hit x coordinate.
		 */
		inline int  GetPosHit_x() { return m_hit_x; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_y()
		 *
		 * @brief	�����蔻��̍���y���W��Ԃ�
		 *
		 * @returns	The position hit y coordinate.
		 */
		inline int  GetPosHit_y() { return m_hit_y; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_w()
		 *
		 * @brief	�����蔻��̕���Ԃ�
		 *
		 * @returns	�����蔻��̕�.
		 */
		inline int  GetPosHit_w() { return m_hit_w; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_h()
		 *
		 * @brief	�����蔻��̍�����Ԃ�
		 *
		 * @returns	�����蔻��̍���
		 */
		inline int  GetPosHit_h() { return m_hit_h; }

		/**
		 * @fn	inline int ObjectBase::GetHitNoCount()
		 *
		 * @brief	�����蔻�薳�����Ԃ�Ԃ�
		 *
		 * @returns	�����蔻�薳���J�E���^
		 */
		inline int GetHitNoCount() { return m_hit_no_count; }

		/**
		 * @fn	inline bool ObjectBase::GetIsHitFlag()
		 *
		 * @brief	�����蔻�肪�L�����Ԃ�
		 *
		 * @returns	�����蔻��L���t���O
		 */
		inline bool GetIsHitFlag() { return m_ishit_flag; }

		/**
		 * @fn	inline int ObjectBase::GetPlayerNum()
		 *
		 * @brief	�v���C���[�ԍ���Ԃ�
		 * @detail	�I�u�W�F�N�g���ǂ̃v���C���[�ɑ��������̂����ׂ邽��
		 *
		 * @returns	�v���C���[�ԍ�
		 */
		inline int GetPlayerNum() { return m_player_num; }

		/**
		 * @brief�@�I�u�W�F�N�g�̌�����Ԃ�.
		 * 
		 * @return �I�u�W�F�N�g�̌���
		 */
		inline int GetDirection_x() { return m_direction_x; }

	protected:
		PARAMS m_params;	//!<	�v���C���[�p�p�����[�^

		int m_graph;	//!< �`��p�O���t�B�b�N�n���h��
		int m_x, m_y;				//!<���W
		int m_width, m_height;	//!<���A����
		int m_speed;					//!<����

		//!<�����蔻��p���W
		int m_hit_x, m_hit_y;
		int m_hit_w, m_hit_h;

		int m_direction_x;  //!< ����
		int m_direction_y;

		bool m_turn_flag;   //!< �`�攽�]�t���O
		bool m_ishit_flag;  //!< �����蔻��L���t���O

		int m_frame_count;  //!< �t���[���J�E���^
		int m_hit_no_count; //!< ���G���ԃJ�E���^

		int m_player_num;   //!< player���Ƃ�boss�ɗ^�����_���[�W�L�^�p�ϐ�
	};
}