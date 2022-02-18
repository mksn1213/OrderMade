/**
*
* @file		CSound.cpp
* @brief	�T�E���h����
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Sound/CSound.h>

/** �ÓI�����N���C�u���� */
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")


/** �}�N����` */
namespace
{
#include <System/Sound/SoundData.hpp>
	LPCWSTR g_pszDirSound = L"data/";
	LPCWSTR g_pszDirBGM = L"Sound/";
	LPCWSTR g_pszDirSE = L"Sound/";

	HRESULT CreateMFReader(LPCWSTR mediaFile, COMPTR(IMFSourceReader)& reader, WAVEFORMATEX* wfx, size_t maxwfx);
}

/**
* @brief	�R���X�g���N�^
*/
CSoundManager::CSoundManager()
	: m_pXAudio2(nullptr)
	, m_pMasteringVoice(nullptr)
	, m_pBgm(nullptr)
	, m_pSe(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CSoundManager::~CSoundManager()
{

}


/**
* @brief	����������
*/
HRESULT CSoundManager::Init()
{
	Uninit();	// �O�̂��߉��

	HRESULT hr = S_OK;
	if (!m_pXAudio2) 
	{
		UINT32 flags = 0;
#if defined(_DEBUG)
		//flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		hr = XAudio2Create(&m_pXAudio2, flags);
		if (FAILED(hr)) 
		{
			m_pXAudio2 = nullptr;
		}
		else 
		{
#if defined(_DEBUG)
			XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
			debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
			debug.BreakMask = XAUDIO2_LOG_ERRORS;
			m_pXAudio2->SetDebugConfiguration(&debug, 0);
#endif
			hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
			if (FAILED(hr)) 
			{
				m_pMasteringVoice = nullptr;
				SAFE_RELEASE(m_pXAudio2);
			}
			else 
			{
				hr = MFStartup(MF_VERSION);
				if (FAILED(hr)) 
				{
					SAFE_DESTROYVOICE(m_pMasteringVoice);
					SAFE_RELEASE(m_pXAudio2);
				}
			}
		}
	}
	if (m_pXAudio2) 
	{
		m_pBgm = new SoundStream[MAX_BGM];
		m_pSe = new SoundEffect[MAX_SE];
		WCHAR szPath[_MAX_PATH];
		for (int i = 0; i < MAX_BGM; ++i) 
		{
			lstrcpyW(szPath, g_pszDirSound);
			lstrcatW(szPath, g_pszDirBGM);
			lstrcatW(szPath, g_pszFileBGM[i]);
			if (FAILED(m_pBgm[i].Open(m_pXAudio2, szPath))) 
			{
				::MessageBoxW(nullptr, szPath, L"BGM:error", MB_OK);
			}
		}
		for (int i = 0; i < MAX_SE; ++i) 
		{
			lstrcpyW(szPath, g_pszDirSound);
			lstrcatW(szPath, g_pszDirSE);
			lstrcatW(szPath, g_pszFileSE[i]);
			if (FAILED(m_pSe[i].Open(m_pXAudio2, szPath))) 
			{
				::MessageBoxW(nullptr, szPath, L"SE:error", MB_OK);
			}
		}
	}
	// �}�X�^�[�{�����[���Z�b�g
	SetVolume(0.1f);

	return S_OK;
}


/**
* @brief	�X�V
*/
void CSoundManager::Update()
{
	if (m_pBgm) 
	{
		for (int i = 0; i < MAX_BGM; ++i) 
		{
			m_pBgm[i].Update();
		}
	}
}


/**
* @brief	���
*/
void CSoundManager::Uninit()
{
	if (m_pBgm) 
	{
		for (int i = 0; i < MAX_BGM; ++i) 
		{
			m_pBgm[i].Close();
		}
	}
	if (m_pSe) 
	{
		for (int i = 0; i < MAX_SE; ++i) 
		{
			m_pSe[i].Close();
		}
	}
	MFShutdown();
	SAFE_DELETE_ARRAY(m_pSe);
	SAFE_DELETE_ARRAY(m_pBgm);
	SAFE_DESTROYVOICE(m_pMasteringVoice);
	SAFE_RELEASE(m_pXAudio2);
}


/**
* @brief	BGM�Đ�
* @param	eBGM	BGM�^�C�v
*/
void CSoundManager::Play(EBGM eBGM)
{
	if (!m_pBgm || eBGM < 0 || eBGM >= MAX_BGM) return;
	m_pBgm[eBGM].Play();
}


/**
* @brief	SE�Đ�
* @param	eSE		SE�^�C�v
*/
void CSoundManager::Play(ESE eSE)
{
	if (!m_pSe || eSE < 0 || eSE >= MAX_SE) return;
	m_pSe[eSE].Play();
}


/**
* @brief	BGM�Đ������ǂ���
* @param	eBGM
* @return	bool	true/�Đ��� false/�Đ��Ȃ�
*/
bool CSoundManager::IsPlaying(EBGM eBGM)
{
	if (!m_pBgm || eBGM < 0 || eBGM >= MAX_BGM) return false;
	return m_pBgm[eBGM].IsPlaying();
}


/**
* @brief	BGM�Đ���~
* @param	eBGM	BGM�^�C�v
*/
void CSoundManager::Stop(EBGM eBGM)
{
	if (!m_pBgm || eBGM < 0 || eBGM >= MAX_BGM) return;
	m_pBgm[eBGM].Stop();
}


/**
* @brief	SE�Đ���~
* @param	eSE		SE�^�C�v
*/
void CSoundManager::Stop(ESE eSE)
{
	if (!m_pSe || eSE < 0 || eSE >= MAX_SE) return;
	m_pSe[eSE].Stop();
}


/**
* @brief	�ꎞ��~
*/
void CSoundManager::Pause()
{
	for (int i = 0; i < MAX_SE; ++i)
		m_pSe[i].Pause();
	for (int i = 0; i < MAX_BGM; ++i)
		m_pBgm[i].Pause();
}


/**
* @brief	�Đ��ĊJ
*/
void CSoundManager::Resume()
{
	for (int i = 0; i < MAX_SE; ++i)
		m_pSe[i].Resume();
	for (int i = 0; i < MAX_BGM; ++i)
		m_pBgm[i].Resume();
}


/**
* @brief	�}�X�^�[�{�����[���ݒ�
* @param	fVol	�{�����[���T�C�Y
*/
void CSoundManager::SetVolume(float fVol)
{
	if (m_pMasteringVoice)	m_pMasteringVoice->SetVolume(fVol);
}


/**
* @brief	�}�X�^�[�{�����[���擾
* @return	float	�{�����[���T�C�Y
*/
float CSoundManager::GetVolume()
{
	float fVol = 0.0f;
	if (m_pMasteringVoice)	m_pMasteringVoice->GetVolume(&fVol);
	return fVol;
}


/**
* @brief	BGM�{�����[���ݒ�
* @param	eBGM	BGM�^�C�v
* @param	fVol	�{�����[���T�C�Y
*/
void CSoundManager::SetVolume(EBGM eBGM, float fVol)
{
	if (!m_pBgm || eBGM < 0 || eBGM >= MAX_BGM)		return;
	m_pBgm[eBGM].SetVolume(fVol);
}


/**
* @brief	BGM�{�����[���擾
* @param	eBGM	BGM�^�C�v
* @return	float	�{�����[���T�C�Y
*/
float CSoundManager::GetVolume(EBGM eBGM)
{
	if (!m_pBgm || eBGM < 0 || eBGM >= MAX_BGM)		return 0.0f;
	return m_pBgm[eBGM].GetVolume();
}


/**
* @brief	SE�{�����[���ݒ�
* @param	eSE		SE�^�C�v
* @return	float	�{�����[���T�C�Y
*/void CSoundManager::SetVolume(ESE eSE, float fVol)
{
	if (!m_pSe || eSE < 0 || eSE >= MAX_SE)	return;
	m_pSe[eSE].SetVolume(fVol);
}


/**
* @brief	SE�{�����[���擾
* @param	eSE		SE�^�C�v
* @return	float	�{�����[���T�C�Y
*/
float CSoundManager::GetVolume(ESE eSE)
{
	if (!m_pSe || eSE < 0 || eSE >= MAX_SE) {
		return 0.0f;
	}
	return m_pSe[eSE].GetVolume();
}


/**
* @brief	�R���X�g���N�^
*/
SoundStream::SoundStream()
	: m_pSourceVoice(nullptr)
	, m_reader(nullptr)
	, m_currentStreamBuffer(0)
	, m_endOfStream(false)
	, m_status(SS_STOP)
{
	for (int i = 0; i < MAX_BUFFER_COUNT; ++i) 
		m_buffers[i].resize(32768);
}


/**
* @brief	�f�X�g���N�^
*/
SoundStream::~SoundStream()
{
	SAFE_DESTROYVOICE(m_pSourceVoice);
}


/**
* @brief	BGM�I�[�v��
*/
HRESULT SoundStream::Open(IXAudio2* pXAudio2, LPCWSTR pszPath)
{
	if (!pszPath || !*pszPath)	return E_INVALIDARG;

	HRESULT hr;
	WAVEFORMATEX wfx;
	::ZeroMemory(&wfx, sizeof(wfx));
	hr = CreateMFReader(pszPath, m_reader, &wfx, sizeof(wfx));
	if (FAILED(hr)) {
		return hr;
	}

	hr = pXAudio2->CreateSourceVoice(&m_pSourceVoice, &wfx, XAUDIO2_VOICE_NOPITCH, 1.0f, nullptr);
	return hr;
}


/**
* @brief	�X�V
*/
void SoundStream::Update()
{
	if (m_status != SS_PLAY)	return;
	if (m_endOfStream) 
	{
		Stop();
		Play();
		return;
	}
	if (!m_pSourceVoice) 
	{
		return;
	}
	XAUDIO2_VOICE_STATE state = { 0 };
	m_pSourceVoice->GetState(&state);
	if (state.BuffersQueued >= MAX_BUFFER_COUNT - 1)	return;
	if (!m_reader) return;
	COMPTR(IMFSample) sample;
	DWORD flags = 0;
	HRESULT hr;
	hr = m_reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
	if (FAILED(hr))	return;
	if (flags & MF_SOURCE_READERF_ENDOFSTREAM) 
	{
		m_endOfStream = true;
		return;
	}
	COMPTR(IMFMediaBuffer) mediaBuffer;
	hr = sample->ConvertToContiguousBuffer(&mediaBuffer);
	if (FAILED(hr))	return;
	BYTE* audioData = nullptr;
	DWORD sampleBufferLength = 0;
	hr = mediaBuffer->Lock(&audioData, nullptr, &sampleBufferLength);
	if (FAILED(hr))	return;
	std::vector<BYTE>& buffer = m_buffers[m_currentStreamBuffer];
	m_currentStreamBuffer++;
	m_currentStreamBuffer %= MAX_BUFFER_COUNT;
	buffer.resize(sampleBufferLength);
	memcpy_s(&buffer[0], sampleBufferLength, audioData, sampleBufferLength);
	hr = mediaBuffer->Unlock();
	if (FAILED(hr))	return;
	XAUDIO2_BUFFER buf = { 0 };
	buf.AudioBytes = sampleBufferLength;
	buf.pAudioData = &buffer[0];
	m_pSourceVoice->SubmitSourceBuffer(&buf);
}


/**
* @brief	BGM�N���[�Y
*/
void SoundStream::Close()
{
	Stop();
	if (m_reader)	m_reader->Flush(MF_SOURCE_READER_FIRST_AUDIO_STREAM);
	SAFE_DESTROYVOICE(m_pSourceVoice);
}


/**
* @brief	BGM�Đ�
*/
void SoundStream::Play()
{
	if (m_pSourceVoice && m_status != SS_PLAY) 
	{
		m_pSourceVoice->Start();
		m_status = SS_PLAY;
	}
}


/**
* @brief	BGM��~
*/
void SoundStream::Stop()
{
	if (m_pSourceVoice && m_status != SS_STOP) 
	{
		m_status = SS_STOP;
		m_pSourceVoice->Stop();
		m_pSourceVoice->FlushSourceBuffers();
		if (m_reader) 
		{
			PROPVARIANT var = { 0 };
			var.vt = VT_I8;
			m_reader->SetCurrentPosition(GUID_NULL, var);
		}
		m_endOfStream = false;
	}
}


/**
* @brief	BGM�ꎞ��~
*/
void SoundStream::Pause()
{
	if (m_pSourceVoice && m_status == SS_PLAY) 
	{
		m_status = SS_PAUSE;
		m_pSourceVoice->Stop();
	}
}


/**
* @brief	BGM�Đ��ĊJ
*/
void SoundStream::Resume()
{
	if (m_pSourceVoice && m_status == SS_PAUSE)	Play();
}


/**
* @brief	BGM�Đ����`�F�b�N
*/
bool SoundStream::IsPlaying()
{
	return m_status == SS_PLAY && !m_endOfStream;
}


/**
* @brief	BGM�{�����[���ݒ�
* @param	fVol	�{�����[���T�C�Y
*/
void SoundStream::SetVolume(float fVol)
{
	if (m_pSourceVoice) {
		m_pSourceVoice->SetVolume(fVol);
	}
}


/**
* @brief	BGM�{�����[���擾
* @param	float	�{�����[���T�C�Y
*/
float SoundStream::GetVolume()
{
	float fVol = 0.0f;
	if (m_pSourceVoice)	m_pSourceVoice->GetVolume(&fVol);
	return fVol;
}


/**
* @brief	�R���X�g���N�^
*/
SoundEffect::SoundEffect() 
	: m_bufferLength(0)
{
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		m_pSourceVoice[i] = nullptr;
		m_status[i] = SS_STOP;
	}
}


/**
* @brief	�f�X�g���N�^
*/
SoundEffect::~SoundEffect()
{
	for (int i = 0; i < MAX_DUP; ++i) 
		SAFE_DESTROYVOICE(m_pSourceVoice[i]);
}


/**
* @brief	SE�I�[�v��
*/
HRESULT SoundEffect::Open(IXAudio2* pXAudio2, LPCWSTR pszPath)
{
	if (!pszPath || !*pszPath)
		return E_INVALIDARG;

	HRESULT hr;
	COMPTR(IMFSourceReader) reader;
	WAVEFORMATEX wfx;
	::ZeroMemory(&wfx, sizeof(wfx));
	hr = CreateMFReader(pszPath, reader, &wfx, sizeof(wfx));
	if (FAILED(hr))	return hr;
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		hr = pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &wfx, XAUDIO2_VOICE_NOPITCH, 1.0f, nullptr);
		if (FAILED(hr))	return hr;
	}

	m_bufferLength = 0;
	for (;;) 
	{
		COMPTR(IMFSample) sample;
		DWORD flags = 0;
		hr = reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
		if (FAILED(hr))	return hr;
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)	break;
		COMPTR(IMFMediaBuffer) mediaBuffer;
		hr = sample->ConvertToContiguousBuffer(&mediaBuffer);
		if (FAILED(hr))	return hr;
		BYTE* audioData = nullptr;
		DWORD sampleBufferLength = 0;
		hr = mediaBuffer->Lock(&audioData, nullptr, &sampleBufferLength);
		if (FAILED(hr))	return hr;
		m_buffer.resize(m_bufferLength + sampleBufferLength);
		memcpy_s(&m_buffer[m_bufferLength], sampleBufferLength, audioData, sampleBufferLength);
		m_bufferLength += sampleBufferLength;
		hr = mediaBuffer->Unlock();
		if (FAILED(hr))	return hr;
	}

	reader->Flush(MF_SOURCE_READER_FIRST_AUDIO_STREAM);

	return hr;
}


/**
* @brief	SE�N���[�Y
*/
void SoundEffect::Close()
{
	Stop();
	for (int i = 0; i < MAX_DUP; ++i)
		SAFE_DESTROYVOICE(m_pSourceVoice[i]);
}


/**
* @brief	SE�Đ�
*/
void SoundEffect::Play()
{
	int i;
	for (i = 0; i < MAX_DUP; ++i) 
	{
		if (!m_pSourceVoice[i])		continue;
		if (m_status[i] == SS_STOP)	break;
	}
	if (i >= MAX_DUP) 
	{
		for (i = 0; i < MAX_DUP; ++i) 
		{
			if (!m_pSourceVoice[i])	continue;
			if (m_status[i] == SS_PAUSE) 
			{
				Stop(i);
				break;
			}
		}
		if (i >= MAX_DUP) 
		{
			XAUDIO2_VOICE_STATE state = { 0 };
			for (i = 0; i < MAX_DUP; ++i) 
			{
				if (!m_pSourceVoice[i])			continue;
				m_pSourceVoice[i]->GetState(&state);
				if (state.BuffersQueued > 0)	continue;
				Stop(i);
				break;
			}
		}
		if (i >= MAX_DUP) 
		{
			i = rand() % MAX_DUP;
			if (!m_pSourceVoice[i])	return;
			Stop(i);
		}
	}
	XAUDIO2_BUFFER buf = { 0 };
	buf.AudioBytes = m_bufferLength;
	buf.pAudioData = &m_buffer[0];
	buf.Flags = XAUDIO2_END_OF_STREAM;
	m_pSourceVoice[i]->SubmitSourceBuffer(&buf);
	m_pSourceVoice[i]->Start();
	m_status[i] = SS_PLAY;
}


/**
* @brief	SE��~
*/
void SoundEffect::Stop(int n)
{
	if (n < 0 || n >= MAX_DUP) 
	{
		for (int i = 0; i < MAX_DUP; ++i) 
		{
			if (m_pSourceVoice[i] && m_status[i] != SS_STOP) 
			{
				m_status[i] = SS_STOP;
				m_pSourceVoice[i]->Stop();
				m_pSourceVoice[i]->FlushSourceBuffers();
			}
		}
		return;
	}
	if (m_pSourceVoice[n] && m_status[n] != SS_STOP) 
	{
		m_status[n] = SS_STOP;
		m_pSourceVoice[n]->Stop();
		m_pSourceVoice[n]->FlushSourceBuffers();
	}
}


/**
* @brief	SE�ꎞ��~
*/
void SoundEffect::Pause()
{
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		if (m_pSourceVoice[i] && m_status[i] == SS_PLAY) 
		{
			m_status[i] = SS_PAUSE;
			m_pSourceVoice[i]->Stop();
		}
	}
}


/**
* @brief	SE�ĊJ
*/
void SoundEffect::Resume()
{
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		if (m_pSourceVoice[i] && m_status[i] == SS_PAUSE) 
		{
			m_status[i] = SS_PLAY;
			m_pSourceVoice[i]->Start();
		}
	}
}


/**
* @brief	SE�Đ����`�F�b�N
*/
bool SoundEffect::IsPlaying()
{
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		if (m_pSourceVoice[i] && m_status[i] == SS_PLAY)	return true;
	}
	return false;
}


/**
* @brief	SE�{�����[���ݒ�
* @param	fVol	�{�����[���T�C�Y
*/
void SoundEffect::SetVolume(float fVol)
{
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		if (m_pSourceVoice[i])	m_pSourceVoice[i]->SetVolume(fVol);
	}
}


/**
* @brief	SE�{�����[���T�C�Y�擾
* @return	float	�{�����[���T�C�Y
*/
float SoundEffect::GetVolume()
{
	float fVol = 0.0f;
	for (int i = 0; i < MAX_DUP; ++i) 
	{
		if (m_pSourceVoice[i]) {
			m_pSourceVoice[i]->GetVolume(&fVol);
			break;
		}
	}
	return fVol;
}


//--------------------------------------------------------------------------------------
// Helper for setting up the MF source reader
//--------------------------------------------------------------------------------------
namespace {
	HRESULT CreateMFReader(LPCWSTR mediaFile, COMPTR(IMFSourceReader)& reader, WAVEFORMATEX* wfx, size_t maxwfx)
	{
		if (!mediaFile || !wfx) {
			return E_INVALIDARG;
		}

		HRESULT hr;
		COMPTR(IMFAttributes) attr;
		hr = MFCreateAttributes(&attr, 1);
		if (FAILED(hr))
			return hr;
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
		hr = attr->SetUINT32(MF_LOW_LATENCY, TRUE);
		if (FAILED(hr))
			return hr;
#endif

		hr = MFCreateSourceReaderFromURL(mediaFile, attr, &reader);
		if (FAILED(hr))
			return hr;

		//
		// Make the output from Media Foundation PCM so XAudio2 can consume it
		//
		COMPTR(IMFMediaType) mediaType;
		hr = MFCreateMediaType(&mediaType);
		if (FAILED(hr))
			return hr;

		hr = mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		if (FAILED(hr))
			return hr;

		hr = mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		if (FAILED(hr))
			return hr;

		hr = reader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);
		if (FAILED(hr))
			return hr;

		//
		// Get the wave format
		//
		COMPTR(IMFMediaType) outputMediaType;
		hr = reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &outputMediaType);
		if (FAILED(hr))
			return hr;

		UINT32 waveFormatSize = 0;
		WAVEFORMATEX* waveFormat = nullptr;
		hr = MFCreateWaveFormatExFromMFMediaType(outputMediaType, &waveFormat, &waveFormatSize);
		if (FAILED(hr))
			return hr;

		memcpy_s(wfx, maxwfx, waveFormat, waveFormatSize);
		CoTaskMemFree(waveFormat);

		return S_OK;
	}
};