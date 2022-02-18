#pragma once
/**
*
* @file		CColor.h
* @brief	色クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/18	実装開始
*
*/

/** インクルード部 */

/** 色クラス */
class CColor
{
public:
	/**
	* @enum		EColor
	* @brief	色情報
	*/
	enum class EColor
	{
		White = 0,
		Cyan,
		Magenta,
		Yellow,

		Red,
		Green,
		Blue,

		MaxColor
	};

	CColor operator + (const CColor& addColor)const
	{
		switch (colorType)
		{
		case CColor::EColor::White:
			switch (addColor.colorType)
			{
			case EColor::Cyan:		return CColor(EColor::Cyan);
			case EColor::Magenta:	return CColor(EColor::Magenta);
			case EColor::Yellow:	return CColor(EColor::Yellow);
			}

		case CColor::EColor::Cyan:
			switch (addColor.colorType)
			{
			case EColor::Cyan:		return CColor(EColor::Cyan);
			case EColor::Magenta:	return CColor(EColor::Blue);
			case EColor::Yellow:	return CColor(EColor::Green);
			}
		case CColor::EColor::Magenta:
			switch (addColor.colorType)
			{
			case EColor::Cyan:		return CColor(EColor::Blue);
			case EColor::Magenta:	return CColor(EColor::Magenta);
			case EColor::Yellow:	return CColor(EColor::Red);
			}
		case CColor::EColor::Yellow:
			switch (addColor.colorType)
			{
			case EColor::Cyan:		return CColor(EColor::Green);
			case EColor::Magenta:	return CColor(EColor::Red);
			case EColor::Yellow:	return CColor(EColor::Yellow);
			}
		}
		return CColor(EColor::White);
	}

public:
	CColor() { colorType = EColor::White; }
	CColor(EColor color) { colorType = color; }
	~CColor() {}

	EColor colorType;

private:
};