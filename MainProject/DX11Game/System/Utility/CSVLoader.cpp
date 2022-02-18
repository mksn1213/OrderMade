/**
*
* @file		CSVLoader.cpp
* @brief	CSVファイル読み込み実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
* @date		2021/12/08	int型データの読み込み処理作成
*
*/

/** インクルード部 */
#include <System/Utility/CSVLoader.h>
#include <fstream>
#include <string>
#include <Component/Game/Order/COrderData.h>
#include <Component/Game/Order/COrderManager.h>

/**
* @brief	csvファイルからデータ読み込み
* @param	fileName	読み込むファイル名
* @param	ignoreLine	読み込まない行数
* @param	column		読み込まない列数
* @return	std::vector<std::vector<int>>	フィールドのデータ配列
*/
std::vector<std::vector<int>> LoadIntDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// 読み取り専用
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// 読み込み失敗
		// TODO : エラー処理作成する
	}

	std::string lineBuffer;
	// ignoreLine分、空読みする
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::vector<int>> data;
	// 読み込みデータを動的配列に格納
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<int> temp = SplitConvertInt(lineBuffer, ',', column);
		data.push_back(temp);
	}
	return data;
}


/**
* @brief	分割してint型に変換
* @param	fileName	分割する文字列
* @param	del			区切り文字
* @param	column		読み込まない列数
* @return	std::vector<int>
*/
std::vector<int> SplitConvertInt(std::string str, char del, int column)
{
	int first = 0;
	int last = str.find_first_of(del);
	int num = 0;
	std::vector<int> result;
	while (first < str.size())
	{
		std::string substr(str, first, last - first);
		if (num >= column)
			result.push_back(atoi(substr.c_str()));
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos)
			last = str.size();
		num++;
	}
	return result;
}


/**
* @brief	csvファイルからデータ読み込み
* @param	fileName	読み込むファイル名
* @param	ignoreLine	読み込まない行数( ヘッダー用 )
* @param	column		読み込まない列数( 項目用 )
* @return	std::string	読み込んだ文字列データ
*/
std::vector<std::string> LoadStrDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// 読み取り専用
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// 読み込み失敗
		// TODO : エラー処理作成する
	}

	std::string lineBuffer;
	// ignoreLine分、空読みする
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::string> data;
	// 読み込みデータを動的配列に格納
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<std::string> temp = Split(lineBuffer, ',', column);
		data.insert(data.end(), temp.begin(), temp.end());
	}
	return data;
}


/**
* @brief	文字データを分割する
* @param	str			分割する文字列
* @param	del			区切り文字
* @param	column		読み込まない列数
* @return	std::vecter<std::string>	分割後の文字配列
*/
std::vector<std::string> Split(std::string str, char del, int column)
{
	int first = 0;
	int last = str.find_first_of(del);
	int num = 0;
	std::vector<std::string> result;
	while (first < str.size())
	{
		std::string substr(str, first, last - first);
		if (num >= column)
			result.push_back(substr);
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos)
			last = str.size();
		num++;
	}
	return result;
}


/**
* @brief	csvファイルから注文データ読み込み
* @param	fileName	読み込むファイル名
* @param	ignoreLine	読み込まない行数( ヘッダー用 )
* @param	column		読み込まない列数( 項目用 )
*/
void LoadOrderDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// 読み取り専用
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// 読み込み失敗
		// TODO : エラー処理
	}

	std::string lineBuffer;
	// ignoreLine分、空読みする
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())break;
	}

	// 読み込みデータをリストに格納
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)break;
		std::vector<std::string> data;
		data = Split(lineBuffer, ',');
		// 注文データに変換してリストに追加
		COrderData orderData = ConvertToOrderData(data);
		ORDER_MANAGER->AddOrderData(orderData);
	}
}


/**
* @brief	ゲームオブジェクトデータ読み込み
* @param	fileName	読み込むファイル名
* @param	ignoreLine	読み込まない行数
* @param	column		読み込まない列数
* @return	std::vector<std::vector<string>>	読み込んだゲームオブジェクトデータ
*/
std::vector<std::vector<std::string>> LoadObjectDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// 読み取り専用
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// 読み込み失敗
		// TODO : エラー処理作成する
		std::vector<std::vector<std::string>> d;
		return d;
	}

	std::string lineBuffer;
	// ignoreLine分、空読みする
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::vector<std::string>> data;
	// 読み込みデータを格納
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<std::string> temp = Split(lineBuffer, ',');
		data.push_back(temp);
	}

	return data;
}


/**
* @brief	注文データに変換
* @param	data		変換するデータ
* @return	COrderData	変換した注文データ
*/
COrderData	ConvertToOrderData(std::vector<std::string> data)
{
	bool need;
	EObjectType type;
	CColor::EColor color;

	// 鉢植えの有無
	if (std::stoi(data.at(0)) == 0)	need = false;
	else							need = true;

	// 種類
	std::string typeData = data.at(1);
	if		(typeData == "F1")	type = EObjectType::Flower;
	else if (typeData == "F2")	type = EObjectType::Flower;
	else if (typeData == "F3")	type = EObjectType::Flower;
	else if (typeData == "F4")	type = EObjectType::Flower;
	else if (typeData == "S1")	type = EObjectType::Sprout;
	else if (typeData == "S2")	type = EObjectType::Sprout;
	else if (typeData == "S3")	type = EObjectType::Sprout;
	else if (typeData == "S4")	type = EObjectType::Sprout;

	// 色
	std::string colorData = data.at(2);
	if		(colorData == "W")	color = CColor::EColor::White;
	else if (colorData == "C")	color = CColor::EColor::Cyan;
	else if (colorData == "M")	color = CColor::EColor::Magenta;
	else if (colorData == "Y")	color = CColor::EColor::Yellow;
	else if (colorData == "R")	color = CColor::EColor::Red;
	else if (colorData == "G")	color = CColor::EColor::Blue;
	else if (colorData == "B")	color = CColor::EColor::Green;

	// スコア
	int nScoreData = atoi(data.at(3).c_str());

	// データの作成
	COrderData orderData(need, type, color, nScoreData);
	return orderData;
}