/**
 * @file  EffectComponent.h
 * @brief �C�[�W���O
 *
 * @date 2020-06-28
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */

#pragma once
#include "easing.h"
#include <string>
#include	<unordered_map>

namespace utility
{
	class EffectComponent;
	using EffectComponentMap = std::unordered_map<std::string, EffectComponent>;

	/**
	 * @class	EffectComponent
	 *
	 * @brief	An effect component.
	 */
	class EffectComponent
	{
	public:

		/**
		 * @fn	EffectComponent::EffectComponent()
		 *
		 * @brief	Default constructor
		 * @detail	�f�t�H���g����Linear�Ő��`�⊮����
		 */
		EffectComponent() { _easing = Easing::GetFunction("Linear"); }

		/**
		 * @fn	EffectComponent::EffectComponent(bool active, int delay, int lifetime, int start_time, double value, double start, double stop, std::string type = "Linear" );
		 *
		 * @brief	Constructor
		 *
		 * @param active   ������
		 * @param delay    �x������
		 * @param lifetime ��������
		 * @param start_time �J�n����
		 * @param value    ���݂̒l
		 * @param start    �J�n�̒l
		 * @param stop	    �I���̒l
		 * @param type	  	�C�[�W���O�̎��
		 */
		EffectComponent(bool active,
			int delay, int lifetime, int start_time,
			double value, double start, double stop,
			std::string type = "Linear"
		);

		void Update(int current);

		/**
		 * @fn	void EffectComponent::SetParam(bool active, int delay, int lifetime, int start_time, double value, double start, double stop, std::string type);
		 *
		 * @brief	Sets a parameter
		 *
		 * @param active   ������
		 * @param delay    �x������
		 * @param lifetime ��������
		 * @param start_time �J�n����
		 * @param value    ���݂̒l
		 * @param start    �J�n�̒l
		 * @param stop	    �I���̒l
		 * @param type	  	�C�[�W���O�̎��
		 */
		void SetParam(bool active, int delay, int lifetime, int start_time,
			double value, double start, double stop, std::string type);

		/**
		 * @fn	void EffectComponent::ReStart(int current)
		 *
		 * @brief	Re start
		 *
		 * @param 	current	The current.
		 */
		void ReStart(int current)
		{
			_active = true;
			_start_time = current;
			_value = _start;
		}

		/**
		 * @fn	void EffectComponent::SetEasing(std::string type)
		 *
		 * @brief	Sets an easing
		 *
		 * @param 	type	The type.
		 */
		void SetEasing(std::string type) { _easing = Easing::GetFunction(type); }

		/**
		 * @fn	bool EffectComponent::IsActive() const
		 *
		 * @brief	Query if this object is active
		 *
		 * @returns	True if active, false if not.
		 */
		bool IsActive() const { return _active; }

		/**
		 * @fn	double EffectComponent::GetValue() const
		 *
		 * @brief	Gets the value
		 *
		 * @returns	The value.
		 */
		double GetValue() const { return _value; }

	private:
		Param _easing;
		bool _active;   //!< ������
		int _delay; //!< �x��
		int _lifetime;  //!< ��������
		int _start_time;	//!< �J�n����

		double _value;  //!< ���݂̒l
		double _start;  //!< �J�n�̒l
		double _stop;   //!< �I���̒l
	};
}