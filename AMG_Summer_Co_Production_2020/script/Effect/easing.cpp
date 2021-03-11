/**
 * @file  easing.cpp
 * @brief イージング
 *
 * @date 2020-06-28
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */
 #define _USE_MATH_DEFINES
 #include <cmath>
#include "easing.h"
using namespace utility;

 /**	@brief イージング
  *
  *	@param t カレントタイム
  *	@param b 開始値
  *	@param c 全体の変化量
  *	@param d デュレーション
  *	@return  計算結果
  */
const EasingMap Easing::_type = {
	{ "Linear",
		[](double t, double b, double c, double d) {
			return c * t / d + b;
		}
	},
	{ "InQuad",
		[](double t, double b, double c, double d) {
			t /= d;
			return c * t * t + b;
		}
	},
	{ "OutQuad",
		[](double t, double b, double c, double d) {
			t /= d;
			return -c * t * (t - 2) + b;
		}
	},
  { "InOutQuad",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return c / 2.0 * t * t + b;
      }
      t--;
      return -c / 2.0 * (t * (t - 2) - 1) + b;
    }
  },
  { "InCubic",
    [](double t, double b, double c, double d) {
      t /= d;
      return c * t * t * t + b;
    }
  },
  { "OutCubic",
    [](double t, double b, double c, double d) {
      t /= d;
      t--;
      return c * (t * t * t + 1) + b;
    }
  },
  { "InOutCubic",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return c / 2.0 * t * t * t + b;
      }
      t -= 2;
      return c / 2.0 * (t * t * t + 2) + b;
    }
  },
  { "InQuart",
    [](double t, double b, double c, double d) {
      t /= d;
      return c * t * t * t * t + b;
    }
  },
  { "OutQuart",
    [](double t, double b, double c, double d) {
      t /= d;
      t--;
      return -c * (t * t * t * t - 1) + b;
    }
  },
  { "InOutQuart",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return c / 2.0 * t * t * t * t + b;
      }
      t -= 2;
      return -c / 2.0 * (t * t * t * t - 2) + b;
    }
  },
  { "InQuint",
    [](double t, double b, double c, double d) {
      t /= d;
      return c * t * t * t * t * t + b;
    }
  },
  { "OutQuint",
    [](double t, double b, double c, double d) {
      t /= d;
      t--;
      return c * (t * t * t * t * t + 1) + b;
    }
  },
  { "InOutQuint",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return c / 2.0 * t * t * t * t * t + b;
      }
      t -= 2;
      return c / 2.0 * (t * t * t * t * t + 2) + b;
    }
  },
  { "InSine",
    [](double t, double b, double c, double d) {
      return -c * cos(t / d * (M_PI / 2.0)) + c + b;
    }
  },
  { "OutSine",
    [](double t, double b, double c, double d) {
      return c * sin(t / d * M_PI / 2.0) + b;
    }
  },
  { "InOutSine",
    [](double t, double b, double c, double d) {
      return -c / 2.0 * (cos(M_PI * t / d) - 1) + b;
    }
  },
  { "InExpo",
    [](double t, double b, double c, double d) {
      return c * pow(2, 10 * (t / d - 1)) + b;
    }
  },
  { "OutExpo",
    [](double t, double b, double c, double d) {
      return c * (-pow(2, -10 * t / d) + 1) + b;
    }
  },
  { "InOutExpo",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return c / 2.0 * pow(2, 10 * (t - 1)) + b;
      }
      t--;
      return c / 2.0 * (-pow(2, -10 * t) + 2) + b;
    }
  },
  { "InCirc",
    [](double t, double b, double c, double d) {
      t /= d;
      return -c * (sqrt(1 - t * t) - 1) + b;
    }
  },
  { "OutCirc",
    [](double t, double b, double c, double d) {
      t /= d;
      t--;
      return c * sqrt(1 - t * t) + b;
    }
  },
  { "InOutCirc",
    [](double t, double b, double c, double d) {
      t /= d / 2.0;
      if (t < 1) {
        return -c / 2.0 * (sqrt(1 - t * t) - 1) + b;
      }
      t -= 2;
      return c / 2 * (sqrt(1 - t * t) + 1) + b;
    }
  }

};

