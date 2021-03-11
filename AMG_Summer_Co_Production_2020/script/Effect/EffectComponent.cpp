/**
 * @file	AMG_Summer_Co_Production_2020\script\EffectComponent.cpp
 *
 * @brief イージング
 *
 * @date 2020-06-28
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */

#include "EffectComponent.h"
#include "DxLib.h"
#include "easing.h"
using namespace utility;

EffectComponent::EffectComponent(
  bool active,
  int delay, int lifetime, int start_time,
  double value, double start, double stop,
  std::string type):
  _active{active},
  _delay{delay}, _lifetime{lifetime}, _start_time{start_time},
  _value{value}, _start{start}, _stop{stop},
  _easing(Easing::GetFunction(type))
{
}

void EffectComponent::SetParam(bool active, int delay, int lifetime, int start_time,
  double value, double start, double stop, std::string type)
{
  _active = active;
  _delay = delay; _lifetime = lifetime; _start_time = start_time;
  _value = value; _start = start; _stop = stop;
  _easing = Easing::GetFunction(type);
}

void EffectComponent::Update(int current)
{
  if (!_active)
  {
    return;
  }
  // 経過時間＝現在時刻－(開始時刻＋遅延時間)
  auto elapsed = current - (_start_time + _delay);
  if (elapsed < 0)
  {
    return; // ディレイ(遅延)中
  }

  if (elapsed < _lifetime)
  {
    _value = _easing(elapsed, _start, _stop - _start, _lifetime);
  }
  else
  {
    _value = _stop;
    _active = false;
  }
}
