#pragma once
/**
*
* @file		CSVLoader.h
* @brief	CSVファイル読み込み
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
*
*/

/** インクルード部 */
#include <vector>
class COrderData;

std::vector<std::vector<int>>	LoadIntDataFromCSV(const std::string& fileName, int ignoreLine = 0, int column = 0);
std::vector<int>				SplitConvertInt(std::string str, char del, int column = 0);

std::vector<std::string>		LoadStrDataFromCSV(const std::string& fileName, int ignoreLine = 0, int column = 0);
std::vector<std::string>		Split(std::string str, char del, int column = 0);
std::vector<std::vector<std::string>> LoadObjectDataFromCSV(const std::string& fileName, int ignoreLine = 0, int column = 0);
void		LoadOrderDataFromCSV(const std::string& fileName, int ignoreLine = 0, int column = 0);
COrderData	ConvertToOrderData(std::vector<std::string> data);