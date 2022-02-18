#pragma once
/**
*
* @file		CSound.h
* @brief	�T�E���h
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <System/Sound/SoundData.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <objbase.h>
#include <vector>
#include <mmreg.h>
#include <comip.h>
#include <comdef.h>
#include <xaudio2.h>
#include <initguid.h>
#include <mfidl.h>
#include <mfapi.h>
#include <mfreadwrite.h>

/** �}�N����` */
#define SOUND_MANAGER	(CSoundManager::GetInstance())

#ifdef COMPTR
#undef COMPTR
#endif
#define COMPTR(type) _com_ptr_t<_com_IIID<type,&__uuidof(type)>>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){x->Release();x=nullptr;}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){delete[]x;x=nullptr;}
#endif
#ifndef SAFE_DESTROYVOICE
#define SAFE_DESTROYVOICE(x)	if(x){x->DestroyVoice();x=nullptr;}
#endif
#define MAX_BUFFER_COUNT		3	// �X�g���[���Đ��p�o�b�t�@��
#define MAX_DUP					16	// �ő命�d�Đ���

/**
* @enum		ESoundStatus
* @brief	�T�E���h�X�e�[�g
*/
enum ESoundStatus
{
	SS_STOP = 0,
	SS_PLAY,
	SS_PAUSE,

	MAX_SOUND_STATUS
};

/** BGM�N���X */
struct SoundStream
{
private:
	IXAudio2SourceVoice*	m_pSourceVoice;
	COMPTR(IMFSourceReader)	m_reader;
	DWORD					m_currentStreamBuffer;
	std::vector<BYTE>		m_buffers[MAX_BUFFER_COUNT];
	bool					m_endOfStream;
	ESoundStatus			m_status;

public:
	SoundStream();
	virtual ~SoundStream();
	HRESULT Open(IXAudio2* pXAudio2, LPCWSTR pszPath);
	void Update();
	void Close();
	void Play();
	void Stop();
	void Pause();
	void Resume();
	bool IsPlaying();
	void SetVolume(float fVol);
	float GetVolume();
};

/** SE�N���X */
struct SoundEffect
{
public:
	IXAudio2SourceVoice*	m_pSourceVoice[MAX_DUP];
	ESoundStatus			m_status[MAX_DUP];
	std::vector<BYTE>		m_buffer;
	DWORD					m_bufferLength;

public:
	SoundEffect();
	virtual ~SoundEffect();
	HRESULT Open(IXAudio2* pXAudio2, LPCWSTR pszPath);
	void Close();
	void Play();
	void Stop(int n = -1);
	void Pause();
	void Resume();
	bool IsPlaying();
	void SetVolume(float fVol);
	float GetVolume();
};

/** �T�E���h�Ǘ��N���X */
class CSoundManager final : public Singleton<CSoundManager>
{
public:
	CSoundManager();
	virtual ~CSoundManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Play(EBGM eBGM);
	void	Play(ESE eSE);
	bool	IsPlaying(EBGM eBGM);
	void	Stop(EBGM eBGM);
	void	Stop(ESE eSE);
	void	Pause();
	void	Resume();
	void	SetVolume(float fVol);
	void	SetVolume(EBGM eBGM, float fVol);
	void	SetVolume(ESE eSE, float fVol);
	float	GetVolume();
	float	GetVolume(EBGM eBGM);
	float	GetVolume(ESE eSE);

private:
	IXAudio2*				m_pXAudio2;
	IXAudio2MasteringVoice*	m_pMasteringVoice;
	SoundStream*			m_pBgm;
	SoundEffect*			m_pSe;
};