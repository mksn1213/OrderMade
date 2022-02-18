/**
*
* @file		CSVLoader.cpp
* @brief	CSV�t�@�C���ǂݍ��ݎ���
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	�����J�n
* @date		2021/12/08	int�^�f�[�^�̓ǂݍ��ݏ����쐬
*
*/

/** �C���N���[�h�� */
#include <System/Utility/CSVLoader.h>
#include <fstream>
#include <string>
#include <Component/Game/Order/COrderData.h>
#include <Component/Game/Order/COrderManager.h>

/**
* @brief	csv�t�@�C������f�[�^�ǂݍ���
* @param	fileName	�ǂݍ��ރt�@�C����
* @param	ignoreLine	�ǂݍ��܂Ȃ��s��
* @param	column		�ǂݍ��܂Ȃ���
* @return	std::vector<std::vector<int>>	�t�B�[���h�̃f�[�^�z��
*/
std::vector<std::vector<int>> LoadIntDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// �ǂݎ���p
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// �ǂݍ��ݎ��s
		// TODO : �G���[�����쐬����
	}

	std::string lineBuffer;
	// ignoreLine���A��ǂ݂���
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::vector<int>> data;
	// �ǂݍ��݃f�[�^�𓮓I�z��Ɋi�[
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<int> temp = SplitConvertInt(lineBuffer, ',', column);
		data.push_back(temp);
	}
	return data;
}


/**
* @brief	��������int�^�ɕϊ�
* @param	fileName	�������镶����
* @param	del			��؂蕶��
* @param	column		�ǂݍ��܂Ȃ���
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
* @brief	csv�t�@�C������f�[�^�ǂݍ���
* @param	fileName	�ǂݍ��ރt�@�C����
* @param	ignoreLine	�ǂݍ��܂Ȃ��s��( �w�b�_�[�p )
* @param	column		�ǂݍ��܂Ȃ���( ���ڗp )
* @return	std::string	�ǂݍ��񂾕�����f�[�^
*/
std::vector<std::string> LoadStrDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// �ǂݎ���p
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// �ǂݍ��ݎ��s
		// TODO : �G���[�����쐬����
	}

	std::string lineBuffer;
	// ignoreLine���A��ǂ݂���
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::string> data;
	// �ǂݍ��݃f�[�^�𓮓I�z��Ɋi�[
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<std::string> temp = Split(lineBuffer, ',', column);
		data.insert(data.end(), temp.begin(), temp.end());
	}
	return data;
}


/**
* @brief	�����f�[�^�𕪊�����
* @param	str			�������镶����
* @param	del			��؂蕶��
* @param	column		�ǂݍ��܂Ȃ���
* @return	std::vecter<std::string>	������̕����z��
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
* @brief	csv�t�@�C�����璍���f�[�^�ǂݍ���
* @param	fileName	�ǂݍ��ރt�@�C����
* @param	ignoreLine	�ǂݍ��܂Ȃ��s��( �w�b�_�[�p )
* @param	column		�ǂݍ��܂Ȃ���( ���ڗp )
*/
void LoadOrderDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// �ǂݎ���p
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// �ǂݍ��ݎ��s
		// TODO : �G���[����
	}

	std::string lineBuffer;
	// ignoreLine���A��ǂ݂���
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())break;
	}

	// �ǂݍ��݃f�[�^�����X�g�Ɋi�[
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)break;
		std::vector<std::string> data;
		data = Split(lineBuffer, ',');
		// �����f�[�^�ɕϊ����ă��X�g�ɒǉ�
		COrderData orderData = ConvertToOrderData(data);
		ORDER_MANAGER->AddOrderData(orderData);
	}
}


/**
* @brief	�Q�[���I�u�W�F�N�g�f�[�^�ǂݍ���
* @param	fileName	�ǂݍ��ރt�@�C����
* @param	ignoreLine	�ǂݍ��܂Ȃ��s��
* @param	column		�ǂݍ��܂Ȃ���
* @return	std::vector<std::vector<string>>	�ǂݍ��񂾃Q�[���I�u�W�F�N�g�f�[�^
*/
std::vector<std::vector<std::string>> LoadObjectDataFromCSV(const std::string& fileName, int ignoreLine, int column)
{
	std::ifstream file;
	// �ǂݎ���p
	file.open(fileName, std::ios::in);
	if (!file)
	{
		// �ǂݍ��ݎ��s
		// TODO : �G���[�����쐬����
		std::vector<std::vector<std::string>> d;
		return d;
	}

	std::string lineBuffer;
	// ignoreLine���A��ǂ݂���
	for (int line = 0; line < ignoreLine; ++line)
	{
		std::getline(file, lineBuffer);
		if (file.eof())	break;
	}

	std::vector<std::vector<std::string>> data;
	// �ǂݍ��݃f�[�^���i�[
	while (std::getline(file, lineBuffer))
	{
		if (lineBuffer.size() == 0)	break;
		std::vector<std::string> temp = Split(lineBuffer, ',');
		data.push_back(temp);
	}

	return data;
}


/**
* @brief	�����f�[�^�ɕϊ�
* @param	data		�ϊ�����f�[�^
* @return	COrderData	�ϊ����������f�[�^
*/
COrderData	ConvertToOrderData(std::vector<std::string> data)
{
	bool need;
	EObjectType type;
	CColor::EColor color;

	// ���A���̗L��
	if (std::stoi(data.at(0)) == 0)	need = false;
	else							need = true;

	// ���
	std::string typeData = data.at(1);
	if		(typeData == "F1")	type = EObjectType::Flower;
	else if (typeData == "F2")	type = EObjectType::Flower;
	else if (typeData == "F3")	type = EObjectType::Flower;
	else if (typeData == "F4")	type = EObjectType::Flower;
	else if (typeData == "S1")	type = EObjectType::Sprout;
	else if (typeData == "S2")	type = EObjectType::Sprout;
	else if (typeData == "S3")	type = EObjectType::Sprout;
	else if (typeData == "S4")	type = EObjectType::Sprout;

	// �F
	std::string colorData = data.at(2);
	if		(colorData == "W")	color = CColor::EColor::White;
	else if (colorData == "C")	color = CColor::EColor::Cyan;
	else if (colorData == "M")	color = CColor::EColor::Magenta;
	else if (colorData == "Y")	color = CColor::EColor::Yellow;
	else if (colorData == "R")	color = CColor::EColor::Red;
	else if (colorData == "G")	color = CColor::EColor::Blue;
	else if (colorData == "B")	color = CColor::EColor::Green;

	// �X�R�A
	int nScoreData = atoi(data.at(3).c_str());

	// �f�[�^�̍쐬
	COrderData orderData(need, type, color, nScoreData);
	return orderData;
}